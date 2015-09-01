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

#ifndef SHOT_HPP
#define SHOT_HPP

#include <SFML/Graphics.hpp>

/////////////////////////////////////////////////
///
/// \brief A spaceship's shot
///
/////////////////////////////////////////////////
class Shot
{
    public:

        static const float SPEED; ///< The moving speed for the shots

        /////////////////////////////////////////////////
        ///
        /// \brief The constructor
        ///
        /// \param texture The image to use to display the shot
        /// \param startingPos The position where the shot will begin
        /// \param goesUp Set to true to make the shot go from the bottom to the top of the screen
        ///
        /////////////////////////////////////////////////
        Shot(const sf::Texture& texture, const sf::Vector2f& startingPos, bool goesUp);


        /////////////////////////////////////////////////
        ///
        /// \brief Gives the shot's position
        ///
        /////////////////////////////////////////////////
        sf::Vector2f getPosition();


        /////////////////////////////////////////////////
        ///
        /// \brief Refreshes the shot's position
        ///
        /////////////////////////////////////////////////
        void refresh();


        /////////////////////////////////////////////////
        ///
        /// \brief Displays the shot
        ///
        /// \param window The window where the shot will be displayed
        ///
        /////////////////////////////////////////////////
        void display(sf::RenderWindow& window);


    private:

        sf::Sprite m_sprite; ///< The sprite that represents the shot

        bool m_goesUp; ///< Set to true to make the shot go from the bottom to the top of the screen
};

#endif // SHOT_HPP
