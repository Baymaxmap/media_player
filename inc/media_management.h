/*
This folder is used to store all the media files in it, no matter where they are
*/

#ifndef MEDIA_MANAGEMENT_H
#define MEDIA_MANAGEMENT_H

#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include <memory>
#include <filesystem>

#include "media.h"
#include "playlist.h"
#include "view_media.h"

class Playlist;

class MediaManagement{
    static int mIndex;
    static std::vector<std::shared_ptr<MediaFile>> mMediaManager;
    //Mediafile is used by shared_ptr as playlist uses weak_ptr to point to MediaFile, not own it
    static std::map<std::string, std::shared_ptr<Playlist>> mPlaylistManager;
public:
    MediaManagement();
    MediaManagement(std::string);
    void addMediaFile(std::string);
    void addPlaylist(std::string);

    std::string getAllMediaFiles() const;
    std::string getAllPlaylistName() const;
    std::string getAllFilesInPlaylist(std::string) const;

    void showAllMediaFiles() const;
    void showAllPlaylist() const;
    void showAllFilesInPlaylist(std::string) const;

    std::shared_ptr<Playlist> getPlaylist(const std::string&);

    friend class Playlist;
};


#endif