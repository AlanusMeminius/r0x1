#include "app.h"
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QThread>
#include <aria2.h>

App::App()
    : ui(std::make_unique<Ui::BaseWindow>()),
      setting(std::make_unique<Core::AppSetting>()) {
    QString dir = QDir::currentPath();
    qDebug() << dir;
    activateStylesheet(false);
    setSignalsSlot();
    ui->show();
    if (setting->loadAria2Setting()) {
        ui->loadSettingUi(setting->settingList);
    }
}

URLParser::Result App::processUrl() {
    static QString strLast;
    QString input = ui->getInputUrl();

    if (input == strLast) {
        return {};
    } else {
        strLast = input;
    }

    URLParser::URL url(strLast);
    return url.get();
}

void App::processSingleUrl() {
    URLParser::Result url = processUrl();
    auto path = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
    qDebug()<<"GUI thread = "<<QThread::currentThreadId();
    if (!url.urls.isEmpty()) {
        aria2Controller = std::make_unique<Aria2::Aria2Controller>();
        aria2Controller->addTaskInfo(url.urls, path.at(0));
    }
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
void App::activateStylesheet(bool dark) {
    if (styleSheetContent.isNull()) {
        getStyleSheetContent();
    }
    if (!styleSheetContent.isEmpty()) {
        QStringList lines = styleSheetContent.split('\n');
        const auto removeLine = [dark](const QString &line) {
            if (line.contains("[DARK]"))
                return !dark;
            else if (line.contains("[LIGHT]"))
                return dark;
            return false;
        };
        lines.removeIf(removeLine);
        ui->setStyleSheet(lines.join('\n'));
    }
}
void App::setSignalsSlot() {
    connect(AppEvent::getInstance(), &AppEvent::themeIndexChange, [this](int which) {
        if (which < 2) {
            ColorRepository::setDarkMode(which);
            activateStylesheet(which);
        }
    });
    connect(AppEvent::getInstance(), &AppEvent::addTaskAction, this, &App::processSingleUrl);

}
void App::getStyleSheetContent() {
    QFile file(QString(":/res/style.qss"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&file);
    styleSheetContent = in.readAll();
}

