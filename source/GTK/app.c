#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

#include "../imagery_treatment/Hough/hough.h"
#include "../imagery_treatment/Hough/segmentation.h"
//#include "../imagery_treatment/Pretreatment/pixel_operations.h"
#include "../imagery_treatment/Pretreatment/image_operations.h"
//#include "../imagery_treatment/Pretreatment/sdl_functions.h"
#include "../imagery_treatment/Pretreatment/grayscale.h"
#include "../imagery_treatment/Pretreatment/pretreatment_color.h"
#include "../imagery_treatment/Rotation/manual_rotation.h"
//#include "../imagery_treatment/autorotate.h"
//#include "../imagery_treatment/split.h"

//#include "../imagery_treatment/split.h"
//#include "../imagery_treatment/detection/detection.h"
//#include "../neural_network/digit.h"
//#include "../sudoku_solver/solver.h"
#include "../../include/sudoku_solver/solver.h"
//#include "../sudoku_solver/print.h"
#include "final.h"
#include "from_N_to_S.h"

int stage;
int rotation = 0;

char image_initial[100] = "Images/image_initial.bmp";
char image_result[100] = "";
char image_treatment[100] = "Images/image_treatment.bmp";
char image_treatment_rotation[100] = "Images/image_treatment_rotation.bmp";
char image_copy[100] = "";
char image_copy2[100] = "Images/image_copy2.bmp";


char string_stage[100] = "";

//struct extremities e = {{0,0},{0,0},{0,0},{0,0}};

//int unsolved[81];
int unsolved[81] = {0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0};

/*
int unsolved[81] = {5,3,0,0,7,0,0,0,0,
		6,0,0,1,9,5,0,0,0,
		0,9,8,0,0,0,0,6,0,
		8,0,0,0,6,0,0,0,3,
		4,0,0,8,0,3,0,0,1,
		7,0,0,0,2,0,0,0,6,
		0,6,0,0,0,0,2,8,0,
		0,0,0,4,1,9,0,0,5,
		0,0,0,0,8,0,0,7,9};*/

GtkWidget *window;
GtkWidget *paned;
GtkWidget *grid;
GtkWidget *box;
GtkWidget *next_step;
GtkWidget *label;
GtkWidget *file;
GtkWidget *image;
GtkWidget *save;
GtkWidget *rotation_button;
GtkWidget *resize_scale;
GtkWidget *resize_button;

GtkBuilder *builder;

void resize_window()
{
	gtk_window_resize(GTK_WINDOW(window), 850, 500);
}


void on_save_clicked()
{
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;

	dialog = gtk_file_chooser_dialog_new (
		"Save File",
		GTK_WINDOW(window),
		action,
		(const gchar*)"Cancel",
		GTK_RESPONSE_CANCEL,
		(const gchar*)"Save",
		GTK_RESPONSE_ACCEPT,
		NULL);
	chooser = GTK_FILE_CHOOSER (dialog);

	gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);


	gtk_file_chooser_set_filename (chooser,"test.bmp");

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *filename;

		filename = gtk_file_chooser_get_filename (chooser);
		copy(filename, image_result);
		g_free (filename);
  	}

	gtk_widget_destroy (dialog);
}


//Initialise GtkWidget values
void GetWidget()
{
	grid = GTK_WIDGET(gtk_builder_get_object(builder, "grid"));
	next_step = GTK_WIDGET(gtk_builder_get_object(builder, "next_step"));
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
	file = GTK_WIDGET(gtk_builder_get_object(builder, "file"));
	image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));
	save = GTK_WIDGET(gtk_builder_get_object(builder, "save"));
	rotation_button = GTK_WIDGET(gtk_builder_get_object(builder, "rotation_button"));
	box = GTK_WIDGET(gtk_builder_get_object(builder, "box"));
	resize_scale = GTK_WIDGET(gtk_builder_get_object(builder, "resize_scale"));
	resize_button = GTK_WIDGET(gtk_builder_get_object(builder, "resize_button"));
}


// Display an image in GTK app
void display_image_GTK(char path[100])
{
	if (image)
		gtk_container_remove(GTK_CONTAINER(box), image);
	image = gtk_image_new_from_file((const gchar*) path);
	gtk_container_add(GTK_CONTAINER(box), image);
	gtk_widget_show(GTK_WIDGET(image));
}

char is_cell2(char name[], int len)
{
	return len == 6 && name[0] == 'c'; 
}

// Load the image
void on_file_set(GtkFileChooserButton *f)
{
	// Set back window initial size
	resize_window();

	// Copy selected image
	strcpy(image_result, gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f)));

	// Initialize treatmented image
	copy("Images/image_treatment.bmp", image_result);
	
	// Initialize treatmented rotation image
	copy("Images/image_treatment_rotation.bmp", image_result);

	// Copy to initial the selected image
	copy("Images/image_initial.bmp", image_result);
	
	// Initialize result image
	copy("Images/image_result.bmp", image_result);
	strcpy(image_result, "Images/image_result.bmp");

	// Display image_result image
	display_image_GTK(image_result);
	stage = 0;
	gtk_label_set_label(GTK_LABEL(label), (const gchar*)"Ready for OCRisation");

	// Keep a copy of image
	strcpy(image_copy,"image_result");
	copy("/Images/image_copy.bmp", image_result);

	// Deactivate rotation widget
	gtk_widget_set_sensitive(rotation_button, FALSE);
	gtk_widget_set_sensitive(resize_scale, FALSE);
	gtk_range_set_value(GTK_RANGE(resize_scale), 0);

	//Remove cells
	//int n_file = 0;
	//struct file *files = get_files("cell/", &n_file, is_cell2);
	//for (int i = 0; i < n_file; i++)
	//{
	//	remove(files[i].name);
	//}
}

// Select the step to print
void print_result_GTK(char string_stage[])
{
	switch (stage)
	{
		case 0:
			// Manual rotation

			// Activate rotation widget
			gtk_widget_set_sensitive(rotation_button, TRUE);
			gtk_widget_set_sensitive(resize_scale, TRUE);

			strcpy(string_stage, "Manual rotation");
			break;
		case 1:
			// Set new image_treatment
			copy(image_treatment, image_treatment_rotation);
			copy(image_result, image_treatment_rotation);
			copy(image_copy, image_treatment_rotation);

			// Deactivate rotation widget
			gtk_widget_set_sensitive(rotation_button, FALSE);
			gtk_widget_set_sensitive(resize_scale, FALSE);

			// Grayscale
			strcpy(string_stage, "Grayscale: ok");
			//Filter_step(image_treatment, 1);
			grayscale(image_treatment);
			copy(image_copy2, image_treatment);
			display_image_GTK(image_treatment);
			break;
		case 2:
			// Contrast 3
			strcpy(string_stage, "Contrast 3: ok");
			contrast(image_treatment,10);
			invert(image_treatment);
			//Filter_step(image_treatment, 2);
			display_image_GTK(image_treatment);
			break;
		case 3:
			// Blur 1
			strcpy(string_stage, "Blur 1: ok");
			//Filter_step(image_treatment, 3);
			brightness(image_treatment);
                        median_filter(image_treatment);
                        //binarize(image_treatment);
                        //invert(image_treatment);
			display_image_GTK(image_treatment);
			break;
		case 4:
			// Edge 2
			strcpy(string_stage, "Edge 2: ok");
			//Filter_step(image_treatment, 4);
			binarize(image_treatment);
                        invert(image_treatment);

			display_image_GTK(image_treatment);
			break;
		case 5:
			// Black and White 
		//	Filter_step(image_treatment, 5);

			// Another filter if result isn't good
		/*	if (More_dark(image_treatment) == 0)
			{
				copy(image_treatment, "Images/filter_step_1.bmp");
				strcpy(string_stage, "Black and White: failed");
			}
			// Black and white works fine
			else
			{
				strcpy(string_stage, "Black and White: ok");
				stage += 3;
			}*/
			stage+=3;
			display_image_GTK(image_treatment);
			break;
		//==================================
		case 6 :
			// Blur 3
			strcpy(string_stage, "Blur 3: ok");
			//Filter_step(image_treatment, 51);
			display_image_GTK(image_treatment);
			break;
		case 7 :
			// Sobel 2
			strcpy(string_stage, "Sobel 2: ok");
			//Filter_step(image_treatment, 52);
			display_image_GTK(image_treatment);
			break;
		case 8 :
			// Black and white
			strcpy(string_stage, "Black and White: ok");
			//Filter_step(image_treatment, 53);
			display_image_GTK(image_treatment);
			break;
		//==================================
		case 9 :
			// Detection
			//copy(image_copy, "Images/filter_step_5.bmp");
			//if (detection(image_treatment, image_copy, &e) != 0)
			//copy(image_copy, image_initial);
			//Filter_step(image_copy, 6);
			//Filter_step(image_copy, 7);
			/*if (detection(image_treatment, image_copy, &e) != 0)
			{
				strcpy(string_stage, "Grid detection without filter: ok");
			}
			else
				strcpy(string_stage, "Grid detection: failed");
			//display_image_GTK(image_copy);*/
			houghTransformation(image_treatment);
			break;
		case 10 :
			// Display image_treatment
			strcpy(string_stage, "Grid detection with filter: ok");
			display_image_GTK(image_treatment);
			break;
		case 11 :
			// Autorotate
			strcpy(string_stage, "Auto rotate: ok");
			//Autorotate(image_result, &e);
			display_image_GTK(image_treatment);
			break;
		case 12:
			// Contrast
			strcpy(string_stage, "Contrast: ok");
			//Filter_step(image_result, 6);
			display_image_GTK(image_treatment);
			break;
		case 13:
			// Black and white
			strcpy(string_stage, "Detect: ok");
			//Filter_step(image_result, 7);
			detect2(image_treatment);
			display_image_GTK(image_treatment);
			break;
		case 14:
			// Split
			strcpy(string_stage, "Split of sudoku: ok");
			//invert(image_treatment);
			display_image_GTK(image_treatment);
			split(image_treatment);
			break;
		case 15:
			// Get_grid and display it
			strcpy(string_stage, "Grid to solve");
			//print_sudoku_unsolved(image_result, unsolved, "./cell/");
			main_from();
			main_solver();
			display_image_GTK("Print/empty_sudoku.jpg");
			break;
		case 16:
			// Solver
			strcpy(string_stage, "Grid solved - Process finished");
			//print_sudoku(image_result, unsolved);
			main_final();
			display_image_GTK("Solve/solve_img.bmp");

			// Activate save button
			gtk_widget_set_sensitive(save, TRUE);
			break;
		
		default:
			strcpy(string_stage, "");
	}
	gtk_label_set_label(GTK_LABEL(label), (const char*)string_stage);
}

// Next step on each button clicked
void on_next_step_clicked()
{
	if (strlen(image_result) != 0)
	{
		print_result_GTK(string_stage);
		stage += 1;
	}
}

// Slider to rotate manually image
void on_slide(GtkScale *scale)
{
	// Copy before manually rotation
	copy(image_treatment_rotation, image_treatment);

	rotation = gtk_range_get_value(GTK_RANGE(scale));
	rotation %= 360;
	if(rotation != 0)
	{
		manual_rotation(image_treatment_rotation, (double)rotation);
	}
	else
	{
		copy(image_treatment_rotation, image_initial);
		resize_window();
	}
	display_image_GTK(image_treatment_rotation);
}

// Button to apply rotation
void on_rotation_clicked()
{
	if (strlen(image_result) != 0)
		on_slide(GTK_SCALE(resize_scale));
}

int main(int argc, char *argv[])
{

	gtk_init(&argc, &argv);
	g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);

	builder = gtk_builder_new_from_file("app.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	paned = GTK_WIDGET(gtk_builder_get_object(builder, "paned"));
	GetWidget();

	// Set window parameter
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window), "Projet-S3 OCR");
	resize_window();
	
	// Deactivate rotation widget
	gtk_widget_set_sensitive(rotation_button, FALSE);
	gtk_widget_set_sensitive(resize_scale, FALSE);

	// Deactivate save button
	gtk_widget_set_sensitive(save, FALSE);

	// Set resize_scale widget
	gtk_range_set_range(GTK_RANGE(resize_scale), 0, 360);
	gtk_range_set_show_fill_level(GTK_RANGE(resize_scale), TRUE);

	// Connects signal handlers
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(save), "clicked", G_CALLBACK(on_save_clicked), NULL);
	g_signal_connect(G_OBJECT(next_step), "clicked", G_CALLBACK(on_next_step_clicked), NULL);
	g_signal_connect(G_OBJECT(file), "file-set", G_CALLBACK(on_file_set), NULL);
	g_signal_connect(G_OBJECT(rotation_button), "clicked", G_CALLBACK(on_rotation_clicked), NULL);
	g_signal_connect(G_OBJECT(resize_button), "clicked", G_CALLBACK(resize_window), NULL);

	gtk_widget_show_all(window);
	gtk_main();

	return EXIT_SUCCESS;

}
