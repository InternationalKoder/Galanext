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

#include "../include/KeyboardSpaceshipController.hpp"
#include "../include/Config.hpp"
#include "../include/Log.hpp"

/////////////////////////////////////////////////

KeyboardSpaceshipController::KeyboardSpaceshipController(const sf::Texture& shotTexture) :
    m_shotTexture(shotTexture)
{
    m_shotsTicksCounter = SpaceshipController::TICKS_SHOTS;
}

/////////////////////////////////////////////////

void KeyboardSpaceshipController::handleEvents()
{
    // Refreshing the shots
    std::list<Shot*>::iterator it = m_shots.begin();

    while(it != m_shots.end())
    {
        if((*it)->getPosition().y < 0 || (*it)->getPosition().y > Config::WINDOW_HEIGHT)
        {
            delete (*it);
            it = m_shots.erase(it);
        }
        else
        {
            (*it)->refresh();
            ++it;
        }
    }

    // Reading keayboard inputs and executing the matching action
    sf::Vector2f movement(0.0f, 0.0f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        movement.x = Spaceship::SPEED * -1.0f;
        Log::debug("Keyboard controller -> moving to left");
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        movement.x = Spaceship::SPEED;
        Log::debug("Keyboard controller -> moving to right");
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_shotsTicksCounter >= SpaceshipController::TICKS_SHOTS)
    {
        for(int i = 0 ; i < m_spaceships.size() ; i++)
        {
            Shot* shot = m_spaceships[i]->fire(m_shotTexture, true);
            m_shots.push_back(shot);
        }

        m_shotsTicksCounter = 0;
        Log::debug("Keyboard controller -> fire");
    }

    if(movement.x != 0.0f || movement.y != 0.0f)
    {
        for(int i = 0 ; i < m_spaceships.size() ; i++)
        {
            m_spaceships[i]->move(movement);
        }
    }

    m_shotsTicksCounter++;
}

/////////////////////////////////////////////////

void KeyboardSpaceshipController::displayShots(sf::RenderWindow& window)
{
    for(std::list<Shot*>::iterator it = m_shots.begin() ; it != m_shots.end() ; ++it)
    {
        (*it)->display(window);
    }
}
