#include "node.h"

Node::Node(float x, float y) {
  circle.setRadius(20);
  circle.setOrigin(circle.getRadius(), circle.getRadius());
  circle.setPosition(x, y);
  circle.setFillColor(sf::Color::Red);
}

bool Node::operator<(const Node& other) const {
  return id < other.id;
}

void Node::setOnClickAction(std::function<void(Node*)> action) {
  onClickAction = action;
}

void Node::addConnection(Node* other) {
  connections.push_back(other);
}

void Node::sendMessage(const std::string& message, Node* other) {
  messages.push_back(message);
  other->receiveMessage(message);
}

void Node::receiveMessage(const std::string& message) {
  messages.push_back(message);
}

bool Node::onClick(const sf::Vector2f& clickPosition) {
    float distance = std::sqrt(std::pow(circle.getPosition().x - clickPosition.x, 2) +
                              std::pow(circle.getPosition().y - clickPosition.y, 2));
    if (distance < circle.getRadius()) {
      onClickAction(this);
      return true;
    }
    return false;
}

void Node::drawConnections(sf::RenderWindow& window) {
    for (const Node* connectedNode : connections) {
        // Get the radius of the circles
        float nodeRadius = circle.getRadius();
        float connectedNodeRadius = connectedNode->circle.getRadius();

        // Start position is at the edge of the current node's circle
        sf::Vector2f start = circle.getPosition();
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

void Node::drawDirectedConnections(sf::RenderWindow& window) {
    for (const Node* connectedNode : connections) {
        // Get the radius of the circles
        float nodeRadius = circle.getRadius();
        float connectedNodeRadius = connectedNode->circle.getRadius();

        // Start position is at the edge of the current node's circle
        sf::Vector2f start = circle.getPosition();
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

void Node::drawMessages(sf::RenderWindow& window) {
    for (size_t i = 0; i < messages.size(); ++i) {
        static sf::Font font;
        static bool isFontLoaded = false;
        if (!isFontLoaded) {
            if (!font.loadFromFile("path/to/font.ttf")) {
          // Handle error, use default font
          if (!font.loadFromFile("/System/Library/Fonts/SFNS.ttf")) {
              // Handle error if default font is not found
          }
            }
            isFontLoaded = true;
        }
        sf::Text text(messages[i], font, 12);
        text.setPosition(circle.getPosition().x + circle.getRadius() + 5, circle.getPosition().y + i * 15);
        window.draw(text);
    }
}