#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "node.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Distributed System Visualization");

  // Create nodes
  Node node1(100, 100);
  Node node2(300, 200);
  Node node3(400, 100);
  node1.addConnection(&node2);
  node2.addConnection(&node3);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2f clickPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
          node1.onClick(clickPosition, [](Node* node) {
            node->circle.setFillColor(sf::Color::Green);
          });
          node2.onClick(clickPosition, [](Node* node) {
            node->circle.setFillColor(sf::Color::Green);
          });
          node3.onClick(clickPosition, [](Node* node) {
            node->circle.setFillColor(sf::Color::Green);
        });
        }
      }
    }

    window.clear();

    // Draw connections and nodes
    node1.drawConnections(window);
    node2.drawDirectedConnections(window);
    window.draw(node1.circle);
    window.draw(node2.circle);
    window.draw(node3.circle);

    window.display();
  }

  return 0;
}
