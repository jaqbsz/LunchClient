#include "SrvConnection.h"
#include <QString>

//**************************************************************************************
//* constructor()
//*
//**************************************************************************************
SrvConnection::SrvConnection(const QObject * qmlObjSettings, QObject *parent) :
    QObject(parent),
    m_qmlObjSettings(qmlObjSettings),
    m_state(SrvConnection::ConnState::UNKNOWN),
    m_rpcrecv(nullptr)
{
}

//**************************************************************************************
//* doConnect()
//*
//**************************************************************************************
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
    m_state = SrvConnection::ConnState::DISCONNECTED;
  }
  else
    m_state = SrvConnection::ConnState::CONNECTED;
}

//**************************************************************************************
//* connected()
//*
//**************************************************************************************
void SrvConnection::connected()
{
  qDebug() << "connected...";
  emit qmlConnected(true);
}

//**************************************************************************************
//* disconnected()
//*
//**************************************************************************************
void SrvConnection::disconnected()
{
  qDebug() << "disconnected...";
  emit qmlConnected(false);
}

//**************************************************************************************
//* bytesWritten()
//*
//**************************************************************************************
void SrvConnection::bytesWritten(qint64 bytes)
{
  qDebug() << bytes << " bytes written...";
}

//**************************************************************************************
//* readyRead()
//*
//**************************************************************************************
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

//**************************************************************************************
//* sendData()
//*
//**************************************************************************************
bool SrvConnection::sendData(const QByteArray &outData)
{
  bool res = false;

  qDebug() << "Sending... ";

  if ( m_state == SrvConnection::ConnState::CONNECTED )
  {
    m_socket->write(outData);
    m_socket->flush();
    res = true;
  }

  qDebug() << res;

  return res;
}

//**************************************************************************************
//* qmlConnect()
//*
//**************************************************************************************
void SrvConnection::qmlConnect()
{
  qDebug() << "QmlConnect...";

  QString hostname = m_qmlObjSettings->property("hostname").toString();
  int portnr = m_qmlObjSettings->property("portnr").toInt();

  doConnect(hostname, portnr);
}

//**************************************************************************************
//* qmlDisconnect()
//*
//**************************************************************************************
void SrvConnection::qmlDisconnect()
{
  qDebug() << "Disconnect...";
  m_socket->disconnectFromHost();
}
