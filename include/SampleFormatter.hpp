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

#ifndef CODEDIARY_SAMPLEFORMATTER
#define CODEDIARY_SAMPLEFORMATTER

#include "Logger.hpp"
#include <unordered_set>

namespace CodeDiary
{

/// An example of how a formatter should be. SampleFormatter
/// extends BaseFormatter to get access to GetCurrentTime() function.
class SampleFormatter : public BaseFormatter<SampleFormatter>
{
protected:
    static std::string Format(const std::string& msg, const std::string& type)
    {
        std::string rVal;
        
        std::unordered_set<char> specialCharacters = 
        {
            'T',    // time
            'L'     // type
        };

        // Parse message
        for(auto it = std::begin(msg); it != std::end(msg); it++)
        {
            // Probably special type
            if(*it == '\\')
            {
                // Check next
                auto tempIt = it;
                tempIt++;

                // Check if we are at a special character
                bool isSpecialCharacter = (specialCharacters.count(*tempIt) != 0);

                // Handle special character
                if(isSpecialCharacter)
                {
                    if(*tempIt == 'T')
                        rVal += GetCurrentTime();
                    else if(*tempIt == 'L')
                        rVal += type;
                    
                    // Ignore the special character part and continue
                    it++;
                    continue;
                }
            }
            else
            {
                rVal += *it;
            }
        }

        return rVal;
    }
};

} // namespace CodeDiary

#endif