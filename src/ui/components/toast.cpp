#include "toast.h"
Toast::Toast(const QString &message,QWidget *parent)
    : QDialog(parent),
      timer(new QTimer(this)) {

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(24, 0, 24, 0);
    auto *messageLabel = new QLabel(message);
    layout->addWidget(messageLabel,0, Qt::AlignHCenter | Qt::AlignVCenter);

    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, this, &QWidget::close);

    timer->start(3000);


    adjustSize();
    setFixedHeight(42);
    QRect parentGeometry;
    QWidget *parentWidget = nativeParentWidget();
    if (parentWidget == nullptr) {
        QPoint cursorPos = QCursor::pos();
        QScreen *screen = QGuiApplication::screenAt(cursorPos);
        parentGeometry = screen->availableGeometry();
    } else {
        parentGeometry = parentWidget->geometry();
    }

    int x = (parentGeometry.width() - width()) / 2;
    int y = (parentGeometry.height() - height()) / 2;
    move(x, y);

}
Toast::~Toast() {
    timer->stop();
    timer->deleteLater();
}
void Toast::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(171, 171, 171,25));
    painter.drawRoundedRect(rect(), 4, 4);
//    painter.setBrush(Qt::NoBrush);
//    painter.setPen(QPen(m_borderColor, 1));
//    painter.drawRoundedRect(rect(), 4, 4);
}
void Toast::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        timer->stop();
        close();
    }
}
