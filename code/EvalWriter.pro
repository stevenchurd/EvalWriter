#-------------------------------------------------
#
# Project created by QtCreator 2012-06-20T17:37:49
#
#-------------------------------------------------

QT       += core gui widgets declarative quick qml

TARGET = EvalWriter
TEMPLATE = app

DEFINES += _SCL_SECURE_NO_WARNINGS

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
    gui/models/qgradingcriteriamodel.cpp \
    gui/models/qcriteriaitemlistmodel.cpp \
    model/visitors/replacecriteriaitemvisitor.cpp \
    gui/models/qgenericlistmodel.cpp \
    gui/models/qstudentslistmodel.cpp \
    gui/models/qevalslistmodel.cpp \
    gui/models/qmainnavigationmodel.cpp \
    gui/models/qevalsetslistmodel.cpp \
    model/evalset.cpp \
    utilities/persistentdatamanager.cpp \
    model/visitors/evalsetsavevisitor.cpp \
    utilities/evalsetpropertytreeparser.cpp \
    model/visitors/removeevalvisitor.cpp

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
    gui/models/qgradingcriteriamodel.h \
    gui/models/qcriteriaitemlistmodel.h \
    model/visitors/replacecriteriaitemvisitor.h \
    gui/models/qgenericlistmodel.h \
    gui/models/qstudentslistmodel.h \
    gui/models/qevalslistmodel.h \
    gui/models/qmainnavigationmodel.h \
    gui/models/qevalsetslistmodel.h \
    model/evalset.h \
    utilities/persistentdatamanager.h \
    model/visitors/evalsetsavevisitor.h \
    utilities/evalsetpropertytreeparser.h \
    model/visitors/removeevalvisitor.h \
    globalenums.h \
    model/visitors/containerinsertvisitor.h

FORMS    +=

INCLUDEPATH += $$(BOOST_INCLUDE_PATH) \
    ./

OTHER_FILES += \
    gui/qml/TextButton.qml \
    gui/qml/CommonListView.qml \
    gui/qml/CommonListDelegate.qml \
    gui/qml/CourseListDelegateItem.qml \
    gui/qml/Scrollbar.qml \
    gui/qml/main.qml \
    gui/qml/VerticalSplitter.qml \
    gui/qml/GradingCriteriaRow.qml \
    gui/qml/CriteriaItemRow.qml \
    gui/qml/GradingCriteriaModel.qml \
    gui/qml/GradingCriteriaDelegate.qml \
    gui/qml/YesNoDialog.qml \
    gui/qml/WizardLoader.qml \
    gui/qml/Dialog.qml \
    gui/qml/CriteriaItemDialog.qml \
    gui/qml/CriteriaItemEditDialog.qml \
    gui/qml/EvalModel.qml \
    gui/qml/FlowListView.qml \
    gui/qml/utilities.js \
    gui/qml/CustomTextItemEditDialog.qml \
    gui/qml/EvalEditor.qml \
    gui/qml/EvalItemDelegate.qml \
    gui/qml/MainNavigationModel.qml \
    gui/qml/SideListDelegate.qml \
    gui/qml/criteriaItemRowCreation.js \
    gui/qml/pageCreator.js \
    gui/qml/PageStack.qml \
    gui/qml/stack.js \
    gui/qml/NavigationBar.qml \
    gui/qml/subModelCreator.js \
    gui/qml/NavigationListSubModel.qml \
    gui/qml/SingleLineTextEditDialog.qml \
    gui/qml/ListChooserDialog.qml \
    gui/qml/AddStudentDialog.qml \
    gui/qml/NavigationListDelegate.qml \
    gui/qml/PageOperationsContainer.qml \
    gui/qml/Checkbox.qml \
    gui/qml/NavigationBarDelegate.qml \
    gui/qml/hoverTextCreator.js \
    gui/qml/HoverText.qml \
    gui/qml/IconButton.qml

RESOURCES += \
    resources.qrc
