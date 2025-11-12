#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void interpret_data() {
    // import csv
    ifstream infile;
    infile.open("g.csv");
    
    // declare line
    string line;
    
    while(getline(infile, line)) {
        cout << line << endl;
    }
    
}

// function that gets the weights
void get_weights() {
    
}

vector<int> multiply_matrix(vector<int> A, vector<int> w, vector<int>& g) {

    // modify g through ref
}

void print_result(vector<int> g) {

}

int main(){
    // declare all 3 matrices
    vector<int> A;
    vector<int> w;
    vector<int> g;
    
    interpret_data();
    
    // a, h, e, are "Assessments %", "Homework %", "Employability %"
    // three weights are decided on our end, should all add up to 1 (example weights are 0.7, 0.2, 0.1 (traditional grading method))    
    get_weights();

    multiply_matrix(A, w, g);

    print_result(g);

    return 0;
}