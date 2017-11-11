
#include<iostream>
#include<vector>
#include "bitmap.h"
#include <string>
using namespace std;
bool validpic(Bitmap image,int no,int &sizex,int &sizey);
int avg (int a , int b,int c , int d , int e,int f);

int main()
{
	Bitmap image[10];
	vector <vector <Pixel> > bmp[12];
	int sizex = 0;
	int sizey = 0;
	int no = 0;
	int average = 0;
	int red;
	int green;
	int blue;
	bool validBmp;

	Pixel rgb;
	string fname;

	/* Ask for files from user until they enter "done" or for 10 names*/
	while((no<10) &&(fname != "done"))
	{
	cout << "Enter Filename for picture " <<no+1<<" :";
	cin >>fname;
	
	
	/*if the input is not "done"*/
	if(fname != "done")
	{	
	/* put the file to image */
	image[no].open(fname);	
	
	/*Call the validpic Function to make sure if the picture is valid or the same size*/
	validBmp = validpic(image[no],no,sizex,sizey);
	no++;

	/*if its not valid , reduce the  number  */

	if(validBmp == 0)
	{
		no = no-1;

	}
	}
	}

	/* The no has to be more than 1 because need atleast 2 images to make composite*/
	if(no>1)
	{
	
	image[11] = image[0];
	/*Put All the images to the pixelMatrixes*/
	for(int i =0;i<no;i++){
		bmp[i] = image[i].toPixelMatrix();
	}	
		/*The final image will be created in bmp[11]*/
		bmp[11] = image[0].toPixelMatrix();	


	for(int z = 0;z<no;z++)
	{	/*Loop for how many images*/
		
	
	cout <<"image "<<z+1<<" of "<< no << " is done" << endl;	
	for(int i = 0;i< bmp[z].size();i++)
	{

		for(int j = 0;j<bmp[z][0].size();j++)
		{
	 
			rgb =  bmp[z][i][j];
			/*Get the rgb values of the pixels*/	
			red = rgb.red;
			green = rgb.green;
			blue = rgb.blue;

			rgb = bmp[11][i][j];
		/*Put into the function avg to get the average of all the values of rgb of both pictures*/

			average = avg(red,green,blue,rgb.red,rgb.green,rgb.blue);	

		
			rgb = bmp[11][i][j];
		
			rgb.red = average;
			rgb.green = average;
			rgb.blue = average;
			/*Put the REsult to bmp[11]*/
			bmp[11][i][j] = rgb;
 
		}


	}
	}
/*	Save picture from bmp[11] as composite-malteneiji		*/

	image[11].fromPixelMatrix(bmp[11]);
	image[11].save("composite-malteneiji.bmp");
	
	
	}
	else
	{
		cout <<"composite image cannot be created without at least 2 images" << endl;
	}

	return 0 ;
}
int avg( int a , int b, int c, int d, int e, int f)
{

	return (a+b+c+d+e+f)/6;
}

bool validpic(Bitmap image,int no,int &sizex,int &sizey)
{	/* Make sure the picture is valid	 	*/
	vector <vector <Pixel> > bmp;

	if(image.isImage())
	{
		bmp = image.toPixelMatrix();
		if(no == 0)
		{	
		/*	size x and y is pass by reference so 
			record the first image's x and y values to those variables		*/

				

		
			sizex = bmp.size();
			sizey = bmp[0].size();
			return 1;
		}
		else
		{
			
	
		if((bmp.size() == sizex) && (bmp[0].size() == sizey))
		{

		/*
		Check if the sizes match the first image's size
		*/
			return 1;
		}	
		else
		{
			cout <<"Image not the same size as first. Image should be "<<sizex << " x " <<sizey << endl;
		}
		}


	}
	return 0;
}
