// (C) Copyright Steven Hurd 2013

#include <QApplication>
#include <QVector>
#include <QQuickView>
#include <QQmlContext>
#include <QFileDialog>
#include <QQmlEngine>
#include <QQmlComponent>

#include "mainwindow.h"
#include "utilities/filelogger.h"
#include "model/course.h"
#include "model/student.h"
#include "model/gradingcriteria.h"
#include "gui/models/qcourseslistmodel.h"
#include "gui/models/qgradingcriteriatreemodel.h"
#include "utilities/coursespropertytreeparser.h"
#include "utilities/gradingcriteriapropertytreeparser.h"
#include "utilities/studentpropertytreeparser.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


QVector<boost::shared_ptr<Course> > m_courses;
QVector<boost::shared_ptr<GradingCriteria> > m_gradingCriteria;
QVector<boost::shared_ptr<Student> > m_students;

void loadFile()
{
    boost::property_tree::ptree loadPt;

    QString fileName = "G:/GitRepos/EvalWriter/testfiles/test5.ewd";

    if(!fileName.isEmpty())
    {
        boost::property_tree::xml_parser::read_xml(fileName.toStdString(), loadPt);

        m_courses.clear();
        m_gradingCriteria.clear();
        m_students.clear();

        CoursesPropertyTreeParser ptreeParser;
        ptreeParser.parseTree(loadPt, std::inserter(m_courses, m_courses.begin()));

        GradingCriteriaPropertyTreeParser gcPtParser;
        gcPtParser.parseTree(loadPt, std::inserter(m_gradingCriteria, m_gradingCriteria.begin()));

        StudentPropertyTreeParser studentPtParser;
        studentPtParser.parseTree(loadPt,
                                  std::inserter(m_students, m_students.begin()),
                                  m_courses.begin(),
                                  m_courses.end(),
                                  m_gradingCriteria.begin(),
                                  m_gradingCriteria.end());
    }
}




int main(int argc, char *argv[])
{
    loadFile();

    try {
#if 0
        QApplication app(argc, argv);
        QQmlEngine engine;
        QQmlComponent component(&engine);
        component.loadUrl(QUrl::fromLocalFile("C:/Qt/Qt5.0.0/Tools/QtCreator/bin/EvalWriter/EvalWriter-Qml-prototype/code/gui/qml/main.qml"));
        if ( !component.isReady() ) {
            qWarning("%s", qPrintable(component.errorString()));
            return -1;
        }
        QObject *topLevel = component.create();
        QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
        if ( !window ) {
            qWarning("Error: Your root item has to be a Window.");
            return -1;
        }
        window->show();
        return app.exec();
#else
        QApplication a(argc, argv);

        QGradingCriteriaTreeModel gcTreeModel(m_gradingCriteria);
        QCoursesListModel coursesModel(m_courses);
        QQuickView view(QUrl::fromLocalFile("G:/GitRepos/EvalWriter/code/gui/qml/main.qml"));
        QQmlContext* context = view.rootContext();
        view.setResizeMode(QQuickView::SizeRootObjectToView);
        context->setContextProperty("courseModel", &coursesModel);
        context->setContextProperty("gradingCriteriaModel", &gcTreeModel);

        view.show();

        return a.exec();
#endif

    } catch(std::exception& e) {
        FileLogger::getInst()->log(e.what());
        //rethrow
        throw;
    }
}
