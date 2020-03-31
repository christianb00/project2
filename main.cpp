//Christian Brito , 186006499
//Project 2

#include <iostream>
using std::cout;
using std::cin;

void disp(int *, int, int);
void matAdd(int *, int *, int, int);
void matSub(int *, int *, int, int);
void matMlt(int *, int *, int, int, int);
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

void disp(int *p1, int rows, int cols){
  // display arrays
  for(int i = 0; i<rows;i++){
    for(int j =0; j<cols;j++){
      cout<<*(p1+i*cols+j)<<" ";
    }
    cout<<"\n";
  }
}

void matAdd(int *p1,int *p2, int rows, int cols){
  int *sum = new int[rows*cols];
  for (int i = 0; i<rows;i++){
    for (int j = 0; j<cols;j++){
      *(sum+i*cols+j) = *(p1+i*cols+j) + *(p2+i*cols+j);
    }
  }
  delete[] p1;
  delete[] p2;
  cout<<"\nDisplaying Sum Array:\n";
  disp(sum,rows,cols);
  delete[] sum;
  cout<<"\nOperation complete. Returning to menu...\n";
  main();
}

void matSub(int *p1, int*p2, int rows, int cols){
  int *dif = new int[rows*cols];
  for (int i = 0; i<rows;i++){
    for (int j = 0; j<cols;j++){
      *(dif+i*cols+j) = *(p1+i*cols+j) - *(p2+i*cols+j);
    }
  }
  delete[] p1;
  delete[] p2;
  cout<<"\nDisplaying Difference Array:\n";
  disp(dif,rows,cols);
  delete[] dif;
  cout<<"\nOperation complete. Returning to menu...\n";
  main();
}

void matMlt(int *p1, int*p2, int rows1, int cols1, int cols2){
int *mlt = new int[rows1*cols2];
for (int i = 0 ; i<rows1; i++){
  for (int j = 0 ; j<cols2; j++){
    for (int k = 0 ; k<cols1 ; k++){
      *(mlt+i*cols2+j) += *(p1+i*cols1+k)**(p2+k*cols2+j);
    }
  }
}
delete[] p1;
delete[] p2;
cout<<"\nDisplaying product of arrays: \n";
disp(mlt,rows1,cols2);
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
int *p1 = new int[rows1*cols1];
int *p2 = new int[rows2*cols2];

// initialize arrays 1 and 2
for(int i = 0; i<rows1; i++){
  for (int j = 0; j<cols1; j++){
    cout<<"\nPlease enter value at Arr1["<<i<<"]["<<j<<"]: ";
    cin>> *(p1+i*cols1+j);
  }
}
for(int i = 0; i<rows2; i++){
  for (int j = 0; j<cols2; j++){
    cout<<"\nPlease enter value at Arr2["<<i<<"]["<<j<<"]: ";
    cin>> *(p2+i*cols2+j);
  }
}

//call display func.
cout<<"\nDisplaying Array 1:\n";
disp(p1,rows1,cols1);
cout<<"\nDisplaying Array 2:\n";
disp(p2,rows2,cols2);

//switch case for menu input
switch(n){
  case 1: matAdd(p1,p2,rows1,cols1);
  break;
  case 2: matSub(p1,p2,rows1,cols1);
  break;
  case 3: matMlt(p1,p2,rows1,cols1,cols2);
  break;
}

}
