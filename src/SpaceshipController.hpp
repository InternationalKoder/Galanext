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

#ifndef SPACESHIPCONTROLLER_HPP_INCLUDED
#define SPACESHIPCONTROLLER_HPP_INCLUDED

#include "Spaceship.hpp"

class Spaceship;

/////////////////////////////////////////////////
/// \brief A controller for a spaceship
/////////////////////////////////////////////////
class SpaceshipController
{
	public:

        /////////////////////////////////////////////////
		/// \brief Constructor
        ///
        /// \param spaceship The spaceship to control
        /// \param enemies The enemies which may be destroyed by the controled spaceship
        ///
        /////////////////////////////////////////////////
		SpaceshipController(Spaceship *spaceship, std::vector<Spaceship*> *enemies);

        /////////////////////////////////////////////////
		/// \brief Checks the events and updates the spaceship
        ///
        /////////////////////////////////////////////////
		virtual void events() = 0;

        /////////////////////////////////////////////////
		/// \brief Fires a new shot
		///
		/// \param direction The shot's direction
        ///
        /////////////////////////////////////////////////
        void fire(char direction);

        /////////////////////////////////////////////////
		/// \brief A getter for the controlled spaceship
		///
		/// \return A pointer to the controlled spaceship
        ///
        /////////////////////////////////////////////////
        Spaceship* getSpaceship();

        /////////////////////////////////////////////////
		/// \brief A getter for the direction
        ///
        /// \return The current spaceship's direction
        ///
        /////////////////////////////////////////////////
		char getDirection();

        /////////////////////////////////////////////////
		/// \brief A setter for the direction
        ///
        /// \param shot The new spaceship's direction
        ///
        /////////////////////////////////////////////////
		void setDirection(char direction);

        /////////////////////////////////////////////////
		/// \brief The destructor
        ///
        /////////////////////////////////////////////////
		virtual ~SpaceshipController();

	protected:

		Spaceship *m_spaceship; ///< The spaceship to control

		std::vector<Spaceship*> *m_enemies; ///< The spaceship's enemies

        char m_direction; ///< The spaceship's current direction (positive = right, negative = left)
};

#endif // SPACESHIPCONTROLLER_HPP_INCLUDED
