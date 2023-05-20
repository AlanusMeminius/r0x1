#include "aria2worker.h"

namespace Aria2 {
int Aria2Worker::downloadEventCallBack(aria2::Session *session, aria2::DownloadEvent event, Gid gid, void *userData)
{
    return static_cast<Aria2Worker *>(userData)->eventCallback(session, event, gid);
}

int Aria2Worker::eventCallback(aria2::Session *session, aria2::DownloadEvent event, Gid gid)
{
    switch (event) {
    case aria2::EVENT_ON_DOWNLOAD_START:
        qDebug() << "start";
        break;
    case aria2::EVENT_ON_DOWNLOAD_PAUSE:
        qDebug() << "pause";
        break;
    case aria2::EVENT_ON_DOWNLOAD_STOP:
        qDebug() << "stop";
        break;
    case aria2::EVENT_ON_DOWNLOAD_COMPLETE:
        qDebug() << "complete";
        emit downloadComplete();
        break;
    case aria2::EVENT_ON_DOWNLOAD_ERROR:
        qDebug() << "error";
        break;
    case aria2::EVENT_ON_BT_DOWNLOAD_COMPLETE: break;
    default: return 0;
    }
    return 0;
}
Aria2Worker::Aria2Worker()
{
    aria2::libraryInit();
    aria2::SessionConfig config;
    config.keepRunning = true;
    config.useSignalHandler = false;
    config.userData = this;
    config.downloadEventCallback = downloadEventCallBack;
    session = aria2::sessionNew(aria2::KeyVals(), config);
}
Aria2Worker::~Aria2Worker()
{
    aria2::sessionFinal(session);
    aria2::libraryDeinit();
    qDebug() << "aria2 library dead";
}
int Aria2Worker::stPosition(Gid gid, int pos, aria2::OffsetMode how)
{
    return aria2::changePosition(session, gid, pos, how);
}

int Aria2Worker::changeGlobalOption(const Options &options)
{
    return aria2::changeGlobalOption(session, options);
}

std::pair<int, Aria2Worker::Gid>
Aria2Worker::addDownload(const std::vector<std::string> &uris, const Options &options, int position)
{
    Gid id;
    auto rv = aria2::addUri(session, &id, uris, options, position);
    return std::pair{rv, id};
}

int Aria2Worker::run(aria2::RUN_MODE mode)
{
    return aria2::run(session, mode);
}

int Aria2Worker::pause(Aria2Worker::Gid gid, bool force)
{
    return aria2::pauseDownload(session, gid, force);
}

int Aria2Worker::remove(Aria2Worker::Gid gid, bool force)
{
    return aria2::removeDownload(session, gid, force);
}

int Aria2Worker::showDown(bool force)
{
    return aria2::shutdown(session, force);
}

Aria2Worker::dhPtr Aria2Worker::getDownloadHandle(Gid gid)
{
    return std::unique_ptr<aria2::DownloadHandle>(aria2::getDownloadHandle(session, gid));
}
void Aria2Worker::doDownloadWork(const QUrl &url, const QDir &dir)
{
    qDebug()<<"aria2 thread = "<<QThread::currentThreadId();
    qDebug() << "start download";
    Options options;
    std::vector<std::string> uris = {url.toString().toStdString()};
    options.emplace_back(std::make_pair("dir", dir.absolutePath().toStdString()));
    auto [rv, gid] = addDownload(uris, options);
    if (rv != 0) {
        qDebug() << "add failed";
        return;
    } else {
        QVariant task = Core::Task(url, dir, gid);
        emit addTaskItemToUi(task);
    }
    auto start = std::chrono::steady_clock::now();
    for (rv = 0; (rv = this->run()) == 1;) {
        auto now = std::chrono::steady_clock::now();
        auto count = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
        if (count >= 750) {
            start = now;
            for (auto id : aria2::getActiveDownload(session)) {
                auto downloadHandle = getDownloadHandle(id);
                if (downloadHandle) {
                    QVariant status = Core::Status{
                        id,
                        downloadHandle->getTotalLength(),
                        downloadHandle->getCompletedLength(),
                        downloadHandle->getDownloadSpeed(),
                        downloadHandle->getUploadSpeed()};
                    emit updateTaskInfoToUi(status);
                }
            }
        }
        {
            QMutexLocker lock(&m_lock);
            if (aria2Exit) {
                qDebug() << "aria2 update loop exit";
                break ;
            }
        }
    }
}
void Aria2Worker::stopThread()
{
    qDebug()<<"Exec aria2 thread = "<<QThread::currentThreadId();
    QMutexLocker lock(&m_lock);
    aria2Exit = true;
}

}// namespace Aria2
