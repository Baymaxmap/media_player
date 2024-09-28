#ifndef METADATA_H
#define METADATA_H

#include <string>
#include <iostream>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>

//general metadata for media file
class Metadata{
private:
    int mYear;
    int mDuration;
    std::string mPath;
    std::string mName;
    std::string mArtist;
    std::string mComment;
public:
    Metadata(std::string);
    virtual std::string getInf() const;
    std::string getName() const;
};

//class MetadataAudio for audio file
class MetadataAudio : public Metadata{
    int mSampleRate;
    int mBitRate;
    int mChannel;
public:
    MetadataAudio(std::string);
    std::string getInf() const override;
};

//class MetadataVideo for video file
class MetadataVideo : public Metadata{
    std::string mSize;
public:
    MetadataVideo(std::string);
    std::string getInf() const override;
};


#endif