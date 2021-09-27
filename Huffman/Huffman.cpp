#include "Huffman.h"


void Huffman::compress(const std::string& fileName, const std::string& compressedFileName){
	std::ifstream ifs;
	std::vector<HuffCode> huffmanCodes;
	ifs.open(fileName, std::ifstream::in);
	
	std::string text; 
	std::getline(ifs, text,'\0');
	ifs.close();
	this->determineFrequency(text, huffmanCodes);

	HuffmanTree ht(huffmanCodes);
	
	this->extractBinariesFromTree(ht,huffmanCodes);
	this->createHuffMapCompress(huffmanCodes);
	std::string huffmanCode = this->huffmanEncodeText(text);
	std::string binary = this->huffmanToBinary(huffmanCode);
	std::ofstream ofs;
	ofs.open(compressedFileName, std::ios::out | std::ios::binary);
	ofs << binary;

}

void Huffman::writeHuffmap(const std::string& newFileName){
	if(huffmanMapCompress.size() == 0){
		printf("HuffmapCompress was empty. Compress a file first.\n");
		return;
	}

	std::ofstream ofs;
	ofs.open(newFileName, std::ofstream::out);

	for(std::pair<char, std::string> p : huffmanMapCompress){
		ofs << "{" << p.first << "," << p.second << "}\n";
	}
	ofs.close();

}

void Huffman::readHuffMap(const std::string& huffmapFile){
	std::ifstream ifs;
	ifs.open(huffmapFile, std::ifstream::in);
	char* ch = new char[1];
	char ascii;
	std::string huffcode;
	while(!ifs.eof()){
		ifs.read(ch, 1);
		if(*ch == '{'){
			huffcode = "";
			ifs.read(ch, 1);
			ascii = *ch;
			
			ifs.read(ch, 1);
			if(*ch != ','){
				printf("An error occured while parsing huffmap\n");
			}
			else{
				ifs.read(ch, 1);
				while(*ch != '}'){
					huffcode += *ch;
					ifs.read(ch, 1);
				}
				huffmanMapDecompress[huffcode] = ascii;
			}

		}
	}
	ifs.close();
	delete[] ch;
	
}

void Huffman::decompress(const std::string& compressedFileName, const std::string& decompressedFileName){
	if(huffmanMapDecompress.size() == 0){
		printf("A huffmap is needed to decompress file. Please use readHuffMap to read the huffmap\n");
		return;
	}
	std::string decompressed;
	std::string tmp;
	std::ofstream ofs;
	std::string binary = binaryReader(compressedFileName);

	for(char ch : binary){
		tmp += ch;
		if(huffmanMapDecompress.find(tmp) != huffmanMapDecompress.end()){
			decompressed += huffmanMapDecompress[tmp];
			tmp = "";
		}
	}

	ofs.open(decompressedFileName, std::ofstream::out);
	ofs << decompressed;
	ofs.close();
	
}

void Huffman::determineFrequency(const std::string& text, std::vector<HuffCode>& huffmanCodes){
	std::map<char, HuffCode> huffMap;
	
	for(char ch : text){
		if(huffMap.find(ch) == huffMap.end()){
			HuffCode h;
			h.ascii = ch;
			huffMap[ch] = h;
		} else{
			huffMap[ch].freq++;
		}
	}
	for(std::pair<const char, HuffCode>& p : huffMap){
		huffmanCodes.push_back(p.second);
	}
}

void Huffman::extractBinariesFromTree(const HuffmanTree& ht, std::vector<HuffCode>& huffmanCodes){
	for(HuffCode& hc : huffmanCodes){
		std::shared_ptr<Node> current = ht.root;
		std::string bits;
		while(current->characters.size() != 1){
			if(charInVector(hc.ascii, current->left->characters)){
				bits += '0';
				current = current->left;
			}
			else{
				bits += '1';
				current = current->right;
			}
		}
		hc.bits = bits;
	}
}

bool Huffman::charInVector(const char& ch, const std::vector<char>& vec){
	for(char c : vec){
		if(ch == c){
			return true;
		}
	}
	return false;
}

void Huffman::createHuffMapCompress(std::vector<HuffCode>& huffmanCodes){
	for(HuffCode& hc : huffmanCodes){
		huffmanMapCompress[hc.ascii] = hc.bits;
	}
}

std::string Huffman::huffmanEncodeText(const std::string& text){
	std::string huffmanCode = "";
	for(char ch : text){
		huffmanCode += huffmanMapCompress[ch];
	}
	return huffmanCode;
}

std::string Huffman::huffmanToBinary(const std::string& huffmanCode){
	std::string binary = "";
	int offset;
	for(offset = 0; offset + 7 < huffmanCode.size(); offset += 8){
		uint8_t bin = 0;
		uint8_t mask = 1 << 7;
		for(int i = 0; i < 8; i++){
			if(huffmanCode[i+offset] == '1'){
				bin = bin | mask;
			}
			mask = mask >> 1;
		}
		binary += (char)bin;
	}
	size_t remainingBits = huffmanCode.size() - offset;
	uint8_t bin = 0;
	uint8_t mask = 1 << remainingBits-1;
	for(int i = 0; i < remainingBits; i++){
		if(huffmanCode[i + offset] == '1'){
			bin = bin | mask;
		}
		mask = mask >> 1;
	}
	binary += (char) bin;
	return binary;

}

std::string Huffman::binaryReader(const std::string& fileName){
	std::string binaryAscii;
	std::ifstream ifs;
	char binBuffer[1];
	memset(binBuffer, 0, 1 * sizeof(char));
	ifs.open(fileName, std::ios::out | std::ios::binary);
	if(!ifs){
		printf("Could not open file: %s \n",fileName);
	}
	while(!ifs.eof()){
		ifs.read(binBuffer, 1);
		uint8_t mask = 1 << 7;
		for(int i = 0; i < 8; i++){
			char tmp = binBuffer[0] & mask;
			if((binBuffer[0] & mask) == 0){
				binaryAscii += '0';
			} else{
				binaryAscii += '1';
			}
			mask = mask >> 1;
		}
	}



	ifs.close();

	return binaryAscii;
}


