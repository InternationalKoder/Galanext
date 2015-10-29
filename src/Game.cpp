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

#include "../include/Game.hpp"
#include "../include/Config.hpp"
#include "../include/Log.hpp"
#include <fstream>

/////////////////////////////////////////////////

Game::Game() :
    m_scoreText("SCORE", m_font),
    m_scoreValueText("0", m_font),
    m_levelText("LEVEL", m_font),
    m_levelValueText("1", m_font),
    m_pauseText("GAME PAUSED", m_font),
    m_gameOverText("GAME OVER", m_font),
    m_introScreens(m_window),
    m_topBar(sf::Vector2f(Config::WINDOW_WIDTH, Config::TOP_MARGIN)),
    m_window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE)

{
    Log::debug("Opened window with resolution " + std::to_string(Config::WINDOW_WIDTH) + "x"
               + std::to_string(Config::WINDOW_HEIGHT));

    m_window.setVerticalSyncEnabled(true);

    m_ticksCounter = 0;
    m_level = 1;
    m_score = 0;

    loadResources();


    // player's spaceship
    unsigned int playerSpaceshipSW = m_playerSpaceshipT.getSize().x / Spaceship::NUMBER_ANIMATION;
    unsigned int playerSpaceshipSH = m_playerSpaceshipT.getSize().y;

    sf::Vector2f playerSpaceshipStartingPos(Config::WINDOW_WIDTH / 2 - playerSpaceshipSW / 2,
                                            Config::WINDOW_HEIGHT - playerSpaceshipSH - Config::BOTTOM_MARGIN);
    m_playerSpaceship = Spaceship(m_playerSpaceshipT, playerSpaceshipStartingPos, &m_enemiesSpaceships);
    m_playerSpaceships.push_back(&m_playerSpaceship);

    m_keyboardController = KeyboardSpaceshipController(m_shotT);
    m_keyboardController.addSpaceship(m_playerSpaceship);
    Log::info("Using keyboard controller for player's spaceship");


    // enemies' spaceships
    m_cpuController = CpuSpaceshipController(m_shotT);
    for(int i = 0 ; i < ENEMIES_COLS_COUNT ; i++)
    {
        m_enemies[0][i] = Spaceship(m_enemy0SpaceshipT, sf::Vector2f(0.0f, 0.0f), &m_playerSpaceships);
        m_enemies[1][i] = Spaceship(m_enemy1SpaceshipT, sf::Vector2f(0.0f, 0.0f), &m_playerSpaceships);
        m_enemies[2][i] = Spaceship(m_enemy2SpaceshipT, sf::Vector2f(0.0f, 0.0f), &m_playerSpaceships);

        for(int j = 0 ; j < ENEMIES_LINES_COUNT ; j++)
        {
            m_enemiesSpaceships.push_back(&m_enemies[j][i]);
            m_cpuController.addSpaceship(m_enemies[j][i]);
        }
    }

    // texts
    m_scoreText.setColor(sf::Color::White);
    m_scoreText.setCharacterSize(18);

    unsigned int textPosY = Config::TOP_MARGIN / 2 - m_scoreText.getGlobalBounds().height;

    m_scoreText.setPosition(Config::SCORE_TEXT_POS_X, textPosY);

    m_scoreValueText.setColor(sf::Color::White);
    m_scoreValueText.setCharacterSize(18);
    unsigned int scoreValuePosX = Config::SCORE_TEXT_POS_X + m_scoreText.getGlobalBounds().width + Config::SCORE_MARGIN;
    m_scoreValueText.setPosition(scoreValuePosX, textPosY);

    m_levelText.setColor(sf::Color::White);
    m_levelText.setCharacterSize(18);
    m_levelText.setPosition(Config::LEVEL_TEXT_POS_X, textPosY);

    m_levelValueText.setColor(sf::Color::White);
    m_levelValueText.setCharacterSize(18);
    unsigned int levelValuePosX = Config::LEVEL_TEXT_POS_X + m_levelText.getGlobalBounds().width + Config::LEVEL_MARGIN;
    m_levelValueText.setPosition(levelValuePosX, textPosY);

    m_pauseText.setColor(sf::Color::White);
    m_pauseText.setCharacterSize(24);
    m_pauseText.setPosition(Config::WINDOW_WIDTH / 2 - m_pauseText.getGlobalBounds().width / 2,
                          Config::WINDOW_HEIGHT / 2 - m_pauseText.getGlobalBounds().height / 2);

    m_gameOverText.setColor(sf::Color::White);
    m_gameOverText.setCharacterSize(26);
    m_gameOverText.setPosition(Config::WINDOW_WIDTH / 2 - m_gameOverText.getGlobalBounds().width / 2,
                               Config::WINDOW_HEIGHT / 2 - m_gameOverText.getGlobalBounds().height / 2);


    m_topBar.setFillColor(sf::Color::Black);


    readHighscoresFile();

    m_introScreens.displayAuthor();
}

/////////////////////////////////////////////////

void Game::gameLoop()
{
    m_gameLost = true;
    sf::Clock clock;

    while(m_window.isOpen())
    {
        if(clock.getElapsedTime().asMilliseconds() > 20)
        {
            m_ticksCounter++;
            if(m_gameLost)
            {
                firstLevel();
                m_ticksCounter = 0;
                m_gameLost = false;
            }

            if(m_ticksCounter >= 100)
            {
                Log::debug(std::to_string(1.0f / clock.getElapsedTime().asSeconds()) + " ticks/s");
                m_ticksCounter = 0;
            }

            sf::Event event;

            clock.restart();

            while(m_window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    m_window.close();
                }
                else if(event.type == sf::Event::KeyReleased || event.type == sf::Event::LostFocus)
                {
                    if(event.key.code == sf::Keyboard::Escape || event.type == sf::Event::LostFocus)
                    {
                        pause();
                    }
                }
            }

            refresh();
            display();
        }
        else
        {
            sf::sleep(sf::seconds(0.02f - clock.getElapsedTime().asSeconds()));
        }
    }
}

////////////////////////////////////////////////////

void Game::refresh()
{
    m_space.refresh();
    m_keyboardController.handleEvents(m_allShots);
    m_cpuController.handleEvents(m_allShots);

    std::list<Spaceship*> destroyedSpaceships;

    for(std::list<Shot*>::iterator it = m_allShots.begin() ; it != m_allShots.end() ; ++it)
    {
        Spaceship* destroyed = (*it)->refresh();
        if(destroyed == &m_playerSpaceship)
        {
            Log::debug("Game over!");

            m_gameLost = true;
            display();
            m_window.draw(m_gameOverText);
            m_window.display();


            // Wait for 3 seconds but keep listening to the events
            sf::Event event;
            unsigned int i = 0;

            while(m_window.isOpen() && i < 12)
            {
                while(m_window.pollEvent(event) && m_window.isOpen())
                {
                    if(event.type == sf::Event::Closed)
                    {
                        m_window.close();
                    }
                }

                i++;
                sf::sleep(sf::seconds(0.25f));
            }
        }
        else if(destroyed != 0)
        {
            destroyedSpaceships.push_back(destroyed);
        }
    }
    if(!m_gameLost)
    {
        for(std::list<Spaceship*>::iterator it = m_playerSpaceships.begin() ; it != m_playerSpaceships.end() ; ++it)
        {
            (*it)->refresh();
        }
        bool enemiesAlive = false;
        for(std::list<Spaceship*>::iterator it = m_enemiesSpaceships.begin() ; it != m_enemiesSpaceships.end() ; ++it)
        {
            (*it)->refresh();

            if((*it)->isActive())
            {
                enemiesAlive = true;
            }

            for(std::list<Spaceship*>::iterator it2 = destroyedSpaceships.begin() ; it2 != destroyedSpaceships.end() ; )
            {
                if(*it == *it2)
                {
                    m_score += 100;
                    Log::debug("Enemy spaceship destroyed: score +100");
                    it2 = destroyedSpaceships.erase(it2);
                }
                else
                {
                    ++it2;
                }
            }
        }

        if(!enemiesAlive)
        {
            nextLevel();
            Log::debug("Going to next level");
        }

        m_scoreValueText.setString(std::to_string(m_score));
    }
}

////////////////////////////////////////////////////

void Game::readHighscoresFile()
{
    bool error = false;
    std::ifstream file(Config::HIGHSCORES_FILE.c_str());

    if(!file)
    {
        error = true;
        Log::warn("File '" + Config::HIGHSCORES_FILE + "' not found for highscores, one will be created");
    }

    std::string line;
    int i;

    do
    {
        if(error)
        {
            file.close();
            createHighscoresFile();
            file.open(Config::HIGHSCORES_FILE.c_str());
            error = false;
        }

        i = 2;

        while(getline(file, line) && !error && i >= 0)
        {
            unsigned int separatorPos = line.find_first_of(' ');

            if(line.find_last_of(' ') != separatorPos)
            {
                error = true;
                Log::warn("Error while reading highscores file '" + Config::HIGHSCORES_FILE + "', a new one will be" +
                          " created");
            }
            else
            {
                std::string name = line.substr(0, separatorPos);
                std::string score = line.substr(separatorPos + 1);

                if(name.length() > 6)
                {
                    error = true;
                    Log::warn("Error while reading highscores file '" + Config::HIGHSCORES_FILE + "', a new one will" +
                              " be created");
                }
                else
                {
                    m_highscores[i] = Highscore(atoi(score.c_str()), name);
                    Log::debug("Read highscore " + std::to_string(i+1) + ": " + score + " by " + name);
                }
            }

            i--;
        }

        if(i >= 0)
        {
            error = true;
            Log::warn("Error while reading highscores file '" + Config::HIGHSCORES_FILE + "', a new one will" +
                      " be created");
        }
    } while(error);

    file.close();
}

////////////////////////////////////////////////////

void Game::loadResources()
{
    // font
    if(m_font.loadFromFile(Config::RESOURCES_PATH + "xen3.ttf"))
    {
        Log::debug("Font '" + Config::RESOURCES_PATH + "xen3.ttf' successfully loaded");
    }
    else
    {
        Log::error("Can not load font '" + Config::RESOURCES_PATH + "xen3.ttf'");
    }

    // player spaceship
    if(m_playerSpaceshipT.loadFromFile(Config::RESOURCES_PATH + "player.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "player.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "player.png'");
    }

    // enemies spaceships
    if(m_enemy0SpaceshipT.loadFromFile(Config::RESOURCES_PATH + "enemy0.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "enemy0.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "enemy0.png'");
    }

    if(m_enemy1SpaceshipT.loadFromFile(Config::RESOURCES_PATH + "enemy1.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "enemy1.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "enemy1.png'");
    }

    if(m_enemy2SpaceshipT.loadFromFile(Config::RESOURCES_PATH + "enemy2.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "enemy2.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "enemy2.png'");
    }

    // shot
    if(m_shotT.loadFromFile(Config::RESOURCES_PATH + "shot.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "shot.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "shot.png'");
    }
}

/////////////////////////////////////////////////

void Game::firstLevel()
{
    m_introScreens.displayTitle(m_font, m_playerSpaceshipT);

    unsigned int playerSpaceshipSW = m_playerSpaceshipT.getSize().x / Spaceship::NUMBER_ANIMATION;
    unsigned int playerSpaceshipSH = m_playerSpaceshipT.getSize().y;

    sf::Vector2f playerSpaceshipStartingPos(Config::WINDOW_WIDTH / 2 - playerSpaceshipSW / 2,
                                            Config::WINDOW_HEIGHT - playerSpaceshipSH - Config::BOTTOM_MARGIN);
    m_playerSpaceship.setActive(true);
    m_playerSpaceship.setPosition(playerSpaceshipStartingPos);

    m_score = 0;
    m_level = 1;

    m_cpuController.resetFireSpeed();

    changeLevel();
}

/////////////////////////////////////////////////

void Game::nextLevel()
{
    m_level++;
    m_cpuController.increaseFireSpeed();

    changeLevel();
}

/////////////////////////////////////////////////

void Game::display()
{
    m_window.clear();
    m_space.display(m_window);
    for(std::list<Spaceship*>::iterator it = m_playerSpaceships.begin() ; it != m_playerSpaceships.end() ; ++it)
    {
        (*it)->display(m_window);
    }
    for(std::list<Spaceship*>::iterator it = m_enemiesSpaceships.begin() ; it != m_enemiesSpaceships.end() ; ++it)
    {
        (*it)->display(m_window);
    }
    for(std::list<Shot*>::iterator it = m_allShots.begin() ; it != m_allShots.end() ; ++it)
    {
        (*it)->display(m_window);
    }
    m_window.draw(m_topBar);
    m_window.draw(m_scoreText);
    m_window.draw(m_scoreValueText);
    m_window.draw(m_levelText);
    m_window.draw(m_levelValueText);
    m_window.display();
}

/////////////////////////////////////////////////

void Game::getReady()
{
    sf::Text text("GET READY", m_font);
    text.setCharacterSize(18);

    unsigned int posX = Config::WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2;
    unsigned int posY = Config::WINDOW_HEIGHT / 2 - text.getGlobalBounds().height / 2;

    text.setPosition(posX, posY);

    m_window.draw(text);
    m_window.display();

    sf::Event event;

    for(unsigned char i = 0 ; i < 8 && m_window.isOpen() ; i++)
    {
        sf::sleep(sf::seconds(0.25f));

        while(m_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }
    }
}

/////////////////////////////////////////////////

void Game::pause()
{
    m_window.draw(m_pauseText);
    m_window.display();

    Log::debug("Game paused");
    bool end = false;
    sf::Clock clock;

    while(!end)
    {
        if(clock.getElapsedTime().asMilliseconds() > 20)
        {
            clock.restart();
            sf::Event event;

            while(m_window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    end = true;
                    m_window.close();
                }
                else if(event.type == sf::Event::KeyReleased)
                {
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        end = true;
                        Log::debug("Game resumed");
                    }
                }
            }
        }
        else
        {
            sf::sleep(sf::seconds(0.02f - clock.getElapsedTime().asSeconds()));
        }
    }
}

/////////////////////////////////////////////////

Game::~Game()
{
    for(std::list<Shot*>::iterator it = m_allShots.begin() ; it != m_allShots.end() ; ++it)
    {
        delete (*it);
    }
}

/////////////////////////////////////////////////

void Game::changeLevel()
{
    for(std::list<Shot*>::iterator it = m_allShots.begin() ; it != m_allShots.end() ; ++it)
    {
        delete (*it);
    }
    m_allShots.clear();

    for(int i = 0 ; i < ENEMIES_LINES_COUNT ; i++)
    {
        for(int j = 0 ; j < ENEMIES_COLS_COUNT ; j++)
        {
            m_enemies[i][j].setActive(true);
            if(i == 0)
            {
                sf::Vector2f startingPos(50 * j + Config::ENEMIES_LEFT_MARGIN, Config::TOP_MARGIN + 10);
                m_enemies[0][j].setPosition(startingPos);
            }
            else if(i == 1)
            {
                sf::Vector2f startingPos(50 * j + Config::ENEMIES_LEFT_MARGIN, Config::TOP_MARGIN + 70);
                m_enemies[1][j].setPosition(startingPos);
            }
            else
            {
                sf::Vector2f startingPos(65 * (j - 1) + Config::ENEMIES_LEFT_MARGIN, Config::TOP_MARGIN + 130);
                m_enemies[i][j].setPosition(startingPos);
                if(j < 2 || j > ENEMIES_COLS_COUNT - 3)
                {
                    m_enemies[i][j].setActive(false);
                }
            }
        }
    }

    m_levelValueText.setString(std::to_string(m_level));
    m_scoreValueText.setString(std::to_string(m_score));

    display();
    getReady();
}

/////////////////////////////////////////////////

void Game::createHighscoresFile()
{
    std::ofstream file(Config::HIGHSCORES_FILE.c_str(), std::ios::trunc);

    if(file)
    {
        file << "INTKOD 15000" << std::endl << "EDISON 10000" << std::endl << "KAYTON 5000" << std::endl;
    }
    else
    {
        Log::error("Could not write new highscores file '" + Config::HIGHSCORES_FILE + "'");
        m_highscores[0].setScore(15000);
        m_highscores[0].setAuthor("INTKOD");
        m_highscores[1].setScore(10000);
        m_highscores[1].setAuthor("EDISON");
        m_highscores[2].setScore(5000);
        m_highscores[2].setAuthor("KAYTON");
    }

    file.close();
}
