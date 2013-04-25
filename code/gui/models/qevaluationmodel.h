// (C) Copyright Steven Hurd 2013

#ifndef QEVALUATIONMODEL_H
#define QEVALUATIONMODEL_H

#include <QAbstractListModel>
#include "globalenums.h"
#include "utilities/tagreplacer.h"

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>
#endif

class Eval;

class QEvaluationModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(EvaluationOperations)

public:
    QEvaluationModel(boost::shared_ptr<Eval> eval,
                     QObject* parent = 0);

    virtual ~QEvaluationModel() {}

    enum EvaluationOperations {
        AddCustomTextItem = ModelOperationRanges::EvaluationOperationsBegin,

        EndOfEnum
    };
    static_assert(EndOfEnum < ModelOperationRanges::EvaluationOperationsEnd,
                  "Too many items in enumeration");


    enum EvaluationRoles{
        StringRole = Qt::UserRole + 1,
        LevelRole,
        SelectedRole,
        TitleRole,
        InPlaceEditableRole
    };

    Q_INVOKABLE QString getEvalTitle() const;
    Q_INVOKABLE QString getFullEvalText() const;
    Q_INVOKABLE int isEvalComplete() const;
    Q_INVOKABLE void toggleEvalComplete() const;

    // operation interface
    Q_INVOKABLE QList<int> getSubModelOperations();
    Q_INVOKABLE QString getOperationExplanationText(int operation, int row);

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int,QByteArray> roleNames() const;

public slots:
    void addCustomTextItem(QString title, QString customText);
    void addCriteriaItem(int index, QString uuid);
    void moveEvalItem(int srcIndex, int destIndex);
    void removeItem(int row);
    void selectItem(int row);
    void deselectItem(int row);
    void deselectAllItems(void);

    void editItemString(int row, QString title, QString string);

private:
    boost::shared_ptr<Eval> m_eval;
    boost::shared_ptr<TagReplacer> m_tagReplacer;
    std::list<int> m_selected;
};

#endif // QEVALUATIONMODEL_H
