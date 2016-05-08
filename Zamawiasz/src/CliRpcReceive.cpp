#include "CliRpcReceive.h"

//**************************************************************************************
//* constructor()
//*
//**************************************************************************************
CliRpcReceive::CliRpcReceive() :
  LRpc("../json/lunch_prot.json"),
  m_lastrequest(LRPC_MAX),
  m_om(nullptr)
{

}

//**************************************************************************************
//* readResponse()
//*
//**************************************************************************************
void CliRpcReceive::readResponse(QByteArray inData)
{
  qDebug() << "New response received.";

  QJsonParseError parseError;
  QJsonDocument in_json(QJsonDocument::fromJson(inData, &parseError));

  if(parseError.error==QJsonParseError::NoError)  //JSON is in the correct format
  {
    qDebug()<<"json data correct";
    QJsonObject jresponse = in_json.object();

    switch ( m_lastrequest.getId() )
    {
      case M_DELETE_USER:
      case M_LIST_USERS:
        qDebug() << "DELETE_USER or LIST_USERS rsp received";
        if ( m_um )
        {
          QJsonArray rsp = getResultArray(jresponse);

          m_um->clearModel();

          for (int i = 0; i < rsp.size(); i++)
          {
            QJsonObject tmpobj = rsp.at(i).toObject();
            m_um->addUser(  tmpobj["U_ID"].toInt(),
                            tmpobj["F_NAME"].toString(),
                            tmpobj["L_NAME"].toString(),
                            tmpobj["INITIALS"].toString());
          }
        }
        break;

      case M_ADD_USER:
        qDebug() << "ADD_USER rsp received";
        if ( m_um )
        {
          QJsonObject rsp = getResultObj(jresponse);
          m_um->addUser(  rsp["U_ID"].toInt(),
                          rsp["F_NAME"].toString(),
                          rsp["L_NAME"].toString(),
                          rsp["INITIALS"].toString());
        }
        break;

      case M_DELETE_ORDER:
      case M_LIST_ORDERS:
        qDebug() << "DELETE_ORDER or LIST_ORDERS rsp received";
        if ( m_om )
        {
          QJsonArray rsp = getResultArray(jresponse);

          m_om->clearModel();

          for (int i = 0; i < rsp.size(); i++)
          {
            QJsonObject tmpobj = rsp.at(i).toObject();
            m_om->addOrder( tmpobj["O_ID"].toInt(),
                            tmpobj["U_INITIALS"].toString(),
            QString::number(tmpobj["MENU_ITEM"].toInt()),
            QString::number(tmpobj["PRICE"].toInt()));
          }
        }
        break;

      case M_MODIFY_USER:
        qDebug() << "MODIFY_USER rsp received";
        break;

      case M_ADD_ORDER:
        qDebug() << "ADD_ORDER rsp received";
        if ( m_om )
        {
          QString msg = checkResponse(jresponse);

          if ( msg == "OK" )
          {
            QJsonObject rsp = getResultObj(jresponse);
            m_om->addOrder( rsp["O_ID"].toInt(),
                            rsp["U_INITIALS"].toString(),
            QString::number(rsp["MENU_ITEM"].toInt()),
            QString::number(rsp["PRICE"].toInt()));
          }
          else
          {
            qDebug() << msg;
          }
        }
        break;

      case M_MODIFY_ORDER:
        qDebug() << "MODIFY_ORDE rsp received";
        break;

      default:
        qDebug() << "error - invalid request";
        break;
    }

  }
}
