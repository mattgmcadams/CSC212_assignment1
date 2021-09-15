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

	return stDev;
}

// & means pass reference, not the object itself
double get_median(std::vector< std::vector<int> > & img){
	double thresh = 0.0f;
	std::vector<int> temp;
	for (int i=0; i<img.size(); i++){
		for (int j=0; j<img[i].size(); j++){
			temp.push_back(img[i][j]);
		}
	}

	//sort temp array - std::sort()
	std::sort(temp.begin(), temp.end());

	int sz=temp.size();
	int mid = sz/2;


	//if length is even, return (temp[n/2]+temp[n/2-1])/2
	//if length is odd, return element at temp[n/2]
	if (sz%2 != 0){
		thresh = temp[mid];
	} else {
		thresh = (temp[mid]+temp[mid-1])/2.0f;
	}


	return thresh;

}

double get_thresh(std::vector< std::vector<int> > & img, int n, int i, int j, int pMax, int pMin) {
	std::vector<int> temp;
	double thresh = 0.0f;
	int start = -(n/2);
	int end = (n/2);
	int count = 0;
	for ( int h = start ;  h <= end ; h++ ){
		for (int k = start ;  k <= end ; k++ ){
			//fill temp with img values excluding any outside the image somehow
			if((i+h)<0 || (i+h)>=img.size()){
			} else if ((j+k)<0 || (j+k)>=img[i].size()) {
			} else {
				temp.push_back(img[i+h][j+k]);
			}
		}
	}


	for (int c=0; c<temp.size(); c++){
		if(temp[c]>=0){

		}
	}


	int sz=temp.size();


	//set variables
	double mean = get_mean(temp);
	double stDev = get_stDev(temp);
	double R = .5f*(pMax-pMin);

	//forumla
	thresh = mean*(1.0f+.2f*(stDev/R-1.0f));

	return thresh;
}


int main(int argc, char** argv) {

	std::string reach = argv[1];
	std::string in_fname = argv[2];
	std::string out_fname = argv[3];
	int n_sz = 0;
	if(reach == "local"){
		n_sz = std::stoi(argv[4]);
	}

	int val;
	std::string line;
	std::vector<std::vector<int>> image;
	std::ifstream in_file(in_fname);

	while(std::getline(in_file, line)) {
		std::vector<int> row;
		std::istringstream myss(line);
		while( myss >> val ) {
			row.push_back(val);
		}
		image.push_back(row);

	}

	in_file.close();

	// save file
	std::ofstream out_file(out_fname);

	std::vector<int> sorted;

	for (int i = 0 ; i < image.size() ; i++){
		for (int j = 0 ; j < image[i].size() ; j++ ) {
			sorted.push_back(image[i][j]);
		}
	}

	std::sort(sorted.begin(), sorted.end());
	int pMin = sorted[0];
	int pMax = sorted[sorted.size()-1];
	double threshold = 0.0f;

	if (reach == "global") {
		threshold = get_median(image);
		for (int i = 0 ; i < image.size() ; i++ ) {
			for (int j = 0 ; j < image[i].size() ; j ++) {
				if (image[i][j] < threshold) {
					out_file << 0 << " ";
				} else {
					out_file << 255 << " ";
				}
			}
			out_file << std::endl;
		}
	} else {
		for (int i = 0 ; i < image.size() ; i++){
			for (int j = 0 ; j < image[i].size() ; j++ ) {
				threshold = get_thresh(image, n_sz, i, j, pMax, pMin);
				if (image[i][j] < threshold) {
					out_file << 0 << " ";
				} else {
					out_file << 255 << " ";
				}
			}
			out_file << std::endl;

		}

	}


	out_file.close();


	return 0;
}