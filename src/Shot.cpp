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

#include "../include/Shot.hpp"
#include "../include/Spaceship.hpp"
#include "../include/Log.hpp"
#include "../include/Config.hpp"

/////////////////////////////////////////////////

const float Shot::SPEED = 10.0f;

/////////////////////////////////////////////////

Shot::Shot(const sf::Texture& texture, const sf::Vector2f& startingPos, bool goesUp,
           std::list<Spaceship*>& targetSpaceships) :
    m_sprite(texture),
    m_goesUp(goesUp),
    m_active(true),
    m_targetSpaceships(targetSpaceships)
{
    m_sprite.setPosition(startingPos);
}

/////////////////////////////////////////////////

sf::Vector2f Shot::getPosition()
{
    return m_sprite.getPosition();
}

/////////////////////////////////////////////////

void Shot::setActive(bool active)
{
    m_active = active;
}

/////////////////////////////////////////////////

bool Shot::isActive()
{
    return m_active;
}

/////////////////////////////////////////////////

Spaceship* Shot::refresh()
{
    Spaceship* spaceship = 0;

    if(m_active)
    {
        if(m_sprite.getPosition().y >= 0 && m_sprite.getPosition().y <= Config::WINDOW_HEIGHT)
        {
            sf::Vector2f movement(0.0f, Shot::SPEED);

            if(m_goesUp)
            {
                movement.y = Shot::SPEED * -1;
            }

            m_sprite.move(movement);

            for(std::list<Spaceship*>::iterator it = m_targetSpaceships.begin() ; it != m_targetSpaceships.end();++it)
            {
                if((*it)->isActive() && m_sprite.getGlobalBounds().intersects((*it)->getGlobalBounds()))
                {
                    m_active = false;
                    (*it)->setActive(false, true);
                    spaceship = (*it);
                    it = m_targetSpaceships.end();
                }
            }
        }
        else
        {
            m_active = false;
        }
    }

    return spaceship;
}

/////////////////////////////////////////////////

void Shot::display(sf::RenderWindow& window)
{
    if(m_active)
    {
        window.draw(m_sprite);
    }
}
