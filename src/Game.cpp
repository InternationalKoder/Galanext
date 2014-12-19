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

#include "Game.hpp"
#include <sstream>
#include "KeyboardSpaceshipController.hpp"
#include "JoystickSpaceshipController.hpp"

const unsigned int Game::WINDOW_WIDTH = 500;
const unsigned int Game::WINDOW_HEIGHT = 400;
const std::string Game::WINDOW_TITLE = "Galanext";
const std::string Game::RESOURCES_LOCATION = "resources/";
const std::string Game::FONT_LOCATION = "xolonium/Xolonium-Regular.otf";
const unsigned int Game::TILES_WIDTH = 32;
const unsigned int Game::TILES_HEIGHT = 32;
const float Game::PLAYER_SPACESHIP_SPEED = 8.0f;
const unsigned short Game::NUMBER_SPACESHIP_TILES = 3;
const float Game::SHOT_SPEED = 12.0f;
const float Game::ENEMY_SPACESHIP_SPEED = 6.0f;
const unsigned short Game::NUMBER_ENEMIES_PER_ROW = 8;
const unsigned short Game::NUMBER_ROWS = 2;
const float Game::PIXELS_BETWEEN_ENEMIES = 20.0f;
const float Game::PIXELS_BETWEEN_ROWS = 10.0f;

/////////////////////////////////////////////////

Game::Game()
{
    // loading the textures
    m_playerTexture.loadFromFile(RESOURCES_LOCATION + "player.png");
    m_shotTexture.loadFromFile(RESOURCES_LOCATION + "shot.png");

    // creating the window and the player
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
    m_player = new Spaceship(m_playerTexture, PLAYER_SPACESHIP_SPEED);

    for(unsigned short row = 0 ; row < NUMBER_ROWS ; row++)
    {
        sf::Texture currentTexture;

        std::ostringstream oss;
        oss << RESOURCES_LOCATION << "enemy" << row << ".png";
        currentTexture.loadFromFile(oss.str());
        m_enemiesTextures.push_back(currentTexture);
    }

    m_enemies = new EnemiesGroup(m_player, m_enemiesTextures, m_shotTexture);

    // setting the controllers
    m_player->addController(new KeyboardSpaceshipController(m_window, m_player, m_shotTexture, m_enemies->getSpaceships()));
    m_player->addController(new JoystickSpaceshipController(m_window, m_player, m_shotTexture, m_enemies->getSpaceships()));

    // setting the window
    m_window.setVerticalSyncEnabled(true);
}

/////////////////////////////////////////////////

void Game::start()
{
    sf::Clock clock;

    while(m_window.isOpen())
    {
        if(clock.getElapsedTime().asMilliseconds() > 20)
        {
            sf::Event event;

            clock.restart();

            while(m_window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    m_window.close();
                else if(event.type == sf::Event::LostFocus)
                {
                    // pauses the game when focus is lost
                    bool resume(false);
                    while(!resume)
                    {
                        m_window.pollEvent(event);
                        if(event.type == sf::Event::GainedFocus)
                            resume = true;

                        sf::sleep(sf::milliseconds(100));
                    }
                }
            }

            refresh();

            draw();

        }
        else
            sf::sleep(sf::seconds(0.02f - clock.getElapsedTime().asSeconds()));
    }
}

/////////////////////////////////////////////////

Game::~Game()
{
    delete m_player;
    delete m_enemies;
}

/////////////////////////////////////////////////

void Game::refresh()
{
    m_space.refresh();
    if(m_player != NULL)
        m_player->refresh();
    if(m_enemies->getSpaceships()->size() != 0)
        m_enemies->refresh();

    if(m_enemies->isPlayerDestroyed())
        m_player = NULL;
}

/////////////////////////////////////////////////

void Game::draw()
{
    m_window.clear();

    m_window.draw(m_space);
    if(m_player != NULL)
        m_window.draw(*m_player);
    if(m_enemies->getSpaceships()->size() != 0)
        m_window.draw(*m_enemies);

    m_window.display();
}
