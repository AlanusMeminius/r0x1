#pragma once
#include "core/task.h"
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
namespace Ui {

class TaskModel : public QAbstractListModel  {
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


}// namespace Ui
