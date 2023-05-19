#include "commonsetting.h"

#include "ui/theme.h"

namespace Ui {
CommonSetting::CommonSetting(QWidget *parent)
    : QWidget(parent),
      //      mainLayout(new QGridLayout(this)),
      themeSwitchBtn(new ThemeSwitchBtn(this)) {

    this->setObjectName("CommonSetting");
    this->setContentsMargins(0, 0, 0, 0);
    this->setMinimumWidth(300);
    auto mainLayout = new QGridLayout(this);
    this->setLayout(mainLayout);

    // ------
    auto appearanceLabel = new QLabel("Appearance");
    appearanceLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    appearanceLabel->setObjectName("AppearanceLabel");
    mainLayout->addWidget(appearanceLabel, 0, 0, 1, 1);
    mainLayout->addWidget(themeSwitchBtn, 0, 1, 2, 1);
    themeSwitchBtn->setMinimumHeight(80);
    // ------
    auto accentColorLabel = new QLabel("Accent Color");
    mainLayout->addWidget(accentColorLabel, 2, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    // ------
    auto language = new QLabel("Language");
    language->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(language, 3, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    auto languageComboBox = new QComboBox(this);
    languageComboBox->setPlaceholderText("English");
    mainLayout->addWidget(languageComboBox, 3, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    // ------
    auto systemTray = new QLabel("SystemTray");
    systemTray->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    mainLayout->addWidget(systemTray, 4, 0, 1, 1);
    auto enableSystemTray = new CommonSwitchBtn(this, "Enable SystemTray");
    mainLayout->addWidget(enableSystemTray, 4, 1, 1, 1);
    auto minimizeToSystemTray = new CommonSwitchBtn(parent, "Minimize to SystemTray");
    mainLayout->addWidget(minimizeToSystemTray, 5, 1, 1, 1);
    // -----
    auto startUpLabel = new QLabel("StartUp");
    startUpLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    mainLayout->addWidget(startUpLabel, 6, 0, 1, 1);
    auto openAtStartUp = new CommonSwitchBtn(this, "Open at StartUp");
    mainLayout->addWidget(openAtStartUp, 6, 1, 1, 1);
    auto keepSizeExit = new CommonSwitchBtn(this, "Keep size and position of the window when exit");
    mainLayout->addWidget(keepSizeExit, 7, 1, 1, 1);
    auto resumeTasks = new CommonSwitchBtn(this, "Automatically resume all unfinished tasks");
    mainLayout->addWidget(resumeTasks, 8, 1, 1, 1);

    auto defaultPath = new QLabel("DefaultPath");
    defaultPath->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(defaultPath, 9, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    auto defaultPathLineEdit = new QLineEdit;
    mainLayout->addWidget(defaultPathLineEdit, 9, 1, 1, 1);


    mainLayout->setColumnStretch(1, 1);
}

}// namespace Ui