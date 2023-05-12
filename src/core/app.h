/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/21 22:49
* @description: 
*/
#pragma once
#include "setting.h"
#include "ui/basewindow.h"
#include <QObject>
#include <QSettings>

class App : public QObject {
  Q_OBJECT
 public:
  explicit App();
  void processUrl();
 private:
  std::unique_ptr<Ui::BaseWindow> ui;
  std::unique_ptr<Core::AppSetting> setting;
 private:
//  void loadSetting();
  void saveSetting();

 private:
  QString lastDirectory;

  bool saveChanges{};
};
