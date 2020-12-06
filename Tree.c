#include "Tree.h"

Node *allocate_node (Pixel zone_color_avg, int x, int y) {
	Node *temp;
	
	temp = (Node *) malloc(sizeof(Node));
	
	if (temp != NULL) {
		temp->pixel.red = zone_color_avg.red;
		temp->pixel.green = zone_color_avg.green;
		temp->pixel.blue = zone_color_avg.blue;
		temp->pixel.alpha = zone_color_avg.alpha;
		temp->x = x;
		temp->y = y;
		temp->northwest = temp->northeast = temp->southeast = temp->southwest = NULL;
	}
	
	return temp;
}

int tree_depth (Tree tree) {
	if (tree == NULL)
		return 0;
	else {
		int northwest_depth = tree_depth(tree->northwest);
		int northeast_depth = tree_depth(tree->northeast);
		int southeast_depth = tree_depth(tree->southeast);
		int southwest_depth = tree_depth(tree->southwest);
		
		return (((northwest_depth > northeast_depth ? northwest_depth : northeast_depth)
								 > southeast_depth ? northwest_depth : southeast_depth) 
								 > southwest_depth ? northwest_depth : southwest_depth);
	}
}

int add_node_tree (Tree *tree, Pixel zone_color_avg, int x, int y) {
	if (*tree == NULL) {
		*tree = allocate_node(zone_color_avg, x, y);
		return 0;
	}
	/* The zone is positionned in northwest of the current point. */
	if ((*tree)->x > x && (*tree)->y > y)
		return add_node_tree(&((*tree)->northwest), zone_color_avg, x, y);
		
	/* The zone is positionned in northeast of the current point. */
	if ((*tree)->x < x && (*tree)->y > y)
		return add_node_tree(&((*tree)->northeast), zone_color_avg, x, y);
	
	/* The zone is positionned in southeast of the current point. */
	if ((*tree)->x > x && (*tree)->y < y)
		return add_node_tree(&((*tree)->southeast), zone_color_avg, x, y);
	
	/* The zone is positionned in southwest of the current point. */
	if ((*tree)->x < x && (*tree)->y < y)
		return add_node_tree(&((*tree)->southwest), zone_color_avg, x, y);
}

