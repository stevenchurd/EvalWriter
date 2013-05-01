// (C) Copyright Steven Hurd 2013

#include <QApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlComponent>
#include <QStandardPaths>

#ifdef _DEBUG
#include <QDebug>
#endif

#include "utilities/filelogger.h"
#include "utilities/persistentdatamanager.h"
#include "model/course.h"
#include "model/student.h"
#include "model/gradingcriteria.h"
#include "gui/models/qcriteriaitemlistmodel.h"
#include "gui/models/qcourseslistmodel.h"
#include "gui/models/qstudentslistmodel.h"
#include "gui/models/qevalslistmodel.h"
#include "gui/models/qgradingcriteriamodel.h"
#include "gui/models/qevaluationmodel.h"
#include "gui/models/qmainnavigationmodel.h"
#include "gui/models/qgenericlistmodel.h"
#include "gui/models/qevalsetslistmodel.h"

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);

        a.setApplicationName("EvalWriter");

        PDM().loadFile(QStandardPaths::writableLocation(QStandardPaths::DataLocation).toStdString(),
                       PersistentDataManager::s_saveFileName);

        qmlRegisterUncreatableType<QCoursesListModel>("CppEnums", 1, 0, "QCoursesListModel", "Need enum types");
        qmlRegisterUncreatableType<QEvalSetsListModel>("CppEnums", 1, 0, "QEvalSetsListModel", "Need enum types");
        qmlRegisterUncreatableType<QStudentsListModel>("CppEnums", 1, 0, "QStudentsListModel", "Need enum types");
        qmlRegisterUncreatableType<QEvalsListModel>("CppEnums", 1, 0, "QEvalsListModel", "Need enum types");
        qmlRegisterUncreatableType<QGradingCriteriaModel>("CppEnums", 1, 0, "QGradingCriteriaModel", "Need enum types");
        qmlRegisterUncreatableType<QEvaluationModel>("CppEnums", 1, 0, "QEvaluationModel", "Need enum types");
        qmlRegisterUncreatableType<QGenericListModel>("ModelTypeEnums", 1, 0, "QGenericListModel", "Model enum types");

        // set up models
        QGradingCriteriaModel gcModel;

        // set up view with QML main
        QQuickView view;

        // set context properties of view
        QQmlContext* context = view.rootContext();

        QGenericListModel* coursesModel = new QCoursesListModel();
        QGenericListModel* studentsModel = new QStudentsListModel() ;
        QGenericListModel* evalSetModel = new QEvalSetsListModel();

        QMainNavigationModel* mainModel = new QMainNavigationModel(std::string());
        mainModel->addSubModel("Classes", coursesModel, QGenericListModel::CourseList);
        mainModel->addSubModel("Students", studentsModel, QGenericListModel::StudentList);
        mainModel->addSubModel("Evaluation Sets", evalSetModel, QGenericListModel::EvalSetList);
        mainModel->addSubModel("Grading Categories", &gcModel, QGenericListModel::GradingCriteria);

        context->setContextProperty("mainModel", mainModel);
        context->setContextProperty("gradingCriteriaModel", &gcModel);
        context->setContextProperty("pdm", &PDM());

        // set view properties
        view.setSource(QUrl::fromLocalFile("../code/gui/qml/main.qml"));
        view.setResizeMode(QQuickView::SizeRootObjectToView);

        view.setMinimumSize(QSize(600,400));
        view.show();

        return a.exec();

    } catch(std::exception& e) {
        FileLogger::getInst()->log(e.what());

        try {
            //attempt to save the data as an alternate file, if this fails, do nothing
            PDM().saveFile(QStandardPaths::writableLocation(QStandardPaths::DataLocation).toStdString(),
                           PersistentDataManager::s_crashFileName);
        } catch(...) {
            // log an error but otherwise do nothing
            FileLogger::getInst()->log(std::string("FAILSAFE SAVE ERROR: ") + e.what());
        }

        //rethrow
        throw;
    }
}
