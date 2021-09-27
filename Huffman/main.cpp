#include "Huffman.h"

int main(){
	Huffman huffman;
	huffman.compress("file.txt", "compressed.txt");
	huffman.writeHuffmap("huffmap.txt");
	huffman.readHuffMap("huffmap.txt");
	huffman.decompress("compressed.txt","decompressed.txt");
	return 0;
}