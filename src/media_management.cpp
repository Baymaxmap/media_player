#include "media_management.h"

/************************************** CONSTRUCTOR *****************************************/
int MediaManagement::mIndex = 0;
std::vector<std::shared_ptr<MediaFile>> MediaManagement::mMediaManager;
std::map<std::string, std::shared_ptr<Playlist>> MediaManagement::mPlaylistManager;

MediaManagement::MediaManagement(){}

//constructor that take in the folder path to traverse the folder and add all MediaFile objects to unordered_map
MediaManagement::MediaManagement(std::string folderPath){
    for(const auto& entry : std::filesystem::directory_iterator(folderPath)){
        if(entry.is_regular_file() && entry.path().extension() == ".mp3"){
            std::string filePath = entry.path().string();
            mMediaManager.push_back(std::make_shared<MediaFile>(filePath));
            mIndex++;
        }
    }
}

/************************************** ADD MEDIA FILES AND PLAYLIST INTO OBJECT *****************************************/
//add a media file by its path
void MediaManagement::addMediaFile(std::string filePath){
    MediaFile mediaFile(filePath);
    mMediaManager.push_back(std::make_shared<MediaFile>(filePath));
}
//create and add a playlist by its name
void MediaManagement::addPlaylist(std::string namePlaylist){
    mPlaylistManager[namePlaylist] = std::make_shared<Playlist>(namePlaylist);
}

/************************************** GET GENERAL INF OF MEDIA, PLAYLIST *****************************************/
//get all name of playlists
std::string MediaManagement::getAllPlaylistName() const{
    std::string infPlaylist = "";
    for(auto& it : mPlaylistManager){
        infPlaylist += it.first + "\n";
    }
    return infPlaylist;
}
//get all name of media files
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

/************************************** GET DETAILS INF OF MEDIA FILE *****************************************/
std::string MediaManagement::getInfMedia(size_t index) const{
    if(index < 0 || index > mMediaManager.size()){
        std::cout<<"INVALID index\n";
        return "";
    }
    return mMediaManager[index]->getInfMedia();
}

std::string MediaManagement::getPathMedia(size_t index) const{
    if(index < 0 || index > mMediaManager.size()){
        std::cout<<"INVALID index\n";
        return "";
    }
    return mMediaManager[index]->getPathMedia();
}

std::string MediaManagement::getNameMedia(size_t index) const{
    if(index < 0 || index > mMediaManager.size()){
        std::cout<<"INVALID index\n";
        return "";
    }
    return mMediaManager[index]->getNameMedia();
}

/************************************** UPDATE METADATA OF MEDIA FILE *****************************************/
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

/************************************** VIEW CLASS *****************************************/
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


//get shared_ptr<Playlist>
std::shared_ptr<Playlist> MediaManagement::getPlaylist(const std::string& namePlaylist){
    if(mPlaylistManager.find(namePlaylist) != mPlaylistManager.end()){
        return mPlaylistManager[namePlaylist];
    }
    return nullptr;
}