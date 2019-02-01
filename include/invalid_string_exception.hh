#ifndef USY_INVALID_STRING_EXCEPTION_H
#define USY_INVALID_STRING_EXCEPTION_H

#include <string>

namespace usys {

class InvalidString : std::exception
{
  public:
    InvalidString(const std::string &msg) : m_msg(msg) {}

    virtual const char *what() const throw()
    {
        return m_msg.c_str();
    }

  private:
    const std::string m_msg;
};

} // end of namespace
#endif