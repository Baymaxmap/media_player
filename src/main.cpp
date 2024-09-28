#include "media.h"
#include "view_media.h"
#include "media_controller.h"

int main(){
    std::string path;
    std::shared_ptr<MediaFile> mediafile1
    = std::make_shared<MediaFile>("/home/thanhtb5/Documents/FPT/OJT_FRESHER/STUDY_APP/VSCODE/taglib/audio_file/ok.mp3");
    std::shared_ptr<ViewMedia> viewMedia1 = std::make_shared<ViewMedia>();
    MediaController controller1(mediafile1, viewMedia1);
    controller1.updateView();
    controller1.updateMediaFile("Title", "like i used to see u long long time");
    controller1.updateView();
}

