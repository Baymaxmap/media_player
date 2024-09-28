#ifndef MEDIA_CONTROLLER_H
#define MEDIA_CONTROLLER_H

#include <memory>

#include "media.h"
#include "view_media.h"

class MediaController{
    std::shared_ptr<MediaFile> mMediaFile;
    std::shared_ptr<ViewMedia> mViewMediaFile;
public:
    MediaController(std::shared_ptr<MediaFile>, std::shared_ptr<ViewMedia>);
    std::string getInfMedia() const;                //get the inf of Media file using MediaFile pointer
    void updateMediaFile(std::string, std::string); //update the inf of media file
    void updateMediaFile(std::string, int);     
    void updateView() const;
};

#endif