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
};


#endif