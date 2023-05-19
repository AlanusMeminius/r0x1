#include "aria2controller.h"

namespace Aria2 {
Aria2Controller::Aria2Controller() {
    auto *worker = new Aria2Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
//    connect(this,&Aria2Controller::addTaskInfo, worker, &Aria2Worker::doDownloadWork);
    connect(this,&Aria2Controller::addTaskInfo,[=](const QUrl &url, const QDir &dir){
        qDebug() << "Aria2Controller" << url.path() << dir.path();
        worker->doDownloadWork(url,dir);
    });
    connect(worker, &Aria2Worker::addTaskItemToUi, AppEvent::getInstance(), &AppEvent::addTaskItemToUi);
    connect(worker,&Aria2Worker::updateTaskInfoToUi,AppEvent::getInstance(),&AppEvent::updateTaskInfoToUi);
}
Aria2Controller::~Aria2Controller() {
    workerThread.quit();
    workerThread.wait();
}

}// namespace Aria2