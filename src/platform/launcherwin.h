#pragma once
#include <QGridLayout>
#include <QWidget>
#include "../core/launcher.h"

namespace Platform {
class Launcher : public Core::Launcher {
   public:
    Launcher(int argc, char *argv[]);
};

class FramelessWindow : public QWidget {
    Q_OBJECT
   public:
    QWidget *centralWidget;
    QGridLayout *layout;

    explicit FramelessWindow(QWidget *parent);
};
}// namespace Platform
