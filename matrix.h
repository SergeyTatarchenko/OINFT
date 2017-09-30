using namespace std;

class Matrix{
    public:
        int **DynamicMatrix;
        int **DynamicMatrixCreate(int **arr,int dimension);
        int **DynamicMatrixInit(int **arr,int dimension);
        int **DynamicMatrixFill(int **arr,int dimension);
        int **DynamicMatrixFillNull(int **arr,int dimension);
};

class MatrixOperation : public Matrix {
    public:
        int **CopyDynamicMatrix(int **arr_1,int **arr_2,int posX1,int posY1,int posX2,int posY2,int pos2X,int pos2Y);
        void PrintDynamicMatrix(int **arr,int dimension);
        void TransposeMatrix(int **arr, int dimension);
        int** AddMatrix(int **arr_1,int **arr_2,int dimension);
        int** SubtrMatrix(int **arr_1,int **arr_2,int dimension);
        int** MulMatrix(int **arr_1, int **arr_2,int dimension);
        void VinorgadAlg(int **arr_1, int **arr_2,int dimension);
        void ShtrassenAlg(int **arr_1, int **arr_2,int dimension);
};
