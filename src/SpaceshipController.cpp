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

#include "SpaceshipController.hpp"
#include "constants.hpp"
#include <iostream>
/////////////////////////////////////////////////

SpaceshipController::SpaceshipController(Spaceship *spaceship, std::vector<Spaceship*> *enemies) : m_spaceship(spaceship), m_enemies(enemies), m_direction(1) {}

/////////////////////////////////////////////////

void SpaceshipController::fire(char direction)
{
    if(m_spaceship->getShot() == NULL)
    {
        sf::Texture shotTexture;
        shotTexture.loadFromFile(RESOURCES_LOCATION + "shot.png");
        const sf::Vector2f shotSpeed(0.0f, SHOT_SPEED * direction);
        const sf::Vector2f initPos(m_spaceship->getGlobalBounds().left + (TILES_WIDTH / 2) - (shotTexture.getSize().x / 2), m_spaceship->getGlobalBounds().top + TILES_HEIGHT * (direction > 0));
        m_spaceship->setShot(new Shot(RESOURCES_LOCATION + "shot.png", shotSpeed, initPos, m_enemies));
    }
}

/////////////////////////////////////////////////

Spaceship* SpaceshipController::getSpaceship()
{
    return m_spaceship;
}

/////////////////////////////////////////////////

char SpaceshipController::getDirection()
{
    return m_direction;
}

/////////////////////////////////////////////////

void SpaceshipController::setDirection(char direction)
{
    m_direction = direction;
}

/////////////////////////////////////////////////

SpaceshipController::~SpaceshipController() {}
