#pragma once
#include "SimpleIni.h"
#include "util/qvarianthelper.h"
#include <QMap>
#include <QSettings>
#include <QString>
#include <utility>
namespace Core {

class SettingItem {
    QVARIANTMACRO
   public:
   public:
    enum Unit {
        None,
        Number,
        Bool
    };
    explicit SettingItem() = default;
    explicit SettingItem(QString key, QString value, Unit unit = None)
        : m_key(std::move(key)),
          m_value(std::move(value)),
          m_unit(unit){};

    QString key() { return m_key; };
    QString value() { return m_value; };
    Unit unit() { return m_unit; };

    void setKey(QString key) { m_key = std::move(key); };
    void setValue(QString value) { m_value = std::move(value); };
    void setUnit(Unit unit) { m_unit = unit; };

//    SettingItem(const SettingItem &rhs) { operator=(rhs); }
//    SettingItem &operator=(const SettingItem &rhs) = default;

   private:
    QString m_key;
    QString m_value;
    Unit m_unit = None;
};

class AppSetting {
   public:
    typedef std::shared_ptr<SettingItem> SettingItemPtr;
    explicit AppSetting() = default;

   public:
    bool loadAria2Setting();
    QList<SettingItemPtr> settingList;
    static QList<SettingItemPtr> getDefaultSettings() { return DefaultSettings; };

   private:
    static const QList<SettingItemPtr> DefaultSettings;
};

}// namespace Core
Q_DECLARE_METATYPE(Core::SettingItem)