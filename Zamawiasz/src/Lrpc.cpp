#include "Lrpc.h"

#include <QFile>
#include <QDebug>


//**************************************************************************************
//* constructor
//*
//**************************************************************************************
LRpc::LRpc(const char *file_name)
{
  QFile file;

  file.setFileName(file_name);
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QByteArray file_data = file.readAll();
  file.close();

  QJsonDocument jsonDoc = QJsonDocument::fromJson(file_data);

  // todo this could be done as static field
  m_rpcObj = jsonDoc.object();
}

//**************************************************************************************
//* getErrorObj()
//*
//**************************************************************************************
QJsonObject LRpc::getErrorObj(const char *err_name)
{
  QJsonObject::const_iterator i_error = m_rpcObj.find(err_name);
  return i_error.value().toObject();
}

//**************************************************************************************
//* getResultObj()
//*
//**************************************************************************************
QJsonObject LRpc::getResultObj(const QString & res_name)
{
  //TODO throw exceptions

  QJsonObject result;

  QJsonObject::const_iterator i_method = m_rpcObj.find(res_name);

  if (i_method == m_rpcObj.end())
  {
    qDebug() << "getResultObj error e_32601";
    result = getErrorObj("e_32601");
  }
  else
  {
    result = i_method.value().toObject();
  }

  return result;
}


//**************************************************************************************
//* checkResponse()
//*
//**************************************************************************************
QString LRpc::checkResponse(const QJsonObject &frameObj)
{
  QJsonObject check_err = frameObj.value("error").toObject();

  if (check_err.empty())
    return "OK";
  else
    return check_err["message"].toString();
}

//**************************************************************************************
//* getResultObj()
//*
//**************************************************************************************
QJsonObject LRpc::getResultObj(const QJsonObject &frameObj)
{
  return frameObj.value("result").toObject();
}

//**************************************************************************************
//* getResultArray()
//*
//**************************************************************************************
QJsonArray LRpc::getResultArray(const QJsonObject &frameObj)
{
  return frameObj.value("result").toArray();
}

//**************************************************************************************
//* getResultObj()
//*
//**************************************************************************************
QJsonObject LRpc::getResultObj(const LRpcMethod &lrpcMeth)
{
  //TODO throw exceptions

  QJsonObject result;

  QJsonObject::const_iterator i_method = m_rpcObj.find(lrpcMeth.getNameObj());

  if (i_method == m_rpcObj.end())
  {
    qDebug() << "getResultObj error e_32601";
    result = getErrorObj("e_32601");
  }
  else
  {
    result = i_method.value().toObject();
  }

  return result;
}

//**************************************************************************************
//* getMethodObj()
//*
//**************************************************************************************
QJsonObject LRpc::getMethodObj(const T_RPCMETHODID methodid)
{
  LRpcMethod rmethod = methodid;
  QJsonObject::const_iterator i_method = m_rpcObj.find(rmethod.getNameObj());
  QJsonObject methodobj = i_method.value().toObject();
  return methodobj;
}

//**************************************************************************************
//* getResultValue()
//*
//**************************************************************************************
QJsonValue LRpc::getResultValue(const QString & res_name)
{
  //TODO throw exceptions

  QJsonObject::const_iterator i_method = m_rpcObj.find(res_name);

  if (i_method == m_rpcObj.end())
  {
    qDebug() << "getResultValue OBJ parse error";
    throw "parse error";
  }


  QJsonObject objResult = i_method.value().toObject();
  QJsonObject::const_iterator i_result = objResult.find("result");

  if (i_result == objResult.end())
  {
    qDebug() << "getResultValue RES parse error";
    throw "parse error";
  }

  return i_result.value();
}

//**************************************************************************************
//* getFrameId()
//*
//**************************************************************************************
QJsonValue LRpc::getFrameId(const QJsonObject &frameObj)
{
  return frameObj.value("id");
}

//**************************************************************************************
//* getParams()
//*
//**************************************************************************************
QJsonValue LRpc::getParams(const QJsonObject &frameObj)
{
  return frameObj.find("params").value();
}

//**************************************************************************************
//* getParams()
//*
//**************************************************************************************
QJsonObject LRpc::getParams(const T_RPCMETHODID methodid)
{
  //TODO throw exceptions

  LRpcMethod method = methodid;

  QJsonObject::const_iterator i_method = m_rpcObj.find(method.getNameObj());

  QJsonObject jmethod = i_method.value().toObject();
  QJsonObject::const_iterator i_params = jmethod.find("params");

  if (i_params == jmethod.end())
  {
    qDebug() << "No params for this method";
    //TODO support for non "params" methods (list_orders, list_users)
    throw "No params for this method";
  }

  return i_params.value().toObject();
}
