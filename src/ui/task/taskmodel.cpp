#include "taskmodel.h"

namespace Ui {
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
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row) {
        tasks.removeAt(position);
    }
    endRemoveRows();
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
    auto data = sourceModel()->data(index);
    int taskStatus = data.value<Core::Task>().category();
    return taskStatus == statusFilter;
}
bool TaskSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    //  可以使用其他参数来排序
    return QSortFilterProxyModel::lessThan(left, right);
}
}// namespace Ui