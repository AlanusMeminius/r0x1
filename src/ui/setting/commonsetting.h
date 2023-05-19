#pragma once
#include "commonswitchbtn.h"
#include "themeswitchbtn.h"
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
namespace Ui {


class CommonSetting : public QWidget {
    Q_OBJECT
   public:
    explicit CommonSetting(QWidget *parent = nullptr);

   public:
    ThemeSwitchBtn *themeSwitchBtn;
};

}// namespace Ui
