#include "taskdelegate.h"
#include "core/task.h"
#include "ui/theme.h"

namespace Ui {
TaskDelegate::TaskDelegate(QListView *parent) : QStyledItemDelegate(parent) {
}
void TaskDelegate::paint(
    QPainter *painter,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
    Q_ASSERT(index.isValid());

    auto var = index.data(Qt::DisplayRole);
    auto taskData = var.value<Core::Task>();

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    // item 圆角矩形区域
    auto rect = option.rect.toRectF();
    //    qDebug() << rect;
    painter->setPen(Qt::NoPen);
    painter->setBrush(ColorRepository::aria2SettingItemBackgroundColor());
    QRectF background(rect.x() - 5, rect.y(), rect.width() + 3, rect.height());
    painter->drawRoundedRect(background, 5, 5);

    // name
    painter->setPen(QPen(QBrush(ColorRepository::text()), 1));
    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);
    QRectF nameRect(rect.x() + 5, rect.y() + 0, rect.width() - 160, 30);
    painter->drawText(nameRect, Qt::AlignVCenter, taskData.name());
    // pause btn
    QRectF pause(rect.right() - 5 * btnWidth, nameRect.y() + 5, iconSize, iconSize);
    painter->drawPixmap(pause.toRect(), Theme::pix("pause", QSize(iconSize, iconSize)));
    // delete btn
    QRect del = pause.adjusted(btnWidth, 0, btnWidth, 0).toRect();
    painter->drawPixmap(del, Theme::pix("delete", QSize(iconSize, iconSize)));
    // folder btn
    QRect folder = del.adjusted(btnWidth, 0, btnWidth, 0);
    painter->drawPixmap(folder, Theme::pix("folder", QSize(iconSize, iconSize)));
    // link btn
    QRect link = folder.adjusted(btnWidth, 0, btnWidth, 0);
    painter->drawPixmap(link, Theme::pix("url", QSize(iconSize, iconSize)));

    QRect details = link.adjusted(btnWidth, 0, btnWidth, 0);
    painter->drawPixmap(details, Theme::pix("details", QSize(iconSize, iconSize)));

    // progress
    painter->setPen(QPen(Qt::gray, 2));
    QRectF progress(nameRect.x(), rect.y() + iconSize + 15, rect.width() - 18, 5);
    painter->drawRoundedRect(progress, 3, 3);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(87, 110, 128));
    //    if (taskData.status.completedLength)
    auto status = taskData.status;
    auto p = status.totalLength != 0 ? status.completedLength * 100 / status.totalLength : 0;
    if (p > 0) {
        QRectF completed(
            progress.x() + 1,
            progress.y() + 1,
            progress.width() * (double) p - 2,
            progress.height() - 2);
        painter->drawRoundedRect(completed, 1, 1);
    }
    // speed
    painter->setPen(QPen(Qt::black, 1));
    QRectF speed(progress.x(), progress.y() + 10, 80, 30);
    painter->drawText(speed, Qt::AlignVCenter, formatDownloadSpeed(status.downloadSpeed));
    painter->restore();
}
QSize TaskDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return {400, 72};
}
bool TaskDelegate::editorEvent(
    QEvent *event,
    QAbstractItemModel *model,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) {
    auto rect = option.rect.toRectF();

    QRectF details(rect.right() - btnWidth, rect.y(), btnWidth, iconSize);
    QRectF url(details.x() - btnWidth, rect.y(), btnWidth, iconSize);
    QRectF folder(url.x() - btnWidth, rect.y(), btnWidth, iconSize);
    QRectF del(folder.x() - btnWidth, rect.y(), btnWidth, iconSize);
    QRectF pause(del.x() - btnWidth, rect.y(), btnWidth, iconSize);
    auto point = dynamic_cast<QMouseEvent *>(event)->pos();
    auto t = (event->type() == QEvent::MouseButtonPress);
    if (pause.contains(point) && t) {
        emit buttonClicked(index, 0);
    }
    if (del.contains(point) && t) {
        emit buttonClicked(index, 1);
    }
    if (folder.contains(point) && t) {
        emit buttonClicked(index, 2);
    }
    if (url.contains(point) && t) {
        emit buttonClicked(index, 3);
    }
    if (details.contains(point) && t) {
        emit buttonClicked(index, 4);
    }
    return true;
}
QString TaskDelegate::formatDownloadSpeed(int bytesPerSec) {
    const double GIBIBYTES = pow(2, 30);
    const double MEBIBYTES = pow(2, 20);
    const double KIBIBYTES = pow(2, 10);
    if (bytesPerSec >= GIBIBYTES) {
        return QString::number(bytesPerSec / GIBIBYTES) + "GiB/s";
    } else if (bytesPerSec >= MEBIBYTES) {
        return QString::number(bytesPerSec / MEBIBYTES) + "Mib/s";
    } else if (bytesPerSec >= KIBIBYTES) {
        return QString::number(bytesPerSec / KIBIBYTES) + "Kib/s";
    } else {
        return QString::number(bytesPerSec) + "B/s";
    }
}
}// namespace Ui