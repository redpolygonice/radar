#ifndef BROKER_H
#define BROKER_H

#include "common/types.h"
#include "common/singleton.h"
#include "common/frame.h"

#include <QObject>
#include <QVariantMap>
#include <QQmlEngine>
#include <QJSEngine>

// The intermediate object
class Broker : public QObject, public Singleton<Broker>
{
	friend class Singleton<Broker>;

	Q_OBJECT
	Q_PROPERTY(QVariantMap frame READ frame WRITE setFrame NOTIFY frameChanged)
	Q_PROPERTY(QVariantList frames READ frames WRITE setFrames NOTIFY framesChanged)

private:
	QVariantMap _frame;
	QVariantList _frames;
	std::mutex _mutex;

private:
	Broker(QObject *parent = nullptr);

public:
	~Broker();

public slots:
	Q_INVOKABLE void start();
	Q_INVOKABLE void stop();

signals:
	void frameChanged();
	void framesChanged();

public:
	bool init();

	const QVariantMap &frame() const { return _frame; }
	void setFrame(const QVariantMap &map) { _frame = map; }
	void updateFrame(const Frame &frame);

	const QVariantList &frames() const { return _frames; }
	void setFrames(const QVariantList &list) { _frames = list; }
	void updateFrames(const FrameList &frames);
};

static QObject *BrokerSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)
	return Broker::instance();
}

#endif // BROKER_H
