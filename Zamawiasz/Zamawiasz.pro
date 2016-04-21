TEMPLATE = app

QT += qml quick
QT += network
CONFIG += c++11

SOURCES += main.cpp \
    srvconnection.cpp \
    ordersmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    srvconnection.h \
    order.h \
    ordersmodel.h


RC_ICONS = zamawiasz.ico
