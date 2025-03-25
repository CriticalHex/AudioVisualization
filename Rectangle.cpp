#include "Rectangle.h"
#include <cmath>

au::Rectangle::Rectangle(int x, int y, int width, int height, int band,
                         int maxBand) {
  _rect.setPosition(sf::Vector2f(x, y));
  sf::Color color = au::colors[599 - int((float(band) / maxBand) * 599)];
  color.a = 150;
  _rect.setFillColor(color);
  _rect.setSize(sf::Vector2f(width, height));
  _band = band;
  _maxBand = maxBand;
  _maxHeight = height;
}

au::Rectangle::~Rectangle() {}

sf::RectangleShape au::Rectangle::getRect() { return _rect; }

void au::Rectangle::update(std::vector<float> volume) {
  if (volume[_band] == 0) {
    // if volume is 0 then slowly descend, makes for a nice effect.
    _rect.setSize(sf::Vector2f(_rect.getSize().x, _rect.getSize().y * .98f));
  } else {
    // rate is used to slow the transition between the last value
    // and a new one. A value of 1 means that the transition
    // is instant, making for a reactive visualization, but sensitive
    float rate = .5f;
    float newHeight =
        rate * (volume[_band] * _maxHeight) + (1.f - rate) * _rect.getSize().y;
    _rect.setSize(sf::Vector2f(_rect.getSize().x, newHeight));
  }
  // since rects are drawn from the top left, and we just changed the top
  // otherwise it would be an upsidedown visualization
  _rect.setOrigin(sf::Vector2f(0, _rect.getSize().y));
}

void au::Rectangle::update(std::vector<float> volume, sf::Color color) {
  _rect.setFillColor(color);
  update(volume);
}

void au::Rectangle::draw(sf::RenderWindow &window) { window.draw(_rect); }