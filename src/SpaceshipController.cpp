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

#include "../include/SpaceshipController.hpp"

/////////////////////////////////////////////////

const unsigned int SpaceshipController::TICKS_SHOTS = 50;

/////////////////////////////////////////////////

void SpaceshipController::addSpaceship(Spaceship* spaceship)
{
    m_spaceships.push_back(spaceship);
}

/////////////////////////////////////////////////

SpaceshipController::~SpaceshipController()
{
    for(std::list<Shot*>::iterator it = m_shots.begin() ; it != m_shots.end() ; ++it)
    {
        delete (*it);
    }
}
