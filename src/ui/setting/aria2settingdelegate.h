#pragma once
#include "ui/components/horizonnavigation.h"
#include <QListView>
#include <QStyledItemDelegate>

namespace Ui {
class Aria2SettingItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
   public:
    explicit Aria2SettingItemDelegate(QListView *parent = nullptr);
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

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void paintSwitch(QPainter *painter, const QRectF &rectF, const QString &value) const;
    void paintNumber(QPainter *painter, const QRectF &rectF, const QString &value) const;

   private:
    int borderRadius = 2;
    int spacing = 2;
    int itemHeight = 30;
    int nameWidth = 200;
    int control = 60;
    int diameter = 18;
};

}// namespace Ui
