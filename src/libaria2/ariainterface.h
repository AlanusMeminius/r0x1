/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/5/4 14:09
* @description: 
*/
#pragma once
#include "aria2.h"
#include <QFuture>
#include <QUrl>
//#include <SQLiteCpp/SQLiteCpp.h>
//#include <QtSql/QSqlDatabase>
//#include <QtSql/QSqlTableModel>

namespace Aria2 {
class [[maybe_unused]] AriaInterface {
   public:
    enum status {
        stopped,
        paused,
        downloading,
        completed
    };

   private:
    aria2::Session *ariaSession;
    aria2::SessionConfig ariaSessionconfig;
//    std::vector<std::string> ariaUris;
    aria2::KeyVals ariaOptions;
    QFuture<void> ariaFuture;
    QString formatDownSpeed(int64_t bytesPerSec);
    bool ariaLoopExit = false;
//    QSqlDatabase db;


   public:
    explicit AriaInterface();
    int eventCallback(aria2::Session *session, aria2::DownloadEvent event, aria2::A2Gid gid);

    void ariaLoop();
    void addDownload(const QUrl &url, const QString &path);
};
}// namespace Aria2
