// (C) Copyright Steven Hurd 2013

#include <QApplication>
#include <QVector>
#include <QQuickView>
#include <QQmlContext>
#include <QFileDialog>
#include <QQmlEngine>
#include <QQmlComponent>

#ifdef _DEBUG
#include <QDebug>
#endif

#include "mainwindow.h"
#include "utilities/filelogger.h"
#include "utilities/persistentdatamanager.h"
#include "model/course.h"
#include "model/student.h"
#include "model/gradingcriteria.h"
#include "gui/models/qcriteriaitemlistmodel.h"
#include "gui/models/qcourseslistmodel.h"
#include "gui/models/qstudentslistmodel.h"
#include "gui/models/qevalslistmodel.h"
#include "gui/models/qgradingcriteriatreemodel.h"
#include "gui/models/qgradingcriteriamodel.h"
#include "gui/models/qevaluationmodel.h"
#include "gui/models/qmainnavigationmodel.h"
#include "gui/models/qgenericlistmodel.h"
#include "gui/models/qevalsetslistmodel.h"

int main(int argc, char *argv[])
{
    try {
        PDM().loadFile("../testfiles/test5.ewd");

        QApplication a(argc, argv);

        // set up models
        QGradingCriteriaModel gcModel;
        QEvaluationModel evalModel(*(*PDM().studentsBegin())->evalsBegin());

        // set up view with QML main
        QQuickView view;

        // set context properties of view
        QQmlContext* context = view.rootContext();

        QGenericListModel* coursesModel = new QCoursesListModel();
        QGenericListModel* studentsModel = new QStudentsListModel() ;
        QGenericListModel* evalSetModel = new QEvalSetsListModel();

        std::unique_ptr<QMainNavigationModel> mainModel(new QMainNavigationModel());
        mainModel->addSubModel("Classes", coursesModel, MainNavigation);
        mainModel->addSubModel("Students", studentsModel, MainNavigation);
        mainModel->addSubModel("Evaluation Sets", evalSetModel, MainNavigation);

        context->setContextProperty("mainModel", mainModel.get());
        context->setContextProperty("gradingCriteriaModel", &gcModel);
        context->setContextProperty("evalModel", &evalModel);

        // set view properties
        view.setSource(QUrl::fromLocalFile("../code/gui/qml/main.qml"));
        view.setResizeMode(QQuickView::SizeRootObjectToView);
        view.show();

        return a.exec();

    } catch(std::exception& e) {
        FileLogger::getInst()->log(e.what());
        //rethrow
        throw;
    }
}
