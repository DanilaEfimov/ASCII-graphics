#pragma once

#include <cstdint>

enum class Direction : uint8_t {
  RightToLeft,
  LeftToRight,
};

class SimulationContext {
public:
  using speed_t = std::uint8_t;

private:
  std::size_t pos = 0;
  Direction direction;
  char character;
  std::uint8_t speed = 1; // steps per second
  bool running = true;

public:
  SimulationContext(Direction direction = Direction::LeftToRight, char ch = '@')
      : direction(direction), character(ch) {}

  std::size_t getPosition() const noexcept { return this->pos; }

  void setPosition(std::size_t newPos) { this->pos = newPos; }

  Direction getDirection() const noexcept { return this->direction; }

  void setDirection(Direction newDirection) { this->direction = newDirection; }

  char getCharacter() const noexcept { return this->character; }

  void setCharacter(char newCharacter) { this->character = newCharacter; }

  speed_t getSpeed() const noexcept { return this->speed; }

  void setSpeed(speed_t newSpeed) { this->speed = newSpeed; }

  bool isRunning() const noexcept { return this->running; }

  void pause() { this->running = false; }

  void resume() { this->running = true; }
};
