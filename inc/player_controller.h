#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class PlayerMediaController{
    bool mIsPlaying;
public:
    PlayerMediaController();
    void init();
    void play(std::string);
    void pause();
    void resume();
    void end();
};


#endif