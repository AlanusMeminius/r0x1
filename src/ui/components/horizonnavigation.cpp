#include "horizonnavigation.h"
#include <QMouseEvent>
#include <QPainterPath>
#include <utility>

namespace Ui {
//HorizonNavigation::HorizonNavigation(QWidget *parent)
//    : QWidget(parent),
//      animation(new QPropertyAnimation(this, "")) {
//    setUi();
//}
HorizonNavigation::HorizonNavigation(QWidget *parent, QStringList items)
    : QWidget(parent),
      itemList(std::move(items)),
      animation(new QPropertyAnimation(this, "")) {
    setUi();
}

void HorizonNavigation::setUi() {
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedHeight(30);
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::InOutBack);
    connect(animation, &QPropertyAnimation::valueChanged, this, &HorizonNavigation::onValeChanged);
}
void HorizonNavigation::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    // 画背景
    painter.setPen(Qt::NoPen);
    QPainterPath background;
    background.addRoundedRect(QRect(0, 0, columnWidth * int(itemList.length()) + 4, rowHeight), radius, radius);
    painter.fillPath(background, QBrush(ColorRepository::horizonNavigationBackgroundColor()));
    if (itemList.length() > 1) {
    }
    // 画按钮
    QPainterPath itemPath;
    itemPath.addRoundedRect(QRect(2 + offset, 2, columnWidth, rowHeight - 4), radius, radius);
    painter.fillPath(itemPath, ColorRepository::horizonNavigationBtnColor());

    for (int count = 0; count < itemList.length(); ++count) {
        // 画按钮分割线
        if (itemList.length() > 1 && count > 0) {
            painter.setPen(QPen(Ui::fontColor, 1, Qt::SolidLine, Qt::SquareCap));
            if (offset < columnWidth * (count - 1) || offset > columnWidth * (count)) {
                painter.drawLine(2 + columnWidth * count, 8, 2 + columnWidth * count, 20);
            }
        }
        // 画按钮名称
        if (offset == columnWidth * (count)) {
            painter.setPen(ColorRepository::horizonNavigationSelectedBtnFontColor());
            painter.drawText(
                QRect(offset, 0, columnWidth, rowHeight),
                Qt::AlignVCenter | Qt::AlignHCenter,
                itemList.at(count));
            continue;
        }
        painter.setPen(QColor(105, 109, 120));
        painter.drawText(
            QRect(count * columnWidth, 0, columnWidth, rowHeight),
            Qt::AlignVCenter | Qt::AlignHCenter,
            itemList.at(count));
    }

    painter.restore();
}
void HorizonNavigation::mousePressEvent(QMouseEvent *event) {
    if (event->position().x() / columnWidth < int(itemList.length())) {
        currentIndex = qIntCast(event->position().x()) / columnWidth;
        emit currentItemChanged(currentIndex);
        animation->setStartValue(preIndex * columnWidth);
        animation->setEndValue(currentIndex * columnWidth);
        animation->start();
        preIndex = currentIndex;
        update();
    }
}
void HorizonNavigation::mouseReleaseEvent(QMouseEvent *e) {
    Q_UNUSED(e)
}
void HorizonNavigation::onValeChanged(const QVariant &v) {
    offset = v.toInt();
    update();
}
void HorizonNavigation::addItems(const QStringList &items) {
    itemList = items;
    update();
}

}// namespace Ui

