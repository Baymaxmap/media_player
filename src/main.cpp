#include "media.h"
#include "view_media.h"
#include "media_controller.h"
#include "player_controller.h"
#include "media_management.h"
#include "playlist.h"

int main(){
    // std::string path;
    // std::shared_ptr<MediaFile> mediafile1
    // = std::make_shared<MediaFile>("/home/thanhtb5/Documents/FPT/OJT_FRESHER/STUDY_APP/VSCODE/taglib/audio_file/ok.mp3");
    // std::shared_ptr<ViewMedia> viewMedia1 = std::make_shared<ViewMedia>();
    // MediaController controller1(mediafile1, viewMedia1);
    // controller1.updateView();

    // controller1.updateMediaFile("Title", "like i used to see u long long time");
    // controller1.updateView();
    
    
    // PlayerMediaController player;
    // player.init();
    // while(1){
    //     int i;
    //     std::cout<<"press 1 to play\n";
    //     std::cout<<"press 2 to pause\n";
    //     std::cout<<"press 3 to resume\n";
    //     std::cout<<"press 4 to exit\n";
    //     std::cin>>i;
    //     switch(i){
    //         case 1:{
    //             player.play(mediafile1->getPathMedia());
    //             break;
    //         }
    //         case 2:{
    //             player.pause();
    //             break;
    //         }
    //         case 3:{
    //             player.resume();
    //             break;
    //         }
    //         case 4:
    //         {
    //             player.end();
    //             break;
    //         }
    //         default:{std::cout<<"not valid input\n"; break;}
    //     }
    //     if(i==4){
    //         break;
    //     }
    // }

    MediaManagement folderMedia("/home/thanhtb5/Documents/FPT/OJT_FRESHER/STUDY_APP/VSCODE/media/media_file");
    folderMedia.showAllMediaFiles();
    std::cout<<"******* AFTER ADD A MEDIA FILE *******\n";
    folderMedia.addMediaFile("/home/thanhtb5/Documents/FPT/OJT_FRESHER/STUDY_APP/VSCODE/taglib/audio_file/trong_com.mp3");
    folderMedia.showAllMediaFiles();


    folderMedia.addPlaylist("thanh ngu");
    folderMedia.getPlaylist("thanh ngu")->addMediaFile((size_t)0);
    folderMedia.getPlaylist("thanh ngu")->addMediaFile((size_t)1);
    std::shared_ptr<Playlist> playlist = folderMedia.getPlaylist("thanh ngu");
    playlist->show();

    return 0;
}

