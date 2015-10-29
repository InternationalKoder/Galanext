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

#include "../include/Highscore.hpp"

/////////////////////////////////////////////////

Highscore::Highscore(unsigned int score, const std::string& author) :
    m_score(score),
    m_author(author)
{}

/////////////////////////////////////////////////

unsigned int Highscore::getScore()
{
    return m_score;
}

/////////////////////////////////////////////////

std::string& Highscore::getAuthor()
{
    return m_author;
}

//////////////////////////////////////////////

void Highscore::setScore(unsigned int score)
{
    m_score = score;
}

///////////////////////////////////////////////

void Highscore::setAuthor(const std::string& author)
{
    m_author = author;
}
