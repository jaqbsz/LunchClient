#include "srvconnection.h"

#include <QString>

SrvConnection::SrvConnection(const QObject * qmlObjSettings, QObject *parent) :
    QObject(parent),
    qmlObjSettings(qmlObjSettings)
{
}

void SrvConnection::doConnect(QString hostname, int portnr)
{
  socket = new QTcpSocket(this);

  connect(socket, SIGNAL(connected()),this, SLOT(connected()));
  connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
  connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
  connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

  qDebug() << "connecting with " + hostname;

  // this is not blocking call
  socket->connectToHost(hostname, portnr);

  // we need to wait...
  // this is blocking function!!!
  if(!socket->waitForConnected(1000))
  {
    qDebug() << "Error: " << socket->errorString();
  }
}

void SrvConnection::connected()
{
  qDebug() << "connected...";
  emit this->qmlConnected(true);
}

void SrvConnection::disconnected()
{
  qDebug() << "disconnected...";
  emit this->qmlConnected(false);
}

void SrvConnection::bytesWritten(qint64 bytes)
{
  qDebug() << bytes << " bytes written...";
}

void SrvConnection::readyRead()
{
  qDebug() << "reading...";

  // read the data from the socket
  qDebug() << socket->readAll();
}

void SrvConnection::qmlConnect()
{
  qDebug() << "QmlConnect...";

  QString hostname = this->qmlObjSettings->property("hostname").toString();
  int portnr = this->qmlObjSettings->property("portnr").toInt();

  this->doConnect(hostname, portnr);
}

void SrvConnection::qmlDisconnect()
{
  qDebug() << "Disconnect...";
  socket->disconnectFromHost();
}
