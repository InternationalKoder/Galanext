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

#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Space.hpp"
#include "EnemiesGroup.hpp"

/////////////////////////////////////////////////
/// \brief The class handling the game
/////////////////////////////////////////////////
class Game
{
    public:

        /////////////////////////////////////////////////
		/// \brief Constructor which loads the resources and creates the entities
        ///
        /////////////////////////////////////////////////
        Game();

        /////////////////////////////////////////////////
		/// \brief Game loop
        ///
        /////////////////////////////////////////////////
        void start();

        static const unsigned int WINDOW_WIDTH;
        static const unsigned int WINDOW_HEIGHT;
        static const std::string WINDOW_TITLE;

        static const std::string RESOURCES_LOCATION;
        static const std::string FONT_LOCATION;
        static const unsigned int TILES_WIDTH;
        static const unsigned int TILES_HEIGHT;

        static const float PLAYER_SPACESHIP_SPEED;
        static const unsigned short NUMBER_SPACESHIP_TILES;
        static const float SHOT_SPEED;

        static const float ENEMY_SPACESHIP_SPEED;
        static const unsigned short NUMBER_ENEMIES_PER_ROW;
        static const unsigned short NUMBER_ROWS;
        static const float PIXELS_BETWEEN_ENEMIES;
        static const float PIXELS_BETWEEN_ROWS;

        /////////////////////////////////////////////////
		/// \brief Destructor
        ///
        /////////////////////////////////////////////////
        ~Game();

    private:

        void refresh(); ///< Refreshes all the entities

        void draw(); ///< Draws all the entities

        sf::RenderWindow m_window; ///< The window displaying the game

        sf::Texture m_playerTexture; ///< The texture for the player's spaceship

        std::vector<sf::Texture> m_enemiesTextures; ///< The textures for the enemies' spaceships

        Space m_space; ///< The space background

        Spaceship *m_player; ///< The player's spaceship

        EnemiesGroup *m_enemies; ///< The group of enemies

        sf::Texture m_shotTexture; ///< The texture for the shots
};

#endif // GAME_HPP_INCLUDED
