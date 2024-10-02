#include "media.h"
#include "view_media.h"
#include "player_controller.h"
#include "media_management.h"
#include "playlist.h"
#include "app_controller.h"

int main(){
    MediaManagement folderMedia("/home/thanhtb5/Documents/FPT/OJT_FRESHER/STUDY_APP/VSCODE/media/media_file");
    PlayerMediaController player;
    player.init();
    AppController appController(folderMedia, player);
    appController.run();
    return 0;
}

