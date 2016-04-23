#include "clientrpc.h"

ClientRpc::ClientRpc(QObject *parent) :
  QObject(parent),
  LRpc("../json/lunch_prot.json"),
  m_frameid(0)
{

}

void ClientRpc::sendMethod(const T_RPCMETHODID methodid, QJsonValue params)
{
  QJsonDocument out_json;

  QJsonObject methodobj = getMethodObj(methodid);

  methodobj["params"] = params;
  methodobj["id"] = m_frameid++;

  m_frameid = m_frameid == 100 ? 0 : m_frameid;

  out_json.setObject(methodobj);

  QByteArray outData = out_json.toJson(QJsonDocument::Compact);

  emit sig_sendRequest(outData);
}
