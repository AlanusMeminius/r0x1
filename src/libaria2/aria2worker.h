#pragma once
#include "aria2.h"
#include "core/task.h"
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QTimer>
#include <QThread>

namespace Aria2 {
class Aria2Worker : public QObject {
    Q_OBJECT
public:
    explicit Aria2Worker();
    ~Aria2Worker() override;
    Aria2Worker(const Aria2Worker &) = delete;
    Aria2Worker &operator=(const Aria2Worker &) = delete;

public:
    typedef aria2::A2Gid Gid;
    typedef aria2::KeyVals Options;
    typedef std::unique_ptr<aria2::DownloadHandle> dhPtr;
    inline static aria2::Session *session = nullptr;

public:
    int eventCallback(aria2::Session *session, aria2::DownloadEvent event, Gid gid);

private:
    static int downloadEventCallBack(aria2::Session *session, aria2::DownloadEvent event, Gid gid, void *userData);
    static int run(aria2::RUN_MODE mode = aria2::RUN_ONCE);
    std::pair<int, Gid>
    addDownload(const std::vector<std::string> &uris, const Options &options = {}, int position = -1);
    bool aria2Exit = false;
    QMutex m_lock;

public:
    int stPosition(Gid gid, int pos, aria2::OffsetMode how);
    int changeGlobalOption(const Options &options);
    static int remove(Gid gid, bool force = false);
    static int pause(Gid gid, bool force = false);
    static int showDown(bool force = false);
    static dhPtr getDownloadHandle(Gid gid);

signals:
    void addTaskItemToUi(const QVariant &);
    void updateTaskInfoToUi(const QVariant &);
    void downloadComplete();

public slots:
    void doDownloadWork(const QUrl &url, const QDir &dir);
    void stopThread();
};
}// namespace Aria2
