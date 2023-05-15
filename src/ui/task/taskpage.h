#pragma once
#include "core/appevent.h"
#include "core/task.h"
#include "ui/components/horizonnavigation.h"
#include "taskmodel.h"
#include "taskdelegate.h"
#include <QAbstractListModel>
#include <QGridLayout>
#include <QLabel>
#include <QListView>
#include <QWidget>

namespace Ui {
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
