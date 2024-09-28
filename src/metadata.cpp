#include "metadata.h"

/*
**************************** IMPLEMENTATION OF METADATA CLASS ****************************
*/
Metadata::Metadata(std::string path) : mPath(path){
//the parameter of object TagLib::FileRef is const char*, so use .c_str() to return a pointer to const char
    TagLib::FileRef filePath(path.c_str());

    if (!filePath.isNull() && filePath.tag()) {

        //get the inf of media file using TagLib
        TagLib::Tag* tag = filePath.tag();
        mMetadata["Title"] = tag->title().toCString(true);
        mMetadata["Artist"] = tag->artist().toCString(true);
        mMetadata["Year"] = std::to_string(tag->year());
        mMetadata["Comment"] = tag->comment().toCString(true);

        TagLib::AudioProperties *properties = filePath.audioProperties();
        mMetadata["Duration"] = std::to_string(properties->length());
    }
}

//get the inf of media file
std::string Metadata::getInf() const{
    std::string infMedia = "";
    for(auto& it : mMetadata){
        infMedia += it.first + ": " + it.second + "\n";
    }
    return infMedia;
}

//get the name of file
std::string Metadata::getName() const{
    auto it = mMetadata.find("Title");
    if(it != mMetadata.end()){
        return it->second;
    }
    return "";
}

//get the path of file
std::string Metadata::getPath() const{
    return mPath;
}

//update inf of media file
void Metadata::updateMetadata(std::string field, std::string newValue){
    TagLib::FileRef filePath(mPath.c_str());
    TagLib::Tag* tag = filePath.tag();
    if(field == "Title"){
        mMetadata[field] = newValue;
        tag->setTitle(newValue);
        filePath.save();
        return;
    }
    if(field == "Artist"){
        mMetadata[field] = newValue;
        tag->setArtist(newValue);
        filePath.save();
        return;
    }
    if(field == "Comment"){
        mMetadata[field] = newValue;
        tag->setComment(newValue);
        filePath.save();
        return;
    }
    std::cout<<"ERROR: Cannot find the field "<<field<<" to update, check again!\n";
}

void Metadata::updateMetadata(std::string field, int newValue){
    TagLib::FileRef filePath(mPath.c_str());
    TagLib::Tag* tag = filePath.tag();
    if(field == "Year"){
        mMetadata[field] = std::to_string(newValue);
        tag->setYear(newValue);
        filePath.save();
        return;
    }
    std::cout<<"ERROR: Cannot find the field "<<field<<" to update, check again!\n";
}

/*
**************************** IMPLEMENTATION OF METADATAAUDIO CLASS ****************************
*/
MetadataAudio::MetadataAudio(std::string path) : Metadata(path){
    TagLib::FileRef filePath(path.c_str());

    if (!filePath.isNull() && filePath.tag()) {
        TagLib::AudioProperties *properties = filePath.audioProperties();
        mMetadata["Sample Rate"] = std::to_string(properties->sampleRate());
        mMetadata["Bit Rate"] = std::to_string(properties->bitrate());
        mMetadata["Channel"] = std::to_string(properties->channels());
    }
}

std::string MetadataAudio::getInf() const{
    std::string infMedia = "";
    for(auto& it : mMetadata){
        infMedia += it.first + ": " + it.second + "\n";
    }
    return infMedia;
}

/*
**************************** IMPLEMENTATION OF METADATAVIDEO CLASS ****************************
*/
MetadataVideo::MetadataVideo(std::string path) : Metadata(path){
    mMetadata["Size"] = "";
}
std::string MetadataVideo::getInf() const{
    std::string infMedia = "";
    for(auto& it : mMetadata){
        infMedia += it.first + ": " + it.second + "\n";
    }
    return infMedia;
}