#include "metadata.h"

/*
**************************** IMPLEMENTATION OF METADATA CLASS ****************************
*/
Metadata::Metadata(std::string path){
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
std::string Metadata::getInf() const{
    std::string infMedia;
    infMedia = "Name: " + mName +"\nArtist: " + mArtist +"\nYear: " 
                + std::to_string(mYear) + "\nComment: " + mComment + "\nDuration: " + std::to_string(mDuration);
    return infMedia;
}

//get the name of file
std::string Metadata::getName() const{
    return mName;
}

/*
**************************** IMPLEMENTATION OF METADATAAUDIO CLASS ****************************
*/
MetadataAudio::MetadataAudio(std::string path) : Metadata(path){
    TagLib::FileRef filePath(path.c_str());

    if (!filePath.isNull() && filePath.tag()) {
        TagLib::AudioProperties *properties = filePath.audioProperties();
        mSampleRate = properties->sampleRate();
        mBitRate = properties->bitrate();
        mChannel = properties->channels();
    }
}

std::string MetadataAudio::getInf() const{
    return (Metadata::getInf() 
            + "\nSample rate: "+std::to_string(mSampleRate) + "Hz" 
            + "\nBit rate: " +std::to_string(mBitRate) + "kbps" 
            + "\nChannel: " + std::to_string(mChannel)); 
}

/*
**************************** IMPLEMENTATION OF METADATAVIDEO CLASS ****************************
*/
MetadataVideo::MetadataVideo(std::string path) : Metadata(path){
    mSize = "";
}
std::string MetadataVideo::getInf() const{
    return (Metadata::getInf() + "\nSize: "+mSize); 
}