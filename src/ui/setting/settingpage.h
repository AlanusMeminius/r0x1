/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/30 16:09
* @description: 
*/
#pragma once
#include "core/setting.h"
#include "ui/components/horizonnavigation.h"
#include "ui/setting/delegate.h"
#include <QLabel>
#include <QListView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {

class SettingList : public QListView {
    Q_OBJECT
   public:
    explicit SettingList(QWidget *parent = nullptr);

   private:
    SettingItemDelegate *settingItemDelegate;
    QStandardItemModel *model;

   public:
    void loadSetting(const QList<Core::AppSetting::SettingItemPtr> &setting);
};

class SettingPage : public QWidget {
    Q_OBJECT
   public:
    explicit SettingPage(QWidget *parent = nullptr);

    QVBoxLayout *settingPageLayout;
    QLabel *titleLabel;
    HorizonNavigation *horizonNavigation;
    SettingList *settingList;
};

}// namespace Ui
