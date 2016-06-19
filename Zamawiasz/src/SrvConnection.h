#ifndef SRVCONNECTION_H
#define SRVCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QString>
#include <QByteArray>

#include "RpcReceive.h"

class RpcReceive;

class SrvConnection : public QObject
{
    Q_OBJECT

  public:
    enum class ConnState
    {
      UNKNOWN,
      CONNECTED,
      DISCONNECTED
    };

    explicit SrvConnection(const QObject * m_qmlObjSettings, QObject *parent = 0);

    void doConnect(QString hostname, int portnr);
    ConnState state() { return m_state; }
    bool sendData( const QByteArray &outData );
    void rpcrecv(RpcReceive * rpc) {m_rpcrecv = rpc;}

  signals:
      void qmlConnected(QVariant state);
      void sig_newResponse(QByteArray inData);

  public slots:
      void connected();
      void disconnected();
      void bytesWritten(qint64 bytes);
      void readyRead();

      void qmlConnect();
      void qmlDisconnect();

  private:
      QTcpSocket *m_socket;

      //TODO this should be a class holding settings
      const QObject * m_qmlObjSettings;

      ConnState m_state;
      RpcReceive * m_rpcrecv;
};

#endif // SRVCONNECTION_H
