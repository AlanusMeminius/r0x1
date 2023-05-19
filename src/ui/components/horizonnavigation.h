#pragma once

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
}// namespace Ui
