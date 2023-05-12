/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/5/12 18:18
* @description: 
*/
#include "delegate.h"
#include "core/setting.h"
#include <QLineEdit>
#include <QPainter>
namespace Ui {

SettingItemDelegate::SettingItemDelegate(QListView *parent) : QStyledItemDelegate(parent) {
}
void SettingItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    //    QStyledItemDelegate::paint(painter, option, index);
    if (!index.isValid())
        return;
    const auto &data = index.data(Qt::UserRole + 1);
    if (data.isNull())
        return;
    auto setting = data.value<Core::SettingItem>();

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    auto rect = option.rect.toRectF();

    QRectF background(rect.x(), rect.y(), rect.width(), rect.height() - 3);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(235, 235, 235));
    painter->drawRoundedRect(background, borderRadius, borderRadius);
    if (option.state.testFlag(QStyle::State_Selected)) {
        painter->setBrush(QColor(225, 225, 225));
        painter->drawRoundedRect(background, borderRadius, borderRadius);
    }
    QFont font;
    font.setPixelSize(14);
    painter->setFont(font);
    painter->setPen(QPen(Qt::black, 1));
    QRectF nameRect(rect.x() + 15, rect.y(), keyWidth, itemHeight);
    painter->drawText(nameRect, Qt::AlignVCenter, setting.key());

    //    if (setting.unit() == Core::SettingItem::None) {
    //        QRect editRect(nameRect.x() + 300, nameRect.y(), rect.width() - nameRect.width(), 30);
    //        painter->drawText(editRect, Qt::AlignVCenter, setting.value());
    //    }
    QRectF editRect(nameRect.x() + keyWidth, nameRect.y(), rect.width() - keyWidth, itemHeight);
    switch (setting.unit()) {

        case Core::SettingItem::None:
            painter->drawText(editRect, Qt::AlignLeft | Qt::AlignVCenter, setting.value());
            qDebug() << setting.value() << setting.key() << setting.unit();
            break;
        case Core::SettingItem::Second:
            qDebug() << setting.value() << setting.key() << setting.unit();
            break;
            //            painter->drawText(editRect, Qt::AlignLeft, setting.value());
        case Core::SettingItem::Mb:
            qDebug() << setting.value() << setting.key() << setting.unit();
            //            painter->drawText(
            //                QRect(nameRect.x() + 270, nameRect.y(), rect.width() - nameRect.width(), 30),
            //                Qt::AlignLeft | Qt::AlignVCenter,
            //                setting.value()
            //                );
            //            painter->drawText(
            //                QRect(nameRect.x() + 300, nameRect.y(), 30, 30),
            //                Qt::AlignVCenter,
            //                QString("Mb")
            //                );
            break;
        case Core::SettingItem::Number:
            qDebug() << setting.value() << setting.key() << setting.unit();
            painter->drawText(editRect, Qt::AlignLeft | Qt::AlignVCenter, setting.value());
            break;

        case Core::SettingItem::Bool:
            //            break ;
            qDebug() << setting.value() << setting.key() << setting.unit();
            painter->drawText(editRect, Qt::AlignLeft | Qt::AlignVCenter, setting.value());
            break;
    }
    //    QLineF lineF(0,rect.height());

    //    painter->drawLine(rect.bottomLeft() + QPoint(10, 3), rect.bottomRight() + QPoint(-10, 3));
    painter->restore();
}
void SettingItemDelegate::drawSwitch(QPainter *painter, const QRectF &rectF, const QModelIndex &index) {
    painter->setPen(Qt::NoPen);
    QRectF background(rectF.x() + keyWidth + 2,rectF.y() + 3,110,itemHeight - 6);
    painter->drawRoundedRect(background,12,12);
}

void SettingItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {

    QStyledItemDelegate::setEditorData(editor, index);
    auto *lineEdit = qobject_cast<QLineEdit *>(editor);

    QVariant var = index.data(Qt::UserRole + 1);
    auto setting = var.value<Core::SettingItem>();
    lineEdit->setText(setting.value());
}
void SettingItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    //    QStyledItemDelegate::setModelData(editor, model, index);
    const auto *lineEdit = qobject_cast<QLineEdit *>(editor);
    const auto value = lineEdit->text();
    if (value.length() <= 0)
        return;

    QVariant var = index.data(Qt::UserRole + 1);
    auto setting = var.value<Core::SettingItem>();
    setting.setValue(value);
    var.setValue(setting);
    model->setData(index, var, Qt::UserRole + 1);
}
void SettingItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid())
        return;
    editor->setObjectName("SettingEditor");
    QRect rect = option.rect;
    editor->setGeometry(
        rect.x() + keyWidth + 2,
        rect.y() + 3,
        rect.width() - keyWidth - 5,
        itemHeight - 5);
}
QSize SettingItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    //    return QStyledItemDelegate::sizeHint(option, index);
    return {400, 34};
}
bool SettingItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
QWidget *SettingItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
//    const auto &data = index.data(Qt::UserRole + 1);
//    auto setting = data.value<Core::SettingItem>();
//    qDebug() << setting.unit();
//    if (setting.unit() == Core::SettingItem::Bool) {
//        return  new Ui::HorizonNavigation(parent,{"True","False"});
//    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

}// namespace Ui
