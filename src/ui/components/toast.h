#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include <QDialog>

class Toast : public QDialog{
    Q_OBJECT
   public:
    explicit Toast(const QString &message, QWidget *parent = nullptr);
    ~Toast() override;

   protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

   private:
    QTimer *timer;
};
