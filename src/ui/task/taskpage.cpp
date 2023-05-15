#include "taskpage.h"
#include <QRandomGenerator>
namespace Ui {
TaskList::TaskList(QWidget *parent)
    : QListView(parent),
      taskDelegate(new TaskDelegate),
      taskModel(new TaskModel),
      taskSortFilterProxyModel(new TaskSortFilterProxyModel) {
    setAttribute(Qt::WA_StyledBackground, true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setObjectName("TaskList");
    this->setSpacing(5);
    this->setContentsMargins(0, 0, 0, 0);

    this->setItemDelegate(taskDelegate);
    taskSortFilterProxyModel->setSourceModel(taskModel);
    this->setModel(taskSortFilterProxyModel);
    connect(taskDelegate, &TaskDelegate::buttonClicked, this, &TaskList::btnAction);
}
void TaskList::btnAction(const QModelIndex &index, int type) const {
    if (type == 1) {
        taskModel->removeRow(index.row());
    }
    // 发送信号
}
void TaskList::addTask(Core::Task &task) const {
    // TODO 判断是否重复添加
    taskModel->insertRow(0);
    //    auto index = taskModel->index(0);
    taskModel->setData(taskModel->index(0), task, Qt::DisplayRole);
}

TaskPage::TaskPage(QWidget *parent)
    : QWidget(parent),
      taskPageLayout(new QVBoxLayout),
      titleLabel(new QLabel),
      horizonNavigation(new HorizonNavigation(this)),
      taskList(new TaskList) {

    setAttribute(Qt::WA_StyledBackground, true);
    this->setLayout(taskPageLayout);
    this->setObjectName("TaskPage");
    this->setContentsMargins(0, 0, 0, 0);
    titleLabel->setObjectName("TaskLabel");
    taskPageLayout->addWidget(titleLabel);
    titleLabel->setText("Task");

    QStringList horizonNavigationBtn;
    horizonNavigationBtn << "Downloading"
                         << "Waiting"
                         << "Stopped"
                         << "Finished";
    horizonNavigation->addItems(horizonNavigationBtn);
    taskPageLayout->addWidget(horizonNavigation);
    taskPageLayout->addWidget(taskList);
    connect(
        horizonNavigation, &HorizonNavigation::currentItemChanged,
        taskList->taskSortFilterProxyModel, &TaskSortFilterProxyModel::setFilterStatus);

    connect(horizonNavigation, &HorizonNavigation::currentItemChanged, [&] {
        taskList->scrollToTop();
    });
#if 1// 数据测试
    QStringList names;
    names << "archlinux-2023.05.01-x86_64.iso"
          << "qt-everywhere-src-6.5.0.tar.xz"
          << "ちひろさん / Call Me Chihiro 2023.BD.1080P.日语中字.mp4"
          << "Avatar: The Way of Water 2022.HD.1080P.国英双语双字.mp4"
          << "这是一个名称超级长的文件.longNamelongNamelongNamelongNamelongNamelongNamelongNamelongName";
    QString url = "url";
    QString dir = "dir";
    QString gid = "GID";
    for (int i = 0; i < 30; ++i) {
        const QString &name = names.at(QRandomGenerator::global()->bounded(names.length()));
        int progress = QRandomGenerator::global()->bounded(100);
        //        int progress = 100;
        double speed = QRandomGenerator::global()->bounded(20.0);
        int status = QRandomGenerator::global()->bounded(4);
        //        qDebug() << status;
        //        int p = progress + 8 * i;
        auto task1 = Core::Task(name, url, dir, gid, status, progress, speed);
        taskList->addTask(task1);
    }
#endif
}

}// namespace Ui