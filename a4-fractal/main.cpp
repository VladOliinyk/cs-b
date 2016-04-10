// About PPM format:
// http://netpbm.sourceforge.net/doc/ppm.html

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// The size of the fractal image.
static int imageSideSize, iter;

// The scale of the fractal image.
double minR = -1.5;
double maxR = 0.5;
double minI = -1.0;
double maxI = 1.0;

// Get image side size and count of iterations by asking user;
void getInputData() {
    cout << "Enter width of image: ";
    cin >> imageSideSize;
    cout << "Enter count of iterations: ";
    cin >> iter;
}

// Finding the number of iterations in the Mandelbrot formula
int findMandelbrot(double cr, double ci, int max_iterations) {
    int i = 0;
    double zr = 0.0, zi = 0.0;
    while (i < max_iterations && zr * zr + zi * zi < 4.0)
    {
        double temp = zr * zr - zi * zi + cr;
        zi = 2.0 * zr * zi + ci;
        zr = temp;
        i++;
    }
    return i;
}

// Find the real value for C corresponding to x pixel in the image.
double mapToReal(int x, int imageSideSize, double minR, double maxR) {
    double range = maxR - minR;
    return x * (range / imageSideSize) + minR;
}

// Find the imaginary value for C corresponding to x pixel in the image.
double mapToImaginary(int y, int imageSideSize, double minI, double maxI) {
    double range = maxI - minI;
    return y * (range / imageSideSize) + minI;
}

// Print to console the percentage of completion.
void getCompleteness(int cur, int max) {
    cout << "Complete: " << (++cur*100)/max << "%\r";
}

// General function.
// "Drawing" fractal into a file.
void drawFractal(char* filename) {
    // Open the output file, write the PPM header...
    ofstream fout(filename);
    delete filename;
    // A ppm image's magic number
    fout << "P3" << endl;

    // Dimensions
    fout << imageSideSize << " " << imageSideSize << endl;

    // The maximum color value
    fout << "255" << endl;

    // For every pixel
    for (int y = 0; y < imageSideSize; y++)         // Rows
    {
        for (int x = 0; x < imageSideSize; x++)     // Cols
        {
            double cr = mapToReal(x, imageSideSize, minR, maxR);
            double ci = mapToImaginary(y, imageSideSize, minI, maxI);

            int n = findMandelbrot(cr, ci, iter);

            // Convert the map of the resulting number to RGB values
            int r = (n*8 % 256);
            int g = (n*4 % 256);
            int b = (n*2 % 256);


            // Output it to an image
            fout << r << " " << g << " " << b << " ";
        }
        fout << endl;
        getCompleteness(y, imageSideSize);
    }
    fout.close();
    cout << "Finished!" << endl;
}

// Creating the filename by adding side size and count if iterations to the filename.
// "image_" + imageSideSize + countOfIterations + ".ppm"
char* createFilename() {
    char* filename = new char[255];
    char buff[255];

    strcpy(filename, "");
    strcat(filename, "image_");
    sprintf(buff, "%d", imageSideSize);
    strcat(filename, buff);
    strcat(filename, "_");
    sprintf(buff, "%d", iter);
    strcat(filename, buff);
    strcat(filename, ".ppm");

    return filename;
}

int main()
{
    getInputData();
    drawFractal(createFilename());
    return 0;
}
