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
void matDet(matrix*);
void matTran(matrix*);
void matInvr(matrix*);
void matSize(matrix*);
void matShape(matrix*);
void input(int);

int main(){

int n;

cout<<"\nMenu"<<
"\nChoice 1: Addition"<<
"\nChoice 2: Subtraction"<<
"\nChoice 3: Multiplication"<<
"\nChoice 4: Determinant"<<
"\nChoice 5: Transpose"<<
"\nChoice 6: Inverse"<<
"\nChoice 7: Resize"
"\nChoice 8: Reshape"
"\nChoice 0: Exit\n";
cin>>n;

input(n);

return 0;

}

void disp(matrix* arr){
  // display arrays
  for(int i = 0; i<arr->rows;i++){
    for(int j =0; j<arr->cols;j++){
      cout<<*(arr->ptr+i*arr->cols+j)<<"  ";
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
  delete[] arr1->ptr;
  delete[] arr2->ptr;
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
  dif->rows = arr1->rows;
  dif->cols = arr2->cols;
  dif->ptr = new int[dif->rows * dif->cols];
  for (int i = 0; i<dif->rows;i++){
    for (int j = 0; j<dif->cols;j++){

      *(dif->ptr+i*arr1->cols+j) = *(arr1->ptr+i*arr1->cols+j) -
      *(arr2->ptr+i*arr2->cols+j);
    }
  }
  delete[] arr1->ptr;
  delete[] arr2->ptr;
  delete[] arr1;
  delete[] arr2;
  cout<<"\nDisplaying Difference Array:\n";
  disp(dif);
  delete[] dif->ptr;
  delete[] dif;
  cout<<"\nOperation complete. Returning to menu...\n";
  main();
}

void matMlt(matrix *arr1, matrix *arr2){
matrix *mlt = new matrix;
mlt->rows = arr1->rows;
mlt->cols = arr2->cols;
mlt->ptr = new int[mlt->rows * mlt->cols];
for (int i = 0 ; i<mlt->rows; i++){
  for (int j = 0 ; j<mlt->cols; j++){
    for (int k = 0 ; k<arr1->cols ; k++){
      *(mlt->ptr+i*arr2->cols+j) += *(arr1->ptr+i*arr1->cols+k) *
      *(arr2->ptr+k*arr2->cols+j);
    }
  }
}
delete[] arr1->ptr;
delete[] arr2->ptr;
delete[] arr1;
delete[] arr2;
cout<<"\nDisplaying product of arrays: \n";
disp(mlt);
delete[] mlt->ptr;
delete[] mlt;
cout<<"\nOperation complete. Returning to menu...\n";
main();


}

void matDet(matrix *arr){
  int det;
  // check if array is 2x2 to directly apply identity. det(A) = [0]*[3] - [1]*[2]
  if(arr->rows == 2 ){
    det = *(arr->ptr) * *(arr->ptr + 3) -
    *(arr->ptr + 1) * *(arr-> ptr + 2);

    cout<<det;
  }
}


void matTran(matrix *arr){

}

void matInvr(matrix *arr){

}

void matSize(matrix *arr){
  int nuRows, nuCols;
  cout<<"\nPlease enter # of rows and columns, seperated by space: ";
  cin>>nuRows>>nuCols;
  int *nuPtr = new int[nuRows* nuCols]();

  // copy original array to resized arrays
  for(int i = 0; i<arr->rows;i++){
    for(int j = 0; j<arr->cols;j++){
      *(nuPtr+i*nuCols+j) = *(arr->ptr + i*arr->cols+j);
    }
  }
  delete[] arr->ptr;
  arr->rows = nuRows;
  arr->cols = nuCols;
  arr->ptr = nuPtr;

  disp(arr);
  delete[] arr->ptr;
  delete[] arr;
}

void matShape(matrix *arr){
cout<<"\nPlease enter new dimensions, seperated with space ";
int nuCols, nuRows;
cin>>nuRows>>nuCols;
if((nuRows * nuCols) != (arr -> rows * arr-> cols)){
  cout<<"\nInvalid dimensions. Returning to menu...";
  delete[] arr->ptr;
  delete[] arr;
  main();
}
arr->rows = nuRows;
arr->cols = nuCols;
cout<<"\nDisplaying reshaped array...\n";
disp(arr);
cout<<"\nReturning to menu...\n";
delete[] arr->ptr;
delete[] arr;
main();
}



void input(int n){
//check for exit inputs
if (n==0){
  cout<<"Exiting program...\n";
  return;
}
if (n<0 || n>8){
  cout<< "Unrecognized input. Returning to menu...";
  main();
}

//declare arrays
bool need2 = false;
matrix *arr1 = new matrix;
matrix *arr2 = new matrix;
if (n<4) need2 = true;

//recieve user input for num rows, and num cols.
cout<<"\nPlease enter number of rows and columns for matrix 1, with a space inbetween: ";
cin>>arr1->rows>>arr1->cols;

if (need2 == true){
cout<<"\nPlease enter number of rows and columns for matrix 2, with a space inbetween: ";
cin>>arr2->rows>>arr2->cols;
}
//checking validity of dimensions with operation
if ((n == 1 || n == 2) && (arr1->rows != arr2->rows || arr1->cols != arr2->cols)){
  cout<<"\nInvalid dimensions for addition/subtraction. Returning to menu...";
  main();
}
if (n == 3 && (arr1->cols != arr2->rows)){
  cout<<"\nInvalid dimensions for multiplication. Returning to menu...";
  main();
}

// allocating memory for both arrays.

arr1->ptr = new int[arr1->rows * arr1->cols];
arr2->ptr = new int[arr2->rows * arr2->cols];

// initialize arrays 1 and 2
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
if (need2 == true){
cout<<"\nDisplaying Array 2:\n";
disp(arr2);
}
//switch case for menu input
switch(n){
  case 1: matAdd(arr1,arr2);
  break;
  case 2: matSub(arr1,arr2);
  break;
  case 3: matMlt(arr1,arr2);
  break;
  case 4: matDet(arr1);
  break;
  case 5: matTran(arr1);
  break;
  case 6: matInvr(arr1);
  break;
  case 7: matSize(arr1);
  break;
  case 8: matShape(arr1);
  break;
  }
}
