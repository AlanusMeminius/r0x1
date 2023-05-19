#pragma once
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
namespace Ui {

class CommonSwitchBtn : public QWidget{
    Q_OBJECT
   public:
    explicit CommonSwitchBtn() = default;
    explicit CommonSwitchBtn(QWidget *parent, QString item);

   protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

   private:
    int diameter = 18;
    QString item;
    bool checked = false;
};

}// namespace Ui
