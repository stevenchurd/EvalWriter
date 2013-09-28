#ifndef LOCALAPPSETTINGS_H
#define LOCALAPPSETTINGS_H

#include <QSettings>

// lightweight addition to QSettings primarily for access via QML
class LocalAppSettings : public QSettings
{
    Q_OBJECT

    public:
        explicit LocalAppSettings(const QString & organization, const QString & application = QString(), QObject * parent = 0);

        Q_INVOKABLE void setValue(const QString& key, const QVariant& value);
        Q_INVOKABLE QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const;
};

#endif // LOCALAPPSETTINGS_H
