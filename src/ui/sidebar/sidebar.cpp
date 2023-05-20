
#include "sidebar.h"
//#include "ui_SideBar.h"

Ui::SideBar::SideBar(QWidget *parent)
    : QListWidget(parent),
      icon(new QListWidgetItem(Theme::icon(QString("hippo")), QString("R0x1"), this)),
      task(new QListWidgetItem(Theme::icon(QString("flask")), QString("Task"), this)),
      setting(new QListWidgetItem(Theme::icon(QString("gear")), QString("Setting"), this)),
      help(new QListWidgetItem(Theme::icon(QString("help")), QString("Help"), this)),
      about(new QListWidgetItem(Theme::icon(QString("about")), QString("About"), this))
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setContentsMargins(0, 0, 0, 0);
    this->setSpacing(5);
    this->setCurrentRow(0);
}
