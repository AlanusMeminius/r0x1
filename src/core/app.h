#pragma once
#include "core/appevent.h"
#include "core/setting.h"
#include "core/task.h"
#include "libaria2/aria2controller.h"
#include "parser/parser.h"
#include "parser/url.h"
#include "ui/basewindow.h"
#include "ui/theme.h"
#include <QObject>

class App : public QObject {
    Q_OBJECT
   public:
    explicit App();
    URLParser::Result processUrl();
    typedef std::shared_ptr<Core::Task> TaskPtr;

   private:
    std::unique_ptr<Ui::BaseWindow> ui;
    std::unique_ptr<Core::AppSetting> setting;
    std::unique_ptr<Aria2::Aria2Controller> aria2Controller;

   private:
    //  void loadSetting();
    void saveSetting();
    void activateStylesheet(bool);
    void setSignalsSlot();
    void getStyleSheetContent();

   private:
    QString lastDirectory;
    QString styleSheetContent;
    QList<TaskPtr> taskList;

    bool saveChanges{};
   signals:

   private slots:
    void processSingleUrl();
};
