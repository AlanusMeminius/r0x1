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
    connect(AppEvent::getInstance(), &AppEvent::addTaskItemToUi, this, &TaskList::addTask);
    connect(AppEvent::getInstance(), &AppEvent::updateTaskInfoToUi, this, &TaskList::updateTaskStatus);
}
void TaskList::btnAction(const QModelIndex &index, int type) const {
    if (type == 1) {
        taskModel->removeRow(index.row());
    }
    // 发送信号
}
void TaskList::addTask(const QVariant &task) {
    // TODO 判断是否重复添加
    taskModel->insertRow(0);
    //    auto index = taskModel->index(0);
    taskModel->setData(taskModel->index(0), task, Qt::DisplayRole);
}
void TaskList::updateTaskStatus(const QVariant &v) {
    auto taskList = taskModel->getTaskList();
    auto status = v.value<Core::Status>();
    for (int i = 0; i < taskList.count(); ++i) {
        if (taskList.at(i).gid() == status.gid) {
            QModelIndex modelIndex = taskModel->index(i);
            auto var = modelIndex.data(Qt::DisplayRole);
            auto task = var.value<Core::Task>();
            task.status = status;
            taskModel->setData(modelIndex, task, Qt::DisplayRole);
        }
    }
}
QString TaskList::formatDownloadSpeed(int bytesPerSec) {
    const double GIBIBYTES = pow(2, 30);
    const double MEBIBYTES = pow(2, 20);
    const double KIBIBYTES = pow(2, 10);
    if (bytesPerSec >= GIBIBYTES) {
        return QString::number(bytesPerSec / GIBIBYTES) + "GiB/s";
    } else if (bytesPerSec >= MEBIBYTES) {
        return QString::number(bytesPerSec / MEBIBYTES) + "Mib/s";
    } else if (bytesPerSec >= KIBIBYTES) {
        return QString::number(bytesPerSec / KIBIBYTES) + "Kib/s";
    } else {
        return QString::number(bytesPerSec) + "B/s";
    }
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
#if 0// 数据测试
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
        auto task1 = Core::Task();

        taskList->addTask(task1);
    }
#endif
}

}// namespace Ui