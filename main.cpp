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

std::vector<char> directions = {'R', 'R', 'R', 'R', 'R'};
std::vector<std::vector<float>> positions = {{4 * PIXEL_LENGTH, 0},
                                             {3 * PIXEL_LENGTH, 0},
                                             {2 * PIXEL_LENGTH, 0},
                                             {1 * PIXEL_LENGTH, 0},
                                             {0 * PIXEL_LENGTH, 0}};

sf::RenderWindow window(sf::VideoMode({BOARD_HEIGHT, BOARD_WIDTH}), "Snake");

sf::RectangleShape snake({PIXEL_LENGTH, PIXEL_LENGTH});
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

bool updateSnake() {
  directions[0] = direction;
  for (float i = 0; i < positions.size(); i++) {
    if (directions[i] == 'R') {
      positions[i][0] += PIXEL_LENGTH;
    } else if (directions[i] == 'L') {
      positions[i][0] -= PIXEL_LENGTH;
    } else if (directions[i] == 'U') {
      positions[i][1] -= PIXEL_LENGTH;
    } else if (directions[i] == 'D') {
      positions[i][1] += PIXEL_LENGTH;
    }
    snake.setPosition({positions[i][0], positions[i][1]});
    window.draw(snake);
  }
  for (float i = positions.size() - 1; i > 0; i--) {
    directions[i] = directions[i - 1];
  }
  if (positions.back()[0] <= 0 || positions.back()[1] < 0 ||
      positions.back()[0] >= BOARD_WIDTH ||
      positions.back()[1] >= BOARD_HEIGHT) {
    return 1;
  }
  return 0;
}

int main() {
  sf::Clock clock;
  float timer = 0;

  snake.setFillColor(sf::Color(snakeColor));
  line.setFillColor(sf::Color(lineColor));
  while (window.isOpen()) {
    sf::Time elapsed = clock.restart();
    timer += elapsed.asSeconds();

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
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
      if (updateSnake()) {
        window.close();
      }
      drawGridLines();
      window.display();
    }
  }
  return 0;
}
