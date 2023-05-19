#include "basewindow.h"

Ui::BaseWindow::BaseWindow(QWidget *parent)
    : FramelessWindow(parent),
      mainLayout(new QHBoxLayout),
      stackedWidget(new QStackedWidget),
      sideBar(new Ui::SideBar),
      addPage(new Ui::AddPage),
      taskPage(new Ui::TaskPage),
      settingPage(new Ui::SettingPage),
      helpPage(new Ui::HelpPage),
      aboutPage(new Ui::AboutPage) {

    this->setObjectName(QString("BaseWindow"));

    this->resize(890, 550);

    FramelessWindow::centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(sideBar);
    stackedWidget->setObjectName("MainStackedWidget");
    mainLayout->addWidget(stackedWidget);
    mainLayout->setContentsMargins(3, 8, 8, 8);
    stackedWidget->setMinimumWidth(300);
    stackedWidget->insertWidget(0, addPage);
    stackedWidget->insertWidget(1, taskPage);
    stackedWidget->insertWidget(2, settingPage);
    stackedWidget->insertWidget(3, helpPage);
    stackedWidget->insertWidget(4, aboutPage);
    stackedWidget->setCurrentIndex(0);

//    auto t = new Toast("this is a toast");
//    connect(addPage->actionButton, &QPushButton::clicked, t, &Toast::show);



    connect(sideBar, &QListWidget::currentRowChanged, stackedWidget, &QStackedWidget::setCurrentIndex);
}

QString Ui::BaseWindow::getInputUrl() const {
    return addPage->urlInput->text();
}
void Ui::BaseWindow::loadSettingUi(const QList<Core::AppSetting::SettingItemPtr> &setting) {
    settingPage->settingList->loadSetting(setting);
}
