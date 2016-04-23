#ifndef CLIENTRPC_H
#define CLIENTRPC_H

#include <QObject>

#include "Lrpc.h"

class ClientRpc : public QObject, public LRpc
{
    Q_OBJECT
  public:
    explicit ClientRpc(QObject *parent = 0);

    void sendMethod(const T_RPCMETHODID methodid, QJsonValue params );

  signals:
    void sig_sendRequest(QByteArray outData);

  public slots:

  private:
    int m_frameid;
};

#endif // CLIENTRPC_H
