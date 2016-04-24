#include "CliRpcReceive.h"

CliRpcReceive::CliRpcReceive() :
  LRpc("../json/lunch_prot.json"),
  m_lastrequest(LRPC_MAX),
  m_om(nullptr)
{

}


void CliRpcReceive::readResponse(QByteArray inData)
{
  qDebug() << "New response received.";

  QJsonParseError parseError;
  QJsonDocument in_json(QJsonDocument::fromJson(inData, &parseError));

  if(parseError.error==QJsonParseError::NoError)  //JSON is in the correct format
  {
    qDebug()<<"json data correct";
    QJsonObject jresponse = in_json.object();


  }
}
