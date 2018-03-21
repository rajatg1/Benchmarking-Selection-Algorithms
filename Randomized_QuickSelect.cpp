#include "Timer.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

// Used for debugging purpose only
void printVector(vector<int> input){
	for(int i=0; i < input.size(); i++){
		cout << input[i] << "  ";
	}
	cout << endl;
}

// Partition the input vector at pivot index and fill values in L, E and G vectors on the basis of pivot value
void partition(vector<int> &input, int &pivot_index, vector<int> &L, vector<int> &E, vector<int> &G){
	int pivot_value = input[pivot_index];
	for(int i = 0; i < input.size(); i++){
		if(pivot_value > input[i])
			L.push_back(input[i]);
		else if(pivot_value == input[i])
			E.push_back(input[i]);
		else if(pivot_value < input[i])
			G.push_back(input[i]);
	}
}

// Randomized QuickSelect takes input vector and integer k, and returns the kth smallest element
int quickSelect(vector<int> input, int k){
	vector<int> L, E, G;
	srand(time(NULL));
	int size = input.size();
	// Randomly chosen pivot index
	int pivot_index = rand() % size;
	// Partition the vector depending upon the chosen pivot index
	partition(input, pivot_index, L, E, G);
	if(k <= L.size()){
		return quickSelect(L, k);
	}
	else if (k <= (int)(L.size() + E.size())){
		return input[pivot_index];
	}
	else{
		int next_k = k - L.size() - E.size();
		return quickSelect(G, next_k);
	}
}

int main() {

	// Read the input dataset file
	ifstream myfile("benchmarking_input_dataset.txt");
	string line;
	// Input Vector made by reading values from the file
	vector< vector<int> > input_vector;

	while(getline(myfile,line)){
		// Extracting Vector from the input data
		string str = line;
		vector<int> input;
		stringstream ss(str);
		int i;
		while (ss >> i) {
			input.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}
		input_vector.push_back(input);
	}
	myfile.close();

	// Output results vector
	vector<string> output;

	for(int y = 0 ; y < input_vector.size(); y++){
		// kth smallest element (User-desired kth smallest element)
		int k = 1;

		// Sampling phase
		// Run Selection Algorithm 50 times per vector and calculate average User_Time
		double user_time = 0.0;
		for(int x = 0; x < 50; x++){
			Timer t;
			double u_time;
			t.start();
			quickSelect(input_vector[y], k);
			t.elapsedUserTime(u_time);
			user_time += u_time;
		}
		user_time /= 50.0;	// Taking average

		//	Convert in milli_seconds
		user_time *= 1000;

		// Push result in output vector
		string str2 = to_string(input_vector[y].size()) + "," + to_string(user_time);
		output.push_back(str2);
	}

	// Writing Output Data to file
	ofstream my_file;
	my_file.open ("QuickSelect_Median_k.txt", ios::out | ios::app);
	my_file << "Array Size,QUickSelect User_Time" << endl;
	for(int z = 0; z < output.size(); z++){
		my_file << output[z] << endl;
	}
	my_file.close();
	return 0;
}
