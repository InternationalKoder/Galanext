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

#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#include <string>

/////////////////////////////////////////////////
///
/// \brief The values relative to the configuration
///
/////////////////////////////////////////////////
class Config
{
    public:

        static const unsigned int WINDOW_WIDTH;
        static const unsigned int WINDOW_HEIGHT;
        static const std::string WINDOW_TITLE;

        static const std::string RESOURCES_PATH;
        static const std::string HIGHSCORES_FILE;

        static const unsigned int TOP_MARGIN;
        static const unsigned int BOTTOM_MARGIN;

        static const unsigned int ENEMIES_LEFT_MARGIN;

        static const unsigned int SCORE_TEXT_POS_X;
        static const unsigned int SCORE_MARGIN;

        static const unsigned int LEVEL_TEXT_POS_X;
        static const unsigned int LEVEL_MARGIN;

        static const unsigned int HIGHSCORE_TEXT_POS_X;
        static const unsigned int HIGHSCORE_MARGIN;

        static const unsigned int NEW_HIGHSCORE_POS_Y;
        static const unsigned int NEW_HIGHSCORE_MARGIN;

        static const unsigned int HIGHSCORES_WIDTH;
        static const unsigned int HIGHSCORES_POS_Y;
        static const unsigned int HIGHSCORES_MARGIN;
};

#endif // CONFIG_HPP_INCLUDED
