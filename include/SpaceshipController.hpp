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

#ifndef SPACESHIPCONTROLLER_HPP
#define SPACESHIPCONTROLLER_HPP

#include "Spaceship.hpp"
#include "Shot.hpp"
#include <list>

/////////////////////////////////////////////////
///
/// \brief Abstract class for the spaceships' controllers
///
/////////////////////////////////////////////////
class SpaceshipController
{
    public:

        /////////////////////////////////////////////////
        ///
        /// \brief Adds a spaceship to handle
        ///
        /// \param spaceship The new spaceship to control
        ///
        /////////////////////////////////////////////////
        void addSpaceship(Spaceship* spaceship);


        /////////////////////////////////////////////////
        ///
        /// \brief The events' handler
        ///
        /////////////////////////////////////////////////
        virtual void handleEvents() = 0;


        /////////////////////////////////////////////////
        ///
        /// \brief The destructor
        ///
        /////////////////////////////////////////////////
        virtual ~SpaceshipController();


    protected:

        std::vector<Spaceship*> m_spaceships; ///< The spaceships to control

        std::list<Shot*> m_shots; ///< The shots from the spaceships to control

        int m_shotsTicksCounter; ///< A ticks counter for the shots

        static const unsigned int TICKS_SHOTS; ///< The minimum number of ticks between 2 shots
};

#endif // SPACESHIPCONTROLLER_HPP
