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

#include "../include/Space.hpp"
#include "../include/Config.hpp"
#include <cstdlib>
#include <ctime>

/////////////////////////////////////////////////

Space::Space()
{
    srand(time(NULL));
    m_vertex.setPrimitiveType(sf::Points);

    for(unsigned int i = 0 ; i < Config::WINDOW_HEIGHT ; i++)
    {
        int nbPoints = rand() % 2;
        if(nbPoints == 1)
        {
            sf::Vertex v(sf::Vector2f(rand() % (Config::WINDOW_WIDTH+1), i), sf::Color::White);
            m_vertex.append(v);
        }
    }
}

/////////////////////////////////////////////////

void Space::refresh()
{
    sf::VertexArray buffer;

    // Moving the lines
    for(unsigned int i = 0 ; i < m_vertex.getVertexCount() ; i++)
    {
        sf::Vector2f newPos(m_vertex[i].position.x, m_vertex[i].position.y + 1);

        if(newPos.y <= Config::WINDOW_HEIGHT && newPos.y >= 0)
            buffer.append(sf::Vertex(newPos, sf::Color::White));
    }

    // Adding the new line
    if(rand() % 2 == 1)
    {
        sf::Vertex v(sf::Vector2f(rand() % (Config::WINDOW_WIDTH+1), 0), sf::Color::White);
        buffer.append(v);
    }

    // Copying the buffer
    m_vertex.clear();

    for(unsigned int i = 0 ; i < buffer.getVertexCount() ; i++)
    {
        m_vertex.append(buffer[i]);
    }
}

/////////////////////////////////////////////////

void Space::display(sf::RenderWindow& window)
{
    window.draw(m_vertex);
}
