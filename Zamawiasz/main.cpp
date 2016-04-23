#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "srvconnection.h"

#include <QObject>
#include <qqmlcontext.h>

#include "ordersmodel.h"
#include "order.h"
#include "src/clientrpc.h"

int main(int argc, char *argv[])
{
  qDebug() << "Application started...";

  QGuiApplication app(argc, argv);

  ClientRpc rpc;
  OrdersModel model(rpc);

  // test only
  model.addOrder(Order(0, "Wolf", "Medium", "aa"));
  model.addOrder(Order(1, "Polar bear", "Large", "bb"));
  model.addOrder(Order(2, "Quoll", "Small", "cc"));
  //

  QQmlApplicationEngine engine;

  QQmlContext *ctxt = engine.rootContext();
  ctxt->setContextProperty("ordersModel", &model);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  QObject *rootObject = engine.rootObjects().first();
  QObject *qmlObj_topBar = rootObject->findChild<QObject*>("topBar");
  QObject *qmlObj_settings = rootObject->findChild<QObject*>("settings");

  SrvConnection connection(qmlObj_settings);

  // socket - connect
  QObject::connect(qmlObj_topBar, SIGNAL(tb_connect()),
                   &connection,   SLOT(qmlConnect()));
  // socket - disconnect
  QObject::connect(qmlObj_topBar, SIGNAL(tb_disconnect()),
                   &connection,   SLOT(qmlDisconnect()));
  // socket - state changed
  QObject::connect(&connection,   SIGNAL(qmlConnected(QVariant)),
                   rootObject,    SLOT(signalConnected(QVariant)));
  // rpc - send data
  QObject::connect(&rpc,          SIGNAL(sig_sendRequest(QByteArray)),
                   &connection,   SLOT(sendData(QByteArray)));

  return app.exec();
}
