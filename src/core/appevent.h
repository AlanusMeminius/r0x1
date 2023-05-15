#pragma once
#include <QObject>
#include <QMutex>
#include <QSharedPointer>

class AppEvent :public QObject{
    Q_OBJECT
   public:
    static AppEvent *getInstance();
   public:
    explicit AppEvent(QObject *parent = nullptr);
    AppEvent& operator =(AppEvent&) = delete;
    AppEvent(AppEvent&) = delete;

   private:
    static AppEvent *m_appEvent_ptr;
    static QMutex m_mutex;

   public slots:
    signals:


};
