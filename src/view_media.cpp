#include "view_media.h"

/*
**************************** IMPLEMENTATION OF VIEWMEDIA CLASS ****************************
*/

//View media files
void ViewMedia::showMediaInf(std::string infMedia){
    std::cout<<"\n======== INF of mediafile: ========\n";
    std::cout<<infMedia<<std::endl;
}

void ViewMedia::showMediaInfInFolder(std::string infMediaInFolder){
    std::cout<<"\n======== INF of media files in the folder: ========\n";
    std::cout<<infMediaInFolder<<std::endl;
}

//View playlist
void ViewMedia::showAllPlaylist(std::string infPlaylist){
    std::cout<<"\n======== INF of all playlists: ========\n";
    std::cout<<infPlaylist<<std::endl;
}

//View media files in folder
void ViewMedia::showFilesInPlaylist(std::string filesInPlaylist){
    std::cout<<"\n======== INF of all media files in playlist ========\n";
    std::cout<<filesInPlaylist<<std::endl;
}