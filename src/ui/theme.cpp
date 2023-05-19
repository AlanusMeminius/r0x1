#include "theme.h"
#include <QApplication>

static bool darkMode = false;

QPalette ColorRepository::standardPalette() {
    QPalette pal;
    pal.setColor(QPalette::Window, windowBackground());
    pal.setColor(QPalette::Base, baseBackground());
    pal.setColor(QPalette::WindowText, text());

    return pal;
}
QColor ColorRepository::windowBackground() {
    return darkMode ? QColor(53,53,53) : QColor(235, 235, 235);
}
QColor ColorRepository::baseBackground() {
    return darkMode ? QColor(53,53,53) : QColor(235, 235, 235);
}
QColor ColorRepository::text() {
    return darkMode ? QColor(145, 144, 143) : QColor(0, 0, 0);
}
void ColorRepository::setDarkMode(bool dark) {
    darkMode = dark;
    qApp->setPalette(standardPalette());
}
QColor ColorRepository::horizonNavigationBackgroundColor() {
    return darkMode ? QColor(45, 45, 45) : QColor(229, 230, 235);
}
QColor ColorRepository::horizonNavigationBtnColor() {
    return darkMode ? QColor(61, 61, 61) : QColor(255, 255, 255);
}
QColor ColorRepository::horizonNavigationSelectedBtnFontColor() {
    return darkMode ? QColor(200, 200, 200) : QColor(87, 86, 89);
}
QColor ColorRepository::aria2SettingItemBackgroundColor() {
    return darkMode ? QColor(87, 87, 87) : QColor(215, 215, 215);
}
QColor ColorRepository::aria2SettingThemeColor() {
    return darkMode ? QColor(96, 130, 182) : QColor(25, 179, 145);
}
QColor ColorRepository::switchBackgroundColor() {
    return darkMode ? QColor(47, 47, 47) : QColor(205, 205, 205);
}
