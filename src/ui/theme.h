/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/22 16:49
* @description: 
*/
#pragma once
#include <QFile>
#include <QIcon>
#include <QMap>
#include <QPalette>
#include <QString>
#include <QTextStream>
#include <utility>
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
    static inline QIcon icon(const QString &name) {
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

    static bool isDarkTheme() {
        const QPalette defaultPalette;
        return (defaultPalette.color(QPalette::WindowText).lightness() > defaultPalette.color(QPalette::Window).lightness());
    };

    //    static const QColor b = (isDarkTheme()) ? dBackground : lBackground;
    //     struct color {
    //        static QColor background = (isDarkTheme()) ? dBackground : lBackground;
    //        QColor btn = (isDarkTheme()) ? dBtn : lBtn;
    //        QColor btnName = (isDarkTheme()) ? dBtnName : lBtnName;
    //    };
};
//static  QColor background = (isDarkTheme()) ? dBackground : lBackground;