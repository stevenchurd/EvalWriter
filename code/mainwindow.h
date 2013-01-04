// (C) Copyright Steven Hurd 2013

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMainWindow>

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>

#include "model/course.h"
#include "model/gradingcriteria.h"
#include "model/student.h"
#endif


class QMenu;
class QModelIndex;
class QCloseEvent;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QMenu *mainWindowMenu;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    QVector<boost::shared_ptr<Course> > m_courses;
    QVector<boost::shared_ptr<GradingCriteria> > m_gradingCriteria;
    QVector<boost::shared_ptr<Student> > m_students;

    QString m_currentOpenFile;

    void setupMenuBar();
    void saveDataToFile(QString fileName);

    void setCoursesView(void);
    void setStudentsView(boost::shared_ptr<Course> course);
    void setGradingCriteriaListView();

    void closeEvent(QCloseEvent *event);

signals:
    void studentWidgetChanged(boost::shared_ptr<Student> student);

public slots:
    void loadFile();
    void saveFile();
    void saveAsFile();
    void courseSelected(const QModelIndex& index);
    void studentSelected(const QModelIndex& index);

};

#endif // MAINWINDOW_H
