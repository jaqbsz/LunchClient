#include "srvconnection.h"

#include <QString>

SrvConnection::SrvConnection(const QObject * qmlObjSettings, QObject *parent) :
    QObject(parent),
    qmlObjSettings(qmlObjSettings),
    m_state(UNKNOWN),
    m_rpcrecv(nullptr)
{
}

void SrvConnection::doConnect(QString hostname, int portnr)
{
  m_socket = new QTcpSocket(this);

  connect(m_socket, SIGNAL(connected()),this, SLOT(connected()));
  connect(m_socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
  connect(m_socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
  connect(m_socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

  qDebug() << "connecting with " + hostname;

  // this is not blocking call
  m_socket->connectToHost(hostname, portnr);

  // we need to wait...
  // this is blocking function!!!
  if(!m_socket->waitForConnected(1000))
  {
    qDebug() << "Error: " << m_socket->errorString();
    m_state = DISCONNECTED;
  }
  else
    m_state = CONNECTED;
}

//qint64 SrvConnection::sendData(const QByteArray &outData)
//{
//  return m_socket->write(outData);
//}

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
  QByteArray data = m_socket->readAll();
  qDebug() << data;

  //emit sig_newResponse(data);

  if ( m_rpcrecv )
    m_rpcrecv->readResponse(data);
}

void SrvConnection::sendData(const QByteArray &outData)
{
  if ( m_state == CONNECTED )
  {
    m_socket->write(outData);
    m_socket->flush();
  }
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
  m_socket->disconnectFromHost();
}
