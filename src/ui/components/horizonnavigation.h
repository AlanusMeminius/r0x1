/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/5/6 11:26
* @description: 
*/
#pragma once

//#include <QListWidget>
//#include <QPropertyAnimation>
//#include <QStyledItemDelegate>
#include "ui/theme.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QWidget>
namespace Ui {

class HorizonNavigation : public QWidget {
    Q_OBJECT
   public:
    explicit HorizonNavigation(QWidget *parent = nullptr, QStringList items = {});
//    explicit HorizonNavigation(QWidget *parent = nullptr);
    void addItems(const QStringList &items);

   protected:
    void paintEvent(QPaintEvent *event) override;
    //    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

   private:
    QStringList itemList;
    int rowHeight = 28;
    int columnWidth = 110;
    int radius = 4;
    int offset = 0;
    int currentIndex = 0;
    int preIndex = 0;
    QPropertyAnimation *animation;
    void onValeChanged(const QVariant &v);
    void setUi();
   signals:
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
    void currentItemChanged(const int &index);
#pragma clang diagnostic pop
};
#if 0
class ListItemSelectionDelegate : public QStyledItemDelegate {
    Q_OBJECT
   public:
    explicit ListItemSelectionDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

class HorizonNavigation : public QListWidget {
    Q_OBJECT
   public:
    explicit HorizonNavigation(QWidget *parent = nullptr);
    void addItems(const QStringList &labels);
   private:
    QFrame *selectedFrame;
    QPropertyAnimation *animation;
    ListItemSelectionDelegate *itemDelegate;
    void setTextAlignCenter();
   private slots:
    void resizeEvent(QResizeEvent *event) override;
    void updateSelection(QListWidgetItem *current);
};
#endif
}// namespace Ui
