#ifndef SETTINGS_H
#define SETTINGS_H

#include "common/singleton.h"

#include <QObject>
#include <QVariant>
#include <QVariantMap>

// Application settings
class Settings : public Singleton<Settings>
{
	friend class Singleton<Settings>;

private:
	QVariantMap _data;

private:
	Settings();

public:
	~Settings();

	Settings(const Settings &other) = delete;
	Settings(const Settings &&other) = delete;
	void operator= (const Settings &other) = delete;

public:
	bool load();
	bool save();

	QVariant value(const QString &key) const { return _data[key]; }
	void setValue(const QString &key, const QVariant &val) { _data[key] = val; }
};

#endif // SETTINGS_H
