//Christian Brito , 186006499
//Project 2

#include <iostream>
#include <cmath>
#include <iomanip>
using std::cout;
using std::cin;
using std::setw;

struct matrix {
        int rows;
        int cols;
        double* ptr;
};


void disp(matrix*);
void clrMat(matrix*);
matrix* minorMat(matrix*, int, int);
int matDet(matrix*);
matrix* matAdd(matrix*, matrix*);
matrix* matSub(matrix*, matrix*);
matrix* matMlt(matrix*, matrix*);
matrix* matTran(matrix*);
matrix* matInvr(matrix*);
matrix* matSize(matrix*);
matrix* matShape(matrix*);
bool input(int);

int main(){

        int n=0;
        bool xprogram = false;
                while(xprogram == false){
                cout<<"\nWelcome to Ye Olde Matrix Machine"<<
                        "\n~~~Menu~~~"<<
                        "\nChoice 1: Addition"<<
                        "\nChoice 2: Subtraction"<<
                        "\nChoice 3: Multiplication"<<
                        "\nChoice 4: Determinant"<<
                        "\nChoice 5: Transpose"<<
                        "\nChoice 6: Inverse"<<
                        "\nChoice 7: Resize"<<
                        "\nChoice 8: Reshape"<<
                        "\nChoice 0: Exit\n";
                cin>>n;

                xprogram = input(n);
              }


        return 0;

} // driver function

void disp(matrix* arr){
        // display arrays
        for(int i = 0; i<arr->rows; i++) {
                for(int j =0; j<arr->cols; j++) {
                        cout<<*(arr->ptr+i*arr->cols+j)<<setw(5);
                }
                cout<<"\n";
        }
} // complete

void clrMat(matrix* arr){
        free(arr->ptr);
        free(arr);
}

matrix* matAdd(matrix *arr1, matrix *arr2){
        matrix *sum = (matrix*)malloc(sizeof(matrix));
        sum->rows = arr1->rows;
        sum->cols = arr2->cols;
        sum->ptr = (double*)calloc(sum->rows*sum->cols,sizeof(double));
        // element-wise addition of matrix elements
        for (int i = 0; i<sum->rows; i++) {
                for (int j = 0; j<sum->cols; j++) {
                        *((sum->ptr)+i*(arr1->cols)+j) = *((arr1->ptr)+i*(arr1->cols)+j) +
                                                         *((arr2->ptr)+i*(arr1->cols)+j);
                }
        }
        return sum;
} // complete

matrix* matSub(matrix *arr1, matrix *arr2){
        matrix *dif = (matrix*)malloc(sizeof(matrix));
        dif->rows = arr1->rows;
        dif->cols = arr2->cols;
        dif->ptr = (double*)calloc(dif->rows*dif->cols,sizeof(double));
        //element-wise subtraction of arrays
        for (int i = 0; i<dif->rows; i++) {
                for (int j = 0; j<dif->cols; j++) {

                        *(dif->ptr+i*arr1->cols+j) = *(arr1->ptr+i*arr1->cols+j) -
                                                     *(arr2->ptr+i*arr2->cols+j);
                }
        }
        return dif;
} // complete

matrix* matMlt(matrix *arr1, matrix *arr2){
        matrix *mlt = (matrix*)malloc(sizeof(matrix));
        mlt->rows = arr1->rows;
        mlt->cols = arr2->cols;
        mlt->ptr = (double*)calloc(mlt->rows*mlt->cols,sizeof(double));
        // summation of a_ik * b_kj for k = 0 to k = n;
        for (int i = 0; i<mlt->rows; i++) {
                for (int j = 0; j<mlt->cols; j++) {
                        for (int k = 0; k<arr1->cols; k++) {
                                *(mlt->ptr+i*arr2->cols+j) += *(arr1->ptr+i*arr1->cols+k) *
                                                              *(arr2->ptr+k*arr2->cols+j);
                        }
                }
        }
        return mlt;


} // complete

int matDet(matrix *arr){
        int det = 0;
        int n = arr->rows;
        double* A = arr->ptr;
        if(n == 1) {
                det = *A;
        }
        else if(n == 2) {
                det = *(A)**(A+3) - *(A+2) * *(A+1);
        }
        else{
                det = 0;
                for(int i = 0; i<n; i++)
                        for(int j = 0; j<n; j++) {
                                det += pow(-1,i+j) * *(A+j)*matDet(minorMat(arr,i, j));
                        }
        }
        return det;
}         // complete

matrix* minorMat(matrix* arr, int curRow, int curCol){
        int n = arr->rows;
        double *aMin = (double*)calloc(arr->rows*arr->cols,sizeof(double));
        double *ptr = arr->ptr;
        matrix *minor = (matrix*)malloc(sizeof(matrix));
        minor->rows = n-1;
        minor->cols = n-1;
        minor->ptr = aMin;
        int k;
        int p = 0;
        for(int i = 0; i<n; i++) {
                if(i == curRow) { // do not use elements that are within the same row
                        continue;
                }
                else
                        k = 0;
                for(int j = 0; j<n; j++) {
                        if(j == curCol) { // do not use elements that are within the same col.
                                continue;
                        }
                        else
                                *(aMin+p*(n-1)+k) = *(ptr+i*n+j);
                        k++;
                }
                p++;
        }
        return minor;
} // complete

matrix* matTran(matrix *arr){
        matrix *transp = (matrix*)malloc(sizeof(matrix));
        double *tPtr = (double*)calloc(arr->rows*arr->cols,sizeof(double));
        transp->rows = arr->cols;
        transp->cols = arr->rows;
        transp->ptr = tPtr;

        for(int i = 0; i< arr->cols; i++) {
                for (int j = 0; j< arr->rows; j++) {
                        *(tPtr + i*arr->rows+ j) = *(arr->ptr + j*arr->cols + i );
                }
        }

        int temp = arr->rows;
        arr->rows = arr->cols;
        arr->cols = temp;

        return transp;

} //complete

matrix* matInvr(matrix *arr){
        int n = arr->rows;
        double *A = (double*)calloc(arr->rows*arr->cols,sizeof(double));
// creating a matrix of minors
        for(int i = 0; i<n; i++) {
                for(int j=0; j<n; j++) {
                        *(A+i*n + j) = matDet(minorMat(arr,i,j));
                }
        }
// create a matrix of cofactors
        for(int i = 0; i<n; i++) {
                for(int j=0; j<n; j++) {
                        *(A+i*n + j) *= pow(-1,i+j);
                        ; // alternating sign
                }
        }
// transpose matrix of cofactors;

        matrix* inverse = (matrix*)malloc(sizeof(matrix));
        inverse->rows = n;
        inverse->cols = n;
        inverse->ptr = A;
        ;
        cout<<'\n';
        inverse = matTran(inverse);
// multiply by 1/det(arr)

        for(int i = 0; i<n; i++) {
                for(int j=0; j<n; j++) {
                        *(inverse->ptr+i*n + j) *= (1.0/matDet(arr));
                }
        }
        return inverse;

}

matrix* matSize(matrix *arr){
        int nuRows, nuCols;
        cout<<"\nPlease enter # of rows and columns, seperated by space: ";
        cin>>nuRows>>nuCols;
        double *nuPtr = (double*)calloc(nuRows*nuCols,sizeof(double));

        // copy original array to resized arrays
        for(int i = 0; i<arr->rows; i++) {
                for(int j = 0; j<arr->cols; j++) {
                        *(nuPtr+i*nuCols+j) = *(arr->ptr + i*arr->cols+j);
                }
        }
        free(arr->ptr);
        //update original array members
        arr->rows = nuRows;
        arr->cols = nuCols;
        arr->ptr = nuPtr;

        return arr;

} // complete

matrix* matShape(matrix *arr){
        cout<<"\nPlease enter new dimensions, seperated with space ";
        int nuCols, nuRows;
        cin>>nuRows>>nuCols;
        if((nuRows * nuCols) != (arr->rows * arr->cols)) {
                cout<<"\nInvalid dimensions. Returning to menu...";
                clrMat(arr);
                main();
        }
        arr->rows = nuRows;
        arr->cols = nuCols;
        return arr;

} // complete



bool input(int n){
//check for exit inputs
        bool end;
        if (n==0) {
                cout<<"Exiting program...\n";
                end = true;
                return end;
        }
        if (n<0 || n>8) {
                cout<< "Unrecognized input. Returning to menu...";
                end = true;
                return end;
        }


//declare arrays
        bool need2 = false;
        matrix *arr1 = (matrix*)malloc(sizeof(matrix));
        matrix *arr2 = (matrix*)malloc(sizeof(matrix));
        if (n<4) need2 = true;

//recieve user input for num rows, and num cols.
        cout<<"\nPlease enter number of rows and columns for matrix 1, with a space inbetween: ";
        cin>>arr1->rows>>arr1->cols;

        if (need2 == true) {
                cout<<"\nPlease enter number of rows and columns for matrix 2, with a space inbetween: ";
                cin>>arr2->rows>>arr2->cols;
        }
//checking validity of dimensions with operation
        if ((n == 1 || n == 2) && (arr1->rows != arr2->rows || arr1->cols != arr2->cols)) {
                cout<<"\nInvalid dimensions for addition/subtraction. Returning to menu...";
                return end;
        }
        if (n == 3 && (arr1->cols != arr2->rows)) {
                cout<<"\nInvalid dimensions for multiplication. Returning to menu...";
                return end;
        }
        if ((n == 4 || n == 6) && (arr1->rows != arr1->cols)){
          cout<<"\nInvalid dimensions for determinant/inverse. Returning to menu... ";
          return end;
        }

// allocating memory for both arrays.

        arr1->ptr = (double*)calloc(arr1->rows*arr1->cols,sizeof(double));
        arr2->ptr = (double*)calloc(arr2->rows*arr2->cols,sizeof(double));

// initialize arrays 1 and 2
        for(int i = 0; i<arr1->rows; i++) {
                for (int j = 0; j<arr1->cols; j++) {
                        cout<<"\nPlease enter value at Arr1["<<i<<"]["<<j<<"]: ";
                        cin>> *((arr1->ptr)+i*(arr1->cols)+j);
                }
        }
        for(int i = 0; i<arr2->rows; i++) {
                for (int j = 0; j<arr2->cols; j++) {
                        cout<<"\nPlease enter value at Arr2["<<i<<"]["<<j<<"]: ";
                        cin>> *((arr2->ptr)+i*(arr2->cols)+j);
                }
        }

//call display func.
        cout<<"\nDisplaying Array 1:\n";
        disp(arr1);
        if (need2 == true) {
                cout<<"\nDisplaying Array 2:\n";
                disp(arr2);
        }
//switch case for menu input
        switch(n) {
        case 1: cout<<"\nAddition: \n";{
        matrix* sum = matAdd(arr1,arr2);
                disp(sum);
                clrMat(sum);
                break;
              }
        case 2: cout<<"\nSubtraction: \n";{
        matrix* dif = matSub(arr1,arr2);
                disp(dif);
                clrMat(dif);
                break;
              }
        case 3: cout<<"\nMultiplication: \n";{
        matrix* mlt = matMlt(arr1,arr2);
                disp(mlt);
                clrMat(mlt);
                break;
              }
        case 4: cout<<"\nDeterminant: \n"<<matDet(arr1);
                break;
        case 5: cout<<"\nTranspose: \n";{
        matrix* transp = matTran(arr1);
                disp(transp);
                clrMat(transp);
                break;
              }
        case 6: cout<<"\nInverse: \n";{
          if (matDet(arr1) == 0){
          cout<<"Inverse does not exist. Returning to menu...";
          end = false;
          return end;
}
        matrix* invr = matInvr(arr1);
                disp(invr);
                clrMat(invr);
                break;
              }
        case 7: cout<<"\nResize: \n";{
        matrix* resized = matSize(arr1);
                disp(resized);
                clrMat(resized);
                break;
              }
        case 8: cout<<"\nReshape: \n";{
        matrix* reshaped = matShape(arr1);
                disp(reshaped);
                clrMat(reshaped);
                break;
        }
      }
        clrMat(arr1);
        clrMat(arr2);
        cout<<"\nOperation Complete. Returning to menu...\n\n";
        end = false;
        return end;

}
