#include <iostream>

class Matrix
{
	public:
		Matrix():matRow(0),matCol(0),matDt(0){};
		Matrix(unsigned r, unsigned c);
		Matrix(const Matrix& mat);
		
		~Matrix();
		
		unsigned getRows() const {return matRow;}
		unsigned getCols() const {return matCol;}
//		T* operator ()(unsigned row, unsigned col);
		bool operator ==(const Matrix &);
		Matrix operator +(const Matrix &);
		Matrix operator -(const Matrix &);
		Matrix & operator =(const Matrix &);
		Matrix operator *(const Matrix &);
		friend std::ostream & operator <<(std::ostream &, const Matrix &);
		friend std::istream & operator >>(std::istream &, Matrix &);
		
	private:
		unsigned matRow, matCol;
		double** matDt;
		inline void matInit(){matRow = 0; matCol = 0; matDt = 0;};
		void matDim(unsigned row, unsigned col);
		
};


