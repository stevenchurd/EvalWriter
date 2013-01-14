// (C) Copyright Steven Hurd 2013

#ifndef QCOURSESLISTMODEL_H
#define QCOURSESLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>

#ifndef Q_MOC_RUN
#include "model/course.h"
#endif

class QCoursesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    QCoursesListModel(QVector<boost::shared_ptr<Course> >& courses, QObject* parent = 0) :
        QAbstractListModel(parent), m_courses(courses)
    {
    }

    virtual ~QCoursesListModel() {}

    enum CourseRoles {
        NameRole = Qt::UserRole + 1
    };

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

    QHash<int,QByteArray> roleNames() const;

private:
    QVector<boost::shared_ptr<Course> >& m_courses;
};

#endif // QCOURSESLISTMODEL_H
