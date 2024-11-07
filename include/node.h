#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

enum class State {
  IDLE,
  ACTIVE,
  WAITING,
  TERMINATED
};

class Node {
public:
  sf::CircleShape circle;

  std::string id;
  Node() {}
  Node(float x, float y);
  bool operator<(const Node& other) const;

  void setOnClickAction(std::function<void(Node*)> action);

  void addConnection(Node* other);
  void sendMessage(const std::string& message, Node* other);
  void receiveMessage(const std::string& message);

  bool onClick(const sf::Vector2f& clickPosition);

  void drawConnections(sf::RenderWindow& window);
  void drawDirectedConnections(sf::RenderWindow& window);
  void drawMessages(sf::RenderWindow& window);

private:
  std::vector<std::string> messages;
  std::vector<Node*> connections;
  std::function<void(Node*)> onClickAction;
};

#endif
