#include "Image.h"

double get_distance (Pixel pixel1, Pixel pixel2) {
	return sqrt(pow((double) pixel1.red - (double) pixel2.red, 2) +
				pow((double) pixel1.green - (double) pixel2.green, 2) +
				pow((double) pixel1.blue - (double) pixel2.blue, 2) +
				pow((double) pixel1.alpha - (double) pixel2.alpha, 2));
}

void color_average (Pixel *zone, MLV_Image *image, int x, int y, int width, int height) {
	int i, j, red, green, blue, alpha, amount_pixel;
	
	assert(x >= 0 && x <= WIDTH);
	assert(y >= 0 && y <= HEIGHT);
	
	i = y;
	j = x;
		
	MLV_get_pixel(j, i, &(zone->red), &(zone->green), &(zone->blue), &(zone->alpha));

	amount_pixel = 1;

	for (i = y; i < height; i++) {
		for (j = x; j < width; j++) {
			MLV_get_pixel(j, i, &red, &green, &blue, &alpha);
			
			zone->red += red;
			zone->green += green;
			zone->blue += blue;
			zone->alpha += alpha;
			
			amount_pixel += 1;
		}
	}
	
	zone->red = (1/amount_pixel) * zone->red;
	zone->green = (1/amount_pixel) * zone->green;
	zone->blue = (1/amount_pixel) * zone->blue;
	zone->alpha = (1/amount_pixel) * zone->alpha;
}

void build_tree_image (MLV_Image *image, Tree *tree) {
	Pixel zone_color_avg;
	int k, x, y, zone_amount, zone_width, zone_height;
	
	for (k = 0; k < TREE_DEPTH; k++) {
		zone_amount = pow(2, k);
		zone_width = WIDTH / zone_amount;
		zone_height = HEIGHT / zone_amount;
		
		for (x = 0; x < WIDTH; x += zone_width) {
			for (y = 0; y < HEIGHT; y += zone_height) {
				printf("x : %d, y : %d\n", x, y); 
				color_average(&zone_color_avg, image, x, y, zone_width, zone_height);
				printf("après color_average\n");
				add_node_tree(tree, zone_color_avg, x, y);
				printf("après add_node_tree\n");

			}			
		}
	
	}
}

void draw_tree (MLV_Image *image, Tree tree, int tree_depth_lvl) {
	if (tree == NULL)
		return ;
	
	/* MLV_draw_filled_rectangle(tree->x, tree->y, WIDTH / pow(2, tree_depth_lvl), 
												HEIGHT / pow(2, tree_depth_lvl),
												MLV_convert_rgba_to_color(tree->pixel.red,
																		  tree->pixel.green,
																		  tree->pixel.blue,
																		  tree->pixel.alpha)); */
	printf("x : %d, y : %d\n", tree->x, tree->y);
	
	draw_tree(image, tree->northwest, tree_depth_lvl + 1);
	draw_tree(image, tree->northeast, tree_depth_lvl + 1);
	draw_tree(image, tree->southeast, tree_depth_lvl + 1);
	draw_tree(image, tree->southwest, tree_depth_lvl + 1);
}
