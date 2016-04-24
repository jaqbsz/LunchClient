#ifndef CLIRPCSEND_H
#define CLIRPCSEND_H

#include "Lrpc.h"
#include "srvconnection.h"

class SrvConnection;
class CliRpcReceive;

class CliRpcSend : public LRpc
{
  public:
    CliRpcSend();

    void sendMethod(const T_RPCMETHODID methodid, QJsonValue params );

    void conn(SrvConnection * conn) {m_conn = conn;}
    void rpcrcv(CliRpcReceive * rpcrcv) {m_rpcrcv = rpcrcv;}

  private:
    int m_frameid;
    SrvConnection * m_conn;
    CliRpcReceive * m_rpcrcv;
};

#endif // CLIRPCSEND_H
