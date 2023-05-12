/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/5/12 18:18
* @description: 
*/
#pragma once
#include "ui/components/horizonnavigation.h"
#include <QListView>
#include <QStyledItemDelegate>

namespace Ui{
class SettingItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
   public:
    explicit SettingItemDelegate(QListView *parent = nullptr);
    void paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;

    void updateEditorGeometry(
        QWidget *editor,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    [[nodiscard]] QSize sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;

    bool editorEvent(
        QEvent *event, QAbstractItemModel *model,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) override;

    void drawSwitch(
        QPainter *painter,
        const QRectF &rectF,
        const QModelIndex &index);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

   private:
    int borderRadius = 3;
    int itemHeight = 30;
    int keyWidth = 300;
};


}

