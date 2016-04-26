#ifndef USER_H
#define USER_H

#include <QString>

class User
{
  public:
      User(const int u_id, const QString & f_name, const QString & l_name, const QString & initials):
        m_u_id(u_id),
        m_fname(f_name),
        m_lname(l_name),
        m_initials(initials)
      {}

      int     u_id()        const { return m_u_id; }

      QString fname()  const { return m_fname; }
      void    fname( QString f_name) { m_fname = f_name; }

      QString lname()   const { return m_lname; }
      void    lname( QString l_name) { m_lname = l_name; }

      QString initials() const { return m_initials; }
      void    initials( QString initials) { m_initials = initials; }

  private:
      int     m_u_id;
      QString m_fname;
      QString m_lname;
      QString m_initials;
};

#endif // USER_H
