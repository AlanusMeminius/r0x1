#include "task.h"
#include <utility>

namespace Core {

Task::Task(QString name, QString url, QString dir, QString gid, int status, int progress, double speed)
    : m_name(std::move(name)),
      m_url(std::move(url)),
      m_dir(std::move(dir)),
      m_gid(std::move(gid)),
      m_status(status),
      m_progress(progress),
      m_speed(speed) {
}

}// namespace Core