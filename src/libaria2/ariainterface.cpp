/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/5/4 14:09
* @description: 
*/
#include "ariainterface.h"
#include <QDebug>
//#include <QtSql/QSqlError>
//#include <QtSql/QSqlQuery>
//#include <QtSql/QSqlRecord>


Aria2::AriaInterface::AriaInterface() {
//    db =  QSqlDatabase::addDatabase("SQLITE");
//    db.setDatabaseName("downloadTable");
//    db.open();
//    QSqlQuery query(db);
}

int Aria2::AriaInterface::eventCallback(aria2::Session *session, aria2::DownloadEvent event, aria2::A2Gid gid) {
    return 0;
}
void Aria2::AriaInterface::ariaLoop() {
}
void Aria2::AriaInterface::addDownload(const QUrl &url, const QString &path) {
    aria2::KeyVals options;
    aria2::A2Gid gid;

    options.emplace_back("dir", path.toStdString());
//    std::vector<std::string> ariaUris = {url.toString().toStdString()};
    int flag = aria2::addUri(ariaSession, &gid, {url.toString().toStdString()}, options);
    if (flag != 0) {
        qDebug() << "failed";
    } else {
        // TODO 更新界面
    }
}
