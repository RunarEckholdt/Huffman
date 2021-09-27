#pragma once
#include <fstream>
#include <map>
#include "HuffmanTree.h"




class Huffman{
public:
	/// <summary>
	/// Function to huffman compress a file. 
	/// Remember to use write Huffmap afterwards to recieve a file that allows decompression later.
	/// </summary>
	/// <param name="fileName">File that you want to compress</param>
	/// <param name="compressedFileName">The file name for the resulting compressed file</param>
	void compress(const std::string& fileName,const std::string& compressedFileName);
	
	/// <summary>
	/// Writes the huffmap into a file that can be parsed later.
	/// </summary>
	/// <param name="newFileName">Target file to write the map to</param>
	void writeHuffmap(const std::string& newFileName);
	
	/// <summary>
	/// Parse a huffmap file. Must be done before attempting to decompress the file.
	/// </summary>
	/// <param name="huffmapFile">File to parse</param>
	void readHuffMap(const std::string& huffmapFile);

	/// <summary>
	/// Decompress a compressed file. The huffmap need to be parsed before calling this function.
	/// </summary>
	/// <param name="compressedFileName">Path to compressed file</param>
	/// <param name="decompressedFileName">Path to file where decompressed text will be written to</param>
	void decompress(const std::string& compressedFileName, const std::string& decompressedFileName);
private:
	std::map<char, std::string> huffmanMapCompress;
	std::map<std::string, char> huffmanMapDecompress;
	void determineFrequency(const std::string& text,std::vector<HuffCode>& huffmanCodes);
	void extractBinariesFromTree(const HuffmanTree& ht, std::vector<HuffCode>& huffmanCodes);
	bool charInVector(const char& ch,const std::vector<char>& vec);
	void createHuffMapCompress(std::vector<HuffCode>& huffmanCodes);
	std::string huffmanEncodeText(const std::string& text);
	std::string huffmanToBinary(const std::string& huffmanCode);
	std::string binaryReader(const std::string& fileName);
	

};

