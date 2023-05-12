/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/27 09:52
* @description: 
*/
#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
namespace Ui {

class AboutPage final : public QWidget{
    Q_OBJECT
   public:
    explicit AboutPage(QWidget *parent = nullptr);
    QLabel *aboutLabel;
    QLabel *about;
   private:
    QVBoxLayout *mainLayout;

};


}// namespace Ui
