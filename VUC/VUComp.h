/*******************************************************************

        PROPRIETARY NOTICE

These coded instructions, statements, and computer programs contain
proprietary information of the Visual Urlang project, and are protected
under copyright law. They may not be distributed, copied, or used except
under the provisions of the terms of the End-User License Agreement, in
the file "EULA.md", which should have been included with this file.

        Copyright Notice

    (c) 2019 The Visual Urlang Project.
              All rights reserved.
********************************************************************/

#pragma once

#include "Lemon/lemon_base.h"
#include <string>

struct Token
{
    Token() = default;
    Token(const Token &) = default;
    Token(Token &&) = default;

    Token(int i) : intValue(i) {}
    Token(const std::string &s) : stringValue(s) {}
    Token(std::string &&s) : stringValue(std::move(s)) {}

    Token &operator=(const Token &) = default;
    Token &operator=(Token &&) = default;

    int intValue = 0;
    std::string stringValue;
};

class VU_Parser : public lemon_base<Token>
{
  protected:
    std::string fName;
    std::string &fText;
    int m_line = 0, m_col = 0, m_pos = 0;

  public:
    using lemon_base::parse;

    static VU_Parser *create(std::string fName, std::string &fText);

    VU_Parser(std::string f, std::string &ft) : fName(f), fText(ft) {}

    void parse(int major) { parse(major, Token{}); }

    template <class T> void parse(int major, T &&t)
    {
        parse(major, Token(std::forward<T>(t)));
    }

    virtual void trace(FILE *, const char *) = 0;

    /* line tracking */
    void cr()
    {
        m_pos += m_col + 1;
        m_line++;
        m_col = 0;
    }
    void incCol() { m_col++; }
};