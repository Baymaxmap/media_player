#include "view_media.h"

/*
**************************** IMPLEMENTATION OF VIEWMEDIA CLASS ****************************
*/

//View media files
void ViewMedia::showMediaInf(std::string infMedia){
    std::cout<<"\n\n======== INF of mediafile: ========\n";
    std::cout<<infMedia;
    std::cout<<"====================================\n";
}

void ViewMedia::showMediaInfInFolder(std::string infMediaInFolder){
    std::cout<<"\n\n======== INF of media files in the folder: ========\n";
    std::cout<<infMediaInFolder<<std::endl;
}

//View playlist
void ViewMedia::showAllPlaylist(std::string infPlaylist){
    std::cout<<"\n\n=================== INF OF ALL PLALIST ===================\n";
    std::cout<<infPlaylist<<std::endl;
    std::cout<<"==========================================================\n";
}

//view media files in folder
void ViewMedia::showFilesInPlaylist(std::string filesInPlaylist){
    std::cout<<"\n\n======== INF of all media files in playlist ========\n";
    std::cout<<filesInPlaylist<<std::endl;
}

//view media files per page
void ViewMedia::showMediaInfPerPage(std::vector<std::shared_ptr<MediaFile>>& mediaFiles, size_t start, size_t end){
    for(size_t i = start; i<end; i++){
        std::cout<<i<<". "<<mediaFiles[i]->getNameMedia()<<"\n";
    }
}

/************************************** VIEW APP *****************************************/
//main menu of app
void ViewMedia::showAppMainMenu(){
    std::cout<<"\n\n=================== MEDIA BROWSER ===================\n";
    std::cout<<"1. Browse media files\n";
    std::cout<<"2. Playlist\n";
    std::cout<<"3. View/Edit metadata of media files\n";
    std::cout<<"4. Play music\n";
    std::cout<<"5. Quit";
    std::cout<<"\n=====================================================\n";
    std::cout<<"Enter your choice: ";
}

//********************* BROWSE MEDIA MENU ***********************/
//view browse media menu, flag is used to call which page to be displayed
void ViewMedia::showBrowseMedia(MediaManagement& mediaManagement, char flag){
    std::cout<<"\n\n=================== BROWSE MEDIA FILES ===================\n";
    if(flag == 'c'){mediaManagement.showCurrentPage();}
    if(flag == 'n'){mediaManagement.showNextPage();}
    if(flag == 'p'){mediaManagement.showPreviousPage();}
    std::cout<<"[Next page] (press n)       [Previous page] (press p)\n";
    std::cout<<"==========================================================\n";
    std::cout<<"Enter the number to play, or press (b) to back to main menu: ";
}

//********************* PLAYLIST MENU ***********************/
void ViewMedia::showPlaylistMenu(){
    std::cout<<"\n\n=================== PLAYLIST ===================\n";
    std::cout<<"1. View all Playlists\n";
    std::cout<<"2. Create a new Playlist\n";
    std::cout<<"3. Edit a playlist\n";
    std::cout<<"4. Delete a playlist\n";
    std::cout<<"5. Back to main menu";
    std::cout<<"\n=================================================\n";
    std::cout<<"Enter your choice: ";
}

void ViewMedia::showEditPlaylistMenu(std::string namePlaylist){
    std::cout<<"\n\n=================== EDIT PLAYLIST "<<namePlaylist<< " ===================\n";
    std::cout<<"1. Add media file to the playlist\n";
    std::cout<<"2. Remove media file from the playlist\n";
    std::cout<<"3. View current media files in the playlist\n";
    std::cout<<"4. Rename the playlist\n";
    std::cout<<"5. Back to previous menu";
    std::cout<<"\n=====================================================\n";
    std::cout<<"Enter your choice: ";
}

void ViewMedia::showFilesToAddPlaylist(std::vector<std::shared_ptr<MediaFile>>& mediaFiles){
    std::cout<<"\n\n=================== ADD FILE INTO PLAYLIST ===================\n";
    for(size_t i = 0; i<mediaFiles.size(); i++){
        std::cout<<i+1<<". "<<mediaFiles[i]->getNameMedia()<<std::endl;
    }
    std::cout<<"\n==========================================================\n";
}

//********************* EDIT/VIEW METADATA OF FILE ***********************/
void ViewMedia::showEditViewMetadata(MediaManagement& mediaManagement, char flag){
    std::cout<<"\n\n=================== VIEW/EDIT METADATA OF A FILE ===================\n";
    if(flag == 'c'){mediaManagement.showCurrentPage();}
    if(flag == 'n'){mediaManagement.showNextPage();}
    if(flag == 'p'){mediaManagement.showPreviousPage();}
    std::cout<<"[Next page] (press n)       [Previous page] (press p)       [Back] (press b)\n";
    std::cout<<"====================================================================\n";
    std::cout<<"Choose which file you want to view/edit (enter the number): ";
}

//********************* PLAY MUSIC MENU ***********************/
void ViewMedia::showPlayMusic(){
    std::cout<<"\n\n=================== PLAY MUSIC ===================\n";
    std::cout<<"1. Play music all current media files\n";
    std::cout<<"2. Play music from a specific playlist\n";
    std::cout<<"3. Back\n";
    std::cout<<"====================================================\n";
    std::cout<<"Enter your otion: ";
}

void ViewMedia::showOptionPlayMusic(){
    std::cout<<"\n====================================================\n";
    std::cout<<"1. Start playing music\n";
    std::cout<<"2. Pause\n";
    std::cout<<"3. Resume\n";
    std::cout<<"4. Next Track\n";
    std::cout<<"5. Previous Track\n";
    std::cout<<"6. Stop and exit\n";
    std::cout<<"====================================================\n";
    std::cout<<"Enter your option: ";
}

/************************************** OTHER FEATURES *****************************************/
void ViewMedia::showErrorInput(){
    std::cout<<"**ERROR: invalid input, check again!!!\n";
}