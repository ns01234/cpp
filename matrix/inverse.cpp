#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void matrix_printer(const vector<vector<double>>& matrix){
    int rows = matrix.size();
    for(int i = 0; i < rows; i++){
        cout << '|';
        for(int j = 0; j < rows; j++){
            if (j == rows-1){
                cout << matrix[i][j];
            }else {
                cout << matrix[i][j] << ' ';
            }
        }
        cout << '|';
        cout << '\n';
    }
}

vector<vector<double>> matrix_partitioner(vector<vector<double>> matrix, int row, int column){
    int rows = matrix.size();
    vector<vector<double>> new_matrix(rows - 1, vector<double>(rows - 1));
    for(int i=0; i<rows-1; i++){
        for(int j=0; j<rows-1; j++){
            if(i<row && j<column){

                new_matrix[i][j] = matrix[i][j];
            }else if(i<row && j>=column){
                new_matrix[i][j] = matrix[i][j+1];
            }else if(i>=row && j>=column){
                new_matrix[i][j] = matrix[i+1][j+1];
            }else if(i>=row && j<column){
                new_matrix[i][j] = matrix[i+1][j];
            }
        }
    }
    return new_matrix;
}

double det(vector<vector<double>> matrix){
    double determinant = 0;
    if(matrix.size() == 1){
        determinant = matrix[0][0];
    }
    else{
        for(int i=0; i<matrix.size();i++){
        int sign = pow(-1,(i%2));
        determinant += sign * matrix[i][0] * det(matrix_partitioner(matrix,i,0));
        }
    }
    return determinant;
}

vector<vector<double>> inverse_calculator(vector<vector<double>> matrix){
    vector<vector<double>> inverse_matrix(matrix.size(),(vector<double>(matrix.size(),0)));
    int row = matrix.size();
    if(row == 1){
        inverse_matrix[0][0] = 1/matrix[0][0];
        return inverse_matrix;
    }
    for(int i=0; i<row; i++){
        for(int j=0; j<row; j++){
            int sign = pow((-1),(i+j));
            inverse_matrix[j][i] = sign * 1/det(matrix) * (det(matrix_partitioner(matrix,i,j)));
        }
    }
    return inverse_matrix;
}

int main(){
    int dimension;
    cout << "enter the dimension of the matrix: ";
    cin >> dimension;
    vector<vector<double>> matrix(dimension, vector<double>(dimension));
    
    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension; j++){
            cout << "entry in row " << i+1 << ", column " << j+1 << ": ";
            cin  >> matrix[i][j];
        }
    }

    matrix_printer(matrix);
    if(det(matrix) == 0){
        cout << "this matrix has no inverse";
    }else{
        cout << "---------inverse--------\n";
        matrix_printer(inverse_calculator(matrix));
    }
    
    return 0;
}
