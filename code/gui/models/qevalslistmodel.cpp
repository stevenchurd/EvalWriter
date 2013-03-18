#include "qevalslistmodel.h"
#include "utilities/persistentdatamanager.h"

QEvalsListModel::QEvalsListModel(boost::shared_ptr<Student> student, QObject* parent) :
    QGenericListModel(parent), m_student(student)
{
}


std::string QEvalsListModel::getItemString(int index) const
{
    return elementAt<Eval>(m_student->evalsBegin(), index)->getEvalName();
}


int QEvalsListModel::getNumItems() const
{
    return m_student->getNumEvals();
}
