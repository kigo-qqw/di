import config;

import di;


int main() {
  container_t container;

  [[maybe_unused]] auto foo = container.resolve<foo_i>();
  [[maybe_unused]] auto bar = container.resolve<bar_i>();

  return 0;
}