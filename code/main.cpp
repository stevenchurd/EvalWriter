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
#include "gui/models/qcriteriaitemlistmodel.h"
#include "gui/models/qcourseslistmodel.h"
#include "gui/models/qgradingcriteriatreemodel.h"
#include "gui/models/qgradingcriteriamodel.h"
#include "gui/models/qevaluationmodel.h"
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

    QString fileName = "../testfiles/test5.ewd";

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
        QVector<boost::shared_ptr<Eval> > studentEvals;

        // set up models
        QGradingCriteriaModel gcModel(m_gradingCriteria, m_students);
        m_students[0]->getEvals(std::inserter(studentEvals, studentEvals.begin()));
        QEvaluationModel evalModel(studentEvals[0]);
        QCoursesListModel coursesModel(m_courses);

        // set up view with QML main
        QQuickView view;

        // set context properties of view
        QQmlContext* context = view.rootContext();
        context->setContextProperty("gradingCriteriaModel", &gcModel);
        context->setContextProperty("evalModel", &evalModel);

        // set view properties
        view.setSource(QUrl::fromLocalFile("../code/gui/qml/main.qml"));
        view.setResizeMode(QQuickView::SizeRootObjectToView);
        view.show();

        return a.exec();
#endif

    } catch(std::exception& e) {
        FileLogger::getInst()->log(e.what());
        //rethrow
        throw;
    }
}
