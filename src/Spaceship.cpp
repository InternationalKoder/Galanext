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
#include "../include/Config.hpp"

/////////////////////////////////////////////////

const unsigned char Spaceship::NUMBER_ANIMATION = 4;

const float Spaceship::SPEED = 8.0f;

/////////////////////////////////////////////////

Spaceship::Spaceship() :
    m_ticksCounter(0),
    m_active(true),
    m_exploding(false)
{}

/////////////////////////////////////////////////

Spaceship::Spaceship(const sf::Texture& texture, const sf::Vector2f& startingPos, std::list<Spaceship*>* targets) :
    m_sprite(texture),
    m_ticksCounter(0),
    m_active(true),
    m_targets(targets),
    m_exploding(false)
{
    unsigned int spriteWidth = texture.getSize().x / NUMBER_ANIMATION;

    m_sprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, texture.getSize().y));
    m_sprite.setPosition(startingPos);
}

/////////////////////////////////////////////////

void Spaceship::move(const sf::Vector2f& movement)
{
    if(m_active)
    {
        sf::Vector2f newPosition = m_sprite.getPosition() + movement;

        if(newPosition.x > 0.0f && newPosition.x + m_sprite.getGlobalBounds().width < Config::WINDOW_WIDTH)
        {
            m_sprite.move(movement);
        }
    }
}

/////////////////////////////////////////////////

Shot* Spaceship::fire(const sf::Texture& texture, bool goesUp)
{
    Shot* newShot = 0;

    if(m_active)
    {
        float xStart = m_sprite.getPosition().x + (m_sprite.getGlobalBounds().width / 2 - texture.getSize().x / 2);
        float yStart = m_sprite.getPosition().y;

        if(goesUp)
        {
            yStart -= texture.getSize().y;
        }
        else
        {
            yStart += texture.getSize().y;
        }

        sf::Vector2f startingPos(xStart, yStart);

        newShot = new Shot(texture, startingPos, goesUp, *m_targets);
    }

    return newShot;
}

/////////////////////////////////////////////////

sf::FloatRect Spaceship::getGlobalBounds()
{
    return m_sprite.getGlobalBounds();
}

/////////////////////////////////////////////////

void Spaceship::setPosition(const sf::Vector2f& position)
{
    m_sprite.setPosition(position);
}

/////////////////////////////////////////////////

void Spaceship::setActive(bool active, bool exploding)
{
    m_active = active;
    m_exploding = exploding;

    m_ticksCounter = 0;

    if(!exploding)
    {
        const sf::Vector2u textureSize = m_sprite.getTexture()->getSize();
        unsigned int spriteWidth = textureSize.x / NUMBER_ANIMATION;

        m_sprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, textureSize.y));
    }
}

/////////////////////////////////////////////////

bool Spaceship::isActive()
{
    return m_active;
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
        unsigned int spriteWidth = texture->getSize().x / NUMBER_ANIMATION;

        if(rectPos >= texture->getSize().x - spriteWidth)
        {
            rectPos = 0;
        }

        m_sprite.setTextureRect(sf::IntRect(rectPos, 0, textureRect.width, textureRect.height));
    }
}

/////////////////////////////////////////////////

void Spaceship::display(sf::RenderWindow& window)
{
    if(m_active)
    {
        window.draw(m_sprite);
    }
    else if(m_exploding)
    {
        const sf::Vector2u textureSize = m_sprite.getTexture()->getSize();
        unsigned int spriteWidth = textureSize.x / NUMBER_ANIMATION;

        m_sprite.setTextureRect(sf::IntRect(textureSize.x - spriteWidth, 0, spriteWidth, textureSize.y));

        window.draw(m_sprite);

        if(m_ticksCounter >= 5)
        {
            m_exploding = false;
        }
    }
}
