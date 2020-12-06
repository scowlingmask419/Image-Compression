#ifndef __TREE__
#define __TREE__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TREE_DEPTH 4

typedef struct {
	int red, green, blue, alpha;
} Pixel;

typedef struct node {
	Pixel pixel;
	int x, y;
	struct node *northwest, *northeast, *southeast, *southwest;
} Node, *Tree;


Node *allocate_node (Pixel zone_color_avg, int x, int y);

int tree_depth (Tree tree);

int add_node_tree (Tree *tree, Pixel zone_color_avg, int x, int y);

#endif
	
