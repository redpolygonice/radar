#include "frame.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDateTime>

Frame::Frame()
{
}

QString Frame::toJsonText() const
{
	QJsonObject object;
	object["id"] = QString::number(_id);
	object["state"] = stateToString(_state);
	object["ts"] = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz");

	QJsonObject objectPos;
	objectPos["x"] = _x;
	objectPos["y"] = _y;
	object["pos"] = objectPos;

	QJsonDocument document(object);
	return document.toJson();
}

bool Frame::fromJson(const QString &text)
{
	QJsonParseError error;
	QJsonDocument document = QJsonDocument::fromJson(text.toUtf8(), &error);
	if (error.error != QJsonParseError::NoError)
	{
		std::cout << "Json parse error: code " << error.error << ", " << error.errorString().toStdString() << std::endl;
		return false;
	}

	QJsonObject object = document.object();
	_id = object["id"].toInt();
	_state = stringToState(object["state"].toString());
	QJsonObject objectPos = object["pos"].toObject();
	_x = objectPos["x"].toInt();
	_y = objectPos["y"].toInt();
	_ts = QDateTime::fromString(object["ts"].toString(), "dd.MM.yyyy hh:mm:ss.zzz").toSecsSinceEpoch();
	return true;
}

QString Frame::stateToString(State state) const
{
	if (state == State::Found)
		return "Found";
	else if (state == State::Leading)
		return "Leading";
	else if (state == State::Lost)
		return "Lost";
	return {};
}

Frame::State Frame::stringToState(const QString &text) const
{
	if (text == "Found")
		return State::Found;
	else if (text == "Leading")
		return State::Leading;
	else if (text == "Lost")
		return State::Lost;
	return State::Unknown;
}
