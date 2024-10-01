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

#define ITEMS_PER_PAGE 10

class Playlist;

class MediaManagement{
    static int mIndex;
    size_t mCurrentPage;
    static std::vector<std::shared_ptr<MediaFile>> mMediaManager;
//Mediafile is used by shared_ptr as playlist uses weak_ptr to point to MediaFile, not own it
    static std::map<std::string, std::shared_ptr<Playlist>> mPlaylistManager;

public:
    MediaManagement();
    MediaManagement(std::string);

/*************************** MANAGE VECTOR OF FILES AND MAP OF PLAYLIST *****************************/
    void addMediaFile(std::string);
    void addPlaylist(std::string);
    void deletePlaylist(std::string);

//get general Inf of media files and playlist
    std::string getAllMediaFiles() const;
    std::string getAllPlaylistName() const;
    std::string getAllFilesInPlaylist(std::string) const;


/************************************** MANAGE A PLAYLIST **************************************/
    void updateNamePlaylist(std::string, std::string);
    void addFileToPlaylist(std::string, size_t);

/************************************** MANAGE A MEDIA FILE **************************************/
//get details inf of media file
    std::string getInfMedia(size_t) const;
    std::string getPathMedia(size_t) const;
    std::string getNameMedia(size_t) const;
//update metadata of media file
    void updateMediaFile(size_t, std::string, std::string);
    void updateMediaFile(size_t, std::string, int);


/*************************** RETURN VECTOR AND POINTER *****************************/
    std::shared_ptr<Playlist> getPlaylist(const std::string&);
    std::vector<std::shared_ptr<MediaFile>>& getVectorMediaFile();


/************************************** UPDATE VIEW **************************************/
//use View class to show Inf of all media files and playlists
    void showInfMediaFile(size_t) const;
    void showAllMediaFiles() const;
    void showAllPlaylist() const;
    void showAllFilesInPlaylist(std::string) const;
//view items per page
    void showCurrentPage();
    void showNextPage();
    void showPreviousPage();

    friend class Playlist;
};


#endif