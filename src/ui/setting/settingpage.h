#pragma once
#include "advancedsetting.h"
#include "aria2settingdelegate.h"
#include "commonsetting.h"
#include "core/setting.h"
#include "ui/components/horizonnavigation.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QWidget>
namespace Ui {

class Aria2SettingList : public QListView {
    Q_OBJECT
   public:
    explicit Aria2SettingList(QWidget *parent = nullptr);

   private:
    Aria2SettingItemDelegate *settingItemDelegate;
    QStandardItemModel *model;

   public:
    void loadSetting(const QList<Core::AppSetting::SettingItemPtr> &setting);

   public slots:
    void itemClicked(const QModelIndex &index);
};

class SettingPage : public QWidget {
    Q_OBJECT
   public:
    explicit SettingPage(QWidget *parent = nullptr);

    QVBoxLayout *settingPageLayout;
    QLabel *titleLabel;
    QHBoxLayout *navigationLayout;
    HorizonNavigation *horizonNavigation;
    QPushButton *defaultBtn;
    QPushButton *saveBtn;
    QStackedWidget *stackedWidget;
    CommonSetting *commonSetting;
    AdvancedSetting *advancedSetting;
    Aria2SettingList *settingList;
};

}// namespace Ui
