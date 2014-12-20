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

#include "KeyboardSpaceshipController.hpp"
#include <SFML/Graphics.hpp>
#include "Game.hpp"

/////////////////////////////////////////////////

KeyboardSpaceshipController::KeyboardSpaceshipController(sf::RenderWindow& window, Spaceship *spaceship, const sf::Texture& shotTexture, std::vector<Spaceship*> *enemies, const sf::Font& font) : SpaceshipController(spaceship, shotTexture, enemies), m_window(window), m_font(font) {}

/////////////////////////////////////////////////

void KeyboardSpaceshipController::events()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_spaceship->move(-1);
        m_direction = -1;
    }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_spaceship->move(1);
        m_direction = 1;
    }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		fire(-1);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        pause();
}

/////////////////////////////////////////////////

void KeyboardSpaceshipController::pause()
{
    sf::Event event;
    bool resume(false);

    sf::sleep(sf::milliseconds(200));

    sf::Text text("Press escape to resume the game", m_font, 16);
    text.setPosition(Game::WINDOW_WIDTH/2 - text.getGlobalBounds().width/2, Game::WINDOW_HEIGHT/2 - text.getGlobalBounds().height/2);

    m_window.draw(text);
    m_window.display();

    while(m_window.pollEvent(event) || !resume)
    {
        if(!resume)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                resume = true;
                sf::sleep(sf::milliseconds(200));
            }
            else if(event.type == sf::Event::Closed)
            {
                resume = true;
                m_window.close();
            }

            sf::sleep(sf::milliseconds(20));
        }
    }
}
