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

#ifndef CODEDIARY_LOGGER
#define CODEDIARY_LOGGER

#include <string>
#include <ctime>
#include <chrono>
#include <iostream>

namespace CodeDiary
{

/// Base formatter is an optional CRTP interface you can use. It
/// gives your formatter access to GetCurrentTime() (see DefaultFormatter
/// or SampleFormatter)
template<typename Implementation>
class BaseFormatter
{
protected:
    static std::string Format(const std::string& msg, const std::string& type)
    {
        return Implementation::Format(msg, type);
    }

    static std::string GetCurrentTime()
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        time_t curTime = std::chrono::system_clock::to_time_t(now);

        // CAREFUL: This rVal has a newline at the end. Don't return it
        std::string rVal(ctime(&curTime));

        return std::string(std::begin(rVal), std::end(rVal) - 1);
    }
};

/// Default formatter. Just formatts the log by putting first the current time,
/// then the type and then the log itself
class DefaultFormatter : public BaseFormatter <DefaultFormatter>
{
protected:
    static std::string Format(const std::string& msg, const std::string& type)
    {
        return std::string(GetCurrentTime() + " " + type + " " + msg);
    }
};

/// Default Dispatcher. Just prints the log to std::cout
class DefaultDispatcher
{
protected:
    static void Dispatch(const std::string& msg)
    {
        std::clog << msg << std::endl;
    }
};

/// BaseLogger class serves as a wrapper for the LogType. I only have it to keep
/// CodeDiary v1.1.0 compatible with v1.0.0. In v2.0.0 the LogType will be standing
/// alone in the namespace.
/*
* TODO: I kept this because for compatibility reasons with v1.0.0. In the next Major release
*       this will be removed
*/
class BaseLogger
{
public:
    enum class LogType
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };
};

/// This empty base Logger class helps me implement template class overloading. Without this
/// I wouldn't be able to create "class Logger<Obj, Formatter, Dispatcher>"
template<typename... T>
class Logger {};

/// Policy:
/// Formatter   -> must have "static std::string Format(const std::string& msg, const std::string& type)"
/// Dispatcher  -> must have "static void Dispatch(const std::string& msg)"
template<class Formatter, class Dispatcher>
class Logger<Formatter, Dispatcher> : public BaseLogger, private Formatter, private Dispatcher
{
public:
    static void Log(const std::string& msg, LogType type)
    {
        Dispatcher::Dispatch(Formatter::Format(msg, LogTypeToString(type)));
    }

private:
    static std::string LogTypeToString(LogType type)
    {
        switch(type)
        {
            case LogType::DEBUG:
                return "DEBUG";
            case LogType::INFO:
                return "INFO";
            case LogType::WARN:
                return "WARN";
            case LogType::ERROR:
                return "ERROR";
            default:
                return "";
        }
    }
};

/// Logger<> specialization is just the Logger with default formatter/dispatcher
template<>
class Logger<> : public Logger<DefaultFormatter, DefaultDispatcher>
{
};

/// This template specialization takes only one tempalte argument which is the formatter.
/// It is just the logger with the argument as Formatter and DefaultDispatcher as Dispatcher.
/* 
 * TODO: I kept this because for compatibility reasons with v1.0.0. In the next Major release
 *       this will be removed 
 */
template<class Formatter>
class Logger<Formatter> : public Logger<Formatter, DefaultDispatcher>
{
};

/// Policy:
/// Obj         -> must have "std::string ToString()"
/// Formatter   -> must have "static std::string Format(const std::string& msg, const std::string& type)"
/// Dispatcher  -> must have "static void Dispatch(const std::string& msg)"
template<class Obj, class Formatter, class Dispatcher>
class Logger<Obj, Formatter, Dispatcher> : public Logger<Formatter, Dispatcher>
{
public:
    static void Log(const Obj& obj, BaseLogger::LogType type)
    {
        Logger<Formatter, Dispatcher>::Log(obj.ToString(), type);
    }
};

} // namespace CodeDiary

#endif