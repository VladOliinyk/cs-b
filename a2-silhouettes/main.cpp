#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include "silhouettes.h"

using namespace std;

/* Way to your file: */
string FILENAME = " ";

/* Main logic metgod.
 * Counting the number of objects on the image. */
int getCountOfObj(int **pixelArray, int imgHeight, int imgWidth);

/* Method that chack the size of the image
 *  and resize it if needed. */
QImage* loadImage() {
    QImage* myImage = new QImage(FILENAME.c_str());
    if ( (myImage->height() * myImage->width()) > 44000 ) {
        QImage* myImage2 = new QImage(myImage->scaled(500, 300, Qt::KeepAspectRatio));
        myImage = myImage2;
    }
    return myImage;
}

/* Main method.
 * Opening file.
 * Creating binary pixel array.
 * Counting the number of silhouettes on the image by calling main logic method.
 * Printing the binary array into the file if debug == true. */
int main(){
    /* Open image */
    if (FILENAME == " ") {
        cout << " Please enter the path to your file: ";
        getline(cin, FILENAME);
    }
    if (debug) { cout << "d:        Initiated opening the image file." << endl; }
    QImage* image = loadImage();
    if (debug) { cout << "d:        Image file successfully open." << endl; }

    if(debug){
        cout << "d:        Image  width: " << image->width()<<endl;
        cout << "d:        Image height: " << image->height()<<endl;
    }

    int imgHeight = image->height();
    int imgWidth = image->width();

    /* Calculating the MINIMUM_SILHOUETTE_SIZE given the image size */
    MINIMUM_SILHOUETTE_SIZE = (imgHeight*imgWidth) * MINIMUM_SILHOUETTE_SIZE;

    /* Creating pixel array */
    if (debug) { cout << "d:        Initiated the creation of the array.." << endl; }

    //initializing
    int **pixelArray;
    pixelArray = new int *[imgHeight];
    for (int i=0; i < imgHeight; i++) {
        pixelArray[i] = new int[imgWidth];
    }

    //filling
    //imageBinarization(pixelArray, imgHeight, imgWidth);
    /// NOTE! QImage pixel(  col , row )
    for (int i = 0; i < imgHeight; i++) {                //rows
        for (int j = 0; j < imgWidth; j++) {             //cols


            /* First binarization method.*/
            QColor curPixCol = image->pixel(j, i);
            if (curPixCol.lightness() >= LIGHTNESS) {
                pixelArray[i][j] = 0;
            } else {
                pixelArray[i][j] = 1;
            }
        }
    }
    if (debug) { cout << "d:        Array created successfully." << endl; }

    /* Counting the number of objects on the image */
    if (debug) { cout << "d:        Initiated the counting of the number of silhouettes.." << endl; }
    int count = getCountOfObj(pixelArray, imgHeight, imgWidth);
    if (debug) { cout << "d:        Counting of the number completed." << endl; }

    if (debug && createFile_debug) {
        cout << "d: cf:    Initiated the writing binary array into file.." << endl;
        ///just to see how it looks.
        QFile file("silhouettes.txt");
        QTextStream out(&file);
        if(file.open(QIODevice::Append))
        {
            for (int i = 0; i < imgHeight; i++) {
                for (int j = 0; j < imgWidth; j++) {
                    if (pixelArray[i][j] == 0) {
                        out << "-";
                    } else {
                        out << pixelArray[i][j];
                    }
                }
                out << endl;
            }
        }
        file.close();
        cout << "d: cf:    Binary array successfully written into the file.." << endl;
    }

    /* Clear memory */
    if (debug) { cout << "d:        Initiated the clearing the memory.." << endl; }
    for (int i=0; i < imgHeight; i++) {
        delete pixelArray[i];
    }
    delete [] pixelArray;
    delete image;
    if (debug) { cout << "d:        Memory successfully cleared.." << endl; }

    /* Done! */
    if (debug) { cout << endl << endl; }
    cout << " The number of silhouettes: " << count << endl;
    system("pause");
    return 0;
}

///// ///// ///// ///// ///// ///// LOGIC ///// ///// ///// ///// ///// /////

/* Recursive method that fill the single silhouettes.
 *
 * @param pixelArray  - pixel array of image.
 * @param imgH - image height.
 * @param imgW - image width.
 * @param x - x-coord of 'current' pixel (pixel which is analysed now)
 * @param y - н-coord of 'current' pixel (pixel which is analysed now)
 * @param marker - the int value which is equal to counter+2
 *  to mark the object in pixel array (0 and 1 is already reserved).
 * @param silhouetteSize - size of 'current' object (object (part of image) which is analysed now)
 */
void fillArea(int **pixelArray, int imgH, int imgW, int x, int y, int marker, int & silhouetteSize) {

    if (x >= 1 && x < imgH && y >= 1 && y < imgW && pixelArray[x][y] == 1) {

        if (debug && currentPixelRecursive_debug) {
            cout << "d: cpr:   ..checking the: " << x << ":" << y << endl;
        }

        if (pixelArray[x][y] == 1) {
            pixelArray[x][y] = marker;
            silhouetteSize++;

            fillArea(pixelArray, imgH, imgW, x, y+1, marker, silhouetteSize); // down
            fillArea(pixelArray, imgH, imgW, x, y-1, marker, silhouetteSize); // up
            fillArea(pixelArray, imgH, imgW, x+1, y, marker, silhouetteSize); // right
            fillArea(pixelArray, imgH, imgW, x-1, y, marker, silhouetteSize); // left pixel
        } else {
            return;
        }

    }
}

/* Main logic method.
 * Counting the number of objects on the image.
 *
 * @param arr  - pixel array of image.
 * @param imgH - image height.
 * @param imgW - image width.
 * @return counter - the number of objects on the image;
 */
int getCountOfObj(int **arr, int imgH, int imgW) {
    int counter = 0;
    for (int row = 0; row < imgH; row++) {
        for (int col = 0; col < imgW; col++) {
            if (debug && currentPixel_debug) {
                cout << "d: cp:    Current pixel: " << row << ":" << col << endl;
            }
            if (arr[row][col] == 1) {
                int silhouetteSize = 0;
                fillArea(arr, imgH, imgW, row, col, counter+2, silhouetteSize);
                if (silhouetteSize >= MINIMUM_SILHOUETTE_SIZE) {
                    counter++;
                    if (debug && silhouetteFounder_debug) {
                        cout << "d: sf:    Shilouette #" << counter << " founded at: " << row << ":" << col << endl;
                    }
                }

            }

        }
    }
    return counter;
}

///// ///// ///// ///// ///// ///// L END ///// ///// ///// ///// ///// /////
