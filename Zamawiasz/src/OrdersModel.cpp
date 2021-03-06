#include "OrdersModel.h"
#include <QDebug>

//**************************************************************************************
//* constructor()
//*
//**************************************************************************************
OrdersModel::OrdersModel(QObject *parent) :
  QAbstractTableModel(parent)
{
}

//**************************************************************************************
//* clearModel()
//*
//**************************************************************************************
void OrdersModel::clearModel()
{
  m_orders.clear();

  beginResetModel();
  endResetModel();
}

//**************************************************************************************
//* addOrder()
//*
//**************************************************************************************
void OrdersModel::addOrder(const Order &order)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_orders << order;
  endInsertRows();
}

//**************************************************************************************
//* addOrder()
//*
//**************************************************************************************
void OrdersModel::addOrder(int o_id, const QString initials, const QString menuItem, const QString price)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount());

  const Order order(o_id, initials, menuItem, price);

  m_orders << order;
  endInsertRows();
}

//**************************************************************************************
//* addOrder()
//*
//**************************************************************************************
void OrdersModel::addOrder(const QString initials, const QString menuItem, const QString price)
{
  qDebug() << "addOrder (QML)";

  QJsonObject params = m_rpc->getParams(M_ADD_ORDER);
  params["MENU_ITEM"] = menuItem.toInt();
  params["PRICE"] = price.toInt();
  params["U_INITIALS"] = initials;

  if ( !m_rpc->sendMethod(M_ADD_ORDER, QJsonValue(params)) )
  {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    const Order order(m_orders.count(), initials, menuItem, price);
    m_orders << order;
    endInsertRows();
  }
}

//**************************************************************************************
//* modifyOrder()
//*
//**************************************************************************************
void OrdersModel::modifyOrder(const int o_id, const QString initials, const QString menuItem, const QString price)
{
  if (o_id < 0 || o_id >= m_orders.count())
    return;

  qDebug() << "modifyOrder (QML): " + QString(o_id);

  m_orders[o_id].u_initials(initials);
  m_orders[o_id].menu_item(menuItem);
  m_orders[o_id].price(price);

  emit dataChanged(index(0, 0), index(m_orders.count() - 1, 0));
}

//**************************************************************************************
//* deleteOrder()
//*
//**************************************************************************************
void OrdersModel::deleteOrder(const int o_id)
{
  qDebug() << "removeOrder (QML): " + QString(o_id);

  if (o_id < 0 || o_id >= m_orders.count())
    return;

  QJsonObject params = m_rpc->getParams(M_DELETE_ORDER);
  params["O_ID"] = o_id+1;

  if ( !m_rpc->sendMethod(M_DELETE_ORDER, QJsonValue(params)) )
  {
    //TODO check removeRows methods.
    //beginRemoveRows(QModelIndex(), o_id, o_id);
    m_orders.removeAt(o_id);
    //endRemoveColumns();

    //quick fix
    beginResetModel();
    endResetModel();
  }
}

//**************************************************************************************
//* listOrders()
//*
//**************************************************************************************
void OrdersModel::listOrders()
{
  m_rpc->sendMethod(M_LIST_ORDERS);
}

//**************************************************************************************
//* rowCount()
//*
//**************************************************************************************
int OrdersModel::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return m_orders.count();
}

//**************************************************************************************
//* columnCount()
//*
//**************************************************************************************
int OrdersModel::columnCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return roleCnt;
}

//**************************************************************************************
//* data()
//*
//**************************************************************************************
QVariant OrdersModel::data(const QModelIndex & index, int role) const
{
  if (index.row() < 0 || index.row() >= m_orders.count())
    return QVariant();

  const Order &order = m_orders[index.row()];

  switch (role)
  {
    case u_initialsRole:
      return order.u_initials();

    case menu_itemRole:
      return order.menu_item();

    case priceRole:
      return order.price();

    case o_idRole:
      return order.o_id();

    default:
      return QVariant();
  }
}

//**************************************************************************************
//* getMenuItem()
//*
//**************************************************************************************
QVariant OrdersModel::getMenuItem(int row) const
{
  if (row < 0 || row >= m_orders.count())
    return QVariant();

  const Order &order = m_orders[row];

  return order.menu_item();
}

//**************************************************************************************
//* getPrice()
//*
//**************************************************************************************
QVariant OrdersModel::getPrice(int row) const
{
  if (row < 0 || row >= m_orders.count())
    return QVariant();

  const Order &order = m_orders[row];

  return order.price();
}

//**************************************************************************************
//* getInitials()
//*
//**************************************************************************************
QVariant OrdersModel::getInitials(int row) const
{
  if (row < 0 || row >= m_orders.count())
    return QVariant();

  const Order &order = m_orders[row];

  return order.u_initials();
}

//**************************************************************************************
//* getId()
//*
//**************************************************************************************
QVariant OrdersModel::getId(int row) const
{
  if (row < 0 || row >= m_orders.count())
    return QVariant();

  const Order &order = m_orders[row];

  return order.o_id();
}

//**************************************************************************************
//* roleNames()
//*
//**************************************************************************************
QHash<int, QByteArray> OrdersModel::roleNames() const
{
  QHash<int, QByteArray> roles;

  roles[o_idRole]       = "o_id";
  roles[u_initialsRole] = "u_initials";
  roles[menu_itemRole]  = "menu_item";
  roles[priceRole]      = "price";

  return roles;
}
