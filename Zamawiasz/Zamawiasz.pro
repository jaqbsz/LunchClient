TEMPLATE = app

QT += qml quick
QT += network
CONFIG += c++11

SOURCES += main.cpp \
    src/Lrpc.cpp \
    src/LRpcMethod.cpp \
    src/CliRpcReceive.cpp \
    src/CliRpcSend.cpp \
    src/UsersModel.cpp \
    src/SrvConnection.cpp \
    src/OrdersModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/Lrpc.h \
    src/LRpcMethod.h \
    src/CliRpcReceive.h \
    src/CliRpcSend.h \
    src/UsersModel.h \
    src/User.h \
    src/SrvConnection.h \
    src/OrdersModel.h \
    src/Order.h


RC_ICONS = zamawiasz.ico
