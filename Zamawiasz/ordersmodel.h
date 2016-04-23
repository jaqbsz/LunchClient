#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>
#include <QStringList>

#include "order.h"
#include "src/clientrpc.h"

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

    OrdersModel(ClientRpc &rpc, QObject *parent = 0);
    void addOrder(const Order &order);
    void addOrder(int o_id, const QString initials, const QString menuItem, const QString price);

    Q_INVOKABLE void addOrder(const QString initials, const QString menuItem, const QString price);
    Q_INVOKABLE void modifyOrder(const int o_id, const QString initials, const QString menuItem, const QString price);
    Q_INVOKABLE void deleteOrder(const int o_id);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QVariant getId(int row) const;
    Q_INVOKABLE QVariant getInitials(int row) const;
    Q_INVOKABLE QVariant getMenuItem(int row) const;
    Q_INVOKABLE QVariant getPrice(int row) const;

  protected:
    QHash<int, QByteArray> roleNames() const;

  private:
    ClientRpc &m_rpc;
    QList<Order> m_orders;
};

#endif // MODEL_H
