#include "qstudenttablemodel.h"

#include <QStringList>

int QStudentTableModel::rowCount(const QModelIndex &) const
{
    return m_students.size();
}

int QStudentTableModel::columnCount(const QModelIndex &) const
{
    return COLUMN_COUNT;
}

QVariant QStudentTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_students.size())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return getDataFromRowColumn(index.row(), index.column());
    }
    else
    {
        return QVariant();
    }
}


QVariant QStudentTableModel::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        QVariant qv;

        switch(section)
        {
            case FIRST_NAME_COLUMN:
                qv = QString("First Name");
                break;

            case MIDDLE_NAME_COLUMN:
                qv = QString("Middle Name");
                break;

            case LAST_NAME_COLUMN:
                qv = QString("Last Name");
                break;

            default:
                break;
        }

        return qv;
    }
    else
    {
        return QVariant();
    }
}


Qt::ItemFlags QStudentTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

    return defaultFlags;
}


bool QStudentTableModel::setData(const QModelIndex &/*index*/,
                                 const QVariant &/*value*/, int /*role*/)
{
    return false;
}


bool QStudentTableModel::insertRows(int /*row*/, int /*count*/,
                                    const QModelIndex &/*parent*/)
{
    return false;
}


bool QStudentTableModel::removeRows(int /*row*/, int /*count*/,
                                    const QModelIndex &/*parent*/)
{
    return false;
}


QVariant QStudentTableModel::getDataFromRowColumn(int row, int column) const
{
    QVariant qv;

    switch(column)
    {
        case FIRST_NAME_COLUMN:
            qv = QString::fromStdString(
                    m_students.at(row)->getFirstName());
            break;

        case MIDDLE_NAME_COLUMN:
            qv = QString::fromStdString(
                    m_students.at(row)->getMiddleName());
            break;

        case LAST_NAME_COLUMN:
            qv = QString::fromStdString(
                    m_students.at(row)->getLastName());
            break;

        case COURSES_LIST:
            {
                std::list<std::string> coursesList;
                m_students.at(row)->getCourseNames(std::inserter(coursesList, coursesList.begin()));
                QStringList csl;
                BOOST_FOREACH(std::string course, coursesList){
                    csl.push_back(QString::fromStdString(course));
                }
                qv = csl;
            }
            break;

        case UNIQUE_ID:
            qv = m_students.at(row)->getUniqueId();
            break;

        default:
            break;
    }

    return qv;
}
