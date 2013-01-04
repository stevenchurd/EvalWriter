// (C) Copyright Steven Hurd 2013

#ifndef SINGLESTUDENTWIDGET_H
#define SINGLESTUDENTWIDGET_H

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QLabel;
class QListWidget;
class Student;

class SingleStudentWidget : public QWidget
{
    Q_OBJECT

public:
    SingleStudentWidget(boost::shared_ptr<Student> student,
                                 QWidget *parent = 0);

    SingleStudentWidget(QWidget *parent = 0);


private:
    QLabel* m_firstNameLabel;
    QLabel* m_middleNameLabel;
    QLabel* m_lastNameLabel;
    QLabel* m_coursesLabel;
    QLabel* m_evalLabel;

    QLabel* m_firstName;
    QLabel* m_middleName;
    QLabel* m_lastName;

    QListWidget* m_courseListWidget;


signals:
    
public slots:
    void setStudentWidget(boost::shared_ptr<Student> student);
    
};

#endif // SINGLESTUDENTWIDGET_H
