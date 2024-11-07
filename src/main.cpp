#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "node.h"
#include "world.h"

int main() {
  World world;
  sf::RenderWindow window(sf::VideoMode(800, 600), "Distributed System Visualization");

  // Create nodes & connections
  world.nodes.push_back(Node(100, 100));
  world.nodes.push_back(Node(300, 200));
  world.nodes.push_back(Node(400, 100));
  world.nodes[0].id = "Node 1";
  world.nodes[1].id = "Node 2";
  world.nodes[2].id = "Node 3";

  world.nodes[0].addConnection(&world.nodes[1]);
  world.nodes[1].addConnection(&world.nodes[2]);

  Node* drag_node;

  for (Node& node : world.nodes) {
    node.setOnClickAction([&world](Node* node) {
      world.stepForward();
      node->sendMessage("Hello", &world.nodes[1]);
    });
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      sf::Vector2f mousePosition;
      switch(event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f clickPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            for (std::vector<Node>::reverse_iterator it = world.nodes.rbegin(); it != world.nodes.rend(); it++) {
              if (it->onClick(clickPosition)) {
                drag_node = &(*it);
                break;
              }
            }
          }
          break;
        case sf::Event::MouseButtonReleased:
          if (event.mouseButton.button == sf::Mouse::Left) {
            drag_node = nullptr;
          }
          break;
        case sf::Event::MouseMoved:
          mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
          if (drag_node) {
            drag_node->circle.setPosition(mousePosition);
          }
          break;
        default:
          break;
      }
    }

    window.clear();

    // Draw connections and nodes
    for (Node& node : world.nodes) {
      node.drawConnections(window);
      node.drawDirectedConnections(window);
      window.draw(node.circle);
      node.drawMessages(window);
    }

    window.display();
  }

  return 0;
}
