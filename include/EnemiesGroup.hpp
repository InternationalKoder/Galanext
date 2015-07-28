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
#include "AIEnemiesGroupController.hpp"

/////////////////////////////////////////////////
/// \brief A group of enemies
/////////////////////////////////////////////////
class EnemiesGroup : public sf::Drawable, public sf::Transformable
{
    public:

        /////////////////////////////////////////////////
		/// \brief Constructor
		///
		/// \param playerSpaceship The player's spaceship
        /// \param shotTexture The texture for the shots that will be fired
		/// \param textures The textures for the enemies' spaceships
        ///
        /////////////////////////////////////////////////
        EnemiesGroup(Spaceship *playerSpaceship, const std::vector<sf::Texture>& textures, const sf::Texture& shotTexture);

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
		/// \brief Tells whether the player has been destroyed
		///
		/// \return True if the player has been destroyed
        ///
        /////////////////////////////////////////////////
        bool isPlayerDestroyed();

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

        AIEnemiesGroupController m_controller; ///< The controller for the whole group

        Spaceship *m_playerSpaceship; ///< A pointer to the player's spaceship

        std::vector<Spaceship*> m_player; ///< The player's spaceship in a vector

        std::vector<sf::Texture> m_textures; ///< The textures for the spaceships

        sf::Texture m_shotTexture; ///< The fired shots' texture
};

#endif // ENEMIESGROUP_HPP_INCLUDED
