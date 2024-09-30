#include "media.h"
#include "view_media.h"
#include "player_controller.h"
#include "media_management.h"
#include "playlist.h"

int main(){
//****************** READ THE FOLDER AND STORE MEDIA FILES IN OBJECT ************************* */
    MediaManagement folderMedia("/home/thanhtb5/Documents/FPT/OJT_FRESHER/STUDY_APP/VSCODE/media/media_file");
    folderMedia.showAllMediaFiles();

//****************** CREATE PLAYLIST AND ADD MEDIA FILES ************************* */
    folderMedia.addPlaylist("thanh ngu");
    folderMedia.getPlaylist("thanh ngu")->addMediaFile((size_t)0);
    folderMedia.getPlaylist("thanh ngu")->addMediaFile((size_t)1);
    std::shared_ptr<Playlist> playlist = folderMedia.getPlaylist("thanh ngu");
    folderMedia.showAllFilesInPlaylist("thanh ngu");

    folderMedia.addPlaylist("khanh ngu");
    folderMedia.showAllPlaylist();

    PlayerMediaController player;
    while(1){
        player.runPlaylist(playlist);
        break;
    }

    return 0;
}

