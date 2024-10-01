#include "view_media.h"

/*
**************************** IMPLEMENTATION OF VIEWMEDIA CLASS ****************************
*/

//View media files
void ViewMedia::showMediaInf(std::string infMedia){
    std::cout<<"\n======== INF of mediafile: ========\n";
    std::cout<<infMedia<<std::endl;
}

void ViewMedia::showMediaInfInFolder(std::string infMediaInFolder){
    std::cout<<"\n======== INF of media files in the folder: ========\n";
    std::cout<<infMediaInFolder<<std::endl;
}

//View playlist
void ViewMedia::showAllPlaylist(std::string infPlaylist){
    std::cout<<"\n=================== INF OF ALL PLALIST ===================\n";
    std::cout<<infPlaylist<<std::endl;
    std::cout<<"==========================================================\n";
}

//view media files in folder
void ViewMedia::showFilesInPlaylist(std::string filesInPlaylist){
    std::cout<<"\n======== INF of all media files in playlist ========\n";
    std::cout<<filesInPlaylist<<std::endl;
}

//view media files per page
void ViewMedia::showMediaInfPerPage(std::vector<std::shared_ptr<MediaFile>>& mediaFiles, size_t start, size_t end){
    std::cout<<"\n=================== BROWSE MEDIA FILES ===================\n";
    for(size_t i = start; i<end; i++){
        std::cout<<i<<". "<<mediaFiles[i]->getNameMedia()<<"\n";
    }
    std::cout<<"[Next page] (press n)       [Previous page] (press p)\n";
    std::cout<<"\n==========================================================\n";
    std::cout<<"Enter the number to play, or press (b) to back to main menu: ";
}

/************************************** VIEW APP *****************************************/
//main menu of app
void ViewMedia::showAppMainMenu(){
    std::cout<<"\n=================== MEDIA BROWSER ===================\n";
    std::cout<<"1. Browse media files\n";
    std::cout<<"2. Playlist\n";
    std::cout<<"3. View/Edit metadata of media files\n";
    std::cout<<"4. Play music\n";
    std::cout<<"5. Quit";
    std::cout<<"\n=====================================================\n";
    std::cout<<"Enter your choice: ";
}

//********************* PLAYLIST MENU ********************** */
void ViewMedia::showPlaylistMenu(){
    std::cout<<"\n=================== PLAYLIST ===================\n";
    std::cout<<"1. View all Playlists\n";
    std::cout<<"2. Create a new Playlist\n";
    std::cout<<"3. Edit a playlist\n";
    std::cout<<"4. Delete a playlist\n";
    std::cout<<"5. Back to main menu";
    std::cout<<"\n=====================================================\n";
    std::cout<<"Enter your choice: ";
}

void ViewMedia::showEditPlaylistMenu(std::string namePlaylist){
    std::cout<<"\n=================== EDIT PLAYLIST "<<namePlaylist<< " ===================\n";
    std::cout<<"1. Add media file to the playlist\n";
    std::cout<<"2. Remove media file from the playlist\n";
    std::cout<<"3. View current media files in the playlist\n";
    std::cout<<"4. Rename the playlist\n";
    std::cout<<"5. Back to previous menu";
    std::cout<<"\n=====================================================\n";
    std::cout<<"Enter your choice: ";
}

void ViewMedia::showFilesToAddPlaylist(std::vector<std::shared_ptr<MediaFile>>& mediaFiles){
    std::cout<<"\n=================== ADD FILE INTO PLAYLIST ===================\n";
    for(size_t i = 0; i<mediaFiles.size(); i++){
        std::cout<<i+1<<". "<<mediaFiles[i]->getNameMedia()<<std::endl;
    }
    std::cout<<"\n==========================================================\n";
}

