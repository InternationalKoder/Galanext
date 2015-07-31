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

#include "../include/Spaceship.hpp"

/////////////////////////////////////////////////

const unsigned char Spaceship::NUMBER_ANIMATION = 3;

/////////////////////////////////////////////////

Spaceship::Spaceship(const sf::Texture& texture, const sf::Vector2f& startingPos) : m_sprite(texture)
{
    unsigned int spriteWidth = texture.getSize().x / NUMBER_ANIMATION;

    m_sprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, texture.getSize().y));
    m_sprite.setPosition(startingPos);

    m_ticksCounter = 0;
}

/////////////////////////////////////////////////

void Spaceship::refresh()
{
    if(m_ticksCounter < 5)
    {
        m_ticksCounter++;
    }
    else
    {
        m_ticksCounter = 0;

        const sf::IntRect& textureRect = m_sprite.getTextureRect();
        const sf::Texture* texture = m_sprite.getTexture();

        unsigned int rectPos = textureRect.left + textureRect.width;

        if(rectPos == texture->getSize().x)
        {
            rectPos = 0;
        }

        m_sprite.setTextureRect(sf::IntRect(rectPos, 0, textureRect.width, textureRect.height));
    }
}

/////////////////////////////////////////////////

void Spaceship::display(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}
