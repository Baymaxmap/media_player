#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <filesystem>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "playlist.h"

class PlayerMediaController{
    static PlayerMediaController* sControllerInstance;

    bool mIsPlaying;
    Mix_Music* mMusic;
//mCurrenTrack is used for handling playing Playlist
    std::list<std::string>::iterator mCurrentTrackPlaylist;
    std::list<std::string> mPlaylist;
public:
    PlayerMediaController();
    ~PlayerMediaController();
    void init();
    void play(std::string);
    void pause();
    void resume();
    void end();

    static void musicEndedPlaylistStatic();
    void musicEndedPlaylist();
    void nextTrackInPlaylist();
    void previousTrackInPlaylist();
    void runPlaylist(std::shared_ptr<Playlist>);
};

#endif