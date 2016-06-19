#ifndef CLIRPCSEND_H
#define CLIRPCSEND_H

#include "Lrpc.h"
#include "SrvConnection.h"

class SrvConnection;
class RpcReceive;

class RpcSend : public LRpc
{
  public:
    RpcSend();

    bool sendMethod(const T_RPCMETHODID methodid, QJsonValue params = 0 );

    void conn(SrvConnection * conn) {m_conn = conn;}
    void rpcrcv(RpcReceive * rpcrcv) {m_rpcrcv = rpcrcv;}

  private:
    int m_frameid;
    SrvConnection * m_conn;
    RpcReceive * m_rpcrcv;
};

#endif // CLIRPCSEND_H
