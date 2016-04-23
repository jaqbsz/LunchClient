#include <QDebug>

#include "clientrpc.h"

ClientRpc::ClientRpc(QObject *parent) :
  QObject(parent),
  LRpc("../json/lunch_prot.json"),
  m_frameid(0),
  m_lastrequest(LRPC_MAX)
{

}

void ClientRpc::sendMethod(const T_RPCMETHODID methodid, QJsonValue params)
{
  qDebug() << "Send prepared data.";

  QJsonDocument out_json;

  QJsonObject methodobj = getMethodObj(methodid);

  methodobj["params"] = params;
  methodobj["id"] = m_frameid++;

  m_frameid = m_frameid == 100 ? 0 : m_frameid;

  out_json.setObject(methodobj);

  QByteArray outData = out_json.toJson(QJsonDocument::Compact);

  m_lastrequest = methodid;

  emit sig_sendRequest(outData);
}

void ClientRpc::slot_readResponse(QByteArray inData)
{
  qDebug() << "New response received.";
}
