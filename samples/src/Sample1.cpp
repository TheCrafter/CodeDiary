/******************************************************************************/
/*                                                                            */
/*              __/^\__                                                       */
/*            ./       \.                                                     */
/*           /    ___    \    THE                                             */
/*          /   ./   \.   \    CRAFTER                                        */
/*         /  ./       \.  \                                                  */
/*        /  / ___   ___ \  \                                                 */
/*       /  / |___|-|___| \  \                                                */
/*      /  /               \  \                                               */
/*      \  \               /  /                                               */
/*       \  \/\         /\/  /                                                */
/*        \    \       /    /                                                 */
/*         `\   \     /   /`                                                  */
/*           `\  \   /  /`                                                    */
/*             `\_\ /_/`                                                      */
/*    /  /                   \  \                                             */
/*   /   \                   /    \                                           */
/*   |  _.\\                 //._  |                                          */
/*   !!!!  \|               |/  !!!!                                          */
/*   \\\\                       ////                                          */
/*   _______________________________                                          */
/*   | o o o o o ------ o o o o o o |                                         */
/*   | o ~ ~ o ~~ o o o o o o o o ~~|                                         */
/*   | o ~ ~ o o ~~ o o o o o o o ~~|                                         */
/*   | o - - - - - - - - - - - - - ~|                                         */
/*   |______________________________|                                         */
/*                                                                            */
/*                                                                            */
/* Copyright 2015 Vlachakis Dimitris                                          */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License");            */
/* you may not use this file except in compliance with the License.           */
/* You may obtain a copy of the License at                                    */
/*                                                                            */
/*      http://www.apache.org/licenses/LICENSE-2.0                            */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/*                                                                            */
/******************************************************************************/

#include <string>
#include "Logger.hpp"
#include "SampleFormatter.hpp"

struct MyType
{
    int x;

    MyType() : x(5)
    {
    }

    std::string ToString() const
    {
        return std::to_string(x);
    }
};

void Test()
{
    using namespace CodeDiary;

    // Test default logger
    Logger<>::Log("\\T \\L This is my first log", Logger<>::LogType::DEBUG);

    // Test logger with different formatter
    Logger<SampleFormatter>::Log("\\T \\L This is my second log", Logger<SampleFormatter>::LogType::DEBUG);

    // Test logger with different formatter and different format
    Logger<SampleFormatter>::Log("\\T This is my third log \\L", Logger<SampleFormatter>::LogType::DEBUG);
}

void Test2()
{
    using namespace CodeDiary;

    MyType type;

    // Test logging a type
    Logger<MyType, DefaultFormatter, DefaultDispatcher>::Log(type, Logger<MyType, DefaultFormatter, DefaultDispatcher>::LogType::DEBUG);
}

int main()
{
    Test();
    Test2();
    return 0;
}