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

#ifndef HIGHSCORE_HPP_INCLUDED
#define HIGHSCORE_HPP_INCLUDED

#include <string>

/////////////////////////////////////////////////
///
/// \brief A highscore: the score and the name of its author
///
/////////////////////////////////////////////////
class Highscore
{
    public:

        /////////////////////////////////////////////////
        ///
        /// \brief Constructor
        ///
        /////////////////////////////////////////////////
        Highscore(unsigned int score = 0, const std::string& author = "");


        /////////////////////////////////////////////////
        ///
        /// \brief Gives the score
        ///
        /// \return The score
        ///
        /////////////////////////////////////////////////
        unsigned int getScore();


        /////////////////////////////////////////////////
        ///
        /// \brief Gives the author
        ///
        /// \return The name of the score's author
        ///
        /////////////////////////////////////////////////
        std::string& getAuthor();


        /////////////////////////////////////////////////
        ///
        /// \brief Changes the score
        ///
        /// \param score The new score
        ///
        /////////////////////////////////////////////////
        void setScore(unsigned int score);


        /////////////////////////////////////////////////
        ///
        /// \brief Changes the author
        ///
        /// \param author The new name of the author
        ///
        /////////////////////////////////////////////////
        void setAuthor(const std::string& author);


    private:

        unsigned int m_score; ///< The score

        std::string m_author; ///< The name of the score's author
};

#endif // HIGHSCORE_HPP_INCLUDED
