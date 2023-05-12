/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/5/9 21:22
* @description: 
*/
#include "helppage.h"

namespace Ui {
HelpPage::HelpPage(QWidget *parent)
    : QWidget(parent),
      mainLayout(new QVBoxLayout),
      titleLabel(new QLabel),
      horizonNavigation(new HorizonNavigation(parent)) {
    this->setLayout(mainLayout);
    this->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(titleLabel);
    titleLabel->setText("Help");
    titleLabel->setObjectName("HelpLabel");

    QStringList horizonNavigationBtn;
    horizonNavigationBtn << "Manual"
                         << "Configuration"
                         << "Problem";
    horizonNavigation->addItems(horizonNavigationBtn);
    mainLayout->addWidget(horizonNavigation);
}
}// namespace Ui