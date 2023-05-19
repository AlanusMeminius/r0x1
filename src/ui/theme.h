#pragma once
#include <QFile>
#include <QIcon>
#include <QPixmap>
#include <QMap>
#include <QPalette>
#include <QString>
#include <utility>

namespace ColorRepository {
void setDarkMode(bool dark);
QPalette standardPalette();
QColor windowBackground();
QColor baseBackground();
QColor text();
QColor horizonNavigationBackgroundColor();
QColor horizonNavigationBtnColor();
QColor horizonNavigationSelectedBtnFontColor();
QColor aria2SettingItemBackgroundColor();
QColor aria2SettingThemeColor();
QColor switchBackgroundColor();
}
namespace Ui {
static constexpr QColor const dBackground = QColor(38, 38, 38);
static constexpr QColor const lBackground = QColor(235, 235, 235);
static constexpr QColor const dBtn = QColor(61, 61, 61);
static constexpr QColor const lBtn = QColor(255, 255, 255);
static constexpr QColor const dBtnName = QColor(255, 255, 255);
static constexpr QColor const lBtnName = QColor(0, 0, 0);

constexpr QColor const backgroundColor = lBackground;
constexpr QColor const btnColor = lBtn;
constexpr QColor const fontColor = lBtnName;

}// namespace Ui

class Theme {
   public:
    enum theme {
        Light,
        Dark,
        Auto
    };
    static QIcon icon(const QString &name) {
        return QIcon(QString(":/res/icons/%1.svg").arg(name));
    };
    static QPixmap pix(const QString &name, const QSize &size) {
      return  QIcon(QString(":/res/icons/%1.svg").arg(name)).pixmap(size);
    };
};
