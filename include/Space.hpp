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

#ifndef SPACE_HPP_INCLUDED
#define SPACE_HPP_INCLUDED

#include "../include/Config.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

/////////////////////////////////////////////////
///
/// \brief The moving space background
///
/////////////////////////////////////////////////
class Space
{
    public:

        /////////////////////////////////////////////////
        ///
        /// \brief Constructor
        ///
        /////////////////////////////////////////////////
        Space();

        /////////////////////////////////////////////////
        ///
        /// \brief Moves the background with stars appearing randomly
        ///
        /////////////////////////////////////////////////
        void refresh();

        /////////////////////////////////////////////////
        ///
        /// \brief Displays the space background
        ///
        /////////////////////////////////////////////////
        void display(sf::RenderWindow& window);

    private:

        sf::VertexArray m_vertex; ///< The vertex which contains the stars
};

#endif // SPACE_HPP_INCLUDED
