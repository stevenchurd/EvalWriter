// (C) Copyright Steven Hurd 2013

#include <QGuiApplication>
#include <QVector>
#include <QQuickView>
#include <QQmlContext>
#include "mainwindow.h"
#include "utilities/filelogger.h"
#include "model/course.h"
#include "model/student.h"
#include "model/gradingcriteria.h"
#include "gui/models/qcourseslistmodel.h"
#include "utilities/coursespropertytreeparser.h"
#include "utilities/gradingcriteriapropertytreeparser.h"
#include "utilities/studentpropertytreeparser.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    try {
#if 0
        // first read data from files
        MainWindow w;
        w.show();
        return a.exec();
#endif
        QVector<boost::shared_ptr<Course> > courses;

        boost::shared_ptr<Course> course1(new Course("Spanish 1"));
        boost::shared_ptr<Course> course2(new Course("Spanish 2"));
        boost::shared_ptr<Course> course3(new Course("Spanish 3"));

        courses << course1 << course2 << course3;

        QCoursesListModel coursesModel(courses);
        QQuickView view(QUrl::fromLocalFile("G:/GitRepos/EvalWriter/code/gui/qml/modelprototype.qml"));
        QQmlContext* context = view.rootContext();
        context->setContextProperty("courseModel", &coursesModel);

        view.show();

        return a.exec();

    } catch(std::exception& e) {
        FileLogger::getInst()->log(e.what());
        //rethrow
        throw;
    }
}
