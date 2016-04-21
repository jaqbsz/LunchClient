#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>
#include <QStringList>

#include "order.h"

class OrdersModel : public QAbstractTableModel
{
  Q_OBJECT

  public:
    enum OrderRoles
    {
      u_initialsRole = Qt::UserRole + 1,
      menu_itemRole,
      priceRole
    };

    OrdersModel(QObject *parent = 0);
    void addOrder(const Order &order);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QVariant getInitials(int row) const;
    Q_INVOKABLE QVariant getMenuItem(int row) const;
    Q_INVOKABLE QVariant getPrice(int row) const;

  protected:
    QHash<int, QByteArray> roleNames() const;

  private:
    QList<Order> m_orders;
};

#endif // MODEL_H
