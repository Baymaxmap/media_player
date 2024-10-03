#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include "media_management.h"
#include "player_controller.h"
#include "view_media.h"

class AppController{
    MediaManagement& mMediaManagementController;
    PlayerMediaController& mPlayerController;

public:
    AppController(MediaManagement&, PlayerMediaController&);
    
// run the app
    void run();

//******************** MAIN MENU ***********************/
    void browseMediaFiles();    //option 1: browse media files
    void managePlaylist();      //option 2: playlist
    void manageMediaFile();     //option 3: metadata
    void managePlayMusic();     //option 4: play music

//other features
    bool checkIsChar(const std::string&);   //check a string is char or not
    bool checkIsNumber(const std::string&); //check a string is number or not
};


#endif