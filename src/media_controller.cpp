#include "media_controller.h"

MediaController::MediaController(std::shared_ptr<MediaFile> mediaFile, std::shared_ptr<ViewMedia> view)
    : mMediaFile(mediaFile), mViewMediaFile(view){}

//get the inf of MediaFile
std::string MediaController::getInfMedia() const{
    return mMediaFile->getInfMedia();
}

//update view for media file
void MediaController::updateView() const{
    mViewMediaFile->showMediaInf(mMediaFile->getInfMedia());
}
