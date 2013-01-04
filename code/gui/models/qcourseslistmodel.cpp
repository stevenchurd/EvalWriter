// (C) Copyright Steven Hurd 2013

#include "qcourseslistmodel.h"

int QCoursesListModel::rowCount(const QModelIndex &) const
{
    return m_courses.size();
}


QVariant QCoursesListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_courses.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QString::fromStdString(
                    m_courses.at(index.row())->getCourseName());
    else
        return QVariant();
}


QVariant QCoursesListModel::headerData(int section,
                                       Qt::Orientation orientation,
                                       int role) const
{
    if (role != Qt::DisplayRole)
          return QVariant();

      if (orientation == Qt::Horizontal)
          return QString("Column %1").arg(section);
      else
          return QString("Row %1").arg(section);
}


Qt::ItemFlags QCoursesListModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}


bool QCoursesListModel::setData(const QModelIndex &index, const QVariant &value,
             int role)
{
    if (index.isValid() && role == Qt::EditRole) {

        m_courses.at(index.row())->updateCourseName(value.toString().toStdString());
        emit dataChanged(index, index);
        return true;
    }

    return false;
}


bool QCoursesListModel::insertRows(int row, int count, const QModelIndex &)
{
    beginInsertRows(QModelIndex(), row, row+count);

    for (int i = 0; i < count; ++i) {
        boost::shared_ptr<Course> newCourse(new Course(""));
        m_courses.insert(i, newCourse);
    }

    endInsertRows();
    return true;
}


bool QCoursesListModel::removeRows(int row, int count, const QModelIndex &)
{
    beginRemoveRows(QModelIndex(), row, row+count);

    for (int i = 0; i < count; ++i) {
        m_courses.remove(i);
    }

    endRemoveRows();
    return true;
}
