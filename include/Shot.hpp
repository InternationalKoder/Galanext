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
#include <list>


class Spaceship;

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
        /// \param targetSpaceships The list of the spaceships which can be killed by the shot
        ///
        /////////////////////////////////////////////////
        Shot(const sf::Texture& texture, const sf::Vector2f& startingPos, bool goesUp,
             std::list<Spaceship*>& targetSpaceships);


        /////////////////////////////////////////////////
        ///
        /// \brief Gives the shot's position
        ///
        /////////////////////////////////////////////////
        sf::Vector2f getPosition();


        /////////////////////////////////////////////////
        ///
        /// \brief Allows to kill or awake the shot
        ///
        /// \param active The shot's new state
        ///
        /////////////////////////////////////////////////
        void setActive(bool active);


        /////////////////////////////////////////////////
        ///
        /// \brief Tells whether the shot is alive
        ///
        /// \return True if the shot is still alive
        ///
        /////////////////////////////////////////////////
        bool isActive();


        /////////////////////////////////////////////////
        ///
        /// \brief Refreshes the shot's position
        ///
        /// \return A pointer to the destroyed spaceship, or 0 if no spaceship was destroyed
        ///
        /////////////////////////////////////////////////
        Spaceship* refresh();


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

        std::list<Spaceship*>& m_targetSpaceships; ///< The spaceships which can be destroyed by the shot

        bool m_goesUp; ///< Set to true to make the shot go from the bottom to the top of the screen

        bool m_active; ///< Whether the shot is still alive or not
};

#endif // SHOT_HPP
