/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/21 22:49
* @description: 
*/
#include "app.h"
#include "parser/url.h"
#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QStandardPaths>
#include <aria2.h>
#include <sys/time.h>

App::App()
    : ui(std::make_unique<Ui::BaseWindow>()),
      setting(std::make_unique<Core::AppSetting>()) {
    QString dir = QDir::currentPath();
//    QList<QString> doc = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    qDebug() << dir;

    ui->show();
    if (setting->loadAria2Setting()) {
        ui->loadSettingUi(setting->settingList);
    }
    //    setting->loadAria2Setting();
    //    aria2::libraryInit();
    //    aria2::Session *session;
    //    // Create default configuration. The libaria2 takes care of signal
    //    // handling.
    //    aria2::SessionConfig config;
    //    session = aria2::sessionNew(aria2::KeyVals(), config);
    //
    //    auto option = aria2::getGlobalOptions(session);
    //    for (auto v : option) {
    //        qDebug() << '"'<< v.first.data() << '"' << ',';
    //    }
}

void App::processUrl() {
    static QString strLast;
    QString input = ui->getInputUrl();

    if (input == strLast) {
        return;
    } else
        strLast = input;

    URLParser::URL url(strLast.toStdString());
    URLParser::Result result = url.get();
}
#if 0
void App::loadSetting() {
    QSettings settings("0x1","R0x1");
    lastDirectory = settings.value("LastDirectory").toString();
    if (lastDirectory.isEmpty()) {
        lastDirectory = QDir::currentPath();
    }
    int up = settings.value("UploadLimit").toInt();
    int down = settings.value("DownloadLimit").toInt();

    // TODO 恢复之前的下载
}
#endif
void App::saveSetting() {
    if (!saveChanges) {
        return;
    }
    saveChanges = false;
}
