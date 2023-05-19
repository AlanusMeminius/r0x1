#include "settingpage.h"
#include "core/setting.h"

namespace Ui {
SettingPage::SettingPage(QWidget *parent)
    : QWidget(parent),
      settingPageLayout(new QVBoxLayout(this)),
      titleLabel(new QLabel(this)),
      navigationLayout(new QHBoxLayout),
      horizonNavigation(new HorizonNavigation(this)),
      defaultBtn(new QPushButton),
      saveBtn(new QPushButton),
      stackedWidget(new QStackedWidget),
      commonSetting(new CommonSetting),
      advancedSetting(new AdvancedSetting),
      settingList(new Aria2SettingList) {
    setAttribute(Qt::WA_StyledBackground, true);
    this->setLayout(settingPageLayout);
    this->setObjectName("SettingPage");
    titleLabel->setObjectName("SettingLabel");
    settingPageLayout->addWidget(titleLabel);
    titleLabel->setText("Setting");

    settingPageLayout->addLayout(navigationLayout);
    horizonNavigation->setObjectName("SettingPageNavigation");
    navigationLayout->addWidget(horizonNavigation);
    QStringList horizonNavigationBtn;
    horizonNavigationBtn << "Common"
                         << "Advanced"
                         << "Aria2";
    horizonNavigation->addItems(horizonNavigationBtn);
    navigationLayout->addWidget(defaultBtn);
    defaultBtn->setObjectName("DefaultBtn");
    defaultBtn->setText("Default");
    navigationLayout->addWidget(saveBtn);
    saveBtn->setObjectName("SaveBtn");
    saveBtn->setText("Save");

    settingPageLayout->addWidget(stackedWidget);
    stackedWidget->setObjectName("SettingStackedWidget");

    stackedWidget->addWidget(commonSetting);
    stackedWidget->addWidget(advancedSetting);
    stackedWidget->addWidget(settingList);

    connect(horizonNavigation, &HorizonNavigation::currentItemChanged, stackedWidget, &QStackedWidget::setCurrentIndex);
}

Aria2SettingList::Aria2SettingList(QWidget *parent)
    : QListView(parent),
      model(new QStandardItemModel),
      settingItemDelegate(new Aria2SettingItemDelegate) {
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setObjectName("Aria2SettingList");
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setItemDelegate(settingItemDelegate);
    this->setModel(model);
    this->setContentsMargins(0, 0, 0, 0);
    this->setSpacing(2);

    connect(this, &QListView::clicked, this, &Aria2SettingList::itemClicked);
}
void Aria2SettingList::loadSetting(const QList<Core::AppSetting::SettingItemPtr> &setting) {
    for (const auto &singleSettingItem : setting) {
        auto *pItem = new QStandardItem;
        qDebug() << singleSettingItem->value();
        pItem->setData(*singleSettingItem, Qt::UserRole + 1);
        model->appendRow(pItem);
    }
}
void Aria2SettingList::itemClicked(const QModelIndex &index) {
    if (!index.isValid())
        return;
    const auto &data = index.data(Qt::UserRole + 1);
    if (data.isNull())
        return;
    auto setting = data.value<Core::SettingItem>();
    if (setting.unit() == Core::SettingItem::Bool) {
        QRectF itemRect = this->visualRect(index).toRectF();
        int mouseX = this->mapFromGlobal(QCursor::pos()).x();
        if (setting.value().contains("true", Qt::CaseInsensitive)) {
            if (mouseX >= itemRect.x() + 247 && mouseX <= itemRect.x() + 267) {
                setting.setValue("false");
                model->setData(index, setting, Qt::UserRole + 1);
            }
        } else if (mouseX >= itemRect.x() + 227 && mouseX <= itemRect.x() + 247) {
            setting.setValue("true");
            model->setData(index, setting, Qt::UserRole + 1);
        }
    }
}
}// namespace Ui