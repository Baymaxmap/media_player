#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <memory>
#include <list>

#include "media.h"
#include "media_management.h"

class MediaManagement;

class Playlist{
    std::string mName;
    std::list<std::weak_ptr<MediaFile>> mPlaylist;  
//EXPLAIN for weak_ptr: when folder storing Media is destroyed, this playlist is destroyed too as no ref count increase
public:
    Playlist();
    Playlist(std::string);
    void addMediaFile(size_t);
    void deleteMediaFile(std::string);

    std::string getAllFilesInPlaylist() const;
    
    void show();
};


#endif