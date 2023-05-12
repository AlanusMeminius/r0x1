#pragma once
#include "../core/launcher.h"
#include <QGridLayout>
#include <QWidget>

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