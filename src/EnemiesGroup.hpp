//    Galanext is a Galaxian-like game
//    Copyright (C) 2014  InternationalKoder
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

#ifndef ENEMIESGROUP_HPP_INCLUDED
#define ENEMIESGROUP_HPP_INCLUDED

#include <vector>
#include "Spaceship.hpp"
#include "AISpaceshipController.hpp"

/////////////////////////////////////////////////
/// \brief A group of enemies
/////////////////////////////////////////////////
class EnemiesGroup : public sf::Drawable, public sf::Transformable
{
    public:

        /////////////////////////////////////////////////
		/// \brief Constructor
		/// \param playerSpaceship The player's spaceship
        ///
        /////////////////////////////////////////////////
        EnemiesGroup(Spaceship *playerSpaceship);

        /////////////////////////////////////////////////
		/// \brief Refreshes all the spaceships in the group
        ///
        /////////////////////////////////////////////////
        void refresh();

        /////////////////////////////////////////////////
		/// \brief Gives all the spaceships in the group
		///
		/// \return A vector containing the spaceships
        ///
        /////////////////////////////////////////////////
        std::vector<Spaceship*>* getSpaceships();

        /////////////////////////////////////////////////
		/// \brief Destructor
        ///
        /////////////////////////////////////////////////
        ~EnemiesGroup();

    private:

        /////////////////////////////////////////////////
        /// \brief Draws the group's spaceships (part of SFML lib)
        ///
        /// \param target The target to render
        /// \param states The target's states
        ///
        /////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            for(std::vector<Spaceship*>::const_iterator it = m_spaceships.begin() ; it != m_spaceships.end() ; )
            {
                target.draw((sf::Drawable&) (**it), states);
                ++it;
            }
        }

        std::vector<Spaceship*> m_spaceships; ///< The group's spaceships

        //std::vector<AISpaceshipController*> m_controllers; ///< The controllers for all the spaceships

        Spaceship *m_playerSpaceship; ///< A pointer to the player's spaceship
};

#endif // ENEMIESGROUP_HPP_INCLUDED
