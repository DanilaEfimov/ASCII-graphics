#include "engine.hpp"

int main() {
  KeyMap km;
  Simulation sim;
  Controler ctrl(km, sim);
  Engine engine(sim, ctrl);
  engine.run();
  return 0;
}
