/*******************************************************************

        PROPRIETARY NOTICE

These coded instructions, statements, and computer programs contain
proprietary information of the Visual Urlang project, and are protected
under copyright law. They may not be distributed, copied, or used except
under the provisions of the terms of the End-User License Agreement, in
the file "EULA.md", which should have been included with this file.

        Copyright Notice

    (c) 2019-2020 The Visual Urlang Project.
              All rights reserved.
********************************************************************/

#pragma once

/* Details of the position of some source code. */
class Position
{
    size_t m_oldLine, m_oldCol, m_oldPos;
    size_t m_line, m_col, m_pos;

  public:
    Position(size_t oldLine, size_t oldCol, size_t oldPos, size_t line,
             size_t col, size_t pos)
        : m_oldLine(oldLine), m_oldCol(oldCol), m_oldPos(oldPos), m_line(line),
          m_col(col), m_pos(pos)
    {
    }

    /* Get line number */
    size_t line() const;
    /* Get column number*/
    size_t col() const;
    /* Get absolute position in source-file */
    size_t pos() const;
};

inline size_t Position::line() const { return m_line; }

inline size_t Position::col() const { return m_col; }

inline size_t Position::pos() const { return m_pos; }
