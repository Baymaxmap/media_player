#include "media.h"

/*
**************************** IMPLEMENTATION OF MEDIAFILE CLASS ****************************
*/
MediaFile::MediaFile(std::string path) : mPath(path){
//the parameter of object TagLib::FileRef is const char*, so use .c_str() to return a pointer to const char
    TagLib::FileRef filePath(path.c_str());

    if (!filePath.isNull() && filePath.tag()) {

        //get the inf of media file using TagLib
        TagLib::Tag* tag = filePath.tag();
        mName = tag->title().toCString(true);
        mArtist = tag->artist().toCString(true);
        mYear = tag->year();
        mComment = tag->comment().toCString(true);

        TagLib::AudioProperties *properties = filePath.audioProperties();
        mDuration = properties->length();
    }
}

//get the inf of media file
std::string MediaFile::getInf() const{
    std::string infMedia;
    infMedia = "Name: " + mName +"\nArtist: " + mArtist +"\nYear: " 
                + std::to_string(mYear) + "\nComment: " + mComment + "\nDuration: " + std::to_string(mDuration);
    return infMedia;
}


/*
**************************** IMPLEMENTATION OF AUDIOFILE CLASS ****************************
*/
AudioFile::AudioFile(std::string path) : MediaFile(path){
    TagLib::FileRef filePath(path.c_str());

    if (!filePath.isNull() && filePath.tag()) {
        TagLib::AudioProperties *properties = filePath.audioProperties();
        mSampleRate = properties->sampleRate();
        mBitRate = properties->bitrate();
        mChannel = properties->channels();
    }
}

std::string AudioFile::getInf() const{
    return (MediaFile::getInf() 
            + "\nSample rate: "+std::to_string(mSampleRate) + "Hz" 
            + "\nBit rate: " +std::to_string(mBitRate) + "kbps" 
            + "\nChannel: " + std::to_string(mChannel)); 
}

/*
**************************** IMPLEMENTATION OF VIDEOFILE CLASS ****************************
*/
VideoFile::VideoFile(std::string path) : MediaFile(path){
    mSize = "";
    mDuration = "";
}
std::string VideoFile::getInf() const{
    return (MediaFile::getInf() + "\nSize: "+mSize + "\nDuration: "+mDuration); 
}