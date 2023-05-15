#include "appevent.h"
AppEvent *AppEvent::m_appEvent_ptr=nullptr;
QMutex AppEvent::m_mutex;

AppEvent *AppEvent::getInstance()
{
    if (nullptr == m_appEvent_ptr){
        m_mutex.lock();
        if (nullptr == m_appEvent_ptr){
            m_appEvent_ptr = new AppEvent;
        }
        m_mutex.unlock();
    }
    return m_appEvent_ptr;
}
AppEvent::AppEvent(QObject *parent) : QObject(parent)
{
}