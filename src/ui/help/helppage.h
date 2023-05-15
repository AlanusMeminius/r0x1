#pragma once
#include "ui/components/horizonnavigation.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
namespace Ui {

class HelpPage  final : public QWidget{
    Q_OBJECT
   public:
    explicit HelpPage(QWidget *parent = nullptr);
    QLabel *titleLabel;
   private:
    QVBoxLayout *mainLayout;
    HorizonNavigation *horizonNavigation;
};

}// namespace Ui
