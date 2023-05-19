#include "themeswitchbtn.h"
ThemeSwitchBtn::ThemeSwitchBtn(QWidget *parent) : QWidget(parent) {
    connect(this,&ThemeSwitchBtn::clickedIndexChange,AppEvent::getInstance(),&AppEvent::themeIndexChange);
}
void ThemeSwitchBtn::paintEvent(QPaintEvent *event) {
    //    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing);

    QSize btnSize(80, 50);
    QRectF rectF = event->rect().toRectF();
    QRectF lightRectF = QRectF(rectF.x() + 2, rectF.y() + 2, btnSize.width(), btnSize.height());
    QRectF darkRectF = lightRectF.adjusted(btnSize.width() + 5, 0, btnSize.width() + 5, 0);
    QRectF autoRectF = darkRectF.adjusted(btnSize.width() + 5, 0, btnSize.width() + 5, 0);
    painter.drawPixmap(
        lightRectF.toRect(),
        QIcon(QString(":/res/icons/light.svg")).pixmap(btnSize));
    painter.drawPixmap(
        darkRectF.toRect(),
        QIcon(QString(":/res/icons/dark.svg")).pixmap(btnSize));
    painter.drawPixmap(
        autoRectF.toRect(),
        QIcon(QString(":/res/icons/auto.svg")).pixmap(btnSize));

    QMap<QString, QRectF> text{
        {"Light", lightRectF.adjusted(0, 50, 0, 30)},
        {"Dark", darkRectF.adjusted(0, 50, 0, 30)},
        {"Auto", autoRectF.adjusted(0, 50, 0, 30)}};
    QStringList items{"Light", "Dark", "Auto"};

    for (int i = 0; i < 3; ++i) {
        if (checked == i) {
            painter.setPen(QPen(QBrush(QColor(52, 120, 246)), 1));
            painter.drawText(text[items[i]], Qt::AlignCenter, items[i]);
        } else {
            painter.setPen(QPen(Qt::gray, 1));
            painter.drawText(text[items[i]], Qt::AlignCenter, items[i]);
        }
    }
//        for (const auto [key, value] : text.asKeyValueRange()) {
//            if (checked != std::distance(text.begin(), text.lowerBound(key))) {
//                painter.setPen(QPen(Qt::gray, 1));
//                painter.drawText(value, Qt::AlignCenter, key);
//            } else {
//                painter.setPen(QPen(QBrush(QColor(52, 120, 246)), 1));
//                painter.drawText(value, Qt::AlignCenter, key);
//            }
//        }

    painter.setPen(QPen(QBrush(QColor(52, 120, 246)), 3));
    painter.setBrush(Qt::transparent);
    switch (checked) {
        case Light:
            painter.drawRoundedRect(lightRectF, 9, 9);
            break;
        case Dark:
            painter.drawRoundedRect(darkRectF, 9, 9);
            break;
        case Auto:
            painter.drawRoundedRect(autoRectF, 9, 9);
            break;
    }

    painter.restore();
}
void ThemeSwitchBtn::mousePressEvent(QMouseEvent *event) {
    QRectF lightRectF = QRectF(2, 2, 80, height());
    QRectF darkRectF = lightRectF.adjusted(85, 0, 85, 0);
    QRectF autoRectF = darkRectF.adjusted(85, 0, 85, 0);
    if (lightRectF.contains(this->mapFromGlobal(QCursor::pos()))) {
        checked = Light;
    } else if (darkRectF.contains(this->mapFromGlobal(QCursor::pos()))) {
        checked = Dark;
    } else if (autoRectF.contains(this->mapFromGlobal(QCursor::pos()))) {
        checked = Auto;
    }
    emit clickedIndexChange(checked);
    update();
}
