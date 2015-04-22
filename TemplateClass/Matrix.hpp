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
//		T* operator ()(unsigned row, unsigned col);
		bool operator ==(const Matrix &);
		Matrix operator +(const Matrix &);
		Matrix operator -(const Matrix &);
		Matrix & operator =(const Matrix &);
		Matrix operator *(const Matrix &);
	    template <typename C>
		friend ostream &operator << (ostream &, const Matrix<C> &);
		template <typename C>
		friend istream &operator >> (istream &, Matrix<C> &);
		
	private:
		unsigned matRow, matCol;
		T** matDt;
		void matInit();
		void matDim(unsigned row, unsigned col);
		
};

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
	for(unsigned i = 0; i < matRow; ++i)
	{
		delete [] matDt[i];
	}
	delete [] matDt;
	
}

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
	for(unsigned i=0; i<matRow; ++i)
	{
		matDt[i] = new T [matCol];
	}
	
//	Initialized to Zeros
	for(unsigned i=0; i<matRow; ++i)
	{
		for(unsigned j=0; j<matCol; ++j)
		{
			matDt[i][j] = 1;
//			matDt[i][j] = i*matCol+j+1; // for test
		}
	}
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

// Operator "==" overload
template <typename T>
bool Matrix<T>::operator ==(const Matrix &mat)
{
	if(matRow==mat.getRows() && matCol==mat.getCols())
	{
		for(unsigned i = 0; i < matRow; ++i)
		{
			for(unsigned j = 0; j < matCol; ++j)
			{
				if(matDt[i][j] != mat.matDt[i][j]) return false;
			}
		}
		return true;
	}
	else return false;
}

// Operator "+" overload
template <typename T>
Matrix<T> Matrix<T>::operator +(const Matrix &mat)
{
	if(matRow==mat.matRow && matCol==mat.matCol)
	{
		Matrix<T> matTmp(matRow,matCol);
		for(unsigned irow = 0; irow < matRow; ++irow)
		{
			for(unsigned icol = 0; icol < matCol; ++icol) 
				matTmp.matDt[irow][icol] = matDt[irow][icol]+mat.matDt[irow][icol];
		}
		return matTmp;
	}
	else return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator -(const Matrix &mat)
{
	if(matRow==mat.matRow && matCol==mat.matCol)
	{
		Matrix<T> matTmp(matRow,matCol);
		for(unsigned irow = 0; irow < matRow; ++irow)
		{
			for(unsigned icol = 0; icol < matCol; ++icol) 
				matTmp.matDt[irow][icol] = matDt[irow][icol]-mat.matDt[irow][icol];
		}
		return matTmp;
	}
	else return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator =(const Matrix &mat)
{
	if((*this)==mat) return (*this);
	else
	{
		delete [] matDt[0];
		delete [] matDt;
		matRow = mat.matRow;
		matCol = mat.matCol;
		matDim(mat.matRow,mat.matCol);
		for(unsigned i = 0; i < matRow; ++i)
		{
			for(unsigned j = 0; j < matCol; ++j)
			{
				matDt[i][j] = mat.matDt[i][j];
			}
		}
		return *this;
	}
}

// Operator "*" overload
template <typename T>
Matrix<T> Matrix<T>::operator *(const Matrix &mat)
{
	if(matRow==mat.matCol && matCol==mat.matRow)
	{
		Matrix<T> matTmp(matRow,mat.matCol);
		for(unsigned irow = 0; irow < matRow; ++irow)
		{
			for(unsigned icol = 0; icol < mat.matCol; ++icol)
			{
				matTmp.matDt[irow][icol] = 0;
				for(unsigned index = 0; index < matCol; ++index) 
					matTmp.matDt[irow][icol] += matDt[irow][index]*mat.matDt[index][icol];
			}
		}
		return matTmp;
	}
	else return *this;
}

template <typename T>
ostream &operator <<(ostream &os, const Matrix<T> &mat)
{
	for(unsigned irow = 0; irow<mat.matRow; ++irow)
	{
		for(unsigned icol = 0; icol<mat.matCol; ++icol)
		{
			os << " " << mat.matDt[irow][icol];
		}
		os << "\n";
	}
	
	return os;
}

template <typename T>
istream &operator >>(istream &in, Matrix<T> &mat)
{
	for(unsigned irow = 0; irow<mat.matRow; ++irow)
	{
		for(unsigned icol = 0; icol<mat.matCol; ++icol)
		{
			in >> mat.matDt[irow][icol];
		}
	}
	
	return in;
}

