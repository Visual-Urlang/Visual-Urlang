// VUComp.cpp : This file contains the 'main' function. Program execution begins
// and ends there.
//

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "VUComp.h"
#include "version.h"

#include "parse.h"
#define YY_NO_UNISTD_H
#include "lex.yy.h"

static enum FlagVal {
    evNonFlag,
    evTraceFlag,
};

static std::map<std::string, FlagVal> flagVals;

static void initFlagVals();

void parseFile(bool trace, std::string fName)
{
    bool isCls = fName.substr(fName.size() - 3) == "cls";

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
    if (trace)
        parser->trace(stdout, "<parser>: ");

    vuclex_init_extra(parser, &scanner);
    /* Now we need to scan our string into the buffer. */
    yyb = vuc_scan_string(src.c_str(), scanner);

    // parser->parse(isCls ? TOK_CLASS : TOK_BAS);

    while (vuclex(scanner))
        ;
    parser->parse(TOK_EOF);

    parser->mod()->genSymTabs();
    parser->mod()->print(0);
}

int main(int argc, char *argv[])
{
    std::vector<std::string> modNames;
    bool trace = false;

    std::cout
        << "WebScale Object Solutions (TM) Urlang Compiler version " VERSTR "\n"
           "Copyright (C) WebScale Object Solutions. All rights reserved.\n"
           "Use is subject to license terms.\n\n";

    initFlagVals();

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (!arg.rfind("-", 0))
        {
            /* option */
            switch (flagVals[arg.substr((1))])
            {
            case evTraceFlag:
                trace = true;
                break;
            default:
                break;
            }
        }
        else
        {
            modNames.push_back(arg);
        }
    }

    if (modNames.empty())
        std::cout << "Usage: " + std::string(argv[0]) +
                         " [ options ] modules\n";

    for (auto mod : modNames)
    {
        std::cout << mod + "\n";
        parseFile(trace, mod);
    }

    std::cout << "\n";
}

void initFlagVals() { flagVals["trace"] = evTraceFlag; }