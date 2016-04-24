#include "CliRpcSend.h"

CliRpcSend::CliRpcSend() :
  LRpc("../json/lunch_prot.json"),
  m_frameid(0),
  m_conn(nullptr),
  m_rpcrcv(nullptr)
{
}

void CliRpcSend::sendMethod(const T_RPCMETHODID methodid, QJsonValue params)
{
  qDebug() << "Send prepared data.";

  QJsonDocument out_json;

  QJsonObject methodobj = getMethodObj(methodid);

  methodobj["params"] = params;
  methodobj["id"] = m_frameid;

  if ( m_rpcrcv )
  {
    m_rpcrcv->lastframeid(m_frameid);
    m_rpcrcv->lastrequest(methodid);
  }

  m_frameid = m_frameid == 100 ? 0 : m_frameid+1;

  out_json.setObject(methodobj);

  QByteArray outData = out_json.toJson(QJsonDocument::Compact);

  if ( m_conn )
  {
    m_conn->sendData(outData);
  }
}
