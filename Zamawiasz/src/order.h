#ifndef ORDER_H
#define ORDER_H

#include <QString>

class Order
{
  public:
      Order(const int o_id, const QString & u_initials, const QString & menu_item, const QString & price):
        m_o_id(o_id),
        m_u_initials(u_initials),
        m_menu_item(menu_item),
        m_price(price)
      {}

      int     o_id()        const { return m_o_id; }

      QString u_initials()  const { return m_u_initials; }
      void    u_initials( QString initials) { m_u_initials = initials; }

      QString menu_item()   const { return m_menu_item; }
      void    menu_item( QString mitem) { m_menu_item = mitem; }

      QString price() const { return m_price; }
      void    price( QString price) { m_price = price; }

  private:
      int     m_o_id;
      QString m_u_initials;
      QString m_menu_item;
      QString m_price;
};

#endif // ORDER_H
