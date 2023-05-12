#include "launcherlinux.h"

namespace Platform {

Launcher::Launcher(int argc, char *argv[])
    : Core::Launcher(argc, argv) {
}

FramelessWindow::FramelessWindow(QWidget *parent)
    : QWidget(parent),
      centralWidget(new QWidget),
      layout(new QGridLayout) {

    this->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(centralWidget, 0, 0, 1, 1);
    layout->setSpacing(0);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_StyledBackground, true);
}
}// namespace Platform