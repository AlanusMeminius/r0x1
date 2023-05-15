#pragma once
#include "ui/components/checkablesvglabel.h"
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QWidget>
namespace Ui {

class CommonSetting : public QWidget {
    Q_OBJECT
   public:
    explicit CommonSetting(QWidget *parent = nullptr);

   private:
    QGridLayout *mainLayout;
    QLabel *appearance;

   public:
    CheckableSvgLabel *lightLabelPic;
    CheckableSvgLabel *darkLabelPic;
    CheckableSvgLabel *autoLabelPic;

};

}// namespace Ui
