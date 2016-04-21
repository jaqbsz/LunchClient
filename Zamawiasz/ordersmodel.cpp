#include "ordersmodel.h"

OrdersModel::OrdersModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void OrdersModel::addOrder(const Order &order)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_orders << order;
  endInsertRows();
}

int OrdersModel::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return m_orders.count();
}

int OrdersModel::columnCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);

  /// !!!!!!!!
  /// TODO chage this value to some more generic code
  /// !!!!!!!!
  return 3;
}

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

    default:
      return QVariant();
  }
}

QVariant OrdersModel::getMenuItem(int row) const
{
  if (row < 0 || row >= m_orders.count())
    return QVariant();

  const Order &order = m_orders[row];

  return order.menu_item();
}

QVariant OrdersModel::getPrice(int row) const
{
  if (row < 0 || row >= m_orders.count())
    return QVariant();

  const Order &order = m_orders[row];

  return order.price();
}

QVariant OrdersModel::getInitials(int row) const
{
  if (row < 0 || row >= m_orders.count())
    return QVariant();

  const Order &order = m_orders[row];

  return order.u_initials();
}

QHash<int, QByteArray> OrdersModel::roleNames() const
{
  QHash<int, QByteArray> roles;

  roles[u_initialsRole] = "u_initials";
  roles[menu_itemRole] = "menu_item";
  roles[priceRole] = "price";

  return roles;
}
