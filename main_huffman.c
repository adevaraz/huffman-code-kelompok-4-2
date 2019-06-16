#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "huffmancode.h"
#include "sortedlist.h"
#include "strlist.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	char text[100] = { "Zara Nadia" }, temp[26];
	int i, j, len, spaces = 0;
	sorted_list node_list;
	huffman_tree the_tree;
	List sentence;
	boolean stop;
	
	len = strlen(text);
	for(i = 0; i < len ; i++) {
		text[i] = tolower(text[i]);
	}
	
	CreateList(&sentence);
	for(i = 0; i < len; i++) {
		stop = false;
		j = 0;
		while(!stop) {
			if(text[i] != ' ' && text[i] != '\0') {
				temp[j] = text[i];
				i++;
				j++;
			} else {
				stop = true;
				spaces += 1;
			}
		}
		InsVLast(&sentence, temp);
		ClearArray(temp);
	}
	
	printf("Str List : ");
	PrintInfo(sentence);
	
	GenerateSortedList(sentence, &node_list, (double) (len - spaces));
	
	printf("\nSorted List :\n");
	PrintSorted(node_list);
	
	the_tree = GenerateHuffmanTree(&node_list);
	
	printf("\nHuffman Tree : ");
	PrintTree(the_tree);
	printf("\n\nyahooo!");
	return 0;
}
