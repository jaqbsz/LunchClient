#ifndef UMODEL_H
#define UMODEL_H

#include <QAbstractListModel>
#include <QStringList>

#include "User.h"
#include "RpcSend.h"

class RpcSend;

class UsersModel : public QAbstractTableModel
{
  Q_OBJECT

  public:
    enum UsersRoles
    {
      u_idRole = Qt::UserRole + 1,
      f_nameRole,
      l_nameRole,
      initialsRole,
      roleCnt = initialsRole - Qt::UserRole
    };

    UsersModel(QObject *parent = 0);
    void addUser(const User &user);
    void addUser(int u_id, const QString f_name, const QString l_name, const QString initials);
    void clearModel();

    Q_INVOKABLE void addUser(const QString f_name, const QString l_name, const QString initials);
    Q_INVOKABLE void modifyUser(int u_id, const QString f_name, const QString l_name, const QString initials);
    Q_INVOKABLE void deleteUser(const int u_id);
    Q_INVOKABLE void listUsers();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QVariant getId(int row) const;
    Q_INVOKABLE QVariant getFname(int row) const;
    Q_INVOKABLE QVariant getLname(int row) const;
    Q_INVOKABLE QVariant getInitials(int row) const;

    void rpcsend(RpcSend *rpc) { m_rpc = rpc; }

  protected:
    QHash<int, QByteArray> roleNames() const;

  private:
    RpcSend *m_rpc;
    QList<User> m_users;
};

#endif // UMODEL_H
