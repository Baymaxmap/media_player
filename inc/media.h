#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>

//General
class MediaFile{
    int mYear;
    int mDuration;
    std::string mPath;
    std::string mName;
    std::string mArtist;
    std::string mComment;
public:
    MediaFile(std::string);
    virtual std::string getInf() const;
};


//class AudioFile derived from MediaFile adding some more features
class AudioFile : public MediaFile{
    int mSampleRate;
    int mBitRate;
    int mChannel;
public:
    AudioFile(std::string);
    std::string getInf() const override;
};


//class VideoFile derived from MediaFile adding some more features
class VideoFile : public MediaFile{
    std::string mSize;
    std::string mDuration;
public:
    VideoFile(std::string);
    std::string getInf() const override;
};

#endif