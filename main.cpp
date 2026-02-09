#include <SFML/Graphics.hpp>
#include <iostream>

const int BOARD_HEIGHT = 800;
const int BOARD_WIDTH = 800;
const int PIXEL_LENGTH = 40;
const float DELAY = 0.5;

float x = 0.0;
float y = 0.0;

sf::RenderWindow window(sf::VideoMode({BOARD_HEIGHT, BOARD_WIDTH}), "Snake");
sf::RectangleShape snakeHead({PIXEL_LENGTH, PIXEL_LENGTH});
sf::RectangleShape line({3, 3});

void drawGridLines() {
  line.setFillColor(sf::Color({255, 255, 255}));
  for (float i = PIXEL_LENGTH; i < BOARD_WIDTH; i += PIXEL_LENGTH) {
    line.setPosition({i, 0});
    line.setScale({1, BOARD_HEIGHT});
    window.draw(line);
  }
  for (float i = PIXEL_LENGTH; i < BOARD_HEIGHT; i += PIXEL_LENGTH) {
    line.setPosition({0, i});
    line.setScale({BOARD_WIDTH, 1});
    window.draw(line);
  }
}

int main() {
  sf::Clock clock;
  float timer = 0;
  float delay = 1;

  snakeHead.setFillColor(sf::Color({0, 255, 0}));
  while (window.isOpen()) {
    sf::Time elapsed = clock.restart();
    timer += elapsed.asSeconds();

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    if (timer > delay) {
      timer = 0.0;
      window.clear();
      snakeHead.setPosition({x, y});
      x += PIXEL_LENGTH;
      window.draw(snakeHead);
      drawGridLines();
      window.display();
    }
  }
  return 0;
}
