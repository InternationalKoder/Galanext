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

#ifndef SHOT_HPP_INCLUDED
#define SHOT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <memory>
#include "Spaceship.hpp"

class Spaceship;

/////////////////////////////////////////////////
/// \brief A shot which destroys the other spaceships
/////////////////////////////////////////////////
class Shot : public sf::Transformable, public sf::Drawable
{
	public:

        /////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// \param path The path to the shot's picture
        /// \param speeds The shot's speed on X and Y axis
        /// \param intitialPos The shot's initial position
        /// \param spaceships The spaceships which may be destroyed by this shot
        ///
        /////////////////////////////////////////////////
		Shot(const std::string& path, const sf::Vector2f& speeds, const sf::Vector2f& intitialPos, std::vector<std::shared_ptr<Spaceship>> *spaceships);

        /////////////////////////////////////////////////
		/// \brief Moves the shot in function of its speed
        ///
        /////////////////////////////////////////////////
		void move();

        /////////////////////////////////////////////////
		/// \brief A getter for the shot's position
        ///
        /// \return The shot's position
        ///
        /////////////////////////////////////////////////
		sf::Vector2f getPosition();

        /////////////////////////////////////////////////
		/// \brief Refreshes the shot's status and position
        ///
        /// \return True if the shot must be deleted
        ///
        /////////////////////////////////////////////////
		bool refresh();

	private:

        /////////////////////////////////////////////////
		/// \brief Draws the shot (part of SFML lib)
        ///
        /// \param target The target to render
        /// \param states The target's states
        ///
        /////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();
            states.texture = &m_texture;
            target.draw(m_sprite, states);
        }

		sf::Texture m_texture; ///< The shot's texture

		sf::Sprite m_sprite; ///< The shot's sprite

		sf::Vector2f m_speeds; ///< The shot's speed on X and Y axis

		std::vector<std::shared_ptr<Spaceship>> *m_spaceships; ///< The spaceships which may be destroyed by this shot
};

#endif // SHOT_HPP_INCLUDED
