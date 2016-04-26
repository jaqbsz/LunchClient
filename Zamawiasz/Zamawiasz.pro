TEMPLATE = app

QT += qml quick
QT += network
CONFIG += c++11

SOURCES += main.cpp \
    src/Lrpc.cpp \
    src/LRpcMethod.cpp \
    src/ordersmodel.cpp \
    src/srvconnection.cpp \
    src/CliRpcReceive.cpp \
    src/CliRpcSend.cpp \
    src/UsersModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/Lrpc.h \
    src/LRpcMethod.h \
    src/order.h \
    src/ordersmodel.h \
    src/srvconnection.h \
    src/CliRpcReceive.h \
    src/CliRpcSend.h \
    src/UsersModel.h \
    src/User.h


RC_ICONS = zamawiasz.ico
