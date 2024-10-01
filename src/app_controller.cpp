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
                //
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

/************************************** MANAGE  *****************************************/
void AppController::managePlaylist(){
    int inputPlaylistMenu;
    std::cin>>inputPlaylistMenu;
    std::cin.ignore();
    switch(inputPlaylistMenu){
        ViewMedia::showPlaylistMenu();
        case 1:
        {
            mMediaManagementController.showAllPlaylist();
            break;
        }
        case 2:
        {
            std::string namePlaylist;
            std::cout<<"Enter the name of playlist: ";
            std::getline(std::cin, namePlaylist);
            if(mMediaManagementController.getPlaylist(namePlaylist)){
                mMediaManagementController.addPlaylist(namePlaylist);
            }
            
        }

    }
}