#include "Tree.h"
#include "Image.h"

int main () {
	MLV_Image *image;
	Tree quadtree;
			
	MLV_create_window("Image", "MLV", WIDTH, HEIGHT);
	
	image = MLV_load_image("butterfly.jpg");
	MLV_resize_image(image, WIDTH, HEIGHT);
	MLV_draw_image(image, 0, 0);

	MLV_actualise_window();
	
	build_tree_image(image, &quadtree);
	
	MLV_wait_mouse(NULL, NULL);
	
	MLV_draw_filled_rectangle(0, 0, WIDTH, HEIGHT, MLV_COLOR_BLACK);
	
		MLV_wait_mouse(NULL, NULL);
	
	draw_tree(image, quadtree, 0);
	
	MLV_actualise_window();
	
	MLV_wait_mouse(NULL, NULL);
	
	return 0;
}
