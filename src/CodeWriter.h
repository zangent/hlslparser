//=============================================================================
//
// Render/CodeWriter.h
//
// Created by Max McGuire (max@unknownworlds.com)
// Copyright (c) 2013, Unknown Worlds Entertainment, Inc.
//
//=============================================================================

#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include "Engine.h"
#include <string>

namespace M4
{

class Allocator;

/**
 * This class is used for outputting code. It handles indentation and inserting #line markers
 * to match the desired output line numbers.
 */
class CodeWriter
{

public:

    CodeWriter();

    void BeginLine(int indent, const char* fileName = NULL, int lineNumber = -1);
    void Write(const char* format, ...) __attribute__((format (printf, 2, 3)));
    void EndLine(const char* text = NULL);

    void WriteLine(int indent, const char* format, ...) __attribute__((format (printf, 3, 4)));
    void WriteLine(int indent, const char* fileName, int lineNumber, const char* format, ...) __attribute__((format (printf, 5, 6)));

    const char* GetResult() const;
    void Reset();

private:

    std::string     m_buffer;
    int             m_currentLine;
    const char*     m_currentFileName;
    int             m_spacesPerIndent;
    bool            m_writeLines;
    bool            m_writeFileNames;

};

}

#endif
