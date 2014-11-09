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

#ifndef SPACE_HPP_INCLUDED
#define SPACE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

/////////////////////////////////////////////////
/// \brief The moving space background
/////////////////////////////////////////////////
class Space : public sf::Drawable, public sf::Transformable
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /////////////////////////////////////////////////
        Space();

        /////////////////////////////////////////////////
        /// \brief Moves the background with stars appearing randomly
        ///
        /////////////////////////////////////////////////
        void refresh();

    private:

        /////////////////////////////////////////////////
        /// \brief Draws the shot (part of SFML lib)
        ///
        /// \param target The target to render
        /// \param states The target's states
        ///
        /////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();
            target.draw(m_vertex, states);
        }

        sf::VertexArray m_vertex; ///< The vertex which contains the stars
};

#endif // SPACE_HPP_INCLUDED
