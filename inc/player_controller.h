#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <filesystem>
#include <memory>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "playlist.h"
#include "media.h"

class PlayerMediaController{
    static PlayerMediaController* sControllerInstance;

    bool mIsPlaying;
    Mix_Music* mMusic;
//handling playing Playlist
    std::list<std::string>::iterator mCurrentTrack;
    std::list<std::string> mListToPlay;

//handling display current time when playing music
    int mTimePaused;
    int mDuration;
    std::chrono::time_point<std::chrono::steady_clock> mStartTime;

//handling change volume
    int mVolume;
    struct termios mTty;

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
    void runListMediaFiles(std::list<std::shared_ptr<MediaFile>>);

//manage display current time when playing music
    int getCurrentPlayTime();
    std::string formatTime(int);    // format time in mm:ss format
    void showTimeInRealTime();

//manage change volume
    void setNonCanonicalMode(bool = true);  // turn on/off canonical
    void increaseVolume();
    void decreaseVolume();
};

#endif