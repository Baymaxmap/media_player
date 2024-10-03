#include "playlist.h"

Playlist::Playlist() : mName("default playlist"){}
Playlist::Playlist(std::string name) : mName(name){}

//add a media file to the playlist
void Playlist::addMediaFile(size_t index){
    if(index > MediaManagement::mMediaManager.size() || index < 0){
        std::cout<<"INVALID index, cannot add file!\n";
        return;
    }
    else{
        mPlaylist.push_back(MediaManagement::mMediaManager[index]); //access media file by index of vector stored in MediaMangement object
    }
}

//delete a file from playlist by its path
void Playlist::deleteMediaFile(std::string filePath){
    std::list<std::weak_ptr<MediaFile>>::iterator fileErase = mPlaylist.end();
    for(auto it = mPlaylist.begin(); it != mPlaylist.end(); it++){
        if(it->lock()->getPathMedia() == filePath){
            fileErase = it;
        }
    }
    mPlaylist.erase(fileErase);
}

//update a new name for playlist
void Playlist::updateNamePlaylist(std::string newName){
    mName = newName;
}

//get all path of media files in playlist for the purpose of display inf of files in playlist
std::string Playlist::getAllFilesInPlaylist() const{
    std::string allFiles = "";
    for(auto& it : mPlaylist){
        allFiles += it.lock()->getPathMedia() + "\n";
    }
    return allFiles;
}

//get all the path of media files in playlist, store in list => for the purpose of play music
std::list<std::string> Playlist::getPathAllFiles(){
    std::list<std::string> pathAllFiles;
    for(auto& it : mPlaylist){
        pathAllFiles.push_back(it.lock()->getPathMedia());
    }
    return pathAllFiles;
}