#include "commonsetting.h"
#include "ui/theme.h"
#include <QComboBox>
namespace Ui {
CommonSetting::CommonSetting(QWidget *parent)
    : QWidget(parent),
      mainLayout(new QGridLayout),
      appearance(new QLabel),
      autoLabelPic(new CheckableSvgLabel),
      darkLabelPic(new CheckableSvgLabel),
      lightLabelPic(new CheckableSvgLabel) {

    this->setObjectName("CommonSetting");
    this->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);

    appearance->setText("Appearance");
    appearance->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(appearance, 0, 0, 2, 2);

    mainLayout->addWidget(lightLabelPic, 0, 2, 4, 3);
    mainLayout->addWidget(darkLabelPic, 0, 5, 4, 3);
    mainLayout->addWidget(autoLabelPic, 0, 8, 4, 3);

    lightLabelPic->setSvg("light", {80, 50});
    darkLabelPic->setSvg("dark", {80, 50});
    autoLabelPic->setSvg("auto", {80, 50});

    auto lightLabelText = new QLabel("Light");
    auto darkLabelText = new QLabel("Dark");
    auto autoLabelText = new QLabel("Auto");
    lightLabelText->setAlignment(Qt::AlignCenter);
    darkLabelText->setAlignment(Qt::AlignCenter);
    autoLabelText->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(lightLabelText, 6, 2, 1, 3);
    mainLayout->addWidget(darkLabelText, 6, 5, 1, 3);
    mainLayout->addWidget(autoLabelText, 6, 8, 1, 3);

    auto accentColorLabel = new QLabel("Accent Color");
    accentColorLabel->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(accentColorLabel, 7, 0, 2, 2);

    auto line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    //    line->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(line, 9, 0, 1, 20);

    auto language = new QLabel("Language");
    language->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(language,10,0,2,2);

    auto languageComboBox = new QComboBox(this);
    mainLayout->addWidget(languageComboBox,10,3,2,5);

    auto systemTray = new QLabel("SystemTray");
    systemTray->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(systemTray,12,0,2,2);


}
}// namespace Ui