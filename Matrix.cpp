#include "Matrix.h"
using namespace std;

Matrix::Matrix(unsigned r, unsigned c)
{
	matInit();
	matRow = r;
	matCol = c;
	matDim(matRow,matCol);
}

Matrix::Matrix(const Matrix& mat)
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

Matrix::~Matrix()
{
	matRow = 0;
	matCol = 0;
	delete [] *matDt;
	delete [] matDt;
}


void Matrix::matDim(unsigned row, unsigned col)
{
	matRow = row;
	matCol = col;
	
	matDt = new double* [matRow];
	double* ptmp = new double [matRow*matCol];
	for(unsigned i=0; i<matRow; ++i)
	{
		matDt[i] = &(ptmp[i*matCol]);
	}
	
	for(unsigned i=0; i<matRow; ++i)
	{
		for(unsigned j=0; j<matCol; ++j)
		{
			matDt[i][j] = 0;
			matDt[i][j] = 1; // for test
		}
	}
}

bool Matrix::operator ==(const Matrix &mat)
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

Matrix Matrix::operator +(const Matrix &mat)
{
	if(matRow==mat.matRow && matCol==mat.matCol)
	{
		Matrix matTmp(matRow,matCol);
		for(unsigned irow = 0; irow < matRow; ++irow)
		{
			for(unsigned icol = 0; icol < matCol; ++icol) 
				matTmp.matDt[irow][icol] = matDt[irow][icol]+mat.matDt[irow][icol];
		}
		return matTmp;
	}
	else return *this;
}

Matrix Matrix::operator -(const Matrix &mat)
{
	if(matRow==mat.matRow && matCol==mat.matCol)
	{
		Matrix matTmp(matRow,matCol);
		for(unsigned irow = 0; irow < matRow; ++irow)
		{
			for(unsigned icol = 0; icol < matCol; ++icol) 
				matTmp.matDt[irow][icol] = matDt[irow][icol]-mat.matDt[irow][icol];
		}
		return matTmp;
	}
	else return *this;
}

Matrix & Matrix::operator =(const Matrix &mat)
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

Matrix Matrix::operator *(const Matrix &mat)
{
	if(matRow==mat.matCol && matCol==mat.matRow)
	{
		Matrix matTmp(matRow,mat.matCol);
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

ostream & operator <<(ostream & os, const Matrix &mat)
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

istream & operator >>(istream &in, Matrix &mat)
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

