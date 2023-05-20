#include "aria2controller.h"

namespace Aria2 {
Aria2Controller::Aria2Controller() : workerThread(new QThread), worker(new Aria2Worker)
{
    //    auto *worker = new Aria2Worker;
    worker->moveToThread(workerThread);
    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(workerThread, &QObject::destroyed, this, &Aria2Controller::setPtrNullptr);
    connect(worker, &QObject::destroyed, this, &Aria2Controller::setPtrNullptr);
    connect(worker, &Aria2Worker::downloadComplete, worker, &Aria2Worker::stopThread);

    connect(this, &Aria2Controller::addTaskInfo, worker, &Aria2Worker::doDownloadWork);
    connect(worker, &Aria2Worker::addTaskItemToUi, AppEvent::getInstance(), &AppEvent::addTaskItemToUi);
    connect(worker, &Aria2Worker::updateTaskInfoToUi, AppEvent::getInstance(), &AppEvent::updateTaskInfoToUi);
    workerThread->start();
}
Aria2Controller::~Aria2Controller()
{
    workerThread->quit();
    workerThread->wait();
}

void Aria2Controller::setPtrNullptr(QObject *sender)
{
    if (qobject_cast<QObject *>(workerThread) == sender) {
        workerThread = nullptr;
        qDebug() << "set workerThread = nullptr";
    }
    if (qobject_cast<QObject *>(worker) == sender) {
        worker = nullptr;
        qDebug() << "set worker = nullptr";
    }
}

}// namespace Aria2