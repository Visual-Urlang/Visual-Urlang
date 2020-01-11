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

#include <string>

#include "AST/Position.h"
#include "AST/Unit.h"
#include "Lemon/lemon_base.h"

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
    Unit *m_mod;
    int m_line = 0, m_col = 0, m_pos = 0;
    int m_oldLine = 0, m_oldCol = 0, m_oldPos = 0;

  public:
    int line() const;
    int col() const;
    int pos1() const;
    using lemon_base::parse;

    static VU_Parser *create(std::string fName, std::string &fText);

    VU_Parser(std::string f, std::string &ft) : fName(f), fText(ft) {}

    /* parsing */
    void parse(int major) { parse(major, Token{}); }

    template <class T> void parse(int major, T &&t)
    {
        parse(major, Token(std::forward<T>(t)));
    }

    virtual void trace(FILE *, const char *) = 0;

    /* misc */
    Unit *mod() { return m_mod; }

    /* line tracking */
    Position pos();

    void recOldPos()
    {
        m_oldPos = m_pos;
        m_oldLine = m_line;
        m_oldCol = m_col;
    }

    void cr()
    {
        m_pos += m_col + 1;
        m_line++;
        m_col = 0;
    }
    void incCol() { m_col++; }
};

inline int VU_Parser::line() const { return m_line; }

inline int VU_Parser::col() const { return m_col; }

inline int VU_Parser::pos1() const { return m_pos; }