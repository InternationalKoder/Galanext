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

#ifndef JOYSTICKSPACESHIPCONTROLLER_HPP_INCLUDED
#define JOYSTICKSPACESHIPCONTROLLER_HPP_INCLUDED

#include "SpaceshipController.hpp"

/////////////////////////////////////////////////
/// \brief A controller which allows to control a spaceship with a joystick
/////////////////////////////////////////////////
class JoystickSpaceshipController : public SpaceshipController
{
	public:

        /////////////////////////////////////////////////
		/// \brief Constructor
        ///
        /// \param spaceship The spaceship to control
        /// \param enemies The enemies which may be destroyed by the controled spaceship
        ///
        /////////////////////////////////////////////////
		JoystickSpaceshipController(sf::RenderWindow& window, Spaceship *spaceship, std::vector<Spaceship*> *enemies);

        /////////////////////////////////////////////////
		/// \brief Checks the events on the joystick and updates the spaceship
        ///
        /////////////////////////////////////////////////
		void events();

		/////////////////////////////////////////////////
		/// \brief Pauses the game
        ///
        /////////////////////////////////////////////////
		void pause();

    private:

        sf::RenderWindow& m_window; ///< The window which will be paused
};

#endif // JOYSTICKSPACESHIPCONTROLLER_HPP_INCLUDED
