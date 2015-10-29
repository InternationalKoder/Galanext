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

#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>
#include "../include/Spaceship.hpp"
#include "../include/Space.hpp"
#include "../include/IntroScreens.hpp"
#include "../include/KeyboardSpaceshipController.hpp"
#include "../include/CpuSpaceshipController.hpp"
#include "../include/Highscore.hpp"

#define ENEMIES_LINES_COUNT 3 ///< Number of enemies in each column
#define ENEMIES_COLS_COUNT 10 ///< Number of enemies in each line

/////////////////////////////////////////////////
///
/// \brief Starts and handles the game
///
/////////////////////////////////////////////////
class Game
{
    public:

        /////////////////////////////////////////////////
        ///
        /// \brief Constructor
        ///
        /////////////////////////////////////////////////
        Game();


        /////////////////////////////////////////////////
        ///
        /// \brief The main game loop
        ///
        /////////////////////////////////////////////////
        void gameLoop();


        /////////////////////////////////////////////////
        ///
        /// \brief Refreshes the game
        ///
        /////////////////////////////////////////////////
        void refresh();


        /////////////////////////////////////////////////
        ///
        /// \brief Reads the file containing the highscores
        ///
        /////////////////////////////////////////////////
        void readHighscoresFile();


        /////////////////////////////////////////////////
        ///
        /// \brief Loads the resources required by the game
        ///
        /////////////////////////////////////////////////
        void loadResources();


        /////////////////////////////////////////////////
        ///
        /// \brief Loads first level
        ///
        /////////////////////////////////////////////////
        void firstLevel();


        /////////////////////////////////////////////////
        ///
        /// \brief Loads next level
        ///
        /////////////////////////////////////////////////
        void nextLevel();


        /////////////////////////////////////////////////
        ///
        /// \brief Displays the game
        ///
        /////////////////////////////////////////////////
        void display();


        /////////////////////////////////////////////////
        ///
        /// \brief Displays "get ready" message
        ///
        /////////////////////////////////////////////////
        void getReady();


        /////////////////////////////////////////////////
        ///
        /// \brief Pauses the game
        ///
        /////////////////////////////////////////////////
        void pause();


        /////////////////////////////////////////////////
        ///
        /// \brief Destructor
        ///
        /////////////////////////////////////////////////
        ~Game();


    private:

        /////////////////////////////////////////////////
        ///
        /// \brief Makes the usual operation for changing the level
        ///
        /////////////////////////////////////////////////
        void changeLevel();

        /////////////////////////////////////////////////
        ///
        /// \brief Creates a new highscores file with default values
        ///
        /////////////////////////////////////////////////
        void createHighscoresFile();


        sf::RenderWindow m_window; ///< The window which will display the game

        unsigned int m_ticksCounter; ///< A counter to get the number of ticks/s

        unsigned int m_level; ///< The current level

        unsigned int m_score; ///< The current player's score

        bool m_gameLost; ///< Equals true if the player has lost

        Highscore m_highscores[3]; ///< The 3 highest recorded scores


        // resources

        sf::Font m_font; ///< The font which will be used to display text

        sf::Texture m_playerSpaceshipT; ///< Texture for player's spaceship

        sf::Texture m_enemy0SpaceshipT; ///< Texture for an enemy's spaceship;

        sf::Texture m_enemy1SpaceshipT; ///< Texture for an enemy's spaceship;

        sf::Texture m_enemy2SpaceshipT; ///< Texture for an enemy's spaceship;

        sf::Texture m_shotT; ///< Texture for a shot


        // objects

        std::list<Spaceship*> m_playerSpaceships; ///< List of the players' spaceships

        std::list<Spaceship*> m_enemiesSpaceships; ///< List of the enemies' spaceships

        std::list<Shot*> m_allShots; ///< List of all the shots

        Space m_space; ///< The moving space background

        Spaceship m_playerSpaceship; ///< The player's spaceship

        Spaceship m_enemies[ENEMIES_LINES_COUNT][ENEMIES_COLS_COUNT]; ///< The enemies' spaceships

        IntroScreens m_introScreens; ///< Introduction screens and animations

        sf::RectangleShape m_topBar; ///< The top bar for the texts


        // controllers

        KeyboardSpaceshipController m_keyboardController; ///< Keyboard controller for player

        CpuSpaceshipController m_cpuController; ///< CPU controller for enemies


        // texts

        sf::Text m_scoreText; ///< Text displaying "score"

        sf::Text m_scoreValueText; ///< Text displaying the player's current score

        sf::Text m_levelText; ///< Text displaying "level"

        sf::Text m_levelValueText; ///< Text displaying the current level

        sf::Text m_pauseText; ///< Text displaying "pause"

        sf::Text m_gameOverText; ///< Text displaying "game over"
};

#endif // GAME_HPP_INCLUDED
