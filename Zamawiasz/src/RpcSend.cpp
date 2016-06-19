#include "RpcSend.h"

//**************************************************************************************
//* constructor()
//*
//**************************************************************************************
RpcSend::RpcSend() :
  LRpc{"../json/lunch_prot.json"},
  m_frameid{0},
  m_conn{nullptr},
  m_rpcrcv{nullptr}
{
}

//**************************************************************************************
//* sendMethod()
//*
//**************************************************************************************
bool RpcSend::sendMethod(const T_RPCMETHODID methodid, QJsonValue params)
{
  // todo request queue need to be added

  bool res = false;

  qDebug() << "Send prepared data.";

  QJsonObject methodobj = getMethodObj(methodid);

  if ( params != 0 )
  {
    methodobj["params"] = params;
  }

  methodobj["id"] = m_frameid;

  if ( m_rpcrcv )
  {
    // inform receiving module what frame id expect as a response
    m_rpcrcv->lastframeid(m_frameid);

    // inform receiving module what has been asked
    m_rpcrcv->lastrequest(methodid);
  }

  // calculate next frame id
  m_frameid = m_frameid == 100 ? 0 : m_frameid+1;

  QJsonDocument out_json;
  out_json.setObject(methodobj);

  // prepare json to send
  QByteArray outData = out_json.toJson(QJsonDocument::Compact);

  if ( m_conn )
  {
    res = m_conn->sendData(outData);
  }

  // false in case not send (e.g. not connected)
  return res;
}
