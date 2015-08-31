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

#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <SFML/Graphics.hpp>

/////////////////////////////////////////////////
///
/// \brief A spaceship
///
/////////////////////////////////////////////////
class Spaceship
{
    public:

        static const unsigned char NUMBER_ANIMATION; ///< The number of sprites that can be used for the animation

        static const float SPEED; ///< The moving speed for the spaceships

        /////////////////////////////////////////////////
        ///
        /// \brief The constructor
        ///
        /// \param texture The image to use to display the spaceship
        /// \param startingPos The position where the spaceship will begin
        ///
        /////////////////////////////////////////////////
        Spaceship(const sf::Texture& texture, const sf::Vector2f& startingPos);


        /////////////////////////////////////////////////
        ///
        /// \brief Moves the spaceship
        ///
        /// \param movement The requested movement for the spaceship
        ///
        /////////////////////////////////////////////////
        void move(const sf::Vector2f& movement);


        /////////////////////////////////////////////////
        ///
        /// \brief Refreshes the spaceship animation
        ///
        /////////////////////////////////////////////////
        void refresh();


        /////////////////////////////////////////////////
        ///
        /// \brief Displays the spaceship
        ///
        /// \param window The window where the spaceship will be displayed
        ///
        /////////////////////////////////////////////////
        void display(sf::RenderWindow& window);


    private:

        static const unsigned char TICKS_ANIMATION; ///< The number of ticks between 2 elements of animation

        unsigned char m_ticksCounter; ///< A ticks counter for the animation

        sf::Sprite m_sprite; ///< The sprite that represents the spaceship
};

#endif // SPACESHIP_HPP
