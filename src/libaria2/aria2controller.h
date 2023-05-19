#pragma once
#include "aria2worker.h"
#include "core/appevent.h"
#include <QObject>
#include <QThread>

namespace Aria2 {

class Aria2Controller : public QObject {
    Q_OBJECT
    QThread workerThread;

   public:
    explicit Aria2Controller();
    ~Aria2Controller() override;

   signals:
    void addTaskInfo(const QUrl &url, const QDir &dir);
};

}// namespace Aria2
