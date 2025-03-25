#include "../WASAPI/Listener.h"
#include "Lattice.h"
#include "Rectangle.h"

using namespace std;

void smooth(float *x) {
  if (*x == 0)
    *x = 1;
  *x = atan(*x + .2);
}

int main() {
  const UINT screens = 3;
  const UINT frequencies = 96 * screens;
  Listener listener(frequencies);
  float volume;
  vector<float> volumes;

  sf::ContextSettings settings;
  settings.antialiasingLevel = 4;
  sf::RenderWindow window(sf::VideoMode(1920 * screens, 1080), "Leech Lattice",
                          sf::Style::None, settings);
  window.setVerticalSyncEnabled(true);
  sf::Event event;
  sf::Clock time;

  sf::Vector2f winSize = sf::Vector2f(window.getSize().x, window.getSize().y);
  sf::Vector2f middle(winSize.x / screens / 2, winSize.y / 2);

  vector<Lattice *> lattice;
  vector<au::Rectangle *> rects;

  for (int i = 0; i < screens; i++) {
    lattice.push_back(new Lattice(middle.x + (i * winSize.x / screens),
                                  middle.y, winSize.x, winSize.y));
  }

  for (int i = 0; i < frequencies; i++) {
    rects.push_back(new au::Rectangle((winSize.x / float(frequencies)) * i,
                                      winSize.y, winSize.x / float(frequencies),
                                      winSize.y, i, frequencies));
  }

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == event.Closed) {
        window.close();
      }
      if (event.type == event.KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
          window.close();
        }
      }
    }

    volumes = listener.getFrequencyData();

    listener.getAudioLevel(&volume);
    smooth(&volume);

    for (auto lat : lattice) {
      lat->update(time.getElapsedTime().asSeconds() / 30, volume);
    }

    for (auto rec : rects) {
      rec->update(volumes, lattice[0]->getColor());
    }

    window.clear();

    for (auto lat : lattice) {
      lat->draw(window);
    }
    for (auto rec : rects) {
      rec->draw(window);
    }

    window.display();
  }

  for (int i = 0; i < rects.size(); i++) {
    delete rects[i];
  }
  rects.clear();

  for (int i = 0; i < lattice.size(); i++) {
    delete lattice[i];
  }
  lattice.clear();

  return 0;
}