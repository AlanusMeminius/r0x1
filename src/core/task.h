#pragma once
#include "util/qvarianthelper.h"
#include <QDir>
#include <QString>
#include <QUrl>
#include <utility>

namespace Core
{
  typedef uint64_t Gid;
  struct Status {
    QVARIANTMACRO
    //    Core::Status &operator=(const Core::Status &rhs) {
    //        if (this == &rhs) {
    //            return *this;
    //        }
    //        gid = rhs.gid;
    //        totalLength = rhs.totalLength;
    //        completedLength = rhs.completedLength;
    //        uploadSpeed = rhs.uploadSpeed;
    //        return *this;
    //    };
    Gid gid;
    int64_t totalLength;
    int64_t completedLength;
    int downloadSpeed;
    int uploadSpeed;
  };

  class Task {
    QVARIANTMACRO
   public:
    explicit Task () = default;
    explicit Task (QUrl url, const QDir &dir, Gid gid) : m_url (std::move (url)), m_dir (dir), m_gid (gid){};
    [[nodiscard]] QString name () const { return m_url.fileName (); };
    [[nodiscard]] QString url () const { return m_url.url (); };
    [[nodiscard]] QString dir () const { return m_dir.absolutePath (); };
    [[nodiscard]] Gid gid () const { return m_gid; };
    void setName (QString name) { m_name = std::move (name); };
    int category ()
    {
      return 0;
    }
    Core::Status status{};

   private:
    Gid m_gid = 0;
    QUrl m_url;
    QDir m_dir;
    QString m_name;
  };

}// namespace Core
Q_DECLARE_METATYPE (Core::Task)
