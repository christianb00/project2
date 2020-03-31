//Christian Brito , 186006499
//Project 2

#include <iostream>
using std::cout;
using std::cin;

struct matrix {
  int rows;
  int cols;
  int* ptr;
};


void disp(matrix*);
void matAdd(matrix*, matrix*);
void matSub(matrix*, matrix*);
void matMlt(matrix*, matrix*);
void input(int);

int main(){

int n;

cout<<"\nMenu"<<
"\nChoice 1: Addition"<<
"\nChoice 2: Subtraction"<<
"\nChoice 3: Multiplication"<<
"\nChoice 4: Exit\n";
cin>>n;

input(n);

return 0;

}

void disp(matrix* arr){
  // display arrays
  for(int i = 0; i<arr->rows;i++){
    for(int j =0; j<arr->cols;j++){
      cout<<*(arr->ptr+i*arr->cols+j)<<" ";
    }
    cout<<"\n";
  }
}

void matAdd(matrix *arr1, matrix *arr2){
  matrix *sum = new matrix;
  sum->rows = arr1->rows;
  sum->cols = arr2->cols;
  sum->ptr = new int[sum->rows * sum->cols];
  for (int i = 0; i<sum->rows;i++){
    for (int j = 0; j<sum->cols;j++){
      *((sum->ptr)+i*(arr1->cols)+j) = *((arr1->ptr)+i*(arr1->cols)+j) +
      *((arr2->ptr)+i*(arr1->cols)+j);
    }
  }
  delete[] arr1;
  delete[] arr2;
  cout<<"\nDisplaying Sum Array:\n";
  disp(sum);
  delete[] sum->ptr;
  delete[] sum;
  cout<<"\nOperation complete. Returning to menu...\n";
  main();
}

void matSub(matrix *arr1, matrix *arr2){
  matrix *dif = new matrix;
  for (int i = 0; i<arr1->rows;i++){
    for (int j = 0; j<arr1->cols;j++){
      *(dif->ptr+i*arr1->cols+j) = *(arr1->ptr+i*arr1->cols+j) - *(arr2->ptr+i*arr2->cols+j);
    }
  }
  delete[] arr1;
  delete[] arr2;
  cout<<"\nDisplaying Difference Array:\n";
  disp(dif);
  delete[] dif;
  cout<<"\nOperation complete. Returning to menu...\n";
  main();
}

void matMlt(matrix *arr1, matrix *arr2){
matrix *mlt = new matrix;
for (int i = 0 ; i<arr1->rows; i++){
  for (int j = 0 ; j<arr2->cols; j++){
    for (int k = 0 ; k<arr1->cols ; k++){
      *(mlt->ptr+i*arr2->cols+j) += *(arr1->ptr+i*arr1->cols+k)**(arr2->ptr+k*arr2->cols+j);
    }
  }
}
delete[] arr1;
delete[] arr2;
cout<<"\nDisplaying product of arrays: \n";
disp(mlt);
delete[] mlt;
cout<<"\nOperation complete. Returning to menu...\n";
main();


}

void input(int n){
//check for exit inputs
if (n==0){
  cout<<"Exiting program...\n";
  return;
}
if (n<0 || n>7){
  cout<< "Unrecognized input. Returning to menu...";
  main();
}

//declare rows and cols
int rows1, cols1, rows2, cols2;

//recieve user input for num rows, and num cols.
cout<<"\nPlease enter number of rows and columns for matrix 1, with a space inbetween: ";
cin>>rows1>>cols1;
cout<<"\nPlease enter number of rows and columns for matrix 2, with a space inbetween: ";
cin>>rows2>>cols2;

//checking validity of dimensions with operation
if ((n == 1 || n == 2) && (rows1 != rows2 || cols1 != cols2)){
  cout<<"\nInvalid dimensions for addition/subtraction. Returning to menu...";
  main();
}
if (n == 3 && (cols1 != rows2)){
  cout<<"\nInvalid dimensions for multiplication. Returning to menu...";
  main();
}

// allocating memory for both arrays.
matrix *arr1 = new matrix[rows1*cols1];
matrix *arr2 = new matrix[rows2*cols2];

// initialize arrays 1 and 2
arr1->rows = rows1, arr1->cols = cols1;
arr2->rows = rows2, arr2->cols = cols2;
for(int i = 0; i<arr1->rows; i++){
  for (int j = 0; j<arr1->cols; j++){
    cout<<"\nPlease enter value at Arr1["<<i<<"]["<<j<<"]: ";
    cin>> *((arr1->ptr)+i*(arr1->cols)+j);
  }
}
for(int i = 0; i<arr2->rows; i++){
  for (int j = 0; j<arr2->cols; j++){
    cout<<"\nPlease enter value at Arr2["<<i<<"]["<<j<<"]: ";
    cin>> *((arr2->ptr)+i*(arr2->cols)+j);
  }
}

//call display func.
cout<<"\nDisplaying Array 1:\n";
disp(arr1);
cout<<"\nDisplaying Array 2:\n";
disp(arr2);

//switch case for menu input
switch(n){
  case 1: matAdd(arr1,arr2);
  break;
  case 2: //matSub(arr1,arr2);
  break;
  case 3: //matMlt(arr1,arr2);
  break;
  }
}
