#pragma once
#include <memory>
#include <vector>



class Node{
public:
	std::vector<char> characters;
	size_t totalFrequency;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
};

bool operator<(Node& n1, Node& n2);