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

#include "../include/Config.hpp"
#include "../include/Log.hpp"
#include "../include/IntroScreens.hpp"

/////////////////////////////////////////////////

IntroScreens::IntroScreens(sf::RenderWindow* window)
{
    m_window = window;
}

/////////////////////////////////////////////////

void IntroScreens::displayAuthor()
{
    sf::Texture authorScreen;

    if(authorScreen.loadFromFile(Config::RESOURCES_PATH + "InternationalKoder.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "InternationalKoder.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "InternationalKoder.png'");
    }

    sf::Sprite authorScreenS(authorScreen);
    sf::Color newColor = authorScreenS.getColor();
    newColor.a = 0;
    authorScreenS.setColor(newColor);

    sf::CircleShape balls[BALLS_NUMBER];
    char ballSpeedRight[BALLS_NUMBER];
    char ballSpeedDown[BALLS_NUMBER];

    // init
    for(unsigned int i = 0 ; i < BALLS_NUMBER ; i++)
    {
        unsigned int colR = (rand() % 150) + 150;
        unsigned int colG = (rand() % 150) + 150;
        unsigned int colB = (rand() % 150) + 150;

        unsigned int posX = (rand() % (Config::WINDOW_WIDTH - 20) + 10);
        unsigned int posY = (rand() % (BOTTOM_LIMIT - UPPER_LIMIT - 20)) + UPPER_LIMIT;

        balls[i].setRadius(10.0f);
        balls[i].setFillColor(sf::Color(colR, colG, colB, 0));
        balls[i].setPosition(posX, posY);
        ballSpeedRight[i] = (rand() % 20) - 10;
        ballSpeedDown[i] = (rand() % 20) - 10;
    }
    sf::FloatRect bSize = balls[0].getGlobalBounds();
    sf::Vector2f ballSize(bSize.width, bSize.height);


    // appearing
    for(unsigned int i = 0 ; i < 51 ; i++)
    {
        sf::Color newColor = authorScreenS.getColor();
        newColor.a += 5;
        authorScreenS.setColor(newColor);

        m_window->clear();
        m_window->draw(authorScreenS);

        for(unsigned int j = 0 ; j < BALLS_NUMBER ; j++)
        {
            refreshBall(balls, j, ballSpeedRight, ballSpeedDown, ballSize);

            newColor = balls[j].getFillColor();
            newColor.a += 5;
            balls[j].setFillColor(newColor);

            m_window->draw(balls[j]);
        }

        m_window->display();
        sf::sleep(sf::seconds(0.04));
    }

    // "pause"
    for(unsigned int i = 0 ; i < 100 ; i++)
    {
        m_window->clear();
        m_window->draw(authorScreenS);

        for(unsigned int j = 0 ; j < BALLS_NUMBER ; j++)
        {
            refreshBall(balls, j, ballSpeedRight, ballSpeedDown, ballSize);
            m_window->draw(balls[j]);
        }

        m_window->display();
        sf::sleep(sf::seconds(0.04));
    }


    // disappearing
    for(int i = 50 ; i >= 0 ; i--)
    {
        sf::Color newColor = authorScreenS.getColor();
        newColor.a -= 5;
        authorScreenS.setColor(newColor);

        m_window->clear();
        m_window->draw(authorScreenS);

        for(unsigned int j = 0 ; j < BALLS_NUMBER ; j++)
        {
            refreshBall(balls, j, ballSpeedRight, ballSpeedDown, ballSize);

            newColor = balls[j].getFillColor();
            newColor.a -= 5;
            balls[j].setFillColor(newColor);

            m_window->draw(balls[j]);
        }

        m_window->display();
        sf::sleep(sf::seconds(0.04));
    }
}

/////////////////////////////////////////////////

void IntroScreens::refreshBall(sf::CircleShape* balls, unsigned int index, char* ballSpeedRight, char* ballSpeedDown,
                               const sf::Vector2f& ballSize)
{
    balls[index].move(ballSpeedRight[index], ballSpeedDown[index]);
    sf::Vector2f pos = balls[index].getPosition();

    if(pos.x + ballSize.x + ballSpeedRight[index] >= Config::WINDOW_WIDTH || pos.x + ballSpeedDown[index] <= 0)
    {
        ballSpeedRight[index] *= -1;
    }
    if(pos.y + ballSize.y + ballSpeedDown[index] >= BOTTOM_LIMIT || pos.y + ballSpeedDown[index] <= UPPER_LIMIT)
    {
        ballSpeedDown[index] *= -1;
    }
}
