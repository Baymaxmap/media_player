#ifndef VIEW_MEDIA_H
#define VIEW_MEDIA_H

#include <iostream>
#include <string>
#include <vector>

#include "media.h"
#include "media_management.h"

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


//view all media files in each page
    static void showMediaInfPerPage(std::vector<std::shared_ptr<MediaFile>>&, size_t, size_t);

//********************* view main menu of app *********************
    static void showAppMainMenu();
    static void showPlaylistMenu();

//view menu of browse media file
    static void showBrowseMedia(MediaManagement&, char = 'c');

//view menu of playlist
    static void showEditPlaylistMenu(std::string);
    static void showFilesToAddPlaylist(std::vector<std::shared_ptr<MediaFile>>&);

//view menu of edit/view metadata
    static void showEditViewMetadata(MediaManagement&, char = 'c');
    static void showEditViewMetadata(MediaManagement&, size_t); //1111111111111111111111111111111111111

//other feature
    static void showErrorInput();
};

#endif