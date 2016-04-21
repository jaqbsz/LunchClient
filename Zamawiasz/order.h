#ifndef ORDER_H
#define ORDER_H

#include <QString>

class Order
{
  public:
      Order(const QString & u_initials, const QString & menu_item, const QString & price):
        m_u_initials(u_initials),
        m_menu_item(menu_item),
        m_price(price)
      {}

      QString u_initials()  const { return m_u_initials; }
      QString menu_item()   const { return m_menu_item; }
      QString price()       const { return m_price; }

  private:
      QString m_u_initials;
      QString m_menu_item;
      QString m_price;
};

#endif // ORDER_H
