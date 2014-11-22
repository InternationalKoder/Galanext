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
#include "constants.hpp"

/////////////////////////////////////////////////

Spaceship::Spaceship(const std::string& path, const float& speed) : m_shot(NULL), m_speed(speed)
{
	m_texture.loadFromFile(path.c_str());
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(WINDOW_WIDTH/2 - m_texture.getSize().x/2, WINDOW_HEIGHT - m_texture.getSize().y - DIST_SCREEN_BORDER);
}

/////////////////////////////////////////////////

Spaceship::Spaceship(const std::string& path, const float& speed, const sf::Vector2f& initialPos) : m_shot(NULL), m_speed(speed)
{
	m_texture.loadFromFile(path.c_str());
    m_sprite.setTexture(m_texture);
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

	if(newPos >= 0.0f && newPos + m_sprite.getGlobalBounds().width <= WINDOW_WIDTH)
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

sf::FloatRect Spaceship::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
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
		if(m_shot->refresh())
		{
			delete m_shot;
			m_shot = NULL;
		}
	}
}

Spaceship::~Spaceship()
{
    delete m_shot;
}
