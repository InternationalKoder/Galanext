//    Galanext is a Galaxian-like game
//    Copyright (C) 2014-2015  InternationalKoder
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.

#include "../include/Log.hpp"
#include <ctime>

/////////////////////////////////////////////////

Log::LOG_LEVEL Log::m_level = Log::NONE;

/////////////////////////////////////////////////

void Log::setLevel(const Log::LOG_LEVEL level)
{
    m_level = level;
}

/////////////////////////////////////////////////

void Log::info(const std::string& message)
{
    if(m_level >= Log::INFO)
    {
        std::cout << "[INFO " << currentDateTime() << "] " << message << std::endl;
    }
}

//////////////////////////////////////////////

void Log::debug(const std::string& message)
{
    if(m_level >= Log::DEBUG)
    {
        std::cout << "[DEBUG " << currentDateTime() << "] " << message << std::endl;
    }
}

///////////////////////////////////////////////

void Log::warn(const std::string& message)
{
    if(m_level >= Log::WARN)
    {
        std::cout << "[WARNING " << currentDateTime() << "] " << message << std::endl;
    }
}

/////////////////////////////////////////////////

void Log::error(const std::string& message)
{
    if(m_level >= Log::ERROR)
    {
        std::cout << "[ERROR " << currentDateTime() << "] " << message << std::endl;
    }
}

/////////////////////////////////////////////////

const std::string Log::currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];

    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}
