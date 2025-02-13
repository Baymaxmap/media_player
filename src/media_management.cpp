#include "media_management.h"

/************************************** CONSTRUCTOR *****************************************/

std::vector<std::shared_ptr<MediaFile>> MediaManagement::mMediaManager;
std::map<std::string, std::shared_ptr<Playlist>> MediaManagement::mPlaylistManager;

MediaManagement::MediaManagement() : mCurrentPage(0){}


//read the folder path and store all media files into a vector
void MediaManagement::setMediaManager(std::string folderPath) {
    // use recursive_directory_iterator traverse all sub-folder
    for (const auto& entry : std::filesystem::recursive_directory_iterator(folderPath)) {
        // check if the file has extension .mp3
        if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
            std::string filePath = entry.path().string();
            mMediaManager.push_back(std::make_shared<MediaFile>(filePath));
        }
    }
}

/*********************************** MANAGE INF OF VECTOR OF FILES AND MAP OF PLAYLIST **************************************/
//get all name of playlists
std::string MediaManagement::getAllPlaylistName() const{
    if(mPlaylistManager.empty()){
        return "NO playlist found!!!\n";
    }
    std::string infPlaylist = "";
    for(auto& it : mPlaylistManager){
        infPlaylist += it.first + "\n";
    }
    return infPlaylist;
}

//get all name of media files in folder
std::string MediaManagement::getAllMediaFiles() const{
    std::string infMediaFiles = "";
    for(size_t i = 0; i<mMediaManager.size(); i++){
        infMediaFiles += std::to_string(i) + ". " + mMediaManager[i]->getNameMedia() + "\n";
    }
    return infMediaFiles;
}

//get all files in a playlist
std::string MediaManagement::getAllFilesInPlaylist(std::string namePlaylist) const{
    if(mPlaylistManager.find(namePlaylist) != mPlaylistManager.end()){
        return mPlaylistManager[namePlaylist]->getAllFilesInPlaylist();
    }
    std::cout<<"NOT EXIST file name: "<<namePlaylist<<std::endl;
    return "";
}

//get shared_ptr<Playlist>
std::shared_ptr<Playlist> MediaManagement::getPlaylist(const std::string& namePlaylist){
    if(mPlaylistManager.find(namePlaylist) != mPlaylistManager.end()){
        return mPlaylistManager[namePlaylist];
    }
    return nullptr;
}

//get vector of media files
std::vector<std::shared_ptr<MediaFile>>& MediaManagement::getVectorMediaFile(){
    return mMediaManager;
}

//get list of shared_ptr media files
std::list<std::shared_ptr<MediaFile>> MediaManagement::getListMediaFiles(){
    std::list<std::shared_ptr<MediaFile>> listMediaFiles;
    for(auto& it : mMediaManager){
        listMediaFiles.push_back(it);
    }
    return listMediaFiles;
}

//add a media file by its path
void MediaManagement::addMediaFile(std::string filePath){
    MediaFile mediaFile(filePath);
    mMediaManager.push_back(std::make_shared<MediaFile>(filePath));
}

/************************************** MANAGE A PLAYLIST *****************************************/
//create and add a playlist by its name
void MediaManagement::addPlaylist(std::string namePlaylist){
    if(mPlaylistManager.find(namePlaylist) == mPlaylistManager.end()){
        mPlaylistManager[namePlaylist] = std::make_shared<Playlist>(namePlaylist);
        std::cout<<"Succesfully add a playlist: "<<namePlaylist<<std::endl;
    }
    else{
        std::cout<<"Playlist "<<namePlaylist<<" is already existed! Cannot create\n";
    }
}

//delete playlist by its name
void MediaManagement::deletePlaylist(std::string namePlaylist){
    if(mPlaylistManager.find(namePlaylist) != mPlaylistManager.end()){
        mPlaylistManager.erase(namePlaylist);
        return;
    }
    std::cout<<"NO playlist named "<<namePlaylist<<" found!\n";
}

//update name of playlist
void MediaManagement::updateNamePlaylist(std::string oldName, std::string newName){
    if(mPlaylistManager.find(oldName) != mPlaylistManager.end() && mPlaylistManager.find(newName) == mPlaylistManager.end()){
        std::shared_ptr<Playlist> storePlaylist = mPlaylistManager[oldName];
        mPlaylistManager.erase(oldName);
        mPlaylistManager[newName] = storePlaylist;
        storePlaylist->updateNamePlaylist(newName);
        return;
    }
    std::cout<<"**ERROR: invalid old name or new name of playlist, check again!\n";
}

//add a file into playlist
void MediaManagement::addFileToPlaylist(std::string namePlaylist, size_t index){
    if(mPlaylistManager.find(namePlaylist) != mPlaylistManager.end()){
        mPlaylistManager[namePlaylist]->addMediaFile(index);
        return;
    }
    std::cout<<"**ERROR: invalid name of playlist\n";
}

//delete a file from playlist by its path
void MediaManagement::deleteFileInPlaylist(std::string namePlaylist, std::string filePath){
    if(mPlaylistManager.find(namePlaylist) != mPlaylistManager.end()){
        mPlaylistManager[namePlaylist]->deleteMediaFile(filePath);
        return;
    }
    std::cout<<"**ERROR: invalid name of playlist\n";
}


/************************************** MANAGE A MEDIA FILE *****************************************/
//get all inf of a media file, pass index of vector mMediaManager to get inf
std::string MediaManagement::getInfMedia(size_t index) const{
    if(index < 0 || index > mMediaManager.size()){
        std::cout<<"INVALID index\n";
        return "";
    }
    return mMediaManager[index]->getInfMedia();
}

//get path of a media file
std::string MediaManagement::getPathMedia(size_t index) const{
    if(index < 0 || index > mMediaManager.size()){
        std::cout<<"INVALID index\n";
        return "";
    }
    return mMediaManager[index]->getPathMedia();
}

//get name of a media file
std::string MediaManagement::getNameMedia(size_t index) const{
    if(index < 0 || index > mMediaManager.size()){
        std::cout<<"INVALID index\n";
        return "";
    }
    return mMediaManager[index]->getNameMedia();
}

//update metadata of a media file
void MediaManagement::updateMediaFile(size_t index, std::string field, std::string newValue){
    if(index < 0 || index > mMediaManager.size()){
        std::cout<<"INVALID index\n";
        return;
    }
    mMediaManager[index]->updateMetadata(field, newValue);
}

void MediaManagement::updateMediaFile(size_t index, std::string field, int newValue){
    if(index < 0 || index > mMediaManager.size()){
        std::cout<<"INVALID index\n";
        return;
    }
    mMediaManager[index]->updateMetadata(field, newValue);
}

/************************************** GET CURRENT DIRECTORY *****************************************/
//get the current directory
std::string MediaManagement::getCurrentDirectory(){
    char currentPath[PATH_MAX];

    // get the current directory and convert into string
    if (getcwd(currentPath, sizeof(currentPath)) != nullptr) {
        return std::string(currentPath);
    } else {
        std::cerr << "Error getting current directory" << std::endl;
        return "";
    }
}

/************************************** UPDATE VIEW *****************************************/
//show all details inf of a media file
void MediaManagement::showInfMediaFile(size_t index) const{
    ViewMedia::showMediaInf(mMediaManager[index]->getInfMedia());
}
//show all current media files
void MediaManagement::showAllMediaFiles() const{
    ViewMedia::showMediaInfInFolder(this->getAllMediaFiles());
}
//show all playlist
void MediaManagement::showAllPlaylist() const{
    ViewMedia::showAllPlaylist(this->getAllPlaylistName());
}
//show all files in playlist
void MediaManagement::showAllFilesInPlaylist(std::string namePlaylist) const{
    ViewMedia::showFilesInPlaylist(this->getAllFilesInPlaylist(namePlaylist));
}

/************************************** VIEW MEDIA FILES PER PAGE *****************************************/
//show media files in current page
void MediaManagement::showCurrentPage(){
    if(mMediaManager.empty()){
        std::cout<<"NO media files found!\n";
        return;
    }
    size_t start = mCurrentPage * ITEMS_PER_PAGE;
    size_t end = ((mMediaManager.size() < (start + ITEMS_PER_PAGE))? mMediaManager.size() :(start + ITEMS_PER_PAGE));
    ViewMedia::showMediaInfPerPage(mMediaManager, mCurrentPage, start, end);
}

//show media files next page
void MediaManagement::showNextPage(){
    if((mCurrentPage+1) * ITEMS_PER_PAGE < mMediaManager.size()){
        mCurrentPage++;
        showCurrentPage();
    }
    else{
        showCurrentPage();
        std::cout<<"\nYou are on the last page!\n";
    }
}

//show media files in previous page
void MediaManagement::showPreviousPage(){
    if(mCurrentPage == 0){
        showCurrentPage();
        std::cout<<"\nYou are on the first page!\n";
        return;
    }
    mCurrentPage--;
    showCurrentPage();
}