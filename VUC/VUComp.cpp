// VUComp.cpp : This file contains the 'main' function. Program execution begins
// and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "version.h"
#include "VUComp.h"

#include "parse.h"
#define YY_NO_UNISTD_H
#include "lex.yy.h"


void parseFile(std::string fName)
{
    VU_Parser *parser;
    std::string src;
    std::ifstream f;

    yyscan_t scanner;
    YY_BUFFER_STATE yyb;

    f.exceptions(std::ios::failbit | std::ios::badbit);

    try
    {
        f.open(fName);

        f.seekg(0, std::ios::end);
        src.reserve(f.tellg());
        f.seekg(0, std::ios::beg);

        src.assign((std::istreambuf_iterator<char>(f)),
                   std::istreambuf_iterator<char>());
    }

    catch (std::ios_base::failure &e)
    {
        std::cerr << "VUC: Error: File " + fName + " failed:\n\t" +
                         e.code().message() + "\n";
    }

    parser = VU_Parser::create(fName, src);

    vuclex_init_extra(parser, &scanner);
    /* Now we need to scan our string into the buffer. */
    yyb = vuc_scan_string(src.c_str(), scanner);

    while (vuclex(scanner))
        ;
    parser->parse(TOK_EOF);
}

int main(int argc, char *argv[])
{
    std::vector<std::string> modNames;

    std::cout
        << "Visual Urlang (TM) Compiler version " VERSTR "\n"
           "Copyright (C) The Visual Urlang Project. All rights reserved.\n"
           "Use is subject to license terms.\n\n";

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (!arg.rfind("-", 0))
        {
            /* option */
        }
        else
        {
            modNames.push_back(arg);
        }
    }

    if (!modNames.size())
        std::cout << "Usage: " + std::string(argv[0]) +
                         " [ options ] modules\n";

    for (auto mod : modNames)
    {
        std::cout << mod + "\n";
        parseFile(mod);
    }

    std::cout << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project 6. In the future,
//   to open this project again, go to File > Open > Project and select the .sln
//   file
