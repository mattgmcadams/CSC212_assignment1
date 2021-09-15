#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <limits>

double get_mean(std::vector<int>& array){
    double mean = 0, sum = 0;
    int count=0;

    for (int i = 0; i < array.size(); i++){
        if(array[i]>=0){
            sum += array[i];
            count++;
        }
    }
    mean = sum/count;

    return mean;
}

double get_stDev(std::vector<int>& array) {


    double stDev = 0;
    double mean = get_mean(array);
    double sum = 0;
    int count = 0;

    for (int i = 0; i < array.size(); i++){
        if (array[i] >= 0){
            sum += pow(array[i] - mean, 2);
            count++;
        }
    }

    stDev = sqrt(sum/count);

    std::cout << stDev << std::endl;
    std::cout << "This was calculated using mean: " << mean << std::endl;

    return stDev;
}

// & means pass reference, not the object itself
double get_median(std::vector< std::vector<int> > & img){
    double thresh = 0;
    std::vector<int> temp;
    for (int i=0; i<img.size(); i++){
        for (int j=0; j<img[i].size(); j++){
            temp.push_back(img[i][j]);
        }
    }

    //sort temp array - std::sort()
    std::sort(temp.begin(), temp.end());

    int sz=temp.size();

    //if length is even, return (temp[n/2]+temp[n/2-1])/2
    //if length is odd, return element at temp[n/2]
    if (sz%2 == 0){
        thresh = (temp[sz/2]+temp[sz/2-1])/2;
    } else {
        thresh = temp[sz/2];
    }


    return thresh;

}

double get_thresh(std::vector< std::vector<int> > & img, int n, int i, int j) {
    std::vector<int> temp;
    double thresh = 0;
    int start = -(n/2);
    int end = (n/2);
    int count = 0;
    for ( int h = start ;  h <= end ; h++ ){
        for (int k = start ;  k <= end ; k++ ){
            //fill temp with img values excluding any outside the image somehow
            std::cout << "Value for [" << i+h << "][" << j+k << "]: ";
            if((i+h)<0 || (i+h)>=img.size()){

                std::cout << "Null" << std::endl;
            } else if ((j+k)<0 || (j+k)>=img[i].size()) {

                std::cout << "Null" << std::endl;
            } else {
                temp.push_back(img[i+h][j+k]);
                std::cout << img[i+h][j+k] << std::endl;
            }

        }
    }

    std::cout << "For the array: { ";
    for (int c=0; c<temp.size(); c++){
        if(temp[c]>=0){
            std::cout << temp[c] << " ";
        }
    }
    std::cout << "}, the standard deviation is: ";

    int sz=temp.size();

    //sort
    std::sort(temp.begin(), temp.end());


    //set variables
    double mean = get_mean(temp);
    double stDev = get_stDev(temp);
    int pMin = temp[0];
    int pMax = temp[temp.size()-1];
    double R = .5*(pMax-pMin);

    //forumla
    thresh = mean*(1+().2*((stDev/R)-1)));


    return thresh;
}


int main(int argc, char** argv){

    std::vector<std::vector<int>> image;
    std::vector<int> row;
    int val;
    std::string line;

    std::ifstream in_file("input.img");
    while(std::getline(in_file, line)) {
        std::vector<int> row;
        std::istringstream myss(line);
        while( myss >> val ) {
            row.push_back(val);
        }
        image.push_back(row);
    }


    int n_sz = 3;
    double threshold = 0;


    threshold = get_median(image);
    std::cout << "Global threshold: " << threshold << std::endl;

    std::ofstream out_file("thresh_actual.txt");

    for (int i = 0 ; i < image.size() ; i++){
        for (int j = 0 ; j < image[i].size() ; j++ ) {
            threshold = get_thresh(image, n_sz, i, j);
            std::cout << "Local threshold for [" << i << "][" << j << "]: " << threshold << std::endl;
            out_file << threshold << " ";
        }
        out_file << std::endl;



    }





    return 0;
}