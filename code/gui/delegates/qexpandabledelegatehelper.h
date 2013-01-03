#ifndef QEXPANDABLEDELEGATEHELPER_H
#define QEXPANDABLEDELEGATEHELPER_H

#include <QObject>
#include <QTreeView>
#include <QPointer>

class QExpandableDelegateHelper : public QObject
{
    Q_OBJECT

public:
    QExpandableDelegateHelper(QTreeView *parent);
    virtual ~QExpandableDelegateHelper() {}

    enum ItemType{Spacer, Item};
    enum ItemRole{TypeRole = Qt::UserRole + 1000,
                  SignalValueRole = Qt::UserRole + 1001};
signals:
    void itemClicked(int);

private slots:
    void itemClicked(const QModelIndex &index);

private:
    QPointer<QTreeView> m_viewPtr;
};

#endif // QEXPANDABLEDELEGATEHELPER_H
