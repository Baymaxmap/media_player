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
        mPlaylist.push_back(MediaManagement::mMediaManager[index]);
    }
}

void Playlist::deleteMediaFile(std::string filePath){
    std::list<std::weak_ptr<MediaFile>>::iterator fileErase = mPlaylist.end();
    for(auto it = mPlaylist.begin(); it != mPlaylist.end(); it++){
        if(it->lock()->getPathMedia() == filePath){
            fileErase = it;
        }
    }
    mPlaylist.erase(fileErase);
}

//get all name of files in playlist
std::string Playlist::getAllFilesInPlaylist() const{
    std::string allFiles = "";
    for(auto& it : mPlaylist){
        allFiles += it.lock()->getNameMedia() + "\n";
    }
    return allFiles;
}




void Playlist::show(){
    std::cout<<"*********** INF OF PLAYLIST: **************\n";
    for(auto&it : mPlaylist){
        std::cout<<it.lock()->getNameMedia()<<std::endl;
    }
}