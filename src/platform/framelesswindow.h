/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/28 17:20
* @description:
*/
#pragma once
#include <QEvent>
#include <QGridLayout>
#include <QGridLayout>
#include <QMainWindow>
#include <QMouseEvent>
#include <QWidget>

class BlurEffect;

class MacOSThemeObserver;

class FramelessWindow : public QWidget {
    Q_OBJECT
   public:
    QWidget *centralWidget;
    QGridLayout *layout;
    explicit FramelessWindow(QWidget *parent);

   private:
    BlurEffect *blurEffect;

   protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void changeEvent(QEvent *event) override;

   private:
    void hideSystemTitleBar();
    QPoint windowPos{};
    QPoint mousePos{};
    bool mousePressed{};
    bool windowMoving{};
};