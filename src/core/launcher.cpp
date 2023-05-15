#include "launcher.h"
#include "platform/platform.h"
#include "QApplication"
#include "app.h"

namespace Core {
Launcher::Launcher(int argc, char *argv[])
    : _argc(argc), _argv(argv) {
}

std::unique_ptr<Launcher> Launcher::Create(int argc, char *argv[]) {
    return std::make_unique<Platform::Launcher>(argc, argv);
}

int Launcher::exec() {
    initHighDpi();
    //TODO prepare setting ,log

    QApplication a(_argc, _argv);
    QApplication::setApplicationName("R0x1");

    App app;
    QApplication::setWindowIcon(Theme::icon("hippo"));
    return QApplication::exec();
}
void Launcher::initHighDpi() {
    QApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
}

// TODO init log
}// namespace Core
