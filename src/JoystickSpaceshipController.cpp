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

#include "JoystickSpaceshipController.hpp"
#include <SFML/Graphics.hpp>
#include "constants.hpp"

/////////////////////////////////////////////////

JoystickSpaceshipController::JoystickSpaceshipController(Spaceship *spaceship, std::vector<Spaceship*> *enemies) : SpaceshipController(spaceship, enemies) {}

/////////////////////////////////////////////////

void JoystickSpaceshipController::events()
{
    if(sf::Joystick::isConnected(0))
    {
        if(sf::Joystick::hasAxis(0, sf::Joystick::X))
        {
            if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -50.0f)
                m_spaceship->move(-1);

            if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50.0f)
                m_spaceship->move(1);
        }

        if(sf::Joystick::isButtonPressed(0, 0))
        {
            if(m_spaceship->getShot() == NULL)
            {
                sf::Texture shotTexture;
                shotTexture.loadFromFile("resources/shot.png");
                const sf::Vector2f shotSpeed(0.0f, SHOOT_SPEED * -1);
                const sf::Vector2f initPos(m_spaceship->getGlobalBounds().left + (m_spaceship->getGlobalBounds().width / 2) - (shotTexture.getSize().x / 2), m_spaceship->getGlobalBounds().top - shotTexture.getSize().y);

                m_spaceship->setShot(new Shot("resources/shot.png", shotSpeed, initPos, &(*m_enemies)));
            }
        }
	}
}
