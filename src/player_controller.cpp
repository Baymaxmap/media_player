#include "player_controller.h"

PlayerMediaController::PlayerMediaController() : mIsPlaying(false){}

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
    if(!mIsPlaying){
        Mix_Music* music = Mix_LoadMUS(filePath.c_str());
        if(!music){
            std::cout << "Can't load music: " << Mix_GetError() << std::endl;
            Mix_CloseAudio();
            SDL_Quit();
            return ;
        }

        // Start play music
        if(Mix_PlayMusic(music, -1) == -1){
            std::cout << "Can't play music: " << Mix_GetError() << std::endl;
        }
        mIsPlaying = 1;
        return;
    }
    else{
        std::cout<<"Music is already playing.\n";
        return;
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