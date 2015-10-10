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

#include <ctime>
#include "../include/CpuSpaceshipController.hpp"
#include "../include/Config.hpp"
#include "../include/Log.hpp"

/////////////////////////////////////////////////

CpuSpaceshipController::CpuSpaceshipController(const sf::Texture& shotTexture) :
    m_shotTexture(shotTexture)
{
    m_shotsTicksCounter = SpaceshipController::TICKS_SHOTS;
    m_goesRight = true;
    m_fireSpeed = (4/3);
}

/////////////////////////////////////////////////

void CpuSpaceshipController::handleEvents(std::list<Shot*>* allShots)
{
    sf::Vector2f movement(0.0f, 0.0f);

    // Determining the movement
    if(m_goesRight)
    {
        float mostRightPos = -1.0f;

        for(std::list<Spaceship*>::iterator it = m_spaceships.begin() ; it != m_spaceships.end() ; ++it)
        {
            if((*it)->isActive())
            {
                sf::FloatRect globalBounds = (*it)->getGlobalBounds();
                float posX = globalBounds.left + globalBounds.width;

                if(posX > mostRightPos)
                {
                    mostRightPos = posX;
                }
            }
        }

        if(mostRightPos + Spaceship::SPEED >= Config::WINDOW_WIDTH)
        {
            m_goesRight = false;
            movement.x = Spaceship::SPEED * -1.0f;
        }
        else
        {
            movement.x = Spaceship::SPEED;
        }
    }
    else
    {
        float mostLeftPos = Config::WINDOW_WIDTH + 1.0f;

        for(std::list<Spaceship*>::iterator it = m_spaceships.begin() ; it != m_spaceships.end() ; ++it)
        {
            if((*it)->isActive())
            {
                sf::FloatRect globalBounds = (*it)->getGlobalBounds();

                if(globalBounds.left < mostLeftPos)
                {
                    mostLeftPos = globalBounds.left;
                }
            }
        }

        if(mostLeftPos + (Spaceship::SPEED * -1.0f) <= 0.0f)
        {
            m_goesRight = true;
            movement.x = Spaceship::SPEED;
        }
        else
        {
            movement.x = Spaceship::SPEED * -1.0f;
        }
    }

    // Moving and choosing the spaceship which will fire
    for(std::list<Spaceship*>::iterator it = m_spaceships.begin() ; it != m_spaceships.end() ; ++it)
    {
        if((*it)->isActive())
        {
            if(m_shotsTicksCounter >= (SpaceshipController::TICKS_SHOTS) / m_fireSpeed)
            {
                int random = rand() % (m_spaceships.size() * 2);

                if(random == 1)
                {
                    Shot* shot = (*it)->fire(m_shotTexture, false);
                    allShots->push_back(shot);
                    m_shotsTicksCounter = 0;
                }
            }

            (*it)->move(movement);
        }
    }

    m_shotsTicksCounter++;
}

/////////////////////////////////////////////////

void CpuSpaceshipController::increaseFireSpeed()
{
    m_fireSpeed *= 1.5f;
}
