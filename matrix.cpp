#include <iostream>
#include "matrix.h"
#include <stdlib.h>

void MatrixOperation::PrintDynamicMatrix(int **arr,int dimension){
    for(int i = 0; i < dimension; i++) {
		for(int j = 0; j < dimension; j++) {
			cout <<arr[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void MatrixOperation::TransposeMatrix(int **arr,int dimension){
    int temp = 0;
    for(int i = 0 ;i< dimension; i++){
		for(int j=i+1; j< dimension; j++){
			temp =arr[i][j];
			arr[i][j]=arr[j][i];
			arr[j][i]= temp;

		}
	}
}

int** MatrixOperation::AddMatrix(int **arr_1,int **arr_2,int dimension){
    int ** TempMatrix =0;
    TempMatrix = Matrix::DynamicMatrixInit(TempMatrix,dimension);
    for(int i = 0;i< dimension; i++){
		for(int j=0; j< dimension; j++){
			TempMatrix[i][j]=arr_2[i][j]+arr_1[i][j];
		}
	}
    return TempMatrix;
    for(int i=0;i<dimension;i++){
        delete [] TempMatrix[i];
	}
}

int** MatrixOperation::SubtrMatrix(int **arr_1,int **arr_2,int dimension){
    int ** TempMatrix =0;
    TempMatrix = Matrix::DynamicMatrixInit(TempMatrix,dimension);
    for(int i = 0;i< dimension; i++){
		for(int j=0; j< dimension; j++){
			TempMatrix[i][j]=arr_2[i][j]-arr_1[i][j];
		}
	}
    return TempMatrix;
    for(int i=0;i<dimension;i++){
        delete [] TempMatrix[i];
	}
}
int** MatrixOperation::MulMatrix(int **arr_1,int **arr_2,int dimension){
    int ** TempMatrix =0;
    TempMatrix = Matrix::DynamicMatrixInit(TempMatrix,dimension);
    int shift=0,temp=0;
    for(int j=0;j<dimension;j++){
        shift=0;
        while(shift < dimension){
            for(int i=0; i < dimension; i++){
                temp+=arr_1[j][i]*arr_2[i][shift];
            }
            TempMatrix[j][shift]=temp;
            shift++;
            temp=0;
        }
    }
    return TempMatrix;
    for(int i=0;i<dimension;i++){
        delete [] TempMatrix[i];
    }
}

void MatrixOperation::VinorgadAlg(int **arr_1, int **arr_2,int dimension){
    int ** TempMatrix =0;
    TempMatrix = Matrix::DynamicMatrixInit(TempMatrix,dimension);
    TempMatrix=MatrixOperation::MulMatrix(arr_1,arr_2,dimension); // не доделан алгоритм, обычное умножение
    MatrixOperation::PrintDynamicMatrix(TempMatrix,dimension);
     for(int i=0;i<dimension;i++){
        delete [] TempMatrix[i];
    }
}

int **MatrixOperation::CopyDynamicMatrix(int **arr_1,int **arr_2,int pos1X1,int pos1Y1,int pos1X2,int pos1Y2,int pos2X,int pos2Y){
          int columns=pos2X,rows=pos2Y;
            for(int i = pos1Y1;i< pos1Y2; i++){
                for(int j = pos1X1; j< pos1X2; j++){
                    arr_2[rows][columns]=arr_1[i][j];
                    columns++;
                }
                rows++;
                columns=pos2X;
            }
    return arr_2;
}


void MatrixOperation::ShtrassenAlg(int **arr_1, int **arr_2,int dimension){
    int **NewMatrix=0,**TempMatrix=0;
    int **A[4];
    int **B[4];
    int **m[7];
    int **C[4];
    int NewSize=2;
    while(NewSize<dimension){
        NewSize*=2;
    }
    NewMatrix = Matrix::DynamicMatrixInit(NewMatrix,NewSize);
    NewMatrix = Matrix::DynamicMatrixFillNull(NewMatrix,NewSize);
    TempMatrix = Matrix::DynamicMatrixInit(TempMatrix,NewSize/2);
    TempMatrix = Matrix::DynamicMatrixFillNull(TempMatrix,NewSize/2);

    for(int i=0;i<7;i++){
        m[i] = Matrix::DynamicMatrixInit(m[i],NewSize/2);
        m[i] = Matrix::DynamicMatrixFillNull(m[i],NewSize/2);
    }
    for(int i=0;i<4;i++){
        C[i] = Matrix::DynamicMatrixInit(C[i],NewSize/2);
        C[i] = Matrix::DynamicMatrixFillNull(C[i],NewSize/2);
    }
    for(int i=0;i<4;i++){
        A[i]=Matrix::DynamicMatrixInit(A[i],NewSize/2);
        B[i]=Matrix::DynamicMatrixInit(B[i],NewSize/2);
    }
    NewMatrix=MatrixOperation::CopyDynamicMatrix(arr_1,NewMatrix,0,0,dimension,dimension,0,0);

    A[0]=MatrixOperation::CopyDynamicMatrix(NewMatrix,A[0],0,0,NewSize/2,NewSize/2,0,0);
    A[1]=MatrixOperation::CopyDynamicMatrix(NewMatrix,A[1],NewSize/2,0,NewSize,NewSize/2,0,0);
    A[2]=MatrixOperation::CopyDynamicMatrix(NewMatrix,A[2],0,NewSize/2,NewSize/2,NewSize,0,0);
    A[3]=MatrixOperation::CopyDynamicMatrix(NewMatrix,A[3],NewSize/2,NewSize/2,NewSize,NewSize,0,0);

    NewMatrix = Matrix::DynamicMatrixFillNull(NewMatrix,NewSize);
    NewMatrix=MatrixOperation::CopyDynamicMatrix(arr_2,NewMatrix,0,0,dimension,dimension,0,0);

    B[0]=MatrixOperation::CopyDynamicMatrix(NewMatrix,B[0],0,0,NewSize/2,NewSize/2,0,0);
    B[1]=MatrixOperation::CopyDynamicMatrix(NewMatrix,B[1],NewSize/2,0,NewSize,NewSize/2,0,0);
    B[2]=MatrixOperation::CopyDynamicMatrix(NewMatrix,B[2],0,NewSize/2,NewSize/2,NewSize,0,0);
    B[3]=MatrixOperation::CopyDynamicMatrix(NewMatrix,B[3],NewSize/2,NewSize/2,NewSize,NewSize,0,0);

        /** begin alg  **/
    //m1=(A11+A22)*(B11+B22)
    m[0]=MatrixOperation::AddMatrix(A[0],A[3],NewSize/2);
    TempMatrix=MatrixOperation::AddMatrix(B[0],B[3],NewSize/2);
    m[0]=MatrixOperation::MulMatrix(m[0],TempMatrix,NewSize/2);
    // m2=(A21+A22)*B11
    m[1]=MatrixOperation::AddMatrix(A[2],A[3],NewSize/2);
    m[1]=MatrixOperation::MulMatrix(m[1],B[0],NewSize/2);
    //m3=A11*(B12-B22)
    m[2]=MatrixOperation::SubtrMatrix(B[3],B[1],NewSize/2);
    m[2]=MatrixOperation::MulMatrix(A[0],m[2],NewSize/2);
    // m4=A22*(B21-B11)
    m[3]=MatrixOperation::SubtrMatrix(B[0],B[2],NewSize/2);
    m[3]=MatrixOperation::MulMatrix(A[3],m[3],NewSize/2);
    // m5=(A11+A12)*B22
    m[4]=MatrixOperation::AddMatrix(A[0],A[1],NewSize/2);
    m[4]=MatrixOperation::MulMatrix(m[4],B[3],NewSize/2);
    // m6=(A21-A11)*(B11+B12)
    m[5]=MatrixOperation::SubtrMatrix(A[0],A[2],NewSize/2);
    TempMatrix = MatrixOperation::AddMatrix(B[0],B[1],NewSize/2);
    m[5]=MatrixOperation::MulMatrix(m[5],TempMatrix,NewSize/2);
    /* m7=(A12-A22)*(B21+B22)*/
    m[6]=MatrixOperation::SubtrMatrix(A[3],A[1],NewSize/2);
    TempMatrix=MatrixOperation::AddMatrix(B[2],B[3],NewSize/2);
    m[6]=MatrixOperation::MulMatrix(m[6],TempMatrix,NewSize/2);
    //********************************************************
    /*C11=M1+M4-M5+M7*/
    C[0]=MatrixOperation::AddMatrix(m[0],m[3],NewSize/2);
    C[0]=MatrixOperation::SubtrMatrix(m[4],C[0],NewSize/2);
    C[0]=MatrixOperation::AddMatrix(C[0],m[6],NewSize/2);
    /*C12=M3+M5*/
    C[1]=MatrixOperation::AddMatrix(m[2],m[4],NewSize/2);
    /*C21=M2+M4*/
    C[2]=MatrixOperation::AddMatrix(m[1],m[3],NewSize/2);
    /*C22=M1-M2+M3+M6*/
    C[3]= MatrixOperation::SubtrMatrix(m[1],m[0],NewSize/2);
    C[3]=MatrixOperation::AddMatrix(C[3],m[2],NewSize/2);
    C[3]=MatrixOperation::AddMatrix(m[5],C[3],NewSize/2);

    NewMatrix=Matrix::DynamicMatrixFillNull(NewMatrix,NewSize);
    NewMatrix=MatrixOperation::CopyDynamicMatrix(C[0],NewMatrix,0,0,NewSize/2,NewSize/2,0,0);
    NewMatrix=MatrixOperation::CopyDynamicMatrix(C[1],NewMatrix,0,0,NewSize/2,NewSize/2,NewSize/2,0);
    NewMatrix=MatrixOperation::CopyDynamicMatrix(C[2],NewMatrix,0,0,NewSize/2,NewSize/2,0,NewSize/2);
    NewMatrix=MatrixOperation::CopyDynamicMatrix(C[3],NewMatrix,0,0,NewSize/2,NewSize/2,NewSize/2,NewSize/2);


    MatrixOperation::PrintDynamicMatrix(NewMatrix,NewSize);

    for(int i=0;i<4;i++){
        delete [] A[i];
        delete [] B[i];
        delete [] C[i];
    }
    for(int i=0;i<7;i++){
        delete [] m[i];
       }
    for(int i=0;i<NewSize;i++){
        delete [] NewMatrix[i];
    }
    for(int i=0;i<NewSize/2;i++){
        delete [] TempMatrix[i];
    }

}

int** Matrix::DynamicMatrixInit(int **arr,int dimension){
         arr = new int*[dimension];
        for(int i=0;i< dimension;i++){
            arr[i]= new int[dimension];
        }
        return arr;
}

int** Matrix::DynamicMatrixFill(int **arr,int dimension){
    for(int i = 0;i<dimension; i++){
            for(int j=0;j<dimension;j++){
                arr[i][j]= rand() %3;
            }
        }
        return arr;
}

int** Matrix::DynamicMatrixCreate(int **arr,int dimension){
        if(dimension >= 2){
        arr = Matrix::DynamicMatrixInit(arr,dimension);
        arr = Matrix::DynamicMatrixFill(arr,dimension);
        }
        return arr;
}

int** Matrix::DynamicMatrixFillNull(int **arr,int dimension){
    for(int i = 0;i<dimension; i++){
            for(int j=0;j<dimension;j++){
                arr[i][j]=0;
            }
        }
        return arr;
}
