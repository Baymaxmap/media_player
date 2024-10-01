#include "app_controller.h"

AppController::AppController(MediaManagement& mediaManagement, PlayerMediaController& playerController)
                            : mMediaManagementController(mediaManagement), mPlayerController(playerController) {}

/************************************** RUN THE APP *****************************************/
void AppController::run(){
//show the main menu
    while(true){
        ViewMedia::showAppMainMenu();
        char inputMenu;
        std::cin>>inputMenu;
        switch(inputMenu){
            case '1':
            {
                browseMediaFiles();
                break;
            }
            case '2':
            {
                managePlaylist();
                break;
            }
            case '3':
            {
                break;
            }
            case '4':
            {
                break;
            }
            case '5':
            {
                break;
            }
            default:{
                std::cout<<"**EROOR: invalid input\n";
                break;
            }
        }
        if(inputMenu == '5'){break;}
    }
}

/************************************** BROWSE MEDIA FILES*****************************************/
void AppController::browseMediaFiles(){
    mMediaManagementController.showCurrentPage();
    std::cin.ignore();
    while(1){
        std::string inputBrosweFile;
        std::getline(std::cin, inputBrosweFile);
        char inputChar;
        int numPlay;
//check input is char or not
        if (inputBrosweFile.length() == 1 && std::isalpha(inputBrosweFile[0])) {
            inputChar = inputBrosweFile[0];
            switch(inputChar){
                case 'n':{
                    mMediaManagementController.showNextPage();
                    break;
                }
                case 'p':{
                    mMediaManagementController.showPreviousPage();
                    break;
                }
                case 'b':{
                    break;
                }
            }
            if(inputChar == 'b'){break;}
        }
//check input is digit or not
        else{
            bool isNumber = true;
            for (char c : inputBrosweFile) {
                if (!std::isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            if(isNumber){
                numPlay = std::stoi(inputBrosweFile);
                if((size_t)numPlay >= 0 || (size_t)numPlay < (mMediaManagementController.getVectorMediaFile()).size() ){
                    std::string filePlay = mMediaManagementController.getVectorMediaFile()[(size_t)numPlay]->getPathMedia();
                    mPlayerController.play(filePlay);
                    std::cout<<"Enter the number to play, or press (b) to back to main menu: ";
                }
            }
            else{
                std::cout<<"**ERROR: invalid input\n";
                std::cout<<"Enter the number to play, or press (b) to back to main menu: ";
            }
        }
    }
}

/************************************** MANAGE PLAYLIST *****************************************/
void AppController::managePlaylist(){
    int inputPlaylistMenu;
    while(1){
        ViewMedia::showPlaylistMenu();
        std::cin>>inputPlaylistMenu;
        std::cin.ignore();
        switch(inputPlaylistMenu){
    //case 1: view all playlist
            case 1:
            {
                mMediaManagementController.showAllPlaylist();
                break;
            }
    //case 2: add a new playlist
            case 2:
            {
                std::string namePlaylist;
                std::cout<<"Enter the name of playlist: ";
                std::getline(std::cin, namePlaylist);
                mMediaManagementController.addPlaylist(namePlaylist);
                break;
            }
    //case 3: manage editting playlist
            case 3:
            {
                std::string namePlaylist;
                std::cout<<"Enter the name of playlist that you want to edit: ";
                std::getline(std::cin, namePlaylist);
                if(mMediaManagementController.getPlaylist(namePlaylist)){
                    int intputEditPlaylist;
                    while(1){
        //show edit playlist menu
                        ViewMedia::showEditPlaylistMenu(namePlaylist);
                        std::cin>>intputEditPlaylist;
                        std::cin.ignore();
                        switch(intputEditPlaylist){
        //case 3.1: add files into playlist
                            case 1:
                            {
                                ViewMedia::showFilesToAddPlaylist(mMediaManagementController.getVectorMediaFile());
                                int numFile;
                //enter number of file to add to playlist
                                while(1){
                                    std::cout<<"Choose file to add (or enter 0 to back): ";
                                    std::cin>>numFile;
                                    if(numFile==0){break;}
                                    else{
                                        mMediaManagementController.addFileToPlaylist(namePlaylist, numFile-1);
                                    }
                                }
                                break;
                            }
        //case 3.2: remove a file from playlist
                            case 2:
                            {
                                std::string filePath;
                                std::cout<<"Enter the path of media file that you want to remove: ";
                                std::getline(std::cin, filePath);
                                mMediaManagementController.deleteFileInPlaylist(namePlaylist, filePath);
                                break;
                            }
        //case 3.3: view all media files in playlist
                            case 3:
                            {
                                mMediaManagementController.showAllFilesInPlaylist(namePlaylist);
                                break;
                            }
        //case 3.4: rename the playlist
                            case 4:
                            {
                                std::string newName;
                                std::cout<<"Enter the new name for playlist: ";
                                std::getline(std::cin, newName);
                                mMediaManagementController.updateNamePlaylist(namePlaylist ,newName);
                                break;
                            }
        //case 3.5: back to menu of playlist
                            case 5:
                            {
                                break;
                            }
                            default:
                            {
                                std::cout<<"**ERROR: invalid input\n";
                                break;
                            }
                        }
                        if(intputEditPlaylist==5){break;}
                    }
                }
                else{
                    std::cout<<"**ERROR: invaild name of playlist\n";
                }
                break;
            }
    //case 4: delete a playlist
            case 4:
            {
                std::string deletePlaylist;
                std::cout<<"Enter the name of playlist you want to remove: ";
                std::getline(std::cin, deletePlaylist);
                mMediaManagementController.deletePlaylist(deletePlaylist);
                break;
            }
    //case 5: back to main menu
            case 5:
            {
                break;
            }
            default:
            {
                std::cout<<"**ERROR: invalid input\n";
                break;
            }
        }
        if(inputPlaylistMenu == 5){break;}
    }
}