#include "media.h"
#include "view_media.h"
#include "player_controller.h"
#include "media_management.h"
#include "playlist.h"
#include "app_controller.h"

int main(){
    MediaManagement folderMedia;
    std::string folderPath = folderMedia.getCurrentDirectory();
    folderMedia.setMediaManager(folderPath);
    
    PlayerMediaController player;
    player.init();
    AppController appController(folderMedia, player);
    appController.run();
    
    return 0;
}

