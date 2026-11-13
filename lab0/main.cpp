#include "engine.hpp"

int main() {
  KeyMap km;
  Simulation sim;
  Controler ctrl(km, sim);
  Renderer renderer(sim, current_window_size());
  Engine engine(sim, ctrl);
  engine.run();
  return 0;
}
