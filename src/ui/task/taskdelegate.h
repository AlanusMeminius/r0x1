#pragma once
#include <QListView>
#include <QStyledItemDelegate>
namespace Ui {

class TaskDelegate : public QStyledItemDelegate {
    Q_OBJECT
   public:
    explicit TaskDelegate(QListView *parent = nullptr);

    void paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;
    [[nodiscard]] QSize sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;

    bool editorEvent(
        QEvent *event, QAbstractItemModel *model,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) override;

   private:
    int btnWidth = 30;
    int iconSize = 18;

   signals:
    void buttonClicked(const QModelIndex &index, int type);
};

}// namespace Ui
