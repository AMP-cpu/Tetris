#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include "../headers/Globals.hpp"
#include "../headers/User.hpp"
#include "../headers/Score.hpp"
#include <SFML/Graphics.hpp>

void GameOver(sf::RenderWindow& window, sf::Font font, User& user, Score& score, bool& gameOver, bool& menu);

#endif