#ifndef SRVCONNECTION_H
#define SRVCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QString>
#include <QByteArray>

#include "CliRpcReceive.h"

class CliRpcReceive;

class SrvConnection : public QObject
{
    Q_OBJECT

  public:
    enum ConnState
    {
      UNKNOWN = 0,
      CONNECTED,
      DISCONNECTED
    };

    explicit SrvConnection(const QObject * qmlObjSettings, QObject *parent = 0);

    void doConnect(QString hostname, int portnr);

    ConnState state() { return m_state; }

    //qint64 sendData( const QByteArray &outData );

    bool sendData( const QByteArray &outData );
    void rpcrecv(CliRpcReceive * rpc) {m_rpcrecv = rpc;}

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
      const QObject * qmlObjSettings;

      ConnState m_state;
      CliRpcReceive * m_rpcrecv;
};

#endif // SRVCONNECTION_H
