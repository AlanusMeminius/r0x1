/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/26 23:42
* @description: 
*/
#include "taskpage.h"
#include "ui/theme.h"
#include <QFileIconProvider>
#include <QRandomGenerator>
#include <QScroller>
namespace Ui {

#if 0
CustomTaskListItem::CustomTaskListItem(QWidget *parent)
    : QWidget(parent),
      mainLayout(new QGridLayout),
      nameLabel(new QLabel),
      pauseBtn(new QPushButton),
      deleteBtn(new QPushButton),
      folderBtn(new QPushButton),
      linkBtn(new QPushButton),
      progressBar(new QProgressBar),
      leftTimeLabel(new QLabel),
      sizeLabel(new QLabel),
      speedLabel(new QLabel) {
    this->setObjectName("TaskListItem");
    setLayout(mainLayout);
    mainLayout->setContentsMargins(10, 5, 10, 5);

    nameLabel->setObjectName("TaskNameLabel");
    mainLayout->addWidget(nameLabel, 0, 0);
    pauseBtn->setIcon(Theme::icon("pause"));
    mainLayout->addWidget(pauseBtn, 0, 8);
    deleteBtn->setIcon(Theme::icon("delete"));
    mainLayout->addWidget(deleteBtn, 0, 9);
    folderBtn->setIcon(Theme::icon("folder"));
    mainLayout->addWidget(folderBtn, 0, 10);
    linkBtn->setIcon(Theme::icon("link"));
    mainLayout->addWidget(linkBtn, 0, 11);

    progressBar->setObjectName("ProgressBar");
    mainLayout->addWidget(progressBar, 1, 0, 1, 12);

    mainLayout->addWidget(leftTimeLabel, 2, 0);
    mainLayout->addWidget(sizeLabel, 2, 1);
    mainLayout->addWidget(speedLabel, 2, 2);
}

void CustomTaskListItem::setName(const QString &text) {
    nameLabel->setText(text);
}

void CustomTaskListItem::setLeftTime(const QString &text) {
    leftTimeLabel->setText(text);
}

void CustomTaskListItem::setSize(const QString &text) {
    sizeLabel->setText(text);
}

void CustomTaskListItem::setSpeed(const QString &text) {
    speedLabel->setText(text);
}
#endif

TaskModel::TaskModel(QObject *parent) : QAbstractListModel(parent) {
}

[[maybe_unused]] TaskModel::TaskModel(const QList<Core::Task> &tasks, QObject *parent)
    : QAbstractListModel(parent), tasks(tasks) {
}

int TaskModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : int(tasks.size());
}

QVariant TaskModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0) {
        return {};
    }
    if (role == Qt::DisplayRole) {
        return tasks.at(index.row());
    }
    return {};
}

Qt::ItemFlags TaskModel::flags(const QModelIndex &index) const {
    return QAbstractListModel::flags(index);
}
bool TaskModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::DisplayRole) {
        //        const int row = index.row();
        //        auto task = tasks.value(row);
        //        task = value.value<Core::Task>();
        //        qDebug() << task.name();
        tasks.replace(index.row(), value.value<Core::Task>());
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }
    return false;
}
bool TaskModel::insertRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index)
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row) {
        tasks.insert(position, Core::Task());
    }
    endInsertRows();
    return true;
}
bool TaskModel::removeRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index)
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row) {
        tasks.removeAt(position);
    }
    endInsertRows();
    return true;
}
[[maybe_unused]] const QList<Core::Task> &TaskModel::getTaskList() const {
    return tasks;
}

TaskSortFilterProxyModel::TaskSortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {
}
void TaskSortFilterProxyModel::setFilterStatus(const int &index) {
    statusFilter = index;
    invalidateFilter();
}
bool TaskSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    //    auto s = sourceModel()->data(index).value<Core::Task>().status();
    //    return QString::number(s).contains(filterRegularExpression());
    return sourceModel()->data(index).value<Core::Task>().status() == statusFilter;
}
bool TaskSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    //  可以使用其他参数来排序
    return QSortFilterProxyModel::lessThan(left, right);
}

TaskDelegate::TaskDelegate(QListView *parent) : QStyledItemDelegate(parent) {
}
void TaskDelegate::paint(
    QPainter *painter,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
    Q_ASSERT(index.isValid());

    auto var = index.data(Qt::DisplayRole);
    auto taskDate = var.value<Core::Task>();

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    // item 圆角矩形区域
    auto rect = option.rect;
    //    qDebug() << rect;
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(235, 235, 235));
    QRect background(rect.x() - 5, rect.y(), rect.width() + 3, rect.height());
    painter->drawRoundedRect(background, 5, 5);

    // name
    painter->setPen(QPen(Qt::black, 1));
    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);
    QRect nameRect(rect.x() + 5, rect.y() + 0, rect.width() - 160, 30);
    painter->drawText(nameRect, Qt::AlignVCenter, taskDate.name());
    // pause btn
    QRect pause(rect.right() - 150, nameRect.y() + 5, 18, 18);
    painter->drawPixmap(pause, QPixmap(QString(":/res/icons/pause.svg")));
    // delete btn
    QRect del(pause.x() + 40, pause.y(), 18, 18);
    painter->drawPixmap(del, QPixmap(QString(":/res/icons/delete.svg")));
    // folder btn
    QRect folder(del.x() + 40, pause.y(), 18, 18);
    painter->drawPixmap(folder, QPixmap(QString(":/res/icons/folder.svg")));
    // link btn
    QRect link(folder.x() + 40, pause.y(), 18, 18);
    painter->drawPixmap(link, QPixmap(QString(":/res/icons/link.svg")));
    // progress
    painter->setPen(QPen(Qt::gray, 2));
    QRect progress(
        QPoint(nameRect.x(), nameRect.y() + 35),
        QPoint(link.x() + link.height(), nameRect.y() + 40));
    painter->drawRoundedRect(progress, 3, 3);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(84, 90, 110));
    QRect completed(
        progress.x() + 1,
        progress.y() + 1,
        progress.width() * taskDate.progress() / 100 - 2,
        progress.height() - 2);
    painter->drawRoundedRect(completed, 1, 1);
    // speed
    painter->setPen(QPen(Qt::black, 1));
    QRect speed(progress.x(), progress.y() + 10, 80, 30);
    painter->drawText(speed, Qt::AlignVCenter, QString::number(taskDate.speed()) + QString("Gib/s"));
    painter->restore();
}
QSize TaskDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return {400, 72};
}
bool TaskDelegate::editorEvent(
    QEvent *event,
    QAbstractItemModel *model,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) {
    auto rect = option.rect;
    QRect pause(rect.right() - 144, rect.y() + 5, 18, 18);
    QRect del(pause.x() + 40, pause.y(), 18, 18);
    QRect folder(del.x() + 40, pause.y(), 18, 18);
    QRect link(folder.x() + 40, pause.y(), 18, 18);
    auto p = dynamic_cast<QMouseEvent *>(event)->pos();
    auto t = (event->type() == QEvent::MouseButtonPress);
    if (pause.contains(p) && t) emit buttonClicked(index, 0);
    if (del.contains(p) && t) emit buttonClicked(index, 1);
    if (folder.contains(p) && t) emit buttonClicked(index, 2);
    if (link.contains(p) && t) emit buttonClicked(index, 3);
    return true;
}

TaskList::TaskList(QWidget *parent)
    : QListView(parent),
      taskDelegate(new TaskDelegate),
      taskModel(new TaskModel),
      taskSortFilterProxyModel(new TaskSortFilterProxyModel) {
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

#if 0
void TaskList::addTask() {

    auto *customListItem = new CustomTaskListItem(this);
    auto *item = new QListWidgetItem();
    this->insertItem(0, item);
    this->setItemWidget(item, customListItem);
    item->setSizeHint(customListItem->sizeHint());

    customListItem->setName("name");
    customListItem->setSize("10GB");
    customListItem->setSpeed("20M/s");
    customListItem->setLeftTime("3min");

    // 删除 task
    connect(customListItem->deleteBtn, &QPushButton::clicked, [=]() {
        delete this->takeItem(indexFromItem(item).row());
        customListItem->deleteLater();
    });
}
#endif

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