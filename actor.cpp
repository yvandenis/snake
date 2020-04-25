#include "actor.h"
#include <sstream>
#include <utility>
#include <fstream>
#include "QString"
#include <QTextStream>
#include <QDataStream>
#include <QHash>
#include <QFile>
#include <QDirIterator>


QDataStream &operator<<(QDataStream &out, const Actor &actor)
{
    out << actor.getName();
    for(auto iter=actor.getParams().begin(); iter!=actor.getParams().end(); iter++){
        out << iter.key();
        out << QString::number(iter.value());
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, Actor &actor)
{
    QString name;
    QHash<QString, double> params;
    in >> name;
    while (!(in.atEnd())) {
        QString key;
        QString val;
        in >> key;
        in >> val;
        bool ok = false;
        params.insert(key, val.toDouble(&ok));
    }
    actor.setName(name);
    actor.setParams(params);
    return in;
}

QHash<QString, double> Actor::getParams() const
{
    return params;
}

void Actor::setParams(const QHash<QString, double> &value)
{
    params = value;
}

QString Actor::getName() const
{
    return name;
}

void Actor::setName(const QString &value)
{
    name = value;
}

int Actor::getCurrentDirection() const
{
    return currentDirection;
}

void Actor::setCurrentDirection(int value)
{
    currentDirection = value;
}

Actor::Actor(QString name)
{
    this->name = name;
    this->currentDirection = 0;
}
Actor::Actor(QString name, QHash<QString, double> params)
{
    this->name = name;
    this->currentDirection = 0;
    this->params = params;
}

Actor::~Actor(){}

void Actor::saveActor(QString pathToSave){
    QString fileName = pathToSave+this->name+".txt";
    QFile file(fileName);
    QDataStream out(&file);
    out << this;
}

void Actor::loadActor(QString pathToSave){
    QString fileName = pathToSave+this->name+".txt";
    QFile file(fileName);
    QDataStream in(&file);
    in >> *this;
}
