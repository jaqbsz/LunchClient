#ifndef CLIRPCRECEIVE_H
#define CLIRPCRECEIVE_H

#include "ordersmodel.h"
#include "UsersModel.h"
#include "Lrpc.h"

class OrdersModel;
class UsersModel;

class CliRpcReceive : public LRpc
{
  public:
    CliRpcReceive();

    void readResponse(QByteArray inData);

    void omodel(OrdersModel * om) {m_om = om;}
    void umodel(UsersModel * um) {m_um = um;}
    void lastframeid(int id) {m_lastframeid = id;}
    void lastrequest(int id) {m_lastrequest = static_cast<T_RPCMETHODID>(id);}

  private:
    int m_lastframeid;
    LRpcMethod m_lastrequest;
    OrdersModel * m_om;
    UsersModel * m_um;
};

#endif // CLIRPCRECEIVE_H
