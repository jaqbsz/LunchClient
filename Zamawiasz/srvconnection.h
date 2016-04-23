#ifndef SRVCONNECTION_H
#define SRVCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QString>
#include <QByteArray>

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

  signals:
      void qmlConnected(QVariant state);

  public slots:
      void connected();
      void disconnected();
      void bytesWritten(qint64 bytes);
      void readyRead();
      void sendData( const QByteArray &outData );

      void qmlConnect();
      void qmlDisconnect();

  private:
      QTcpSocket *m_socket;

      //TODO this should be a class holding settings
      const QObject * qmlObjSettings;

      ConnState m_state;
};

#endif // SRVCONNECTION_H
