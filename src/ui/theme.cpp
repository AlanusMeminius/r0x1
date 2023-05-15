#include "theme.h"

void Theme::changeTheme(Theme::theme theme) {
    if (theme != currentTheme) {
        currentTheme = theme;
    }
}
QColor Ui::baseBackgroundColor() {
    return darkMode ? QColor(38, 38, 38) : QColor(235, 235, 235);
}
QColor Ui::baseFontColor() {
    return darkMode ? QColor(255, 255, 255) : QColor(0, 0, 0);
}
QColor Ui::horizonNavigationBackgroundColor() {
    return darkMode ? QColor(30, 30, 30) : QColor(229, 230, 235);
}
QColor Ui::horizonNavigationBtnColor() {
    return darkMode ? QColor(61, 61, 61) : QColor(255, 255, 255);
}
QColor Ui::horizonNavigationSelectedBtnFontColor() {
    return darkMode ? QColor(200, 200, 200) : QColor(87, 86, 89);
}
void Ui::setDark() {
    darkMode = true;
}
