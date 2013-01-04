// (C) Copyright Steven Hurd 2013

#include <QApplication>
#include <QVector>
#include "mainwindow.h"
#include "utilities/filelogger.h"
#include "model/course.h"
#include "model/student.h"
#include "model/gradingcriteria.h"
#include "utilities/coursespropertytreeparser.h"
#include "utilities/gradingcriteriapropertytreeparser.h"
#include "utilities/studentpropertytreeparser.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {
        // first read data from files
        MainWindow w;
        w.show();
        return a.exec();
    } catch(std::exception& e) {
        FileLogger::getInst()->log(e.what());
        //rethrow
        throw;
    }
}
