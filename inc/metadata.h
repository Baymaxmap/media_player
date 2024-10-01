#ifndef METADATA_H
#define METADATA_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <taglib/tag.h>
#include <taglib/fileref.h>

//general metadata for media file
class Metadata{
protected:
    std::string mPath;
    std::unordered_map<std::string, std::string> mMetadata;
public:
    Metadata(std::string);
    virtual std::string getInf() const;
    std::string getName() const;
    std::string getPath() const;
    void updateMetadata(std::string, std::string);
    void updateMetadata(std::string, int);
};

//class MetadataAudio for audio file
class MetadataAudio : public Metadata{
public:
    MetadataAudio(std::string);
    std::string getInf() const override;
};

//class MetadataVideo for video file
class MetadataVideo : public Metadata{
public:
    MetadataVideo(std::string);
    std::string getInf() const override;
};


#endif