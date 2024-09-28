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
    MediaFile(std::string);
    std::string getInfMedia() const;
    void updateMetadata(std::string, std::string);
    void updateMetadata(std::string, int);
};


#endif