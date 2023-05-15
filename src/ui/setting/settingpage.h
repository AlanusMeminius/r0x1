#pragma once
#include "core/setting.h"
#include "ui/setting/commonsetting.h"
#include "ui/components/horizonnavigation.h"
#include "ui/setting/settingdelegate.h"
#include <QLabel>
#include <QListView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QWidget>
#include <QPushButton>
namespace Ui {

class Aria2SettingList : public QListView {
    Q_OBJECT
   public:
    explicit Aria2SettingList(QWidget *parent = nullptr);

   private:
    SettingItemDelegate *settingItemDelegate;
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
    QScrollArea *commonSettingScrollArea;
    CommonSetting *commonSetting;
    Aria2SettingList *settingList;
};

}// namespace Ui
