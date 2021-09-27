#include "HuffmanTree.h"




HuffmanTree::HuffmanTree(const std::vector<HuffCode>& hfCodes){
	std::vector<std::shared_ptr<Node>> topNodes;
	for(const HuffCode& hf : hfCodes){
		auto n { std::make_shared<Node>() };
		n->characters.push_back(hf.ascii);
		n->totalFrequency = hf.freq;
		if(topNodes.size() > 0){
			//Insert new node in a sorted possition
			for(int i = 0; i < topNodes.size(); i++){
				if(n->totalFrequency < topNodes[i]->totalFrequency){
					topNodes.insert(topNodes.begin() + i, n);
					break;
				}
				else if(i == topNodes.size()-1){
					topNodes.push_back(n);
					break;
				}
			}
		} else{
			topNodes.push_back(n);
		}
	}
	
	while(topNodes.size() > 1){
		std::shared_ptr<Node> smallest = topNodes[0];
		std::shared_ptr<Node> secondSmallest = topNodes[1];
		auto n { std::make_shared<Node>() };
		n->totalFrequency = smallest->totalFrequency + secondSmallest->totalFrequency;
		for(char ch : smallest->characters){
			n->characters.push_back(ch);
		}
		for(char ch : secondSmallest->characters){
			n->characters.push_back(ch);
		}
		n->left = smallest;
		n->right = secondSmallest;
		topNodes.erase(topNodes.begin(), topNodes.begin()+2);
		if(topNodes.size() < 4){
			int slett = 0;
		}
		if(topNodes.size() == 0){
			root = n;
		}
		else{
			for(int i = 0; i < topNodes.size(); i++){
				if(n->totalFrequency < topNodes[i]->totalFrequency){
					topNodes.insert(topNodes.begin() + i, n);
					break;
				} else if(i == topNodes.size() - 1){
					topNodes.push_back(n);
					break;
				}

			}
		}
		
		
		
	}
	

}
