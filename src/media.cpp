#include "media.h"

/*
**************************** IMPLEMENTATION OF MEDIAFILE CLASS ****************************
*/
MediaFile::MediaFile(std::string path) : mPath(path){
    if(path.find(".mp3") != std::string::npos){
        mMetadata = std::make_shared<MetadataAudio>(path);
    }
    if(path.find(".mp4") != std::string::npos){
        mMetadata = std::make_shared<MetadataVideo>(path);
    }
}

std::string MediaFile::getInfMedia() const{
    return mMetadata->getInf();
}