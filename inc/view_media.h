#ifndef VIEW_MEDIA_H
#define VIEW_MEDIA_H

#include <iostream>
#include <string>
#include <vector>

#include "media.h"

class ViewMedia{
public:
//view a media file
    static void showMediaInf(std::string);
//view media management
    static void showMediaInfInFolder(std::string);
//view all playlists
    static void showAllPlaylist(std::string);
//view all media files in a playlist
    static void showFilesInPlaylist(std::string);

//view all media files in each
    static void showMediaInfPerPage(std::vector<std::shared_ptr<MediaFile>>&, size_t, size_t);

//********************* view main menu of app *********************
    static void showAppMainMenu();
    static void showPlaylistMenu();

//********************* view menu of playlist menu *********************
    static void showEditPlaylistMenu(std::string);
};

#endif