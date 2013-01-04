// (C) Copyright Steven Hurd 2013

#include "gui/widgets/singlestudentwidget.h"
#include "model/student.h"
#include "model/eval.h"

#include <boost/foreach.hpp>

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QTranslator>

#include <list>

SingleStudentWidget::SingleStudentWidget(
        boost::shared_ptr<Student> student,
        QWidget *parent) :
    QWidget(parent), m_firstNameLabel(new QLabel), m_middleNameLabel(new QLabel),
    m_lastNameLabel(new QLabel), m_coursesLabel(new QLabel), m_evalLabel(new QLabel),
    m_firstName(new QLabel), m_middleName(new QLabel), m_lastName(new QLabel),
    m_courseListWidget(new QListWidget)
{
    QGridLayout* layout = new QGridLayout;

    m_firstNameLabel->setText(QString(tr("First name:")));
    m_middleNameLabel->setText(QString(tr("Middle name:")));
    m_lastNameLabel->setText(QString(tr("Last name:")));
    m_coursesLabel->setText(QString(tr("Classes:")));
    m_evalLabel->setText(QString(tr("Evaluations:")));

    layout->addWidget(m_firstNameLabel, 0, 0, 1, 1);
    layout->addWidget(m_middleNameLabel, 1, 0, 1, 1);
    layout->addWidget(m_lastNameLabel, 2, 0, 1, 1);
    layout->addWidget(m_firstName, 0, 1, 1, 1);
    layout->addWidget(m_middleName, 1, 1, 1, 1);
    layout->addWidget(m_lastName, 2, 1, 1, 1);
    layout->addWidget(m_coursesLabel, 3, 0, 1, 2);
    layout->addWidget(m_courseListWidget, 4, 0, 1, 2);
    layout->addWidget(m_evalLabel, 5,0,1,2);

    setLayout(layout);

    if(student.get() != NULL)
    {
        setStudentWidget(student);
    }

}


SingleStudentWidget::SingleStudentWidget(QWidget *parent) :
    QWidget(parent), m_firstNameLabel(new QLabel), m_middleNameLabel(new QLabel),
    m_lastNameLabel(new QLabel), m_coursesLabel(new QLabel), m_evalLabel(new QLabel),
    m_firstName(new QLabel), m_middleName(new QLabel), m_lastName(new QLabel),
    m_courseListWidget(new QListWidget)
{
    QGridLayout* layout = new QGridLayout;

    m_firstNameLabel->setText(QString(tr("First name:")));
    m_middleNameLabel->setText(QString(tr("Middle name:")));
    m_lastNameLabel->setText(QString(tr("Last name:")));
    m_coursesLabel->setText(QString(tr("Classes:")));
    m_evalLabel->setText(QString(tr("Evaluations:")));

    layout->addWidget(m_firstNameLabel, 0, 0, 1, 1);
    layout->addWidget(m_middleNameLabel, 1, 0, 1, 1);
    layout->addWidget(m_lastNameLabel, 2, 0, 1, 1);
    layout->addWidget(m_firstName, 0, 1, 1, 1);
    layout->addWidget(m_middleName, 1, 1, 1, 1);
    layout->addWidget(m_lastName, 2, 1, 1, 1);
    layout->addWidget(m_coursesLabel, 3, 0, 1, 2);
    layout->addWidget(m_courseListWidget, 4, 0, 1, 2);
    layout->addWidget(m_evalLabel, 5,0,1,2);

    setLayout(layout);
}


void SingleStudentWidget::setStudentWidget(boost::shared_ptr<Student> student)
{
    m_firstName->setText(QString::fromStdString(student->getFirstName()));
    m_middleName->setText(QString::fromStdString(student->getMiddleName()));
    m_lastName->setText(QString::fromStdString(student->getLastName()));

    std::list<std::string> courseNames;
    student->getCourseNames(std::inserter(courseNames, courseNames.begin()));

    QStringList qCourseNames;
    m_courseListWidget->clear();
    m_courseListWidget->setSelectionMode(QAbstractItemView::NoSelection);

    BOOST_FOREACH(std::string courseName, courseNames)
    {
        qCourseNames.append(QString::fromStdString(courseName));
    }

    m_courseListWidget->addItems(qCourseNames);

#if 0
    // now get all the evals
    std::list<boost::shared_ptr<Eval> > evals;
    student->getEvals(std::inserter(evals, evals.begin()));

    BOOST_FOREACH(boost::shared_ptr<Eval> eval, evals)
    {
        QPushButton* pb = new QPushButton(QString::fromStdString(eval->getEvalName()));
        layout->addWidget(pb);
    }
#endif

    update();
}

