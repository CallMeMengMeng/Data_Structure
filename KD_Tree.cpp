#include "Compress.h"
using namespace std;

Compress::Compress(){
    size = 0, threshold = 0, nRows=0, nCols=0;
    // Enter in a file name
    cout << "Welcome. Please type in the name of the file to read the numbers.\n";
    cin >> readFileName;

    // Open the file.
    inFile.open(readFileName.c_str());
    if(!inFile.is_open()) {
        cout << "Failed to open the file! Press Enter to exit..." << endl;
        exit(1);
    }

    //Finding the array size and threshold
    inFile >> size;

    nRows = size;
    nCols = size;

    // Enter a threshold.
    cout << "Enter the desired threshold between 50-100: ";
    cin >> threshold;

    // Keep asking for the desired threshold until it is given.
    while (threshold < 50 || threshold > 100){
        cout << "\nIncorrect Threshold.\n";
        cout << "Enter the desired threshold between 50-100: ";
        cin >> threshold;
    }


    //Let's make the array
    // creating the columns
    compressArray = new int* [nCols];

    // creating the rows
    for (int r = 0; r < nRows; r++){
        compressArray[r] = new int[nCols];
    }

    // FIll the array
    for (int i = 0; i < nRows; i++){
        for (int j = 0; j < nCols; j++){
            inFile >> compressArray[i][j];
        }
    }

    inFile.close();

    // Show before editing.
    print();
    work(0, nRows, 0, nCols);

}
Compress::~Compress(){
    for (int i = 0; i < nRows; i ++){
        delete compressArray[i];
    }
    delete [] compressArray;
}


void Compress::work(int start_x, int end_x, int start_y, int end_y){
    int Size = end_y - start_y; // Finding the midpoints.
    int nb_blacks = 0;
    int nb_whites = 0;
    int total_blocks = 0;
    int majority = 0;
    int percent = 0;

//    Testing everything.

//    cout << "\nx1, y1: " << start_x << "," << start_y << " x2,y2: " << end_x << "," << end_y << endl;
//    for (int r = start_x; r < end_x; r++){
//        for (int c = start_y; c < end_y; c++){
//            cout << compressArray[r][c];
//        }
//        cout << endl;
//    }

    // Initial case. If 1, break and start returning results
    if (end_x <= start_x || end_y <= start_y){
        return;
    }

   //  Keep breaking it down until it reaches 1.
    else {
        // Count the Number of Black pieces
        for(int i = start_x; i < end_x; i++){
            for(int j = start_y; j < end_y; j++){
                if(compressArray[i][j] == 1){
                    nb_blacks++;
                }
            }
        }

        // Find the total and number of white pieces.
        total_blocks = ((end_x - start_x) * (end_y - start_y));
        nb_whites = total_blocks - nb_blacks;

        // give the max back
        majority = max(nb_blacks, nb_whites);
        // find the percent of the highest amount of colored blocks.
        percent = ((majority*100)/total_blocks);

//        cout << "Percent: " << percent << " Threshold: " << threshold  << "\n-----\n";


        // majority/total_blocks is determining the percent of the greater
        // color in the box. We are comparing it to the threshold percent.
        if (percent >= threshold){
            for(int i = start_x; i < end_x; i++){
                for(int j = start_y; j < end_y; j++){
                    if(nb_blacks > nb_whites) compressArray[i][j] = 1;
                    else compressArray[i][j] = 0;
                }
            }
        }

        // Keep breaking down until we reach the initial case.
        else {
            work((end_x - (Size/2)), (end_x), (start_y), (start_y + (Size/2)));
            work(start_x, (start_x + (Size/2)), (start_y), (start_y + (Size/2)));
            work((start_x), (start_x + (Size/2)), (end_y - (Size/2)), end_y);
            work((end_x - (Size/2)), end_x, (end_y - (Size/2)), end_y);
//
//            work((start_x), (mid_x), (mid_y), end_y);
//            work(start_x, (mid_x ), (start_y), (mid_y));
//            work((mid_x), end_x, start_y, (mid_y));
//            work((mid_x), end_x, (mid_y), end_y);
        }
    }
}

void Compress::print(){

    // Print the function
    cout << "\nImage: " << threshold << "%\n";
    for (int r = 0; r < nRows; r++){
        for (int c = 0; c < nCols; c++){
            cout << compressArray[r][c];
        }
        cout << endl;
    }
}
