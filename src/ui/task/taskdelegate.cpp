#include "taskdelegate.h"
#include "core/task.h"
#include <QMouseEvent>
#include <QPainter>
namespace Ui {
TaskDelegate::TaskDelegate(QListView *parent) : QStyledItemDelegate(parent) {
}
void TaskDelegate::paint(
    QPainter *painter,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
    Q_ASSERT(index.isValid());

    auto var = index.data(Qt::DisplayRole);
    auto taskDate = var.value<Core::Task>();

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    // item 圆角矩形区域
    auto rect = option.rect.toRectF();
    //    qDebug() << rect;
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(238, 230, 215));
    QRectF background(rect.x() - 5, rect.y(), rect.width() + 3, rect.height());
    painter->drawRoundedRect(background, 5, 5);

    // name
    painter->setPen(QPen(Qt::black, 1));
    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);
    QRectF nameRect(rect.x() + 5, rect.y() + 0, rect.width() - 160, 30);
    painter->drawText(nameRect, Qt::AlignVCenter, taskDate.name());
    // pause btn
    QRectF pause(rect.right() - 5 * btnWidth, nameRect.y() + 5, iconSize, iconSize);
    painter->drawPixmap(pause.toRect(), QPixmap(QString(":/res/icons/pause.svg")));
    // delete btn
    QRectF del(pause.x() + btnWidth, pause.y(), iconSize, iconSize);
    painter->drawPixmap(del.toRect(), QPixmap(QString(":/res/icons/delete.svg")));
    // folder btn
    QRectF folder(del.x() + btnWidth, pause.y(), iconSize, iconSize);
    painter->drawPixmap(folder.toRect(), QPixmap(QString(":/res/icons/folder.svg")));
    // link btn
    QRectF link(folder.x() + btnWidth, pause.y(), iconSize, iconSize);
    painter->drawPixmap(link.toRect(), QPixmap(QString(":/res/icons/url.svg")));

    QRectF details(link.x() + btnWidth, pause.y(), iconSize, iconSize);
    painter->drawPixmap(details.toRect(), QPixmap(QString(":/res/icons/details.svg")));
    // progress
    painter->setPen(QPen(Qt::gray, 2));
    QRectF progress(nameRect.x(), rect.y() + iconSize + 15, rect.width() - 18, 5);
    painter->drawRoundedRect(progress, 3, 3);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(87, 110, 128));
    QRectF completed(
        progress.x() + 1,
        progress.y() + 1,
        progress.width() * taskDate.progress() / 100 - 2,
        progress.height() - 2);
    painter->drawRoundedRect(completed, 1, 1);
    // speed
    painter->setPen(QPen(Qt::black, 1));
    QRectF speed(progress.x(), progress.y() + 10, 80, 30);
    painter->drawText(speed, Qt::AlignVCenter, QString::number(taskDate.speed()) + QString("Gib/s"));
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
    if (pause.contains(point) && t) emit buttonClicked(index, 0);
    if (del.contains(point) && t) emit buttonClicked(index, 1);
    if (folder.contains(point) && t) emit buttonClicked(index, 2);
    if (url.contains(point) && t) emit buttonClicked(index, 3);
    if (details.contains(point) && t) emit buttonClicked(index, 4);
    return true;
}
}// namespace Ui