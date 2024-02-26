#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <SFML/Graphics.hpp>
#include "./User.hpp"
#include "./Score.hpp"

void tetris(sf::RenderWindow& window, sf::Font font, User& user, Score& score, bool& gameOver, bool& menu, int& network);

#endif