/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/30 16:09
* @description: 
*/
#include "settingpage.h"
#include "core/setting.h"

namespace Ui {
SettingPage::SettingPage(QWidget *parent)
    : QWidget(parent),
      settingPageLayout(new QVBoxLayout(this)),
      titleLabel(new QLabel(this)),
      horizonNavigation(new HorizonNavigation(this)),
      settingList(new SettingList) {
    setAttribute(Qt::WA_StyledBackground, true);
    this->setLayout(settingPageLayout);
    this->setObjectName("SettingPage");
    titleLabel->setObjectName("SettingLabel");
    settingPageLayout->addWidget(titleLabel);
    titleLabel->setText("Setting");

    horizonNavigation->setObjectName("SettingPageNavigation");
    settingPageLayout->addWidget(horizonNavigation);
    QStringList horizonNavigationBtn;
    horizonNavigationBtn << "Common"
                         << "Aria2";
    horizonNavigation->addItems(horizonNavigationBtn);
    settingPageLayout->addWidget(settingList);

    //    connect(horizonNavigation, &HorizonNavigation::currentItemChanged, stackedWidget, &QStackedWidget::setCurrentIndex);
}


SettingList::SettingList(QWidget *parent)
    : QListView(parent),
      model(new QStandardItemModel),
      settingItemDelegate(new SettingItemDelegate) {
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setObjectName("SettingList");
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setItemDelegate(settingItemDelegate);
    this->setModel(model);
}
void SettingList::loadSetting(const QList<Core::AppSetting::SettingItemPtr> &setting) {
    for (const auto &singleSettingItem : setting) {
        auto *pItem = new QStandardItem;
        qDebug() << singleSettingItem->value();
        pItem->setData(*singleSettingItem, Qt::UserRole + 1);
        model->appendRow(pItem);
    }
}
}// namespace Ui