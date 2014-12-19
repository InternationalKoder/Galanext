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

#ifndef SPACESHIP_HPP_INCLUDED
#define SPACESHIP_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "SpaceshipController.hpp"
#include "Shot.hpp"

class SpaceshipController;
class Shot;

/////////////////////////////////////////////////
/// \brief Defines a spaceship which may be controlled
/////////////////////////////////////////////////
class Spaceship : public sf::Transformable, public sf::Drawable
{
	public:

        /////////////////////////////////////////////////
		/// \brief Constructor
        ///
        /// \param texture The texture that will be used to display the spaceship
        /// \param speed The spaceship's speed
        ///
        /////////////////////////////////////////////////
		Spaceship(const sf::Texture& texture, const float& speed);

        /////////////////////////////////////////////////
		/// \brief Constructor
        ///
        /// \param texture The texture that will be used to display the spaceship
        /// \param speed The spaceship's speed
        /// \param initialPos The initial spaceship's position
        ///
        /////////////////////////////////////////////////
		Spaceship(const sf::Texture& texture, const float& speed, const sf::Vector2f& initialPos);

        /////////////////////////////////////////////////
		/// \brief Adds a controller for the spaceship
        ///
        /// \param controller The controller to add
        ///
        /////////////////////////////////////////////////
		void addController(SpaceshipController *controller);

        /////////////////////////////////////////////////
		/// \brief Tells if the spaceship is able to move or not
        ///
        /// \param direction The direction for the spaceship to try (negative value for left, positive value for right)
        /// \return True if the move is possible
        ///
        /////////////////////////////////////////////////
		bool movePossible(const char& direction);

        /////////////////////////////////////////////////
		/// \brief Moves the spaceship if it is possible
        ///
        /// \param direction The direction where the spaceship will move (negative value for left, positive value for right)
        ///
        /////////////////////////////////////////////////
		void move(const char& direction);

        /////////////////////////////////////////////////
		/// \brief A getter for the spaceship's global bounds (coordinates and size)
        ///
        /// \return A rectangle which represents the spaceship
        ///
        /////////////////////////////////////////////////
		sf::FloatRect getGlobalBounds();

		/////////////////////////////////////////////////
		/// \brief A getter for the controllers
        ///
        /// \return A pointer to the controllers' vector
        ///
        /////////////////////////////////////////////////
		std::vector<SpaceshipController*>* getControllers();

        /////////////////////////////////////////////////
		/// \brief A getter for the shot
        ///
        /// \return A pointer to the shot fired by the spaceship
        ///
        /////////////////////////////////////////////////
		Shot* getShot();

        /////////////////////////////////////////////////
		/// \brief A setter for the shot
        ///
        /// \param shot The new shot fired by the spaceship
        ///
        /////////////////////////////////////////////////
		void setShot(Shot *shot);

        /////////////////////////////////////////////////
		/// \brief Refreshes the spaceship's status and position
        ///
        /////////////////////////////////////////////////
		void refresh();

        /////////////////////////////////////////////////
		/// \brief The destructor
        ///
        /////////////////////////////////////////////////
		~Spaceship();

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
            if(m_shot != NULL)
                target.draw((sf::Drawable&) *m_shot, states);
        }

		sf::Texture m_texture; ///< The spaceship's texture

		sf::Sprite m_sprite; ///< The spaceship's sprite

		Shot *m_shot; ///< A pointer to the shot fired by the spaceship

		std::vector<SpaceshipController*> m_controllers; ///< The controllers for the spaceship

		float m_speed; ///< The spaceship's speed

		bool m_destroyed; ///< True if the spaceship is destroyed

		unsigned char m_spriteCounter; ///< A counter to animate the sprite

		unsigned char m_framesCounter; ///< A counter for the frames so that events can happen every n frames

        const static int DIST_SCREEN_BORDER = 5; ///< The distance between the screen's border and the spaceship
};

#endif // SPACESHIP_HPP_INCLUDED
