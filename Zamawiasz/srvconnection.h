#ifndef SRVCONNECTION_H
#define SRVCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QString>

class SrvConnection : public QObject
{
    Q_OBJECT

  public:
    explicit SrvConnection(const QObject * qmlObjSettings, QObject *parent = 0);

    void doConnect(QString hostname, int portnr);

  signals:
      void qmlConnected(QVariant state);

  public slots:
      void connected();
      void disconnected();
      void bytesWritten(qint64 bytes);
      void readyRead();

      void qmlConnect();
      void qmlDisconnect();

  private:
      QTcpSocket *socket;
      const QObject * qmlObjSettings;
};

#endif // SRVCONNECTION_H
