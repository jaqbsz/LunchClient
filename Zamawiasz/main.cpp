#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "src/srvconnection.h"

#include <QObject>
#include <qqmlcontext.h>

#include "src/ordersmodel.h"
#include "src/order.h"
#include "src/CliRpcReceive.h"
#include "src/CliRpcSend.h"

int main(int argc, char *argv[])
{
  qDebug() << "Application started...";

  QGuiApplication app(argc, argv);

  CliRpcSend rpcsend;
  CliRpcReceive rpcrecv;
  OrdersModel omodel;

  // test only
  omodel.addOrder(Order(0, "Wolf", "Medium", "aa"));
  omodel.addOrder(Order(1, "Polar bear", "Large", "bb"));
  omodel.addOrder(Order(2, "Quoll", "Small", "cc"));
  //

  QQmlApplicationEngine engine;

  QQmlContext *ctxt = engine.rootContext();
  ctxt->setContextProperty("ordersModel", &omodel);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  QObject *rootObject = engine.rootObjects().first();
  QObject *qmlObj_topBar = rootObject->findChild<QObject*>("topBar");
  QObject *qmlObj_settings = rootObject->findChild<QObject*>("settings");

  SrvConnection connection(qmlObj_settings);

  // define data flow between objects
  omodel.rpcsend(&rpcsend);     // model to rpcsend
  rpcsend.rpcrcv(&rpcrecv);     // rpcsend to rpcrecive - so rpcreceive knows what should be received
  rpcsend.conn(&connection);    // rpcsend to socket
  connection.rpcrecv(&rpcrecv); // socket to rpcreceive
  rpcrecv.omodel(&omodel);      // rpcreceive to model

  // socket - connect
  QObject::connect(qmlObj_topBar, SIGNAL(tb_connect()),
                   &connection,   SLOT(qmlConnect()));
  // socket - disconnect
  QObject::connect(qmlObj_topBar, SIGNAL(tb_disconnect()),
                   &connection,   SLOT(qmlDisconnect()));
  // socket - state changed
  QObject::connect(&connection,   SIGNAL(qmlConnected(QVariant)),
                   rootObject,    SLOT(signalConnected(QVariant)));

  return app.exec();
}
