#include "commonswitchbtn.h"
#include "ui/theme.h"
namespace Ui {
void CommonSwitchBtn::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing);

    QRectF rectF = event->rect().toRectF();

    QRectF btnBackGround(rectF.x(), rectF.y(), 2 * diameter + 4, 22);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(ColorRepository::switchBackgroundColor()));
    painter.drawRoundedRect(btnBackGround, 12, 12);

    QRectF btn;
    if (checked) {
        painter.setBrush(QBrush(QColor(52, 120, 246)));
        btn = QRectF(rectF.x() + 2, rectF.y() + 2, diameter, diameter);
    } else {
        painter.setBrush(QBrush(QColor(235, 66, 19)));
        btn = QRectF(rectF.x() + diameter + 2, rectF.y() + 2, diameter, diameter);
    }
    painter.drawEllipse(btn);

    QRectF text = btnBackGround.adjusted(2 * diameter + 20, 0, 300, 0);
    painter.setPen(QPen(QBrush(ColorRepository::text()), 1));
    painter.drawText(text, Qt::AlignLeft | Qt::AlignVCenter, item);
}

void CommonSwitchBtn::mousePressEvent(QMouseEvent *event) {
    QRectF trueRect(2, 2, diameter, diameter);
    QRectF falseRect(trueRect.adjusted(diameter, 0, diameter, 0));
    if (trueRect.contains(this->mapFromGlobal(QCursor::pos())))
        checked = true;
    if (falseRect.contains(this->mapFromGlobal(QCursor::pos())))
        checked = false;
    update();
}
CommonSwitchBtn::CommonSwitchBtn(QWidget *parent, QString item) : QWidget(parent), item(std::move(item)) {
}

}// namespace Ui