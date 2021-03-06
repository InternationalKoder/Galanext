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
#include "../include/Spaceship.hpp"
#include "../include/IntroScreens.hpp"

/////////////////////////////////////////////////

IntroScreens::IntroScreens(sf::RenderWindow& window) : m_window(window)
{}

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
    sf::Event event;


    // appearing
    for(unsigned int i = 0 ; i < 51 && m_window.isOpen() ; i++)
    {
        sf::Color newColor = authorScreenS.getColor();
        newColor.a += 5;
        authorScreenS.setColor(newColor);

        m_window.clear();
        m_window.draw(authorScreenS);

        for(unsigned int j = 0 ; j < BALLS_NUMBER ; j++)
        {
            refreshBall(balls, j, ballSpeedRight, ballSpeedDown, ballSize);

            newColor = balls[j].getFillColor();
            newColor.a += 5;
            balls[j].setFillColor(newColor);

            m_window.draw(balls[j]);
        }

        m_window.display();

        while(m_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }

        sf::sleep(sf::seconds(0.04));
    }

    // "pause"
    for(unsigned int i = 0 ; i < 100 && m_window.isOpen() ; i++)
    {
        m_window.clear();
        m_window.draw(authorScreenS);

        for(unsigned int j = 0 ; j < BALLS_NUMBER ; j++)
        {
            refreshBall(balls, j, ballSpeedRight, ballSpeedDown, ballSize);
            m_window.draw(balls[j]);
        }

        m_window.display();

        while(m_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }

        sf::sleep(sf::seconds(0.04));
    }


    // disappearing
    for(int i = 50 ; i >= 0 && m_window.isOpen() ; i--)
    {
        sf::Color newColor = authorScreenS.getColor();
        newColor.a -= 5;
        authorScreenS.setColor(newColor);

        m_window.clear();
        m_window.draw(authorScreenS);

        for(unsigned int j = 0 ; j < BALLS_NUMBER ; j++)
        {
            refreshBall(balls, j, ballSpeedRight, ballSpeedDown, ballSize);

            newColor = balls[j].getFillColor();
            newColor.a -= 5;
            balls[j].setFillColor(newColor);

            m_window.draw(balls[j]);
        }

        m_window.display();

        while(m_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }

        sf::sleep(sf::seconds(0.04));
    }
}

/////////////////////////////////////////////////

void IntroScreens::displayTitle(const sf::Font& font, const sf::Texture& spaceshipTexture, Highscore* highscores)
{
    // Loading textures

    sf::Texture titleT;
    if(titleT.loadFromFile(Config::RESOURCES_PATH + "galanext.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "galanext.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "galanext.png'");
    }

    sf::Texture titleBGT;
    if(titleBGT.loadFromFile(Config::RESOURCES_PATH + "title-background.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "title-background.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "title-background.png'");
    }


    // Sprites initialization

    sf::Sprite titleBG(titleBGT);
    sf::Sprite title(titleT);
    title.setPosition(Config::WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, Config::WINDOW_HEIGHT / 5);

    sf::Sprite spaceship(spaceshipTexture);

    int spriteWidth = spaceshipTexture.getSize().x / Spaceship::NUMBER_ANIMATION;
    unsigned int spriteHeight = spaceshipTexture.getSize().y;
    unsigned int spaceshipPosY = (rand() % (Config::WINDOW_HEIGHT - Config::BOTTOM_MARGIN - Config::TOP_MARGIN
                                            - spriteHeight)) + Config::TOP_MARGIN;

    spaceship.setTextureRect(sf::IntRect(0, 0, spriteWidth, spaceshipTexture.getSize().y));
    spaceship.rotate(90.0f);
    spaceship.setPosition(0 - spriteWidth, spaceshipPosY);

    sf::Text pressSpace("PRESS SPACE TO START", font);
    pressSpace.setCharacterSize(20);
    sf::FloatRect pressSpaceSize = pressSpace.getGlobalBounds();
    pressSpace.setPosition(Config::WINDOW_WIDTH / 2 - pressSpaceSize.width / 2,
                           Config::WINDOW_HEIGHT - Config::BOTTOM_MARGIN - pressSpaceSize.height);



    // Highscores

    sf::Text highscoresText("HIGHSCORES", font);
    highscoresText.setCharacterSize(26);
    highscoresText.setPosition(Config::WINDOW_WIDTH / 2 - highscoresText.getGlobalBounds().width / 2,
                               Config::HIGHSCORES_POS_Y);
    highscoresText.setColor(sf::Color::White);

    sf::Text highscoresTexts[3];
    for(unsigned int i = 0 ; i < 3 ; i++)
    {
        std::string name = highscores[i].getAuthor(), score = std::to_string(highscores[i].getScore());

        highscoresTexts[i] = sf::Text(name + score, font);
        highscoresTexts[i].setCharacterSize(24);
        highscoresTexts[i].setColor(sf::Color::White);

        while(highscoresTexts[i].getGlobalBounds().width < Config::HIGHSCORES_WIDTH)
        {
            name.append(".");
            highscoresTexts[i].setString(name + score);
        }

        float width = highscoresTexts[i].getGlobalBounds().width;
        float posY = Config::HIGHSCORES_POS_Y + (i + 1) * Config::HIGHSCORES_MARGIN;
        highscoresTexts[i].setPosition(Config::WINDOW_WIDTH / 2 - width / 2, posY);

    }



    // Loop

    bool go = false;
    unsigned int framesBlink = 0;
    unsigned int framesHighscores = 0;
    unsigned int highscoresStep = 0;
    unsigned int framesAnimation = 0;
    unsigned int stopSpaceshipCounter = 0;
    bool spaceshipGoesRight = true;
    const float spaceshipSpeed = 5.0f;

    sf::Event event;
    sf::Clock clock;

    while(m_window.isOpen() && !go)
    {
        if(clock.getElapsedTime().asMilliseconds() > 20)
        {
            clock.restart();


            // Events

            while(m_window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    m_window.close();
                }
                else if(event.type == sf::Event::KeyReleased)
                {
                    if(event.key.code == sf::Keyboard::Space)
                    {
                        go = true;
                    }
                }
            }


            // Animations

            if(highscoresStep < 5)
            {
                if((highscoresStep > 0 && framesHighscores == 20) || (highscoresStep == 0 && framesHighscores == 100))
                {
                    framesHighscores = 0;
                    highscoresStep++;
                }
                else
                {
                    framesHighscores++;
                }
            }

            if(framesBlink >= 30)
            {
                framesBlink = 0;
                sf::Color color = pressSpace.getColor();

                if(color.a == 0)
                {
                    color.a = 255;
                }
                else
                {
                    color.a = 0;
                }
                pressSpace.setColor(color);
            }
            else
            {
                framesBlink++;
            }

            if(framesAnimation < 5)
            {
                framesAnimation++;
            }
            else
            {
                framesAnimation = 0;

                const sf::IntRect& textureRect = spaceship.getTextureRect();
                unsigned int rectPos = textureRect.left + textureRect.width;

                if(rectPos >= spaceshipTexture.getSize().x - spriteWidth)
                {
                    rectPos = 0;
                }

                spaceship.setTextureRect(sf::IntRect(rectPos, 0, textureRect.width, textureRect.height));
            }


            // Moving the spaceship

            if(stopSpaceshipCounter <= 0)
            {
                if(spaceship.getPosition().x > Config::WINDOW_WIDTH + 5 + spriteWidth
                        || spaceship.getPosition().x < -5 - spriteWidth)
                {
                    stopSpaceshipCounter = 50;
                    unsigned int spaceshipPosY = (rand() % (Config::WINDOW_HEIGHT - Config::BOTTOM_MARGIN
                                                            - Config::TOP_MARGIN - spriteHeight)) + Config::TOP_MARGIN;

                    spaceship.rotate(180);
                    spaceshipGoesRight = !spaceshipGoesRight;

                    if(spaceship.getPosition().x > Config::WINDOW_WIDTH + 5 + spriteWidth)
                    {
                        spaceship.setPosition(Config::WINDOW_WIDTH + 2, spaceshipPosY);
                    }
                    else
                    {
                        spaceship.setPosition(0 - spriteWidth - 2, spaceshipPosY);
                    }
                }
                else
                {
                    if(spaceshipGoesRight)
                    {
                        spaceship.move(spaceshipSpeed, 0);
                    }
                    else
                    {
                        spaceship.move(spaceshipSpeed * -1, 0);
                    }
                }
            }
            else
            {
                stopSpaceshipCounter--;
            }


            // Display

            m_window.clear();
            m_window.draw(titleBG);
            m_window.draw(spaceship);
            m_window.draw(title);
            m_window.draw(pressSpace);
            if(highscoresStep > 0)
            {
                m_window.draw(highscoresText);
            }
            for(unsigned int i = 0 ; i < 3 ; i++)
            {
                if(i + 1 < highscoresStep)
                {
                    m_window.draw(highscoresTexts[i]);
                }
            }
            m_window.display();
        }
        else
        {
            sf::sleep(sf::seconds(0.02f - clock.getElapsedTime().asSeconds()));
        }
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
