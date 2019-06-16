#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "huffmancode.h"
#include "sortedlist.h"
#include "strlist.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	char text[100] = { "Zara" };
	int i, len;
	sorted_list node_list;
	huffman_tree the_tree;
	List sentence;
	
	len = strlen(text);
	for(i = 0; i < len ; i++) {
		text[i] = tolower(text[i]);
	}
	
	CreateList(&sentence);
	InsVLast(&sentence, text);
	
	GenerateSortedList(sentence, &node_list, (double) len);
	
	printf("%c\n\n", node_list.front->next);
	the_tree = GenerateHuffmanTree(&node_list);
	
	PrintTree(the_tree);
	printf("yahooo!");
	return 0;
}
