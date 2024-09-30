#ifndef VIEW_MEDIA_H
#define VIEW_MEDIA_H

#include <iostream>
#include <string>

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
};

#endif