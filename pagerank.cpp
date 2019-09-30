#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;




map<string, float> ReadFile(string fileName);





int main(int argc, char* argv[])
{

    auto websites = ReadFile(argv[1]);

    for (auto sites: websites){
        cout << sites.first << " " << fixed << setprecision(2) << sites.second << endl;
    }

    return 0;
}








map<string, float> ReadFile(string fileName){

    fstream file(fileName, ios_base::in);


    //// CREATE CONTAINERS
    unordered_map<string, int> websites;
    string current;
    int lines;
    int iterations;
    float numSites = 0;


    //// STORE LINES + ITERATIONS
    file >> lines;
    file >> iterations;


    //// ADJACENCY LIST
    //// CREATE AN ARRAY OF PAIRS
    string a[lines][2];


    //// FILL ARRAY WITH WEBSITE CONNECTIONS
    //// rows = lines
    //// column [0] = pointer
    //// column [1] = pointee
    for (int i = 0; i < lines; i++) {

        for (int j = 0; j < 2; j++) {
            file >> a[i][j];
        }
    }


    //// SET IDs FOR EACH WEBSITE BY PASSING TO MAP
    for (int i = 0; i < lines; i++){

        for (int j = 0; j < 2; j++){

            if (websites.find(a[i][j]) == websites.end()){
                websites[a[i][j]] = numSites++;
            }
        }
    }


//    //// PRINT MAP
//    cout << "--- WEBSITE IDs ---" << endl;
//    for (auto site: websites){
//        cout << "ID " << site.second << ": " << site.first << endl;
//    }
//    cout << endl;


    //// ADJACENCY MATRIX
    //// CREATE SQUARE MATRIX TO STORE CONNECTIONS
    float matrix[(int)numSites][(int)numSites] ;



    //// INITIALIZE MATRIX WITH ALL ZEROS
    for (int i = 0; i < numSites; i++){
        for (int j = 0; j < numSites; j++){
            matrix[i][j] = 0;
        }
    }

    //// FILL MATRIX WITH 1s FOR EVERY CONNECTION
    int x,y;

    for (int i = 0; i < lines; i++){
        x = websites[a[i][0]];
        y = websites[a[i][1]];

        matrix[y][x] = 1;
    }


//    //// PRINT BOOLEAN MATRIX
//    cout << "--- BOOLEAN MATRIX ---\n";
//    for (int i = 0; i < numSites; i++){
//        for (int j = 0; j < numSites; j++){
//            cout << matrix[i][j] << " ";
//        }
//
//        cout << endl;
//    }


    //// SET MATRIX TO INITIAL VALUES
    int outDegree = 0;

    for (int i = 0; i < numSites; i++){
        for (int j = 0; j < numSites; j++){
            if (matrix[j][i] == 1){
                outDegree++;
            }
        }

        for (int j = 0; j < numSites; j++){
            if (matrix[j][i] == 1) {
                matrix[j][i] /= outDegree;
            }
        }

        outDegree = 0;
    }


//    //// PRINT UPDATED MATRIX
//    cout << "\n\n--- INITIAL MATRIX ---\n";
//    for (int i = 0; i < numSites; i++){
//        for (int j = 0; j < numSites; j++){
//            cout << setprecision(2) << fixed << matrix[i][j] << "  ";
//        }
//
//        cout << endl;
//    }



    //// CREATE RANK ARRAY
    //// initialize all to 1/n
    float rank[(int)numSites];

    for (int i = 0; i < numSites; i++){
        rank[i] = 1/numSites;
    }



    //// BEGIN ITERATION PROCESS
    float sum = 0;
    float newRank[(int)numSites];

    for (int iters = 0; iters < iterations-1; iters++) {

        for (int i = 0; i < numSites; i++) {

            for (int j = 0; j < numSites; j++){
                sum += rank[j] * matrix[i][j];
            }

            newRank[i] = sum;
            sum = 0;
        }

        for (int i = 0; i < numSites; i++){
            rank[i] = newRank[i];
        }

    }


    //// CREATE FINAL MAP
    //// store URLs and their respective ranks
    map <string, float> pageRanks;

    for (auto page: websites){
        pageRanks[page.first] = rank[page.second];
    }

    return pageRanks;
}