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

#ifndef INTROSCREENS_HPP_INCLUDED
#define INTROSCREENS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Highscore.hpp"

/////////////////////////////////////////////////
///
/// \brief The introduction screens and animations
///
/////////////////////////////////////////////////
class IntroScreens
{
    public:

        /////////////////////////////////////////////////
        ///
        /// \brief Constructor
        ///
        /////////////////////////////////////////////////
        IntroScreens(sf::RenderWindow& window);


        /////////////////////////////////////////////////
        ///
        /// \brief Displays the InternationalKoder animation
        ///
        /////////////////////////////////////////////////
        void displayAuthor();


        /////////////////////////////////////////////////
        ///
        /// \brief Displays the title of the game
        ///
        /// \param font The font to use to display text
        /// \param spaceshipTexture The texture of the spaceship to display
        /// \param highscores The highscores to display
        ///
        /////////////////////////////////////////////////
        void displayTitle(const sf::Font& font, const sf::Texture& spaceshipTexture, Highscore* highscores);


    private:

        /////////////////////////////////////////////////
        ///
        /// \brief Refreshes a ball for the InternationalKoder animation
        ///
        /// \param balls Array with all the balls
        /// \param index Index of the ball to refresh in the array
        /// \param ballSpeedRight Array with all the speeds to the right
        /// \param ballSpeedDown Array with all the speeds to the bottom
        /// \param ballSize The size of the ball to refresh
        ///
        /////////////////////////////////////////////////
        void refreshBall(sf::CircleShape* balls, unsigned int index, char* ballSpeedRight, char* ballSpeedDown,
                         const sf::Vector2f& ballSize);

        sf::RenderWindow& m_window; ///< The window which will display the screens

        const unsigned int UPPER_LIMIT = 138; ///< The upper limit for the balls in the InternationalKoder animation

        const unsigned int BOTTOM_LIMIT = 411; ///< The bottom limit for the balls in the InternationalKoder animation

        const unsigned int BALLS_NUMBER = 15; ///< The number of balls to display for the InternationalKoder animation
};

#endif // INTROSCREENS_HPP_INCLUDED
