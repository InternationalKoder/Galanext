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

#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED

#include <iostream>

/////////////////////////////////////////////////
///
/// \brief Allows to display log messages
///
/////////////////////////////////////////////////
class Log
{
    public:

        /////////////////////////////////////////////////
        ///
        /// \brief The different levels available for the log system
        ///
        /////////////////////////////////////////////////
        typedef enum
        {
            NONE = 0,
            ERROR = 1,
            WARN = 2,
            INFO = 3,
            DEBUG = 4
        } LOG_LEVEL;


        /////////////////////////////////////////////////
        ///
        /// \brief Sets the level to use for the log
        ///
        /// \param level The level to use
        ///
        /////////////////////////////////////////////////
        static void setLevel(const LOG_LEVEL level);


        /////////////////////////////////////////////////
        ///
        /// \brief Displays an information message
        ///
        /// \param message The message to display
        ///
        /////////////////////////////////////////////////
        static void info(const std::string& message);


        /////////////////////////////////////////////////
        ///
        /// \brief Displays a debug message
        ///
        /// \param message The message to display
        ///
        /////////////////////////////////////////////////
        static void debug(const std::string& message);


        /////////////////////////////////////////////////
        ///
        /// \brief Displays a warning message
        ///
        /// \param message The message to display
        ///
        /////////////////////////////////////////////////
        static void warn(const std::string& message);


        /////////////////////////////////////////////////
        ///
        /// \brief Displays an error message
        ///
        /// \param message The message to display
        ///
        /////////////////////////////////////////////////
        static void error(const std::string& message);


    private:

        static LOG_LEVEL m_level; ///< The log level will determine the types of messages that will be displayed

        /////////////////////////////////////////////////
        ///
        /// \brief Gives a string that represents the current date and time
        ///
        /////////////////////////////////////////////////
        static const std::string currentDateTime();
};

#endif // LOG_HPP_INCLUDED
