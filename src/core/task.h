/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/5/8 09:16
* @description: 
*/
#pragma once
#include "../util/qvarianthelper.h"
#include <QString>

//#define QVARIANTMACRO \
//   public:            \
//    inline operator QVariant() const { return QVariant::fromValue(*this); }

namespace Core {
class Task {
    QVARIANTMACRO
   public:
    Task() = default;
    Task(QString name, QString url, QString dir, QString gid, int status, int progress, double speed);
    QString name() const { return m_name; };
    QString url() const { return m_url; };
    QString dir() const { return m_dir; };
    QString gid() const { return m_gid; }
    int status() const { return m_status; };
    int progress() const { return m_progress; };
    double speed() const { return m_speed; };

   private:
    QString m_name;
    QString m_url;
    QString m_dir;
    QString m_gid;
    double m_speed = 0;
    int m_status = 0;
    int m_progress = 0;
};

}// namespace Core
Q_DECLARE_METATYPE(Core::Task)
