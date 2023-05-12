#pragma once

#include "ui/theme.h"
#include <QPushButton>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

namespace Ui {
class SideBar : public QListWidget {
    Q_OBJECT
   public:
    explicit SideBar(QWidget *parent = nullptr);
   private:
    QListWidgetItem *icon;
    QListWidgetItem *task;
    QListWidgetItem *setting;
    QListWidgetItem *help;
    QListWidgetItem *about;
};
}// namespace Ui
