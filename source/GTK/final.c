#include <stdio.h>
#include "stdlib.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "err.h"
#include "../imagery_treatment/Pretreatment/image_operations.h"
#include "../../include/sudoku_solver/solver.h"


void print_numb2(SDL_Surface *img, size_t x, size_t y, int number)
{
	if (number < 1 || number > 9)
		errx(1, "print_numb : solved sudoku is not propely solved");
	else
		{
			SDL_Surface* n;
			init_sdl();
			
			if (number == 1)
				n = load_image("../sudoku_solver/Print/n1.png");
			else if (number == 2)
				n = load_image("../sudoku_solver/Print/n2.png");
			else if (number == 3)
				n = load_image("../sudoku_solver/Print/n3.png");
			else if (number == 4)
				n = load_image("../sudoku_solver/Print/n4.png");
			else if (number == 5)
				n = load_image("../sudoku_solver/Print/n5.png");
			else if (number == 6)
				n = load_image("../sudoku_solver/Print/n6.png");
			else if (number == 7)
				n = load_image("../sudoku_solver/Print/n7.png");
			else if (number == 8)
				n = load_image("../sudoku_solver/Print/n8.png");
			else
				n = load_image("../sudoku_solver/Print/n9.png");
			
			size_t h = n->h;
			size_t w = n->w;
			
			Uint32 pixel;
			Uint8 r2,g2,b2;
			Uint8 r,g,b;
			
			for (size_t i = 0; i < w;i++)//x axe
			{
				for (size_t j = 0; j < h;j++)//y axe
				{
					pixel = get_pixel(n, i, j);
					SDL_GetRGB(pixel, n->format, &r, &g, &b);
					pixel = get_pixel(img, i+x, j+y);
					SDL_GetRGB(pixel, img->format, &r2, &g2, &b2);
					if (r == 0 && g == 0 && b == 0)
						pixel = SDL_MapRGB(img->format, r2, g2, b2);
					else
						{
							
							r = (3*r+r2)/4;
							g = (3*g+g2)/4;
							b = (3*b+b2)/4;
							pixel = SDL_MapRGB(img->format, r, g, b);
						}
					put_pixel(img, i+x, j+y, pixel);
				}
			}
			SDL_FreeSurface(n);
		}
}


void ouiJeLA(int sudoku[], SDL_Surface *img)
{
	int x = 50;
	int y = 127;
	
	
	for (size_t i = 0; i < 9; i++) {
			
		y += 47;
		x = 62;	
		for (size_t j = 0; j < 9; j++) {
				
			x += 46;	
			print_numb2(img, x, y, sudoku[i*9+j]);
		}
			
			
	}
	
	Save_Image(img, "Solve/solve_img.bmp");
}



void main_final() {
	
	int* sudoku= calloc(81, sizeof(int));
	file_to_matrix("Solve/sudoku_unsolved.result", sudoku);
	printf("oui");
	SDL_Surface *img;
	init_sdl();
	img = load_image("../imagery_treatment/sudoku/empty_sudoku.jpg");
	ouiJeLA(sudoku, img);
	free(sudoku);
	free(img);

}


