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

#include "../include/EnemiesGroup.hpp"
#include "../include/Game.hpp"
#include "../include/AISpaceshipController.hpp"
#include <sstream>

/////////////////////////////////////////////////

EnemiesGroup::EnemiesGroup(Spaceship *playerSpaceship, const std::vector<sf::Texture>& textures, const sf::Texture& shotTexture) : m_controller(&m_spaceships), m_playerSpaceship(playerSpaceship), m_textures(textures), m_shotTexture(shotTexture)
{
    for(unsigned short row = 0 ; row < Game::NUMBER_ROWS ; row++)
    {
        float currentPos(0.0f);

        for(unsigned short i = 0 ; i < Game::NUMBER_ENEMIES_PER_ROW ; i++)
        {
            m_spaceships.push_back(new Spaceship(m_textures.at(row), Game::ENEMY_SPACESHIP_SPEED, sf::Vector2f(currentPos, Game::PIXELS_BETWEEN_ROWS * row + Game::TILES_HEIGHT * row + Spaceship::DIST_SCREEN_BORDER + Game::TOP_BAR_HEIGHT)));
            currentPos += Game::TILES_WIDTH + Game::PIXELS_BETWEEN_ENEMIES;
        }
    }

    m_player.push_back(m_playerSpaceship);

    for(std::vector<Spaceship*>::iterator it = m_spaceships.begin() ; it != m_spaceships.end() ; )
	{
        AISpaceshipController *aiEnemy = new AISpaceshipController(*it, m_shotTexture, &m_player);
        (*it)->addController(aiEnemy);
        ++it;
    }
}

/////////////////////////////////////////////////

void EnemiesGroup::refresh()
{
    m_controller.events();
}

/////////////////////////////////////////////////

std::vector<Spaceship*>* EnemiesGroup::getSpaceships()
{
    return &m_spaceships;
}

/////////////////////////////////////////////////

bool EnemiesGroup::isPlayerDestroyed()
{
    return (m_player.size() == 0);
}

/////////////////////////////////////////////////

EnemiesGroup::~EnemiesGroup()
{
    for(std::vector<Spaceship*>::iterator it = m_spaceships.begin() ; it != m_spaceships.end() ; )
	{
        std::vector<SpaceshipController*> *controllers = (*it)->getControllers();

        for(std::vector<SpaceshipController*>::iterator it2 = controllers->begin() ; it2 != controllers->end() ; )
        {
            delete *it2;
            it2 = controllers->erase(it2);
        }
        delete *it;
        it = m_spaceships.erase(it);
    }
}
