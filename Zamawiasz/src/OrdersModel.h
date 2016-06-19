#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>
#include <QStringList>

#include "Order.h"
#include "RpcSend.h"

class RpcSend;

class OrdersModel : public QAbstractTableModel
{
  Q_OBJECT

  public:
    enum OrderRoles
    {
      o_idRole = Qt::UserRole + 1,
      u_initialsRole,
      menu_itemRole,
      priceRole,
      roleCnt = priceRole - Qt::UserRole
    };

    OrdersModel(QObject *parent = 0);

    // todo change this name to addOrderSrv
    void addOrder(const Order &order);

    // todo remove this method, use above instead for adding order form the server
    void addOrder(int o_id, const QString initials, const QString menuItem, const QString price);
    void clearModel();

    // todo change name to addOrderGui
    Q_INVOKABLE void addOrder(const QString initials, const QString menuItem, const QString price);
    Q_INVOKABLE void modifyOrder(const int o_id, const QString initials, const QString menuItem, const QString price);
    Q_INVOKABLE void deleteOrder(const int o_id);
    Q_INVOKABLE void listOrders();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QVariant getId(int row) const;
    Q_INVOKABLE QVariant getInitials(int row) const;
    Q_INVOKABLE QVariant getMenuItem(int row) const;
    Q_INVOKABLE QVariant getPrice(int row) const;

    void rpcsend(RpcSend *rpc) { m_rpc = rpc; }

  protected:
    QHash<int, QByteArray> roleNames() const;

  private:
    RpcSend *m_rpc;
    QList<Order> m_orders;
};

#endif // MODEL_H
