#pragma once
#include "framelesswindow.h"

#include "../core/launcher.h"
namespace Platform {
class Launcher : public Core::Launcher {
   public:
    Launcher(int argc, char *argv[]);

   private:
//    bool launchUpdater(UpdaterLaunch action) override;

};

using FramelessWindow = FramelessWindow;
}// namespace Platform
