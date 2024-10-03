#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>
#include <memory>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>

#include "metadata.h"

//General
class MediaFile{
    std::string mPath;
    std::shared_ptr<Metadata> mMetadata;
public:
    MediaFile(std::string);                 //construct an object by passing file path
    std::string getInfMedia() const;
    std::string getPathMedia() const;
    std::string getNameMedia() const;
    std::string getDuration() const;
    
    void updateMetadata(std::string, std::string);  //key: field and value is year,...type of int
    void updateMetadata(std::string, int);
};


#endif