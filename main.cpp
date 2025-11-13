#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const bool DEBUG = false;
const int col_size = 3;

// iterates through a line in the csv file, skipping initial 3 commas. then, 3 numbers are appended to current_line_values: a_i, h_i, and e_i
void iterate_through_line(string line, vector<double>& current_line_values) {
    int comma_ticker = 0;
    int i = 0;
    // read through the line until 3 commas are read
    // this is to skip all the initial stuff in the line we dont care about
    while(comma_ticker != 4) {
        if (DEBUG) {cout << "w loop. line[i] is " << line[i] << endl;}
            
            if (line[i] == ',') {
                comma_ticker ++;        
                if (DEBUG) {cout << "comma_ticker just updated to " << comma_ticker << " and line[i] is " << line[i] << endl;}
        
            }
        i ++;
        }
    
    // read the first, second, and third next numbers and store in current_line_values, using i from before as index to start at
    string curr_string = "";
    while(comma_ticker != 7) {
        if (DEBUG) {cout << "w loopo. line[i] is " << line[i] << endl;}
        if (line[i] == ',') {
            comma_ticker ++;
            // when comma ticker goes up, it means we hit a comma. So, convert the current string into a double and shove it into current_line_values. then reset curr_string.
            // FYI, d = stod(str) will convert str into a double, d
            current_line_values.push_back(stod(curr_string));
            curr_string = "";
            if (DEBUG) {cout << "comma_ticker just updated to " << comma_ticker << " and line[i] is " << line[i] << ". current_line_values just received " << curr_string << endl;}
        }
        // if not a comma, put the number in a string which we will convert later
        else {
            curr_string += line[i];
            if (DEBUG) {cout << "curr_string is now " << curr_string << endl;}
        }
        i ++;
    }
}

// opens g.csv and iterates through all lines, appending the values a_i, h_i, and e_i to A as a vector
void interpret_data(vector<vector<double>>& A) {
    // open csv
    ifstream infile;
    infile.open("g.csv");
    string line;

    // skip the first few lines
    getline(infile, line);
    getline(infile, line);
    
    // for each line
    while(getline(infile, line)) {   
        vector<double> current_line_values;
        iterate_through_line(line, current_line_values);
        
        if (DEBUG) {
            cout << endl << "current_line_values: ";
            for (int j = 0; j < current_line_values.size(); j ++) {
                cout << current_line_values.at(j) << " ";
            }
            cout << endl;
        }

        // add current student's scores to A
        A.push_back(current_line_values);

    }
    
}

// asks the user to input the weights that A will be multiplied by
void get_weights(vector<double>& w) {
    double temp_weight;
    vector<char> weight_char = {'a', 'h', 'e'};
    for (int i = 0; i < 3; i ++) {
        cout << "Please enter w_" << weight_char[i] << " (only floating-point #s allowed): ";
        cin >> temp_weight;
        w.push_back(temp_weight);
    }
}

// multiplies matrices A * w, result is updated as g
void multiply_matrix(vector<vector<double>> A, vector<double> w, vector<double>& g) {
    // modify g through ref
    
    for (int row = 0; row < A.size(); row ++) {
        double curr_grade = 0;
        for (int col = 0; col < col_size; col ++) {
            curr_grade += A[row][col] * w[col];
            //cout << "multiplying " << A[row][col] << " by " << w[col] << endl;
        }
        g.push_back(curr_grade);
        //cout << "total grade was " << curr_grade << endl << endl;
    }
}

// creates a file with each line of g as a line in the file
void write_to_file(vector<double> g, string flnm) {
    ofstream outfile;
    outfile.open(flnm);
    if (outfile) {
        for (int i = 0; i < g.size(); i ++ ) {
            outfile << g[i] << endl;
        }
        cout << "\nFile successfully generated.\n";
    }
    else {
        cout << "Had trouble creating that file..\n";
    }
    outfile.close();
}

int main(){
    // declare all 3 matrices
    vector<vector<double>> A;
    vector<double> w;
    vector<double> g;
    
    //
    string user_input;
    cout << "Please make sure that g.csv is in the same directory as this program. Type y to continue .. ";
    cin >> user_input;
    if (user_input != "y") {
        exit(0);
    }

    // fill A with 3-wide columns of csv's length
    interpret_data(A);

    cout << "\nMatrix A succesfully generated\n" << endl;
    
    // printing out A
    //cout << "A: first num is " << A[0][0] << endl;
    /*for (int i = 0; i < A.size() ; i ++ ) {
        for (int j = 0; j < A[i].size(); j ++ ) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    */
    
    get_weights(w);
    cout << "\nMatrix w succesfully generated, multiplying A and w .." << endl;

    // printing out w
    /*cout << "w: ";
    for (int i = 0; i < w.size() ; i ++ ) {
        cout << w[i] << " ";    
    }
    cout << endl;
    */
    
    multiply_matrix(A, w, g);
    /*cout << "g: ";
    for (int i = 0; i < g.size() ; i ++ ) {
        cout << g[i] << " ";    
    }
    cout << endl;
    */
    
    cout << "\nMatrix g succesfully generated" << endl;

    string if_write;
    cout << "\nWould you like to output matrix g to a text file? type y/n: ";
    cin >> if_write;

    if (if_write == "y") {
        string flnm;
        cout << "\nPlease enter a valid filename (including .txt): ";
        cin >> flnm;
        write_to_file(g, flnm);
    }
    
    return 0;
}