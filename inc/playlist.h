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
//manage playlist
    void addMediaFile(size_t);                  //all media files stored in vector of MediaManagement object => access media file by its index
    void deleteMediaFile(std::string);          //delete by its path
    void updateNamePlaylist(std::string);

    std::string getAllFilesInPlaylist() const;  //for the purpose of display inf of files in playlist (display path)
    std::list<std::string> getPathAllFiles();   //for the purpose of play music, get all path of media files
};


#endif