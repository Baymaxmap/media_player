#include "media_management.h"

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

//add a media file by its path
void MediaManagement::addMediaFile(std::string filePath){
    MediaFile mediaFile(filePath);
    mMediaManager.push_back(std::make_shared<MediaFile>(filePath));
}
//create and add a playlist by its name
void MediaManagement::addPlaylist(std::string namePlaylist){
    mPlaylistManager[namePlaylist] = std::make_shared<Playlist>(namePlaylist);
}


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