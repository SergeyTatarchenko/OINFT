#include <iostream>
#include "matrix.h"
#include <stdlib.h>

using namespace std;


int main()
{
    int **MatrixForAdd =0,**MatrixForMul=0,**RezMatrix=0;
    int dimension;
    cout<<"enter dimension "<<endl;
    cin>>dimension;
    if(dimension >=  2){
        Matrix NewMatrix;
        NewMatrix.DynamicMatrix = NewMatrix.DynamicMatrixCreate(NewMatrix.DynamicMatrix,dimension);
        MatrixOperation test;

        cout<<"first matrix"<<endl;
        test.PrintDynamicMatrix(NewMatrix.DynamicMatrix,dimension);
        cout<<"----------------------------------------------"<<endl;
    //1
        cout<<"transposed matrix"<<endl;
        test.TransposeMatrix(NewMatrix.DynamicMatrix,dimension);
        test.PrintDynamicMatrix(NewMatrix.DynamicMatrix,dimension);
        cout<<"----------------------------------------------"<<endl;
    //2
        MatrixForAdd = NewMatrix.DynamicMatrixCreate(MatrixForAdd,dimension);
        RezMatrix = NewMatrix.DynamicMatrixInit(RezMatrix,dimension);
        test.PrintDynamicMatrix(NewMatrix.DynamicMatrix,dimension);
        test.PrintDynamicMatrix(MatrixForAdd,dimension);
        cout<<"summarized matrix"<<endl;
        RezMatrix=test.AddMatrix(NewMatrix.DynamicMatrix,MatrixForAdd,dimension);
        test.PrintDynamicMatrix(RezMatrix,dimension);
        cout<<"----------------------------------------------"<<endl;
    //3
        MatrixForMul = NewMatrix.DynamicMatrixCreate(MatrixForMul,dimension);
        test.PrintDynamicMatrix(NewMatrix.DynamicMatrix,dimension);
        test.PrintDynamicMatrix(MatrixForMul,dimension);
        cout<<"multiplied matrix"<<endl;
        RezMatrix=test.MulMatrix(NewMatrix.DynamicMatrix,MatrixForMul,dimension);
        test.PrintDynamicMatrix(RezMatrix,dimension);
        cout<<"----------------------------------------------"<<endl;
    //4
        cout<<"Vinograd algorithm"<<endl;
        test.VinorgadAlg(NewMatrix.DynamicMatrix,MatrixForMul,dimension);
        cout<<"----------------------------------------------"<<endl;

    //5
        cout<<"Strassen algorithm"<<endl;
        test.ShtrassenAlg(NewMatrix.DynamicMatrix,MatrixForMul,dimension);
    }
    else cout<<"wrong dimension"<<endl;

    return 0;
}
