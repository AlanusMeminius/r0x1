
#pragma once
#include "ui/components/horizonnavigation.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class AddPageDefaultSetting : public QWidget {
    Q_OBJECT
   public:
    explicit AddPageDefaultSetting(QWidget *parent = nullptr);

    QGridLayout *layout;
    QLabel *pathLabel;
    QLineEdit *path;
    QLabel *renameLabel;
    QLineEdit *renamePath;

    QPushButton *cancel;
    QPushButton *confirm;

};

class AddPage final : public QWidget {
    Q_OBJECT
   public:
    explicit AddPage(QWidget *parent = nullptr);

    QGridLayout *addPageMainLayout;
    QLabel *addLabel;
    QLineEdit *urlInput;
    QPushButton *actionButton;

    HorizonNavigation *horizonNavigation;

    QStackedWidget *stackedWidget;
    AddPageDefaultSetting *addPageDefaultSetting;
    QLabel *msg;

};


}// namespace Ui
