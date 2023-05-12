/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/26 23:42
* @description: 
*/
#pragma once
#include "core/appevent.h"
#include "core/task.h"
#include "ui/components/horizonnavigation.h"
#include <QAbstractListModel>
#include <QGridLayout>
#include <QLabel>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QWidget>

namespace Ui {

#if 0
class CustomTaskListItem : public QWidget {
    Q_OBJECT
   public:
    explicit CustomTaskListItem(QWidget *parent = nullptr);
    //    [[nodiscard]] QSize sizeHint() const override { return {200, 80}; }
    //    ~CustomTaskListItem() override = default;

   private:
    QGridLayout *mainLayout;
    QLabel *nameLabel;
    QLabel *leftTimeLabel;
    QLabel *sizeLabel;
    QLabel *speedLabel;

   public:
    QPushButton *pauseBtn;
    QPushButton *deleteBtn;
    QPushButton *folderBtn;
    QPushButton *linkBtn;
    QProgressBar *progressBar;

   public:
    void setName(const QString &text);
    void setLeftTime(const QString &text);
    void setSize(const QString &text);
    void setSpeed(const QString &text);
    void updateProgress();
    void pauseTask();
    void deleteTask();
    void openFolder();
    void copyLink();
};
#endif
class TaskModel : public QAbstractListModel {
    Q_OBJECT
   public:
    using QAbstractListModel::QAbstractListModel;
    explicit TaskModel(QObject *parent = nullptr);
    [[maybe_unused]] explicit TaskModel(const QList<Core::Task> &tasks, QObject *parent = nullptr);
    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int position, int rows, const QModelIndex &index) override;
    bool removeRows(int position, int rows, const QModelIndex &index) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    [[maybe_unused]] [[nodiscard]] const QList<Core::Task> &getTaskList() const;

   private:
    QList<Core::Task> tasks;
};

class TaskSortFilterProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
   public:
    explicit TaskSortFilterProxyModel(QObject *parent = nullptr);
   public slots:
    void setFilterStatus(const int &index);

   protected:
    [[nodiscard]] bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    [[nodiscard]] bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

   private:
    int statusFilter = 0;
};

class TaskDelegate : public QStyledItemDelegate {
    Q_OBJECT
   public:
    explicit TaskDelegate(QListView *parent = nullptr);

    void paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;
    [[nodiscard]] QSize sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;

    bool editorEvent(
        QEvent *event, QAbstractItemModel *model,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) override;

   private:
    //    int btnWidth;
    //    QStyle::State _state;

   signals:
    void buttonClicked(const QModelIndex &index, int type);
};

class TaskList : public QListView {
    Q_OBJECT
   public:
    explicit TaskList(QWidget *parent = nullptr);
    void addTask(Core::Task &task) const;

   private:
    TaskDelegate *taskDelegate;
    TaskModel *taskModel;
   public:
    TaskSortFilterProxyModel *taskSortFilterProxyModel;
   public slots:
    void btnAction(const QModelIndex &index, int) const;
};

class TaskPage final : public QWidget {
    Q_OBJECT
   public:
    explicit TaskPage(QWidget *parent = nullptr);

    TaskList *taskList;

   public:
    QVBoxLayout *taskPageLayout;
    QLabel *titleLabel;
    HorizonNavigation *horizonNavigation;
};

}// namespace Ui
