#include "checkablesvglabel.h"
#include <QIcon>
#include <QPainter>

namespace Ui {
CheckableSvgLabel::CheckableSvgLabel(QLabel *parent, Qt::WindowFlags)
    : QLabel(parent) {
    this->setContentsMargins(0, 0, 0, 0);
}
void CheckableSvgLabel::setSvg(const QString &name, QSize size) {
    setPixmap(QIcon(QString(":/res/icons/%1.svg").arg(name)).pixmap(size));
    resize(size);
}
void CheckableSvgLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();
    checked = !checked;
    update();
}

void CheckableSvgLabel::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);
    if (checked) {
        QRectF rectF = event->rect().toRectF();
        QPainter painter(this);
        painter.save();
        painter.setRenderHints(QPainter::Antialiasing);
        painter.setPen(QPen(QBrush(QColor(52, 120, 246)), 2));
        painter.setBrush(Qt::transparent);
        painter.drawRoundedRect(
            QRectF(rectF.x() + 1, rectF.y() + 1, rectF.width() - 2, rectF.height() - 2),
            8,
            8);
        painter.restore();
    }
}
}// namespace Ui