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

//get the inf of media file
std::string MediaFile::getInfMedia() const{
    return mMetadata->getInf();
}
std::string MediaFile::getPathMedia() const{
    return mMetadata->getPath();
}

//update data from user
void MediaFile::updateMetadata(std::string field, std::string newValue){
    mMetadata->updateMetadata(field, newValue);
}
void MediaFile::updateMetadata(std::string field, int newValue){
    mMetadata->updateMetadata(field, newValue);
}