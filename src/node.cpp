#include "node.h"

Node::Node(float x, float y) {
  circle.setRadius(20);
  circle.setOrigin(circle.getRadius(), circle.getRadius());
  circle.setPosition(x, y);
  circle.setFillColor(sf::Color::Red);
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

void Node::onClick(const sf::Vector2f& clickPosition, std::function<void(Node*)>* action) {
    float distance = std::sqrt(std::pow(circle.getPosition().x - clickPosition.x, 2) +
                              std::pow(circle.getPosition().y - clickPosition.y, 2));
    if (distance < circle.getRadius()) {
      (*action)(this);
    }
}
