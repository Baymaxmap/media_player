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
    bool mIsPlaying;        //check whether music is playing or not
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

//play music
    void init();
    void play(std::string);
    void pause();
    void resume();
    void nextTrack();
    void previousTrack();
    void end();


/*handle the event music finished using Mix_HookMusicFinished,it takes the argument of type void (*)(void)..
but the non-static funtion has hiden parameter is this pointer, so need to create a static function as..
it has no parameter and use it to call non-static function*/

    static void musicEndedStatic();         //used to call non-static function: musicEndedPlaylist()
    void musicEnded();                      //handle the event music play finished

//run playlist or run all media files in current folder
    void runPlaylist(std::shared_ptr<Playlist>);
    void runListMediaFiles(std::list<std::shared_ptr<MediaFile>>);

//manage display current time when playing music
    int getCurrentPlayTime();
    std::string formatTime(int);            // format time in mm:ss format
    void showTimeInRealTime();              //show current time playing over total duration of that media file

//manage change volume
    void setNonCanonicalMode(bool = true);  // turn on/off canonical, echo
    void increaseVolume();
    void decreaseVolume();
};

#endif