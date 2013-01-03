#ifndef QSTUDENTTABLEMODEL_H
#define QSTUDENTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>

#include "model/student.h"
#endif

class QStudentTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    QStudentTableModel(QVector<boost::shared_ptr<Student> >& students, QObject* parent = 0) :
        QAbstractTableModel(parent), m_students(students)
    {
    }
    virtual ~QStudentTableModel() {}

    /* virtual functions from QAbstractTableModel */
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

private:
    QVector<boost::shared_ptr<Student> >& m_students;

    enum {
        FIRST_NAME_COLUMN = 0,
        MIDDLE_NAME_COLUMN = 1,
        LAST_NAME_COLUMN = 2,
        COURSES_LIST = 3,
        UNIQUE_ID = 4,
        COLUMN_COUNT
    };


    QVariant getDataFromRowColumn(int row, int column) const;

};

#endif // QSTUDENTTABLEMODEL_H
