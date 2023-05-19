#pragma once
#include "task.h"
#include <QDir>
#include <QMutex>
#include <QObject>
#include <QSharedPointer>
#include <QVariant>

class AppEvent : public QObject {
    Q_OBJECT
   public:
    static AppEvent *getInstance();

   public:
    explicit AppEvent(QObject *parent = nullptr);
    AppEvent &operator=(AppEvent &) = delete;
    AppEvent(AppEvent &) = delete;

   private:
    static AppEvent *m_appEvent_ptr;
    static QMutex m_mutex;

   public slots:
   signals:
    void themeIndexChange(int);
    void addTaskAction();
    void addTaskItemToUi(const QVariant &);
    void updateTaskInfoToUi(const QVariant&);
};
