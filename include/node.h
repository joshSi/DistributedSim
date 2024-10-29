#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

class Node {
public:
  sf::CircleShape circle;

  std::string id;
  std::vector<std::string> messages;
  std::vector<Node*> connections;
  Node() {}
  Node(float x, float y);

  void addConnection(Node* other);
  void sendMessage(const std::string& message, Node* other);
  void receiveMessage(const std::string& message);

  void onClick(const sf::Vector2f& clickPosition, std::function<void(Node*)> action);

  void drawConnections(sf::RenderWindow& window);
  void drawDirectedConnections(sf::RenderWindow& window);
};

#endif
