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

#include "AIEnemiesGroupController.hpp"
#include "Game.hpp"

AIEnemiesGroupController::AIEnemiesGroupController(std::vector<Spaceship*> *spaceships) : m_spaceships(spaceships) {}

/////////////////////////////////////////////////

void AIEnemiesGroupController::events()
{
    if(!movePossibleAllSpaceships())
        changeAllDirections();

    moveAll();

    if(!hasFired())
    {
        int random(rand() % m_spaceships->size());

        if(isFirstOfColumn(random))
            m_spaceships->at(random)->getControllers()->at(0)->fire(1);
    }
}

/////////////////////////////////////////////////

bool AIEnemiesGroupController::movePossibleAllSpaceships()
{
    bool possible(true);

    for(std::vector<Spaceship*>::iterator it = m_spaceships->begin() ; it != m_spaceships->end() ; )
    {
        std::vector<SpaceshipController*> *controllers = (*it)->getControllers();

        for(std::vector<SpaceshipController*>::iterator it2 = controllers->begin() ; it2 != controllers->end() ; )
        {

            if(possible)
                possible = ((*it)->movePossible((*it2)->getDirection()));
            ++it2;
        }

        ++it;
    }

    return possible;
}

/////////////////////////////////////////////////

void AIEnemiesGroupController::changeAllDirections()
{
    for(std::vector<Spaceship*>::iterator it = m_spaceships->begin() ; it != m_spaceships->end() ; )
    {
        std::vector<SpaceshipController*> *controllers = (*it)->getControllers();

        for(std::vector<SpaceshipController*>::iterator it2 = controllers->begin() ; it2 != controllers->end() ; )
        {
            (*it2)->setDirection((*it2)->getDirection() * -1);
            ++it2;
        }
        ++it;
    }
}

/////////////////////////////////////////////////

void AIEnemiesGroupController::moveAll()
{
    for(std::vector<Spaceship*>::iterator it = m_spaceships->begin() ; it != m_spaceships->end() ; )
    {
        (*it)->refresh();
        ++it;
    }
}

/////////////////////////////////////////////////

bool AIEnemiesGroupController::hasFired()
{
    bool fired(false);

    for(std::vector<Spaceship*>::iterator it = m_spaceships->begin() ; it != m_spaceships->end() && !fired ; )
    {
        if((*it)->getShot() != NULL)
            fired = true;

        ++it;
    }

    return fired;
}

/////////////////////////////////////////////////

bool AIEnemiesGroupController::isFirstOfColumn(const int& spaceship)
{
    bool first(true);

    for(unsigned int i = spaceship + Game::NUMBER_ENEMIES_PER_ROW ; i < m_spaceships->size() && first ; i += Game::NUMBER_ENEMIES_PER_ROW)
    {
        if(m_spaceships->at(i) != NULL)
            first = false;
    }

    return first;
}
