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
        std::cin.ignore();
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
                manageMediaFile();
                break;
            }
            case '4':
            {
                managePlayMusic();
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

/************************************** BROWSE MEDIA FILES *****************************************/
void AppController::browseMediaFiles(){
    ViewMedia::showBrowseMedia(mMediaManagementController);
    while(1){
        std::string inputBrosweFile;
        std::getline(std::cin, inputBrosweFile);
        char inputChar;
        int numPlay;
//check input is char or not
        if (checkIsChar(inputBrosweFile)) {
            inputChar = inputBrosweFile[0];
            switch(inputChar){
                case 'n':{
                    ViewMedia::showBrowseMedia(mMediaManagementController, inputChar);
                    break;
                }
                case 'p':{
                    ViewMedia::showBrowseMedia(mMediaManagementController, inputChar);
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
            if(checkIsNumber(inputBrosweFile)){
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

/************************************** MANAGE EDIT/VIEW METADATA *****************************************/
void AppController::manageMediaFile(){
    char inputChar = 'c';
    int inputNum;
    while(1){
        std::string inputMetadata;
        ViewMedia::showEditViewMetadata(mMediaManagementController, inputChar);
        std::getline(std::cin, inputMetadata);
        
    //input is a char
        if(checkIsChar(inputMetadata)){
            inputChar = inputMetadata[0];
            if(inputChar == 'b'){break;}
            if(inputChar != 'n' && inputChar != 'p'){
                ViewMedia::showErrorInput();
                inputChar = 'c';
            }
        }

    //input is a number
        else{
            if(checkIsNumber(inputMetadata)){
                inputNum = std::stoi(inputMetadata);
                mMediaManagementController.showInfMediaFile((size_t)inputNum);  //show inf of media file chosen
                std::cout<<"Do you want to edit this file [y/n]: ";
                char inputOption;
                std::cin>>inputOption;
                std::cin.ignore();
                switch(inputOption){
                
                //user want to edit the metadata of that file chosen
                    case 'y':
                    {
                        std::string field;
                        std::cout<<"Enter EXACTLY the field that you want to change: ";
                        std::getline(std::cin, field);
                        
                        std::cout<<"Enter the new value that you want to subtitute: ";
                        std::string newValue;
                        std::getline(std::cin, newValue);

                        //update new value for metadata of media file
                        if(checkIsNumber(newValue)){
                            int value = std::stoi(newValue);
                            mMediaManagementController.updateMediaFile((size_t)inputNum, field, value);
                        }
                        else{
                            mMediaManagementController.updateMediaFile((size_t)inputNum, field, newValue);
                        }
                        break;
                    }
                //user do not want to edit the metadata of that file chosen
                    case 'n':
                    {
                        break;
                    }
                    default:{
                        ViewMedia::showErrorInput();
                        break;
                    }
                }
            }
            else{
                ViewMedia::showErrorInput();
            }
            inputChar = 'c';
        }
    }
}


/************************************** MANAGE PLAY MUSIC *****************************************/
void AppController::managePlayMusic(){
//show menu of playmusic
    while(1)
    {
        ViewMedia::showPlayMusic();
        char inputPlayOption;
        std::cin>>inputPlayOption;
        std::cin.ignore();

        switch(inputPlayOption){
        //case '1': play all current media files
            case '1':
            {
                mPlayerController.runListMediaFiles(mMediaManagementController.getListMediaFiles());
                break;
            }
        //case '2': play a specific playlist by its name
            case '2':
            {
                mMediaManagementController.showAllPlaylist();
                std::cout<<"Enter EXACTLY the name of playlist that you want to play: ";
                std::string namePlaylist;
                std::getline(std::cin, namePlaylist);
                if(mMediaManagementController.getPlaylist(namePlaylist)){
                    mPlayerController.runPlaylist(mMediaManagementController.getPlaylist(namePlaylist));
                }
                else{
                    std::cout<<"NO found any playlist name "<<namePlaylist<<std::endl;
                }
                break;
            }
            case '3':{break;}
        }
        if(inputPlayOption == '3'){break;}
    }
}


/************************************** OTHER FEATURES *****************************************/
bool AppController::checkIsChar(const std::string& input){
    if (input.length() == 1 && std::isalpha(input[0])){
        return true;
    }
    return false;
}

bool AppController::checkIsNumber(const std::string& input){
    for (char c : input) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}
