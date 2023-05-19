#include "aria2settingdelegate.h"
#include "core/setting.h"
#include "ui/theme.h"
#include <QLineEdit>
#include <QPainter>
#include <QPainterPath>
namespace Ui {

Aria2SettingItemDelegate::Aria2SettingItemDelegate(QListView *parent) : QStyledItemDelegate(parent) {
}
void Aria2SettingItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid())
        return;
    const auto &data = index.data(Qt::UserRole + 1);
    if (data.isNull())
        return;
    auto setting = data.value<Core::SettingItem>();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    auto rect = option.rect.toRectF();
    QPainterPath background;
    background.addRoundedRect(rect.x() - 2, rect.y(), rect.width(), itemHeight, 5, 5);
    painter->fillPath(background, QBrush(ColorRepository::aria2SettingItemBackgroundColor()));
    // name
    QRectF nameRect(rect.topLeft(), rect.topLeft() + QPointF(nameWidth, itemHeight));
    QFont font;
    font.setPixelSize(14);
    painter->setFont(font);
    painter->setPen(QPen(QBrush(ColorRepository::text()), 1));
    painter->drawText(nameRect, Qt::AlignRight | Qt::AlignVCenter, setting.key());
    // control
    QRectF controlRect(nameRect.topRight(), nameRect.topRight() + QPointF(control, itemHeight));
    painter->setPen(QPen(QBrush(ColorRepository::aria2SettingThemeColor()), 2, Qt::SolidLine, Qt::SquareCap));
    painter->drawLine(QPointF(controlRect.x() + 8, controlRect.y() + 8), QPointF(controlRect.x() + 8, controlRect.y() + 24));
    QRectF editRect(nameRect.topRight().x() + 25, nameRect.y(), rect.width() - nameRect.width(), itemHeight);
    if (setting.unit() == Core::SettingItem::None)
        painter->drawText(editRect, Qt::AlignLeft | Qt::AlignVCenter, setting.value());
    else if (setting.unit() == Core::SettingItem::Bool)
        paintSwitch(painter,controlRect,setting.value());
    else
        paintNumber(painter,editRect,setting.value());
    painter->restore();
}

void Aria2SettingItemDelegate::paintSwitch(QPainter *painter, const QRectF &rectF, const QString &value) const{
    painter->setPen(Qt::NoPen);
    QRectF btnBackground(rectF.x() + 25, rectF.y() + 4, 2 * diameter + spacing, diameter + 2 * spacing);
    painter->setBrush(QBrush(ColorRepository::switchBackgroundColor()));
    painter->drawRoundedRect(btnBackground, 11, 11);
    if (value.contains("true", Qt::CaseInsensitive)) {
        QRectF trueBtn(btnBackground.x() + 2, btnBackground.y() + 2, diameter, diameter);
        painter->setBrush(QBrush(QColor(25, 179, 145)));
        painter->drawRoundedRect(trueBtn, diameter, diameter);
    } else if (value.contains("false", Qt::CaseInsensitive)) {
        QRectF falseBtn(btnBackground.x() + diameter, btnBackground.y() + 2, diameter, diameter);
        painter->setBrush(QBrush(QColor(235, 66, 19)));
        painter->drawRoundedRect(falseBtn, diameter, diameter);
    }
}

void Aria2SettingItemDelegate::paintNumber(QPainter *painter, const QRectF &rectF, const QString &value) const {
    if (value.endsWith("M")) {
        auto lastPos = value.lastIndexOf(QChar('M'));
        painter->drawText(rectF, Qt::AlignLeft | Qt::AlignVCenter, value.left(lastPos));
        painter->drawText(QRectF(rectF.x() + 50, rectF.y(), 50, itemHeight), Qt::AlignCenter, "M");
    } else {
        painter->drawText(rectF, Qt::AlignLeft | Qt::AlignVCenter, value);
        painter->drawText(QRectF(rectF.x() + 50, rectF.y(), 50, itemHeight), Qt::AlignCenter, "s");
    }
}

void Aria2SettingItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {

    QStyledItemDelegate::setEditorData(editor, index);
    auto *lineEdit = qobject_cast<QLineEdit *>(editor);

    QVariant var = index.data(Qt::UserRole + 1);
    auto setting = var.value<Core::SettingItem>();
    lineEdit->setText(setting.value());
}
void Aria2SettingItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
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
void Aria2SettingItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid())
        return;
    editor->setObjectName("SettingEditor");
    QRect rect = option.rect;

    const auto &data = index.data(Qt::UserRole + 1);
    if (data.isNull())
        return;
    auto setting = data.value<Core::SettingItem>();
    if (setting.unit() == Core::SettingItem::Bool)
        editor->setGeometry(0, 0, 0, 0);
    else {
        editor->setGeometry(rect.x() + nameWidth + 13, rect.y() + 2, rect.width() - nameWidth - 22, itemHeight - 4);
    }
}
QSize Aria2SettingItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return {option.rect.width(), 34};
}
bool Aria2SettingItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
QWidget *Aria2SettingItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QStyledItemDelegate::createEditor(parent, option, index);
}


}// namespace Ui
