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

JoystickSpaceshipController::JoystickSpaceshipController(sf::RenderWindow& window, Spaceship *spaceship, std::vector<Spaceship*> *enemies) : SpaceshipController(spaceship, enemies), m_window(window) {}

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
            fire();

        if(sf::Joystick::isButtonPressed(0, 7))
            pause();
	}
}

/////////////////////////////////////////////////

void JoystickSpaceshipController::pause()
{
    sf::Event event;
    bool resume(false);

    sf::sleep(sf::milliseconds(200));

    sf::Font xolonium;
    xolonium.loadFromFile(RESOURCES_LOCATION + FONT_LOCATION);
    sf::Text text("Press the start button to resume the game", xolonium, 16);
    text.setPosition(WINDOW_WIDTH/2 - text.getGlobalBounds().width/2, WINDOW_HEIGHT/2 - text.getGlobalBounds().height/2);

    m_window.draw(text);
    m_window.display();

    while(m_window.pollEvent(event) || !resume)
    {
        if(!resume)
        {
            if(sf::Joystick::isButtonPressed(0, 7))
            {
                resume = true;
                sf::sleep(sf::milliseconds(200));
            }
            else if(event.type == sf::Event::Closed)
            {
                resume = true;
                m_window.close();
            }
        }

        sf::sleep(sf::milliseconds(20));
    }
}
