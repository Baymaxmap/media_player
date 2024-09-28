#ifndef METADATA_H
#define METADATA_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>

//general metadata for media file
class Metadata{
protected:
    std::string mPath;
    std::unordered_map<std::string, std::string> mMetadata;
public:
    Metadata(std::string);
    virtual std::string getInf() const;
    std::string getName() const;
    void updateMetadata(std::string, std::string);
    void updateMetadata(std::string, int);
};

//class MetadataAudio for audio file
class MetadataAudio : public Metadata{
    // int mSampleRate;
    // int mBitRate;
    // int mChannel;
public:
    MetadataAudio(std::string);
    std::string getInf() const override;
};

//class MetadataVideo for video file
class MetadataVideo : public Metadata{
    // std::string mSize;
public:
    MetadataVideo(std::string);
    std::string getInf() const override;
};


#endif