#include <iostream>
#include <iomanip>
using namespace std;

template <typename T>
class Matrix
{
	public:
		Matrix():matRow(0),matCol(0),matDt(0){};
		Matrix(unsigned r, unsigned c);
		Matrix(const Matrix& mat);
		
		~Matrix();
		
		unsigned getRows() const {return matRow;}
		unsigned getCols() const {return matCol;}
		void matShow(int numWidth) const;
		void matReverse(Matrix& mat);
		void matInverse(Matrix& mat);
		
		
	private:
		unsigned matRow, matCol;
		T** matDt;
		void matInit();
		void matDim(unsigned row, unsigned col);
		
};

// Initialization 
template <typename T>
inline void Matrix<T>::matInit()
{
	matRow = 0;
	matCol = 0;
	matDt = 0;
}

// Storage allocation 
template <typename T>
void Matrix<T>::matDim(unsigned row, unsigned col)
{
	matRow = row;
	matCol = col;
	
	matDt = new T* [matRow];
	T* ptmp = new T [matRow*matCol];
	for(unsigned i=0; i<matRow; ++i)
	{
		matDt[i] = &(ptmp[i*matCol]);
	}
	
//	for test
	for(unsigned i=0; i<matRow; ++i)
	{
		for(unsigned j=0; j<matCol; ++j)
		{
			matDt[i][j] = j+1;
		}
	}
}

// Constructor
template <typename T>
Matrix<T>::Matrix(unsigned r,unsigned c)
{
	matInit();
	matRow = r;
	matCol = c;
	matDim(matRow,matCol);
}

// Copy Constructor
template <typename T>
Matrix<T>::Matrix(const Matrix& mat)
{
	matInit();
	matDim(mat.matRow,mat.matCol);
//	(*this) = mat;
	for(unsigned irow=0; irow<mat.matRow; ++irow)
	{
		for(unsigned icol=0; icol<mat.matCol; ++icol)
		{
			matDt[irow][icol] = mat.matDt[irow][icol];
		}
	}
}

// Destructor
template <typename T>
Matrix<T>::~Matrix()
{
	matRow = 0;
	matCol = 0;
	delete [] *matDt;
	delete [] matDt;
	
}

// Printer
template <typename T>
void Matrix<T>::matShow(int numWidth) const
{
	for(unsigned irow = 0; irow<matRow; ++irow)
	{
		for(unsigned icol = 0; icol<matCol; ++icol)
		{
			cout << setw(numWidth) << matDt[irow][icol];
		}
		cout << endl;
	}

}

// Matrix Reverse
template <typename T>
void Matrix<T>::matReverse(Matrix& mat)
{
	
}





