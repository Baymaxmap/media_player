#include "app_controller.h"

AppController::AppController(MediaManagement& mediaManagement, PlayerMediaController& playerController)
                            : mMediaManagementController(mediaManagement), mPlayerController(playerController) {}

/************************************** RUN THE APP *****************************************/
void AppController::run(){
//show the main menu
    while(true){
        ViewMedia::clearScreen();
        ViewMedia::showAppMainMenu();
        char inputMenu;
        std::cin>>inputMenu;
        std::cin.ignore();
        switch(inputMenu){
            case '1':
            {
                ViewMedia::clearScreen();
                browseMediaFiles();
                break;
            }
            case '2':
            {
                ViewMedia::clearScreen();
                managePlaylist();
                break;
            }
            case '3':
            {
                ViewMedia::clearScreen();
                manageMediaFile();
                break;
            }
            case '4':
            {
                ViewMedia::clearScreen();
                managePlayMusic();
                break;
            }
            case '5':
            {
                ViewMedia::clearScreen();
                break;
            }
            default:{
                ViewMedia::showErrorInput();
                break;
            }
        }
        if(inputMenu == '5'){break;}
    }
}

/************************************** BROWSE MEDIA FILES *****************************************/
void AppController::browseMediaFiles(){
    ViewMedia::clearScreen();
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
                    ViewMedia::clearScreen();
                    ViewMedia::showBrowseMedia(mMediaManagementController, inputChar);
                    break;
                }
                case 'p':{
                    ViewMedia::clearScreen();
                    ViewMedia::showBrowseMedia(mMediaManagementController, inputChar);
                    break;
                }
                case 'b':{
                    ViewMedia::clearScreen();
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
                    std::cout<<"Enter option: ";
                }
            }
            else{
                ViewMedia::showErrorInput();
                std::cout<<"Enter option ";
            }
        }
    }
}

/************************************** MANAGE PLAYLIST *****************************************/
void AppController::managePlaylist(){
    char inputPlaylistMenu;
    while(1){
        ViewMedia::showPlaylistMenu();
        std::cin>>inputPlaylistMenu;
        std::cin.ignore();
        switch(inputPlaylistMenu){
    //case 1: view all playlist
            case '1':
            {
                ViewMedia::clearScreen();
                mMediaManagementController.showAllPlaylist();
                break;
            }
    //case 2: add a new playlist
            case '2':
            {
                ViewMedia::clearScreen();
                std::string namePlaylist;
                std::cout<<"Enter the name of playlist (or press b to back): ";
                std::getline(std::cin, namePlaylist);
                if(namePlaylist == "b"){break;}
                mMediaManagementController.addPlaylist(namePlaylist);

                break;
            }
    //case 3: manage editting playlist
            case '3':
            {
                ViewMedia::clearScreen();
                std::string namePlaylist;
                mMediaManagementController.showAllPlaylist();   //show all playlist to choose
                std::cout<<"Enter the name of playlist that you want to edit: ";
                std::getline(std::cin, namePlaylist);
                if(mMediaManagementController.getPlaylist(namePlaylist)){
                    char intputEditPlaylist;
                    while(1){
        //show edit playlist menu
                        ViewMedia::showEditPlaylistMenu(namePlaylist);
                        std::cin>>intputEditPlaylist;
                        std::cin.ignore();
                        switch(intputEditPlaylist){
        //case 3.1: add files into playlist
                            case '1':
                            {
                                ViewMedia::clearScreen();
                                std::string inputAddFiles;
                                int numFile;
                                char flagPage = 'c';
                                while(1){
                                    ViewMedia::showFilesToAddPlaylist(mMediaManagementController, flagPage);
                                    while(1){
                                        std::cout<<"Choose file to add (or enter 0 to back): ";
                                        std::getline(std::cin, inputAddFiles);
                                        if(inputAddFiles == "0"){break;}
                                        if(checkIsChar(inputAddFiles)){
                                            flagPage = inputAddFiles[0];
                                            ViewMedia::clearScreen();
                                            ViewMedia::showFilesToAddPlaylist(mMediaManagementController, flagPage);
                                        }
                                        else{
                                            if(checkIsNumber(inputAddFiles)){
                                                numFile = std::stoi(inputAddFiles);
                                                mMediaManagementController.addFileToPlaylist(namePlaylist, numFile-1);
                                            }
                                            else{
                                                ViewMedia::showErrorInput();
                                            }
                                        }
                                    }
                                    if(inputAddFiles == "0"){
                                        ViewMedia::clearScreen();
                                        break;
                                    }
                                }
                                break;
                            }
        //case 3.2: remove a file from playlist
                            case '2':
                            {
                                ViewMedia::clearScreen();
                                mMediaManagementController.showAllFilesInPlaylist(namePlaylist);
                                std::string filePath;
                                std::cout<<"Enter the path of media file that you want to remove (or press b to back): ";
                                std::getline(std::cin, filePath);
                                if(filePath == "b"){break;}
                                mMediaManagementController.deleteFileInPlaylist(namePlaylist, filePath);
                                break;
                            }
        //case 3.3: view all media files in playlist
                            case '3':
                            {
                                ViewMedia::clearScreen();
                                mMediaManagementController.showAllFilesInPlaylist(namePlaylist);
                                break;
                            }
        //case 3.4: rename the playlist
                            case '4':
                            {
                                ViewMedia::clearScreen();
                                std::string newName;
                                std::cout<<"Enter the new name for playlist: ";
                                std::getline(std::cin, newName);
                                mMediaManagementController.updateNamePlaylist(namePlaylist ,newName);
                                break;
                            }
        //case 3.5: back to menu of playlist
                            case '5':
                            {
                                ViewMedia::clearScreen();
                                break;
                            }
                            default:
                            {
                                ViewMedia::showErrorInput();
                                break;
                            }
                        }
                        if(intputEditPlaylist=='5'){break;}
                    }
                }
                else{
                    ViewMedia::clearScreen();
                    std::cout<<"**ERROR: invaild name of playlist\n";
                }
                break;
            }
    //case 4: delete a playlist
            case '4':
            {
                ViewMedia::clearScreen();
                mMediaManagementController.showAllPlaylist();
                std::string deletePlaylist;
                std::cout<<"Enter the name of playlist you want to remove (or press b to back): ";
                std::getline(std::cin, deletePlaylist);
                if(deletePlaylist == "b"){break;}
                mMediaManagementController.deletePlaylist(deletePlaylist);
                break;
            }
    //case 5: back to main menu
            case '5':
            {
                ViewMedia::clearScreen();
                break;
            }
            default:
            {
                ViewMedia::showErrorInput();
                break;
            }
        }
        if(inputPlaylistMenu == '5'){break;}
    }
}

/************************************** MANAGE EDIT/VIEW METADATA *****************************************/
void AppController::manageMediaFile(){
    char inputChar = 'c';
    int inputNum;
    while(1){
        std::string inputMetadata;
        ViewMedia::showEditViewMetadata(mMediaManagementController, inputChar); //show edit metadata menu
        std::getline(std::cin, inputMetadata);
        
    //input is a char
        if(checkIsChar(inputMetadata)){
            inputChar = inputMetadata[0];
            if(inputChar == 'b'){
                ViewMedia::clearScreen();
                break;
            }
            else {
                if(inputChar != 'n' && inputChar != 'p'){
                    ViewMedia::clearScreen();
                    ViewMedia::showErrorInput();
                    inputChar = 'c';
                }

                else{
                    ViewMedia::clearScreen();
                }
            }
        }

    //input is a number
        else{
            if(checkIsNumber(inputMetadata)){
                ViewMedia::clearScreen();
                inputNum = std::stoi(inputMetadata);
                mMediaManagementController.showInfMediaFile((size_t)(inputNum-1));  //show inf of media file chosen
                std::cout<<"Do you want to edit this file [y/n]: ";
                char inputOption;
                std::cin>>inputOption;
                std::cin.ignore();
                
                switch(inputOption){
                //user want to edit the metadata of that file chosen
                    case 'y':
                    {
                        while(1){
                            std::string field;
                            std::cout<<"Enter EXACTLY the field that you want to change (or press b to back): ";
                            std::getline(std::cin, field);
                            if(field == "b"){break;}

                            std::cout<<"Enter the new value that you want to subtitute: ";
                            std::string newValue;
                            std::getline(std::cin, newValue);

                            //update new value for metadata of media file
                            if(checkIsNumber(newValue)){
                                int value = std::stoi(newValue);
                                mMediaManagementController.updateMediaFile((size_t)(inputNum-1), field, value);
                            }
                            else{
                                mMediaManagementController.updateMediaFile((size_t)(inputNum-1), field, newValue);
                            }
                        }
                        break;
                    }
                //user do not want to edit the metadata of that file chosen
                    case 'n':
                    {
                        ViewMedia::clearScreen();
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
                ViewMedia::clearScreen();
                mPlayerController.runListMediaFiles(mMediaManagementController.getListMediaFiles());
                break;
            }
        //case '2': play a specific playlist by its name
            case '2':
            {
                ViewMedia::clearScreen();
                mMediaManagementController.showAllPlaylist();
                std::cout<<"Enter EXACTLY the name of playlist that you want to play (or press b to back): ";
                std::string namePlaylist;
                std::getline(std::cin, namePlaylist);
                if(namePlaylist == "b"){
                    ViewMedia::clearScreen();
                    break;
                }
                if(mMediaManagementController.getPlaylist(namePlaylist)){
                    mPlayerController.runPlaylist(mMediaManagementController.getPlaylist(namePlaylist));
                }
                else{
                    std::cout<<"NOT found any playlist name "<<namePlaylist<<std::endl;
                }
                ViewMedia::clearScreen();
                break;
            }
            case '3':{
                ViewMedia::clearScreen();
                break;
            }
            default:{
                ViewMedia::showErrorInput();
                break;
            }
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
