#ifndef LRPC_H
#define LRPC_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "LRpcMethod.h"

class LRpc
{
  public:
    explicit LRpc(const char * file_name);

    QJsonObject getRpcObj()
    {
      return this->rpcObj;
    }

    QJsonObject getErrorObj   (const char * err_name);
    QJsonObject getResultObj  (const QString &res_name);
    QJsonObject getResultObj  (const QJsonObject &frameObj);
    QJsonArray  getResultArray(const QJsonObject &frameObj);
    QJsonObject getResultObj  (const LRpcMethod &lrpcMeth);
    QJsonObject getMethodObj  (const T_RPCMETHODID methodid);
    QJsonValue  getResultValue(const QString &res_name);
    QJsonValue  getFrameId    (const QJsonObject & frameObj);
    QJsonValue  getParams     (const QJsonObject & frameObj);
    QJsonObject getParams     (const T_RPCMETHODID methodid);

  private:
    QJsonObject rpcObj;

};

#endif // LRPC_H
