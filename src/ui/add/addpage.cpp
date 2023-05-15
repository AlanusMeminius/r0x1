
#include "addpage.h"
namespace Ui {
AddPage::AddPage(QWidget *parent)
    : QWidget(parent),
      addPageMainLayout(new QGridLayout),
      addLabel(new QLabel),
//      urlInputLayout(new QHBoxLayout),
      urlInput(new QLineEdit),
      actionButton(new QPushButton),
      horizonNavigation(new HorizonNavigation),
      stackedWidget(new QStackedWidget),
      addPageDefaultSetting(new AddPageDefaultSetting),
      msg(new QLabel) {
    this->setObjectName("AddPage");
    setAttribute(Qt::WA_StyledBackground, true);
    setLayout(addPageMainLayout);
    addPageMainLayout->addWidget(addLabel,0,0);
    addLabel->setText("Add");
    addLabel->setObjectName("AddLabel");
    addPageMainLayout->addWidget(urlInput,1,0,1,8 );
    urlInput->setObjectName("UrlInput");
    urlInput->setPlaceholderText("enter link");

    addPageMainLayout->addWidget(actionButton,1,9,1,2);
    actionButton->setObjectName("ActionBtn");
    actionButton->setText("dash");

    addPageMainLayout->addWidget(horizonNavigation,2,0,1,11);
    horizonNavigation->setObjectName("AddPageHorizonNavigation");
    QStringList horizonNavigationBtn;
    horizonNavigationBtn << "Default" << "BitTorrent";
    horizonNavigation->addItems(horizonNavigationBtn);
//    horizonNavigation->setCurrentRow(0);

    addPageMainLayout->addWidget(stackedWidget,3,0,7,11);
    stackedWidget->addWidget(addPageDefaultSetting);
    stackedWidget->addWidget(msg);
    msg->setText("BitTorrent Setting");

    connect(horizonNavigation, &HorizonNavigation::currentItemChanged, stackedWidget, &QStackedWidget::setCurrentIndex);
}

AddPageDefaultSetting::AddPageDefaultSetting(QWidget *parent)
    : QWidget(parent),
      layout(new QGridLayout),
      pathLabel(new QLabel),
      path(new QLineEdit),
      renameLabel(new QLabel),
      renamePath(new QLineEdit),
      cancel(new QPushButton),
      confirm(new QPushButton) {
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("AddPageDefaultSetting");
    setLayout(layout);
    setContentsMargins(0,0,0,220);
    layout->addWidget(pathLabel,0,0,1,1);
    pathLabel->setText("Path:");
    pathLabel->setObjectName("AddPagePathLabel");

    layout->addWidget(path,0,3,1,7);
    path->setPlaceholderText("/download");
    path->setObjectName("PathInput");

    layout->addWidget(renameLabel,1,0,1,1);
    renameLabel->setText("Rename:");
    renameLabel->setObjectName("AddPageRenameLabel");

    layout->addWidget(renamePath,1,3,1,7);
    renamePath->setPlaceholderText("xxx.mp4");
    renamePath->setObjectName("RenameInput");

    layout->addWidget(cancel,2,8,1,1);
    cancel->setObjectName("CancelBtn");
    cancel->setText("Cancel");

    layout->addWidget(confirm,2,9,1,1);
    confirm->setObjectName("ConfirmBtn");
    confirm->setText("Confirm");
}
}// namespace Ui
