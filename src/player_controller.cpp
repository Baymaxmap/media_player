#include "player_controller.h"
PlayerMediaController* PlayerMediaController::sControllerInstance = nullptr;

PlayerMediaController::PlayerMediaController() : mIsPlaying(false), mTimePaused(0), mVolume(50){
    mMusic = nullptr;
    sControllerInstance = this;
}

PlayerMediaController::~PlayerMediaController() {
    if (mMusic) {
        Mix_FreeMusic(mMusic);
        mMusic = nullptr;
    }
    Mix_CloseAudio();
    SDL_Quit();
}


//initiaize the SDL
void PlayerMediaController::init(){
    if(SDL_Init(SDL_INIT_AUDIO) < 0){
        std::cout << "SDL can't init: " << SDL_GetError() << std::endl;
        return;
    }

    // Mixer init
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2,2048) < 0){
        std::cout << "Mixer can't init: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return;
    }
}
//*********************************** MANAGE PLAYING MUSIC ***********************************/
//play file media
void PlayerMediaController::play(std::string filePath){
    mMusic = Mix_LoadMUS(filePath.c_str());
    if(!mMusic){
        std::cout << "Can't load music: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return ;
    }

    // Start play music
    if(Mix_PlayMusic(mMusic, 1) == -1){
        std::cout << "Can't play music: " << Mix_GetError() << std::endl;
    }
    else{
        mStartTime = std::chrono::steady_clock::now(); // Start timing
        mIsPlaying = true;
        mTimePaused = 0;
        std::shared_ptr<MediaFile> mediaFile = std::make_shared<MediaFile>(filePath);
        mDuration = std::stoi(mediaFile->getDuration());
        std::cout<<"Playing "<<filePath<<std::endl;
    }
}

//pause the media file
void PlayerMediaController::pause(){
    if(mIsPlaying){
        Mix_PauseMusic();
        mIsPlaying = false;

        //store the time that is paused
        mTimePaused += std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - mStartTime).count();
        std::cout << "Music is paused.\n";
        return;
    }
    else{
        std::cout<<"Music is already paused.\n";
    }
}

void PlayerMediaController::resume(){
    if (!mIsPlaying) {
        Mix_ResumeMusic();
        mIsPlaying = true;
        mStartTime = std::chrono::steady_clock::now();
        std::cout << "Music resumed.\n";
    } else {
        std::cout << "Music is already playing.\n";
    }
}

void PlayerMediaController::end(){
    Mix_HookMusicFinished(nullptr);
    mIsPlaying = false;
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
    if (mMusic != nullptr) {
        Mix_FreeMusic(mMusic);
        mMusic = nullptr;
    }
}

//play next track in playlist
void PlayerMediaController::nextTrackInPlaylist(){
    ++mCurrentTrack;
    if(mCurrentTrack==mListToPlay.end()){
        mCurrentTrack = mListToPlay.begin();
    }
    play(*mCurrentTrack);
}

//play previous track in playlist
void PlayerMediaController::previousTrackInPlaylist(){
    if(mCurrentTrack == mListToPlay.begin()){
        mCurrentTrack = mListToPlay.end();
    }
    --mCurrentTrack;
    play(*mCurrentTrack);
}

//*********************************** MANAGE CHANGE VOLUME ***********************************/
//canonical: line mode => terminal just handles data only when user press enter
//echo: enable display character input on terminal

void PlayerMediaController::setNonCanonicalMode(bool enable){
    tcgetattr(STDIN_FILENO, &mTty); // get and store the current terminal configuration

    if (enable) {
        mTty.c_lflag &= ~(ICANON | ECHO); // turn off canonical and echo
    } else {
        mTty.c_lflag |= (ICANON | ECHO); // turn on canonical and echo
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &mTty); // update configuration
}

//increase volume
void PlayerMediaController::increaseVolume(){
    mVolume += 10;
    if(mVolume<0) mVolume = 0;
    if(mVolume>128) mVolume = 128;
    Mix_VolumeMusic(mVolume);
}

//decrease volume
void PlayerMediaController::decreaseVolume(){
    mVolume -= 10;
    if(mVolume<0) mVolume = 0;
    if(mVolume>128) mVolume = 128;
    Mix_VolumeMusic(mVolume);
}

//*********************************** MANAGE AUTO PLAY NEXT WHEN A SONG ENDED ***********************************/
//function when end a media file
void PlayerMediaController::musicEndedPlaylistStatic(){

    // call static function to call non-static function
    if (sControllerInstance) {
        sControllerInstance->musicEndedPlaylist();
    }
}

void PlayerMediaController::musicEndedPlaylist(){
    std::cout << "\nTrack finished playing." << std::endl;

    // Move to the next track
    mCurrentTrack++;
    if (mCurrentTrack == mListToPlay.end()) {
        mCurrentTrack = mListToPlay.begin(); // Loop back to the start of the playlist
    }

    // Play the next track
    play(*mCurrentTrack);
    mIsPlaying = true;
}

//*********************************** MANAGE DISPLAY CURRENT TIME ***********************************/
//get current play time
int PlayerMediaController::getCurrentPlayTime(){
    if(mIsPlaying){
        auto currentTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - mStartTime);
        return (static_cast<int>(duration.count()) + mTimePaused);
    }
    return mTimePaused;
}

// format time in mm:ss format
std::string PlayerMediaController::formatTime(int seconds){
    int minutes = seconds / 60;
    int secs = seconds % 60;
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, secs);
    return std::string(buffer);
}

// show time in real time
void PlayerMediaController::showTimeInRealTime(){
    while (mIsPlaying) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
        if (mIsPlaying) { // Only display if still playing
            int playTime = getCurrentPlayTime();
            std::cout   << "\rCurrent play time: " << formatTime(playTime) << "/" <<formatTime(mDuration)
                        << "\t||\tEnter your option: "<<std::flush; // Overwrite the previous output
        }
    }
    if(!mIsPlaying){
        int playTime = getCurrentPlayTime();
        std::cout   << "\rCurrent play time: " << formatTime(playTime) << "/" <<formatTime(mDuration)
                    << "\t||\tEnter your option: "<<std::flush; // Overwrite the previous output
    }
}

//*********************************** MANAGE RUN PLAYLIST AND RUN ALL MEDIA FILES ***********************************/
//implement run playlist
void PlayerMediaController::runPlaylist(std::shared_ptr<Playlist> playlist){
    init();
    mIsPlaying =false;
    //call static function to call a non static function
    Mix_HookMusicFinished(musicEndedPlaylistStatic);

    mListToPlay = playlist->getPathAllFiles();
    mCurrentTrack = mListToPlay.begin();

    while(1){
        setNonCanonicalMode(0); //turn on canonical and echo
        char i;
        ViewMedia::showOptionPlayMusic();
        std::cin>>i;
        switch(i){
            case '1':{
                ViewMedia::clearScreen();
                if(!mIsPlaying){
                    play(*mCurrentTrack);
                    std::thread playMusic(&PlayerMediaController::showTimeInRealTime, this);
                    playMusic.detach();
                }
                else{
                    std::cout<<"Music is already playing!\n";
                }
                break;
            }
            case '2':{
                ViewMedia::clearScreen();
                if(mIsPlaying){
                    pause();
                }
                else{
                    std::cout<<"Music is not playing!\n";
                }
                break;
            }
            case '3':{
                ViewMedia::clearScreen();
                if(!mIsPlaying){
                    resume();
                    std::thread playMusic(&PlayerMediaController::showTimeInRealTime, this);
                    playMusic.detach();
                }
                else{
                    std::cout<<"Music is already playing!\n";
                }
                break;
            }
            case '4':
            {
                ViewMedia::clearScreen();
                nextTrackInPlaylist();
                std::thread playMusic(&PlayerMediaController::showTimeInRealTime, this);
                playMusic.detach();
                break;
            }
            case '5':
            {
                ViewMedia::clearScreen();
                previousTrackInPlaylist();
                std::thread playMusic(&PlayerMediaController::showTimeInRealTime, this);
                playMusic.detach();
                break;
            }
            case '6':
            {
                ViewMedia::clearScreen();
                setNonCanonicalMode(1);
                std::cout << "1. (+) volume\n";
                std::cout << "2. (-) volume\n";
                std::cout << "3. Back\n";
                while(1){
                    char inputVolume;
                    std::cin>>inputVolume;
                    switch(inputVolume){
                        case '1': {increaseVolume(); break;}
                        case '2': {decreaseVolume(); break;}
                        case '3': {
                            ViewMedia::clearScreen();
                            break;
                        }
                        default: {ViewMedia::showErrorInput(); break;}
                    }
                    if(inputVolume == '3'){break;}
                }
                break;
            }
            case '7':
            {
                std::cout<<"Stop playing music!!!\n";
                end();
                break;
            }
            default:{ViewMedia::showErrorInput(); break;}
        }
        if(i=='7'){
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
            ViewMedia::clearScreen();
            break;
        }
    }
}


//implement running all media files
void PlayerMediaController::runListMediaFiles(std::list<std::shared_ptr<MediaFile>> listMediaFiles){
    mIsPlaying = false;
    init();
    //call static function to call a non static function
    Mix_HookMusicFinished(musicEndedPlaylistStatic);

    std::list<std::string> tempList;
    for(auto& it : listMediaFiles){
        tempList.push_back(it->getPathMedia());
    }
    mListToPlay = tempList;
    mCurrentTrack = mListToPlay.begin();

    while(1){
        setNonCanonicalMode(0); //turn on canonical and echo
        char i;
        ViewMedia::showOptionPlayMusic();
        std::cin>>i;
        switch(i){
            case '1':{
                ViewMedia::clearScreen();
                if(!mIsPlaying){
                    play(*mCurrentTrack);

                    //create a thread to display real time
                    std::thread playMusic(&PlayerMediaController::showTimeInRealTime, this);
                    playMusic.detach();
                }
                else{
                    std::cout<<"Music is already playing!\n";
                }
                break;
            }
            case '2':{
                ViewMedia::clearScreen();
                if(mIsPlaying){
                    pause();
                }
                else{
                    std::cout<<"Music is not playing!\n";
                }
                break;
            }
            case '3':{
                ViewMedia::clearScreen();
                if(!mIsPlaying){
                    resume();
                    std::thread playMusic(&PlayerMediaController::showTimeInRealTime, this);
                    playMusic.detach();
                }
                else{
                    std::cout<<"Music is already playing!\n";
                }
                break;
            }
            case '4':
            {
                ViewMedia::clearScreen();
                nextTrackInPlaylist();
                std::thread playMusic(&PlayerMediaController::showTimeInRealTime, this);
                playMusic.detach();
                break;
            }
            case '5':
            {
                ViewMedia::clearScreen();
                previousTrackInPlaylist();
                std::thread playMusic(&PlayerMediaController::showTimeInRealTime, this);
                playMusic.detach();
                break;
            }
            case '6':
            {
                ViewMedia::clearScreen();
                setNonCanonicalMode(1);
                std::cout << "1. (+) volume\n";
                std::cout << "2. (-) volume\n";
                std::cout << "3. Back\n";
                while(1){
                    char inputVolume;
                    std::cin>>inputVolume;
                    switch(inputVolume){
                        case '1': {increaseVolume(); break;}
                        case '2': {decreaseVolume(); break;}
                        case '3': {
                            ViewMedia::clearScreen();
                            break;
                        }
                        default: {ViewMedia::showErrorInput(); break;}
                    }
                    if(inputVolume == '3'){break;}
                }
                break;
            }
            case '7':
            {
                std::cout<<"Stop playing music!!!\n";
                end();
                break;
            }
            default:{ViewMedia::showErrorInput(); break;}
        }
        if(i=='7'){
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
            ViewMedia::clearScreen();
            break;
        }
    }
}