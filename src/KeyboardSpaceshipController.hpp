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

#ifndef KEYBOARDSPACESHIPCONTROLLER_HPP_INCLUDED
#define KEYBOARDSPACESHIPCONTROLLER_HPP_INCLUDED

#include "SpaceshipController.hpp"

/////////////////////////////////////////////////
/// \brief A controller which allows to control a spaceship with a keyboard
/////////////////////////////////////////////////
class KeyboardSpaceshipController : public SpaceshipController
{
	public:

        /////////////////////////////////////////////////
		/// \brief Constructor
        ///
        /// \param spaceship The spaceship to control
        /// \param enemies The enemies which may be destroyed by the controled spaceship
        ///
        /////////////////////////////////////////////////
		KeyboardSpaceshipController(std::shared_ptr<Spaceship>& spaceship, std::vector<std::shared_ptr<Spaceship>> *enemies);

        /////////////////////////////////////////////////
		/// \brief Checks the events on the keyboard and updates the spaceship
        ///
        /////////////////////////////////////////////////
		void events();
};

#endif // KEYBOARDSPACESHIPCONTROLLER_HPP_INCLUDED
