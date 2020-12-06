#ifndef __IMAGE__
#define __IMAGE__

#include "Tree.h"

#include <MLV/MLV_all.h>
#include <math.h>

#define WIDTH 512
#define HEIGHT 512

double get_distance (Pixel pixel1, Pixel pixel2);

void color_average (Pixel *zone, MLV_Image *image, int x, int y, int width, int height);

void build_tree_image (MLV_Image *image, Tree *tree);

void draw_tree (MLV_Image *image, Tree tree, int tree_depth_lvl);

#endif
