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

#include "../include/Shot.hpp"
#include "../include/Game.hpp"

/////////////////////////////////////////////////

Shot::Shot(const sf::Texture& texture, const sf::Vector2f& speeds, const sf::Vector2f& initialPos, std::vector<Spaceship*> *spaceships) : m_texture(texture), m_speeds(speeds), m_spaceships(spaceships)
{
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(initialPos);
}

/////////////////////////////////////////////////

void Shot::move()
{
	m_sprite.move(m_speeds);
}

/////////////////////////////////////////////////

sf::Vector2f Shot::getPosition()
{
	return m_sprite.getPosition();
}

/////////////////////////////////////////////////

bool Shot::refresh(int& scoreToAdd)
{
    scoreToAdd = 0;
	bool toDelete(false);
	const sf::FloatRect shotBounds(m_sprite.getGlobalBounds());

	for(std::vector<Spaceship*>::iterator it = m_spaceships->begin() ; it != m_spaceships->end() ; )
	{
		const sf::FloatRect spaceshipBounds((*it)->getGlobalBounds());

		if(shotBounds.intersects(spaceshipBounds))
		{
			delete (*it);
            *it = NULL;
			it = m_spaceships->erase(it);
			toDelete = true;
			scoreToAdd += 100;
		}
		else
			it++;
	}

    if(shotBounds.left < 0.0f || (shotBounds.left + shotBounds.width) > Game::WINDOW_WIDTH || shotBounds.top < 0.0f || (shotBounds.top + shotBounds.height) > Game::WINDOW_HEIGHT)
        toDelete = true;

	move();

	return toDelete;
}
