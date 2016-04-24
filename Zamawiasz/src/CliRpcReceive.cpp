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

    switch ( m_lastrequest.getId() )
    {
      case M_LIST_USERS:
        break;

      case M_ADD_USER:
        break;

      case M_DELETE_ORDER:
      case M_LIST_ORDERS:
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

      case M_DELETE_USER:
        break;

      case M_MODIFY_USER:
        break;

      case M_ADD_ORDER:
        if ( m_om )
        {
          QJsonObject rsp = getResultObj(jresponse);
          m_om->addOrder( rsp["O_ID"].toInt(),
                          rsp["U_INITIALS"].toString(),
          QString::number(rsp["MENU_ITEM"].toInt()),
          QString::number(rsp["PRICE"].toInt()));
        }
        break;

      case M_MODIFY_ORDER:
        break;

      default:
        qDebug() << "error - invalid request";
        break;
    }

  }
}
