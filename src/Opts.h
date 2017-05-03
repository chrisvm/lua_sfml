//
// Created by chrisvm on 5/2/17.
//

#ifndef LUA_SFML_OPTS_H
#define LUA_SFML_OPTS_H
#include <string>
#include <iostream>
#include "getopt.h"

namespace lua_sfml {
    struct ArgumentOptions {
        std::string MainScriptPath;
        bool ShowHelp;

        ArgumentOptions() {
            ShowHelp = 0;
            MainScriptPath = "";
        }

        static ArgumentOptions* GetArgOptions(int argc, char* argv[]) {
            ArgumentOptions *argumentOptions = new ArgumentOptions();
            if (argc < 1) {
                return argumentOptions;
            }

            int c;
            while (optind < argc) {
                if ((c = getopt(argc, argv, "h")) != -1) {
                    // option argument
                    switch (c) {
                        case 'h':
                            argumentOptions->ShowHelp = true;
                            break;
                        default:
                            break;
                    }
                } else {
                    // regular argument
                    argumentOptions->MainScriptPath = argv[optind];
                    optind++;
                }
            }
            return argumentOptions;
        }

        static void ShowHelpText() {
            std::cout << "Usage: lua_sfml [-h] SCRIPT" << std::endl;
            std::cout << "Opens an instance of the lua_sfml rendering engine, executing SCRIPT as main script."
                      << std::endl << std::endl;
            std::cout << "-h       show this help message." << std::endl;
        }
    };
}
#endif //LUA_SFML_OPTS_H
