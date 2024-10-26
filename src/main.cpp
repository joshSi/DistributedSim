#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "node.h"

void drawConnections(sf::RenderWindow& window, const Node& node) {
    for (const Node* connectedNode : node.connections) {
        // Get the radius of the circles
        float nodeRadius = node.circle.getRadius();
        float connectedNodeRadius = connectedNode->circle.getRadius();

        // Start position is at the edge of the current node's circle
        sf::Vector2f start = node.circle.getPosition();
        // End position is at the edge of the connected node's circle
        sf::Vector2f end = connectedNode->circle.getPosition();

        // Calculate direction vector
        sf::Vector2f direction = end - start;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length == 0) continue; // Prevent division by zero
        sf::Vector2f unitDirection = direction / length;

        // Adjust start and end positions to the edges of the circles
        sf::Vector2f adjustedStart = start + unitDirection * nodeRadius;
        sf::Vector2f adjustedEnd = end - unitDirection * connectedNodeRadius;

        // Draw line
        sf::Vertex line[] = {
            sf::Vertex(adjustedStart),
            sf::Vertex(adjustedEnd)
        };
        window.draw(line, 2, sf::Lines);
    }
}

void drawDirectedConnections(sf::RenderWindow& window, const Node& node) {
    for (const Node* connectedNode : node.connections) {
        // Get the radius of the circles
        float nodeRadius = node.circle.getRadius();
        float connectedNodeRadius = connectedNode->circle.getRadius();

        // Start position is at the edge of the current node's circle
        sf::Vector2f start = node.circle.getPosition();
        // End position is at the edge of the connected node's circle
        sf::Vector2f end = connectedNode->circle.getPosition();

        // Calculate direction vector
        sf::Vector2f direction = end - start;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length == 0) continue; // Prevent division by zero
        sf::Vector2f unitDirection = direction / length;

        // Adjust the end position to the edge of the connected node's circle
        sf::Vector2f adjustedEnd = end - unitDirection * connectedNodeRadius;

        // Draw line
        sf::Vertex line[] = {
            sf::Vertex(start + unitDirection * nodeRadius),
            sf::Vertex(adjustedEnd)
        };
        window.draw(line, 2, sf::Lines);

        // Arrowhead size
        float arrowSize = 10.f;

        // Calculate points for arrowhead
        sf::Vector2f arrowPoint1 = adjustedEnd - unitDirection * arrowSize + sf::Vector2f(-unitDirection.y, unitDirection.x) * (arrowSize / 2);
        sf::Vector2f arrowPoint2 = adjustedEnd - unitDirection * arrowSize - sf::Vector2f(-unitDirection.y, unitDirection.x) * (arrowSize / 2);

        // Draw arrowhead
        sf::Vertex arrowhead[] = {
            sf::Vertex(adjustedEnd),
            sf::Vertex(arrowPoint1),
            sf::Vertex(adjustedEnd),
            sf::Vertex(arrowPoint2)
        };
        window.draw(arrowhead, 4, sf::Lines);
    }
}

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
    }

    window.clear();

    // Draw connections and nodes
    drawConnections(window, node1);
    drawDirectedConnections(window, node2);
    window.draw(node1.circle);
    window.draw(node2.circle);
    window.draw(node3.circle);

    window.display();
  }

  return 0;
}
