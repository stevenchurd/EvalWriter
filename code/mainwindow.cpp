// (C) Copyright Steven Hurd 2013

#include "mainwindow.h"

#include <QFileDialog>
#include <QListView>
#include <QTableView>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QSplitter>
#include <QModelIndex>
#include <QSettings>
#include <QTreeView>
#include <QMenuBar>
#include <QHeaderView>
#include <QQuickView>
#include <QQmlContext>

#include "utilities/coursespropertytreeparser.h"
#include "utilities/gradingcriteriapropertytreeparser.h"
#include "utilities/studentpropertytreeparser.h"
#include "model/student.h"
#include "model/visitors/coursesavevisitor.h"
#include "model/visitors/gradingcriteriasavevisitor.h"
#include "model/visitors/studentsavevisitor.h"

#include "gui/models/qcourseslistmodel.h"
#include "gui/models/qstudenttablemodel.h"
#include "gui/models/qgradingcriteriamodel.h"
#include "gui/models/qstudentsortfilterproxymodel.h"

#include "gui/widgets/singlestudentwidget.h"

#include "gui/delegates/qexpandableitemdelegate.h"
#include "gui/delegates/qexpandabledelegatehelper.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QSettings settings("EvalWriterCorp", "EvalWriter5000");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());

    setupMenuBar();
}

MainWindow::~MainWindow()
{
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("EvalWriterCorp", "EvalWriter5000");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}


void MainWindow::setupMenuBar()
{
    QMenu *menu = menuBar()->addMenu(tr("&File"));

    QAction *openAction = menu->addAction(tr("&Open..."));
    connect(openAction, SIGNAL(triggered()), this, SLOT(loadFile()));

    menu->addSeparator();

    QAction *saveAsAction = menu->addAction(tr("&Save As..."));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsFile()));

    QAction *saveAction = menu->addAction(tr("S&ave..."));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    menu->addSeparator();

    menu->addAction(tr("&Quit"), this, SLOT(close()));
}


void MainWindow::loadFile()
{
    boost::property_tree::ptree loadPt;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Evaluation Writer Documents (*.ewd)"));

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

        m_currentOpenFile = fileName;

        /* update data changed */
        setGradingCriteriaListView();
    }
}


void MainWindow::setCoursesView()
{
    QListView* listView = new QListView(this);
    QAbstractListModel* coursesModel = new QCoursesListModel(m_courses);

    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setDragEnabled(true);
    listView->setAcceptDrops(true);
    listView->setDropIndicatorShown(true);
    listView->setDragDropMode(QAbstractItemView::InternalMove);

    listView->setModel(coursesModel);

    connect(listView, SIGNAL(clicked(const QModelIndex&)),
            this, SLOT(courseSelected(const QModelIndex&)));

    setCentralWidget(listView);
}


void MainWindow::setStudentsView(boost::shared_ptr<Course> course)
{
    QSplitter* splitter = new QSplitter(this);
    QTableView* tableView = new QTableView(splitter);
    QWidget* studentWidget = new SingleStudentWidget(splitter);
    QAbstractTableModel* studentsModel = new QStudentTableModel(m_students);
    QSortFilterProxyModel* proxyModel = new QStudentSortFilterProxyModel(course);

    proxyModel->setSourceModel(studentsModel);
    proxyModel->sort(0, Qt::AscendingOrder);

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSortingEnabled(true);
    tableView->setModel(proxyModel);
    tableView->setColumnHidden(3, true);
    tableView->setColumnHidden(4, true);
    tableView->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);

    setCentralWidget(splitter);

    connect(tableView, SIGNAL(clicked(const QModelIndex&)),
            this, SLOT(studentSelected(const QModelIndex&)));
    connect(this, SIGNAL(studentWidgetChanged(boost::shared_ptr<Student>)),
            studentWidget, SLOT(setStudentWidget(boost::shared_ptr<Student>)));
}


void MainWindow::setGradingCriteriaListView()
{
    QGradingCriteriaModel gcModel(m_gradingCriteria);
    QQuickView view(QUrl::fromLocalFile("../EvalWriter/code/gui/qml/main.qml"));
    QQmlContext* context = view.rootContext();
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    context->setContextProperty("gradingCriteriaModel", &gcModel);

    //setCentralWidget(view);
}


void MainWindow::saveFile()
{
    if(!m_currentOpenFile.isEmpty())
    {
        saveDataToFile(m_currentOpenFile);
    }
    else
    {
        saveAsFile();
    }
}


void MainWindow::saveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File As"), "", tr("Files (*.ewd)"));
    saveDataToFile(fileName);
    m_currentOpenFile = fileName;
}


void MainWindow::saveDataToFile(QString fileName)
{
    std::ofstream file;

    if(!fileName.isEmpty())
    {
        file.open(fileName.toStdString());

        CourseSaveVisitor csv;
        BOOST_FOREACH(boost::shared_ptr<Course> singleCourse, m_courses)
        {
            singleCourse->accept(csv);
        }
        csv.saveFile(file);

        GradingCriteriaSaveVisitor gcsv;
        BOOST_FOREACH(boost::shared_ptr<GradingCriteria> singleGradingCriteria, m_gradingCriteria)
        {
            singleGradingCriteria->accept(gcsv);
        }
        gcsv.saveFile(file);

        StudentSaveVisitor ssv;
        BOOST_FOREACH(boost::shared_ptr<Student> singleStudent, m_students)
        {
            singleStudent->accept(ssv);
        }
        ssv.saveFile(file);

        file.close();
    }
}


void MainWindow::courseSelected(const QModelIndex& index)
{
    QString courseName = index.data().toString();
    boost::shared_ptr<Course> courseToView;

    BOOST_FOREACH(boost::shared_ptr<Course> course, m_courses)
    {
        if(QString::fromStdString(course->getCourseName()) == courseName)
        {
            courseToView = course;
        }
    }

    if(courseToView.get() != NULL)
    {
        setStudentsView(courseToView);
    }
    else
    {
        throw UnexpectedModelException(
                    std::string("Selected course does not exist: ") +
                    courseName.toStdString());
    }
}


void MainWindow::studentSelected(const QModelIndex & index)
{
    QModelIndex idIndex = index.model()->index(index.row(),4);
    int uniqueId = index.model()->data(idIndex).toInt();

    boost::shared_ptr<Student> studentToView;

    BOOST_FOREACH(boost::shared_ptr<Student> student, m_students)
    {
        if(student->getUniqueId() == uniqueId)
        {
            studentToView = student;
        }
    }

    if(studentToView.get() != NULL)
    {
        emit studentWidgetChanged(studentToView);
    }
    else
    {
        throw UnexpectedModelException(
                    std::string("Selected student does not exist: ") +
                    index.data().toString().toStdString());
    }
}

