#include "player_controller.h"
PlayerMediaController* PlayerMediaController::sControllerInstance = nullptr;

PlayerMediaController::PlayerMediaController() : mIsPlaying(false){
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
        std::cout<<"Playing "<<filePath<<std::endl;
    }

}

//pause the media file
void PlayerMediaController::pause(){
    if(mIsPlaying){
        Mix_PauseMusic();
        mIsPlaying = false;
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
        std::cout << "Music resumed.\n";
    } else {
        std::cout << "Music is already playing.\n";
    }
}

void PlayerMediaController::end(){
    Mix_CloseAudio();
    SDL_Quit();
}


//function when end a media file
void PlayerMediaController::musicEndedPlaylistStatic(){
    std::cout << "\nTrack finished playing." << std::endl;

    // call static function to call non-static function
    if (sControllerInstance) {
        sControllerInstance->musicEndedPlaylist();
    }
}

void PlayerMediaController::musicEndedPlaylist(){
    std::cout << "\nTrack finished playing." << std::endl;

    // Move to the next track
    mCurrentTrackPlaylist++;
    if (mCurrentTrackPlaylist == mPlaylist.end()) {
        mCurrentTrackPlaylist = mPlaylist.begin(); // Loop back to the start of the playlist
    }

    // Play the next track
    play(*mCurrentTrackPlaylist);
    mIsPlaying = true;
}

//implement run playlist
void PlayerMediaController::runPlaylist(std::shared_ptr<Playlist> playlist){
    init();
    
    //call static function to call a non static function
    Mix_HookMusicFinished(musicEndedPlaylistStatic);

    mPlaylist = playlist->getPathAllFiles();
    mCurrentTrackPlaylist = mPlaylist.begin();

    while(1){
        char i;
        std::cout<<"press 1 to play playlist thanh ngu\n";
        std::cout<<"press 2 to pause\n";
        std::cout<<"press 3 to resume\n";
        std::cout<<"press 4 Next Track\n";
        std::cout<<"press 5 Previous Track\n";
        std::cout<<"press 6 Exit\n";
        std::cin>>i;
        switch(i){
            case '1':{
                if(!mIsPlaying){
                    play(*mCurrentTrackPlaylist);
                    mIsPlaying = true;
                }
                else{
                    std::cout<<"Music is already playing!\n";
                }
                break;
            }
            case '2':{
                if(mIsPlaying){
                    pause();
                }
                else{
                    std::cout<<"Music is not playing!\n";
                }
                break;
            }
            case '3':{
                if(!mIsPlaying){
                    resume();
                }
                else{
                    std::cout<<"Music is already playing!\n";
                }
                break;
            }
            case '4':
            {
                nextTrackInPlaylist();
                break;
            }
            case '5':
            {
                previousTrackInPlaylist();
                break;
            }
            case '6':
            {
                std::cout<<"end program\n";
                break;
            }
            default:{std::cout<<"not valid input\n"; break;}
        }
        if(i=='6'){
            break;
        }
    }
}

//play next track in playlist
void PlayerMediaController::nextTrackInPlaylist(){
    ++mCurrentTrackPlaylist;
    if(mCurrentTrackPlaylist==mPlaylist.end()){
        mCurrentTrackPlaylist = mPlaylist.begin();
    }
    play(*mCurrentTrackPlaylist);
}

//play previous track in playlist
void PlayerMediaController::previousTrackInPlaylist(){
    if(mCurrentTrackPlaylist == mPlaylist.begin()){
        mCurrentTrackPlaylist = mPlaylist.end();
    }
    --mCurrentTrackPlaylist;
    play(*mCurrentTrackPlaylist);
}