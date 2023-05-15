#pragma once
#include <QWidget>
class ThemeSwitchBtn : public QWidget{
    Q_OBJECT
   public:
    enum which {
        Night,
        Dark,
        Auto
    };
    explicit ThemeSwitchBtn(QWidget *parent = nullptr);

   signals:
    void clicked();

   protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *event) override;

   public:
    which checked = Night;
};
