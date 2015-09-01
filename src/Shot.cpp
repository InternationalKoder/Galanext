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

/////////////////////////////////////////////////

const float Shot::SPEED = 10.0f;

/////////////////////////////////////////////////

Shot::Shot(const sf::Texture& texture, const sf::Vector2f& startingPos, bool goesUp) :
    m_sprite(texture), m_goesUp(goesUp)
{
    m_sprite.setPosition(startingPos);
}

/////////////////////////////////////////////////

sf::Vector2f Shot::getPosition()
{
    return m_sprite.getPosition();
}

/////////////////////////////////////////////////

void Shot::refresh()
{
    sf::Vector2f movement(0.0f, Shot::SPEED);

    if(m_goesUp)
    {
        movement.y = Shot::SPEED * -1;
    }

    m_sprite.move(movement);
}

/////////////////////////////////////////////////

void Shot::display(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}
