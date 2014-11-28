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

#include "AISpaceshipController.hpp"
#include <SFML/Graphics.hpp>

/////////////////////////////////////////////////

AISpaceshipController::AISpaceshipController(Spaceship *spaceship, std::vector<Spaceship*> *enemies) : SpaceshipController(spaceship, enemies), m_direction(1) {}

/////////////////////////////////////////////////

void AISpaceshipController::events()
{
    if(!m_spaceship->movePossible(m_direction))
        m_direction *= -1;

    m_spaceship->move(m_direction);
}