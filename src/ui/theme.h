#pragma once
#include <QFile>
#include <QIcon>
#include <QMap>
#include <QPalette>
#include <QString>
#include <QTextStream>
#include <utility>

static bool darkMode = false;

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

void setDark();

QColor baseBackgroundColor();
QColor baseFontColor();

QColor horizonNavigationBackgroundColor();
QColor horizonNavigationBtnColor();
QColor horizonNavigationSelectedBtnFontColor();
}// namespace Ui

class Theme {
   public:
    enum theme {
        Light,
        Dark,
        Auto
    };
    void changeTheme(theme);
    static QIcon icon(const QString &name) {
        return QIcon(QString(":/res/icons/%1.svg").arg(name));
    };

    static QString styleContent(const QString &name) {
        QString qss;
        QFile file(QString(":/res/%1.qss").arg(name));
        if (file.open(QFile::ReadOnly)) {
            QStringList list;
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line;
                in >> line;
                list << line;
            }
            qss = list.join("\n");
            file.close();
        }
        return qss;
    };

   private:
    theme currentTheme;
};
//static  QColor background = (isDarkTheme()) ? dBackground : lBackground;