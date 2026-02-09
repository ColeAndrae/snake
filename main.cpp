#include <SFML/Graphics.hpp>
#include <iostream>

const int BOARD_HEIGHT = 800;
const int BOARD_WIDTH = 800;
const int PIXEL_LENGTH = 40;

const sf::Color backgroundColor = {26, 26, 26};
const sf::Color snakeColor = {68, 194, 68};
const sf::Color lineColor = {217, 217, 217};

const float DELAY = 0.2;

char direction = 'R';

bool gameOver = 0;

float x = 0.0;
float y = 0.0;

sf::RenderWindow window(sf::VideoMode({BOARD_HEIGHT, BOARD_WIDTH}), "Snake");

sf::RectangleShape snakeHead({PIXEL_LENGTH, PIXEL_LENGTH});
sf::RectangleShape line({3, 3});

void drawGridLines() {
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

void updateSnake() {
  if (direction == 'L') {
    x -= PIXEL_LENGTH;
  } else if (direction == 'R') {
    x += PIXEL_LENGTH;
  } else if (direction == 'U') {
    y -= PIXEL_LENGTH;
  } else if (direction == 'D') {
    y += PIXEL_LENGTH;
  }
  if (x < 0 || y < 0 || x >= BOARD_WIDTH || y >= BOARD_HEIGHT) {
    gameOver = 1;
  }
  snakeHead.setPosition({x, y});
  window.draw(snakeHead);
}

int main() {
  sf::Clock clock;
  float timer = 0;

  snakeHead.setFillColor(sf::Color(snakeColor));
  line.setFillColor(sf::Color(lineColor));
  while (window.isOpen()) {
    sf::Time elapsed = clock.restart();
    timer += elapsed.asSeconds();

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>() || gameOver) {
        window.close();
      }
      if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Right) {
          direction = 'R';
        } else if (keyPressed->code == sf::Keyboard::Key::Left) {
          direction = 'L';
        } else if (keyPressed->code == sf::Keyboard::Key::Up) {
          direction = 'U';
        } else if (keyPressed->code == sf::Keyboard::Key::Down) {
          direction = 'D';
        }
      }
    }

    if (timer > DELAY) {
      timer = 0.0;
      window.clear(backgroundColor);
      updateSnake();
      drawGridLines();
      window.display();
    }
  }
  return 0;
}
