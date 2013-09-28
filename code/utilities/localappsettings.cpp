#include "localappsettings.h"

LocalAppSettings::LocalAppSettings(const QString& organization, const QString& application, QObject* parent) :
    QSettings(organization, application, parent)
{
}

void LocalAppSettings::setValue(const QString& key, const QVariant& value)
{
    QSettings::setValue(key, value);
}

QVariant LocalAppSettings::value(const QString& key, const QVariant& defaultValue) const
{
    return QSettings::value(key, defaultValue);
}
