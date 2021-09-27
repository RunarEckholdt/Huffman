#pragma once
#include "Node.h"
#include <string>

struct HuffCode{
	char ascii;
	std::string bits;
	unsigned freq = 1;
};


class HuffmanTree{
public:
	std::shared_ptr<Node> root;
	HuffmanTree(const std::vector<HuffCode>& hfCodes);
private:
	
};


inline bool operator<(const HuffCode& h1, const HuffCode& h2){
	return h1.freq < h2.freq;
}

inline bool operator<=(const HuffCode& h1, const HuffCode& h2){
	return h1.freq <= h2.freq;
}

inline bool operator>(const HuffCode& h1, const HuffCode& h2){
	return h1.freq > h2.freq;
}