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

#ifndef KEYBOARDSPACESHIPCONTROLLER_HPP
#define KEYBOARDSPACESHIPCONTROLLER_HPP

#include "SpaceshipController.hpp"

/////////////////////////////////////////////////
///
/// \brief Allows to control a spaceship with a keyboard
///
/////////////////////////////////////////////////
class KeyboardSpaceshipController : public SpaceshipController
{
    public:

        /////////////////////////////////////////////////
        ///
        /// \brief The constructor
        ///
        /// \param shotTexture The texture to use for the shots
        ///
        /////////////////////////////////////////////////
        KeyboardSpaceshipController(const sf::Texture& shotTexture);


        /////////////////////////////////////////////////
        ///
        /// \brief The events' handler
        ///
        /////////////////////////////////////////////////
        virtual void handleEvents(std::list<Shot*>* allShots);


    private:

        sf::Texture m_shotTexture; ///< The texture to use for the shots
};

#endif // KEYBOARDSPACESHIPCONTROLLER_HPP
