#-------------------------------------------------
#
# Project created by QtCreator 2012-06-20T17:37:49
#
#-------------------------------------------------

QT       += core gui widgets declarative quick qml

TARGET = EvalWriter
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    model/student.cpp \
    model/gradingcriteria.cpp \
    model/evalitem.cpp \
    model/eval.cpp \
    model/customtextitem.cpp \
    model/criteriaitem.cpp \
    model/course.cpp \
    model/visitors/studentsavevisitor.cpp \
    model/visitors/savevisitor.cpp \
    model/visitors/gradingcriteriasavevisitor.cpp \
    model/visitors/coursesavevisitor.cpp \
    utilities/studentpropertytreeparser.cpp \
    utilities/filelogger.cpp \
    gui/models/qcourseslistmodel.cpp \
    gui/models/qevaluationmodel.cpp \
    gui/models/qstudenttablemodel.cpp \
    gui/models/qstudentsortfilterproxymodel.cpp \
    gui/widgets/singlestudentwidget.cpp \
    gui/models/qgradingcriteriamodel.cpp \
    gui/delegates/qexpandabledelegatehelper.cpp \
    gui/delegates/qexpandableitemdelegate.cpp \
    gui/models/qgradingcriteriatreemodel.cpp

HEADERS  += mainwindow.h \
    evalexceptions.h \
    xmlnodenames.h \
    model/student.h \
    model/gradingcriteria.h \
    model/evalitem.h \
    model/eval.h \
    model/customtextitem.h \
    model/criteriaitem.h \
    model/course.h \
    model/visitors/visitor.h \
    model/visitors/visitorelement.h \
    model/visitors/studentsavevisitor.h \
    model/visitors/savevisitor.h \
    model/visitors/gradingcriteriasavevisitor.h \
    model/visitors/coursesavevisitor.h \
    utilities/coursespropertytreeparser.h \
    utilities/gradingcriteriapropertytreeparser.h \
    utilities/studentpropertytreeparser.h \
    utilities/filelogger.h \
    gui/models/qcourseslistmodel.h \
    gui/models/qevaluationmodel.h \
    gui/models/qstudenttablemodel.h \
    gui/models/qstudentsortfilterproxymodel.h \
    gui/widgets/singlestudentwidget.h \
    gui/models/qgradingcriteriamodel.h \
    gui/delegates/qexpandabledelegatehelper.h \
    gui/delegates/qexpandableitemdelegate.h \
    gui/models/qgradingcriteriatreemodel.h \
    gui/utilities/qflattree.h

FORMS    +=

INCLUDEPATH += $$(BOOST_INCLUDE_PATH) \
    ./

OTHER_FILES += \
    gui/qml/TextButton.qml \
    gui/qml/CommonListView.qml \
    gui/qml/CommonListDelegate.qml \
    gui/qml/CourseListDelegateItem.qml \
    gui/qml/TreeViewDelegate.qml \
    gui/qml/Scrollbar.qml \
    gui/qml/GradingCriteriaModelPrototype.qml \
    gui/qml/main.qml \
    gui/qml/CourseListPrototype.qml \
    gui/qml/VerticalSplitter.qml \
    gui/qml/GradingCriteriaRow.qml \
    gui/qml/TreeViewDelegate2.qml \
    gui/qml/CriteriaItemRow.qml

RESOURCES += \
    images.qrc
