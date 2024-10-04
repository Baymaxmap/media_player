#ifndef VIEW_MEDIA_H
#define VIEW_MEDIA_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "media.h"
#include "media_management.h"

class MediaManagement;

class ViewMedia{
public:

//****************************** INF VIEW GENERAL ******************************
    static void showMediaInf(std::string);          //view inf of a media file
    static void showMediaInfInFolder(std::string);  //view all media files in current folder
    static void showAllPlaylist(std::string);       //view all playlist created
    static void showFilesInPlaylist(std::string);   //view all media files in a playlist
    static void showMediaInfPerPage(std::vector<std::shared_ptr<MediaFile>>&, size_t, size_t, size_t);  //view all media files in each page

//****************************** VIEW APP ******************************
    static void showAppMainMenu();                                  //main menu of app

//view menu of browse media file
    static void showBrowseMedia(MediaManagement&, char = 'c');      //flag char is to view current page or next page, previous page

//view menu of playlist
    static void showPlaylistMenu();                                 //menu of playlist
    static void showEditPlaylistMenu(std::string);
    static void showFilesToAddPlaylist(MediaManagement&, char = 'c');

//view menu of edit/view metadata
    static void showEditViewMetadata(MediaManagement&, char = 'c'); //flag char is to view current page or next page, previous page

//view menu of play music: show option play music for all files or for a specific playlist
    static void showPlayMusic();
    static void showOptionPlayMusic();

//other feature
    static void showErrorInput();
    static void clearScreen();
};

#endif