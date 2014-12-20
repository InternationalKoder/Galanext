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

#include "Spaceship.hpp"
#include "Game.hpp"

/////////////////////////////////////////////////

const float Spaceship::DIST_SCREEN_BORDER = 10.0f;

/////////////////////////////////////////////////

Spaceship::Spaceship(const sf::Texture& texture, const float& speed) : m_texture(texture), m_shot(NULL), m_speed(speed), m_spriteCounter(0), m_framesCounter(0), m_score(0)
{
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, Game::TILES_WIDTH, Game::TILES_HEIGHT));
    m_sprite.setPosition(Game::WINDOW_WIDTH/2 - Game::TILES_WIDTH, Game::WINDOW_HEIGHT - Game::TILES_HEIGHT - Spaceship::DIST_SCREEN_BORDER);
}

/////////////////////////////////////////////////

Spaceship::Spaceship(const sf::Texture& texture, const float& speed, const sf::Vector2f& initialPos) : m_texture(texture), m_shot(NULL), m_speed(speed), m_spriteCounter(0), m_framesCounter(0), m_score(0)
{
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, Game::TILES_WIDTH, Game::TILES_HEIGHT));
    m_sprite.setPosition(initialPos);
}

/////////////////////////////////////////////////

void Spaceship::addController(SpaceshipController *controller)
{
	m_controllers.push_back(controller);
}

/////////////////////////////////////////////////

bool Spaceship::movePossible(const char& direction)
{
	const float newPos(m_sprite.getPosition().x + (m_speed * direction));
	bool possible(false);

	if(newPos >= 0.0f && newPos + Game::TILES_WIDTH <= Game::WINDOW_WIDTH)
		possible = true;

	return possible;
}

/////////////////////////////////////////////////

void Spaceship::move(const char& direction)
{
	if(movePossible(direction))
		m_sprite.move((m_speed * direction), 0.0f);
}

/////////////////////////////////////////////////

int Spaceship::getScore()
{
	return m_score;
}

/////////////////////////////////////////////////

sf::FloatRect Spaceship::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
}

/////////////////////////////////////////////////

std::vector<SpaceshipController*>* Spaceship::getControllers()
{
    return &m_controllers;
}

/////////////////////////////////////////////////

Shot* Spaceship::getShot()
{
	return m_shot;
}

/////////////////////////////////////////////////

void Spaceship::setShot(Shot *shot)
{
	m_shot = shot;
}

/////////////////////////////////////////////////

void Spaceship::refresh()
{
	const unsigned int nbC = m_controllers.size();

	for(unsigned int i = 0 ; i < nbC ; i++)
	{
        m_controllers[i]->events();
	}

	if(m_shot != NULL)
	{
        int scoreToAdd(0);

		if(m_shot->refresh(scoreToAdd))
		{
			delete m_shot;
			m_shot = NULL;
		}

		m_score += scoreToAdd;
	}

    if(m_framesCounter == 5)
    {
        m_framesCounter = 0;
        m_sprite.setTextureRect(sf::IntRect(32 * m_spriteCounter, 0, Game::TILES_WIDTH, Game::TILES_HEIGHT));
        if(m_spriteCounter == Game::NUMBER_SPACESHIP_TILES-1)
            m_spriteCounter = 0;
        else
            m_spriteCounter++;
    }
    else
        m_framesCounter++;
}

Spaceship::~Spaceship()
{
    delete m_shot;

    // deleting the controllers
    for(std::vector<SpaceshipController*>::iterator it = m_controllers.begin() ; it != m_controllers.end() ; )
    {
        delete *it;
        it = m_controllers.erase(it);
    }
}
