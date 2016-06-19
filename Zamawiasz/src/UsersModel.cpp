#include "UsersModel.h"
#include <QDebug>

//**************************************************************************************
//* constructor()
//*
//**************************************************************************************
UsersModel::UsersModel(QObject *parent) :
  QAbstractTableModel(parent)
{
}

//**************************************************************************************
//* clearModel()
//*
//**************************************************************************************
void UsersModel::clearModel()
{
  m_users.clear();

  beginResetModel();
  endResetModel();
}

//**************************************************************************************
//* addUser()
//*
//**************************************************************************************
void UsersModel::addUser(const User &user)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_users << user;
  endInsertRows();
}

//**************************************************************************************
//* addUser()
//*
//**************************************************************************************
void UsersModel::addUser(int u_id, const QString f_name, const QString l_name, const QString initials)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount());

  const User user(u_id, f_name, l_name, initials);

  m_users << user;
  endInsertRows();
}

//**************************************************************************************
//* addUser()
//*
//**************************************************************************************
void UsersModel::addUser(const QString f_name, const QString l_name, const QString initials)
{
  qDebug() << "addUser (QML)";

  QJsonObject params = m_rpc->getParams(M_ADD_USER);
  params["F_NAME"] = f_name;
  params["L_NAME"] = l_name;
  params["INITIALS"] = initials;

  if ( !m_rpc->sendMethod(M_ADD_USER, QJsonValue(params)) )
  {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    const User user(m_users.count(), f_name, l_name, initials);
    m_users << user;
    endInsertRows();
  }
}

//**************************************************************************************
//* modifyUser()
//*
//**************************************************************************************
void UsersModel::modifyUser(int u_id, const QString f_name, const QString l_name, const QString initials)
{
  if (u_id < 0 || u_id >= m_users.count())
    return;

  qDebug() << "modifyUser (QML): " + QString(u_id);

  m_users[u_id].fname(f_name);
  m_users[u_id].lname(l_name);
  m_users[u_id].initials(initials);

  emit dataChanged(index(0, 0), index(m_users.count() - 1, 0));
}

//**************************************************************************************
//* deleteUser()
//*
//**************************************************************************************
void UsersModel::deleteUser(const int u_id)
{
  qDebug() << "removeUser (QML): " + QString(u_id);

  if (u_id < 0 || u_id >= m_users.count())
    return;

  QJsonObject params = m_rpc->getParams(M_DELETE_USER);
  params["U_ID"] = u_id+1;

  if ( !m_rpc->sendMethod(M_DELETE_USER, QJsonValue(params)) )
  {
    //TODO check removeRows methods.
    //beginRemoveRows(QModelIndex(), u_id, u_id);
    m_users.removeAt(u_id);
    //endRemoveColumns();

    //quick fix
    beginResetModel();
    endResetModel();
  }
}

//**************************************************************************************
//* listUsers()
//*
//**************************************************************************************
void UsersModel::listUsers()
{
  m_rpc->sendMethod(M_LIST_USERS);
}

//**************************************************************************************
//* rowCount()
//*
//**************************************************************************************
int UsersModel::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return m_users.count();
}

//**************************************************************************************
//* columnCount()
//*
//**************************************************************************************
int UsersModel::columnCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return roleCnt;
}

//**************************************************************************************
//* data()
//*
//**************************************************************************************
QVariant UsersModel::data(const QModelIndex & index, int role) const
{
  if (index.row() < 0 || index.row() >= m_users.count())
    return QVariant();

  const User &user = m_users[index.row()];

  switch (role)
  {
    case f_nameRole:
      return user.fname();

    case l_nameRole:
      return user.lname();

    case initialsRole:
      return user.initials();

    case u_idRole:
      return user.u_id();

    default:
      return QVariant();
  }
}

//**************************************************************************************
//* getFname()
//*
//**************************************************************************************
QVariant UsersModel::getFname(int row) const
{
  if (row < 0 || row >= m_users.count())
    return QVariant();

  const User &user = m_users[row];

  return user.fname();
}

//**************************************************************************************
//* getLname()
//*
//**************************************************************************************
QVariant UsersModel::getLname(int row) const
{
  if (row < 0 || row >= m_users.count())
    return QVariant();

  const User &user = m_users[row];

  return user.lname();
}

//**************************************************************************************
//* getInitials()
//*
//**************************************************************************************
QVariant UsersModel::getInitials(int row) const
{
  if (row < 0 || row >= m_users.count())
    return QVariant();

  const User &user = m_users[row];

  return user.initials();
}

//**************************************************************************************
//* getId()
//*
//**************************************************************************************
QVariant UsersModel::getId(int row) const
{
  if (row < 0 || row >= m_users.count())
    return QVariant();

  const User &user = m_users[row];

  return user.u_id();
}

//**************************************************************************************
//* roleNames()
//*
//**************************************************************************************
QHash<int, QByteArray> UsersModel::roleNames() const
{
  QHash<int, QByteArray> roles;

  roles[u_idRole]     = "u_id";
  roles[f_nameRole]   = "f_name";
  roles[l_nameRole]   = "l_name";
  roles[initialsRole] = "initials";

  return roles;
}
