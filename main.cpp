#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

const int BOARD_HEIGHT = 800;
const int BOARD_WIDTH = 800;
const int PIXEL_LENGTH = 100;

const sf::Color backgroundColor = {26, 26, 26};
const sf::Color snakeColor = {68, 194, 68};
const sf::Color appleColor = {200, 21, 21};
const sf::Color lineColor = {217, 217, 217};

const float DELAY = 0.2;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distr(0, (BOARD_HEIGHT / PIXEL_LENGTH) - 1);

float appleX = distr(gen) * PIXEL_LENGTH;
float appleY = distr(gen) * PIXEL_LENGTH;

char direction = 'R';

std::vector<char> directions = {'R', 'R', 'R', 'R', 'R'};
std::vector<std::vector<float>> positions = {{4 * PIXEL_LENGTH, 0},
                                             {3 * PIXEL_LENGTH, 0},
                                             {2 * PIXEL_LENGTH, 0},
                                             {1 * PIXEL_LENGTH, 0},
                                             {0 * PIXEL_LENGTH, 0}};

sf::RenderWindow window(sf::VideoMode({BOARD_HEIGHT, BOARD_WIDTH}), "Snake");

sf::RectangleShape snake({PIXEL_LENGTH, PIXEL_LENGTH});
sf::RectangleShape apple({PIXEL_LENGTH, PIXEL_LENGTH});
sf::RectangleShape line({1, 1});

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

bool checkCollision() {
  std::unordered_map<std::string, int> positionMap;
  for (int i = 0; i < positions.size(); i++) {
    std::string positionHash = "";
    positionHash += positions[i][0];
    positionHash += positions[i][1];
    if (positionMap[positionHash]) {
      return 1;
    }
    positionMap[positionHash] = 1;
  }
  return 0;
}

bool checkBoundary() {
  if (positions.front()[0] < 0 || positions.front()[1] < 0 ||
      positions.front()[0] >= BOARD_WIDTH ||
      positions.front()[1] >= BOARD_HEIGHT) {
    return 1;
  }
  return 0;
}

void updateApple() {
  if (appleX == positions.front()[0] && appleY == positions.front()[1]) {

    bool inBody = 1;
    while (inBody) {
      inBody = 0;
      appleX = distr(gen) * PIXEL_LENGTH;
      appleY = distr(gen) * PIXEL_LENGTH;
      for (int i = 0; i < positions.size(); i++) {
        if (positions[i][0] == appleX && positions[i][1] == appleY) {
          inBody = 1;
        }
      }
    }

    positions.push_back(positions[positions.size() - 1]);
    directions.push_back(directions[positions.size() - 1]);
  }

  apple.setPosition({appleX, appleY});
  window.draw(apple);
}

void updateSnake() {
  updateApple();

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
}

int main() {
  bool keyPress = 0;
  sf::Clock clock;

  float timer = 0;
  snake.setFillColor(sf::Color(snakeColor));
  apple.setFillColor(sf::Color(appleColor));
  line.setFillColor(sf::Color(lineColor));
  while (window.isOpen()) {
    sf::Time elapsed = clock.restart();
    timer += elapsed.asSeconds();

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Right && direction != 'L' &&
            !keyPress) {
          direction = 'R';
          keyPress = 1;
        } else if (keyPressed->code == sf::Keyboard::Key::Left &&
                   direction != 'R' && !keyPress) {
          direction = 'L';
          keyPress = 1;
        } else if (keyPressed->code == sf::Keyboard::Key::Up &&
                   direction != 'D' && !keyPress) {
          direction = 'U';
          keyPress = 1;
        } else if (keyPressed->code == sf::Keyboard::Key::Down &&
                   direction != 'U' && !keyPress) {
          direction = 'D';
          keyPress = 1;
        }
      }
    }

    if (timer > DELAY) {
      keyPress = 0;
      timer = 0.0;
      window.clear(backgroundColor);
      updateSnake();

      if (checkBoundary() || checkCollision()) {
        window.close();
      }

      updateApple();
      drawGridLines();
      window.display();
    }
  }
  return 0;
}
