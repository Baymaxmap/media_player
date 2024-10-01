#include "media.h"
#include "view_media.h"
#include "player_controller.h"
#include "media_management.h"
#include "playlist.h"
#include "app_controller.h"

int main(){
// //****************** READ THE FOLDER AND STORE MEDIA FILES IN OBJECT ************************* */
//     MediaManagement folderMedia("/home/thanhtb5/Documents/FPT/OJT_FRESHER/STUDY_APP/VSCODE/media/media_file");
//     folderMedia.showAllMediaFiles();

// //****************** CREATE PLAYLIST AND ADD MEDIA FILES ************************* */
//     folderMedia.addPlaylist("thanh ngu");
//     folderMedia.getPlaylist("thanh ngu")->addMediaFile((size_t)0);
//     folderMedia.getPlaylist("thanh ngu")->addMediaFile((size_t)3);
//     std::shared_ptr<Playlist> playlist = folderMedia.getPlaylist("thanh ngu");
//     folderMedia.showAllFilesInPlaylist("thanh ngu");

//     folderMedia.addPlaylist("khanh ngu");
//     folderMedia.showAllPlaylist();

//     folderMedia.showCurrentPage();
//     std::cout<<"next page\n";
//     folderMedia.showNextPage();

//     PlayerMediaController player;
//     while(1){
//         player.runPlaylist(playlist);
//         break;
//     }
    MediaManagement folderMedia("/home/thanhtb5/Documents/FPT/OJT_FRESHER/STUDY_APP/VSCODE/media/media_file");
    PlayerMediaController player;
    player.init();
    AppController appController(folderMedia, player);
    appController.run();
    return 0;
}

