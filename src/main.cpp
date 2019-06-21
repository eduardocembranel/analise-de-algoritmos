#include "app.hpp"

#include <cstdlib>
#include "matriz.hpp"
#include <iostream>
int main() {
  App *app = new App();

  app->loop();

  delete app;
  return 0;
}
