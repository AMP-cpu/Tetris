#ifndef MENU_HPP
#define MENU_HPP

#include "../headers/Globals.hpp"
#include "../headers/User.hpp"
#include "../headers/Score.hpp"
#include <SFML/Graphics.hpp>

void Menu(sf::RenderWindow& window, sf::Font font, bool& gameOver, bool& menu, int& network);

#endif