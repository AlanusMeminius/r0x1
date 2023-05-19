#pragma once
#include "core/appevent.h"
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

class ThemeSwitchBtn : public QWidget{
    Q_OBJECT
   public:
    enum which {
        Light,
        Dark,
        Auto
    };
    explicit ThemeSwitchBtn(QWidget *parent = nullptr);

   signals:
    void clickedIndexChange(int);

   protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *event) override;

   public:
    which checked = Light;
};
