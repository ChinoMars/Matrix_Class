template <typename T>
class Matrix
{
	public:
		Matrix(unsigned, unsigned);
		Matrix(unsigned r, unsigned c):matRow(r),matCol(c){};
		Matrix(const Matrix& mat);
		
		~Matrix();
				
	private:
		unsigned matRow, matCol;
		T** matDt;
		void matInit();
		void matDim(unsigned row, unsigned col);
			
}

template <typename T>
Matrix<T>::matInit()
{
	matRow = 0;
	matCol = 0;
	matDt = 0;
}

template <typename T>
Matrix<T>::matDim(unsigned row, unsigned col)
{
	matRow = row;
	matCol = col;
	
	matDt = new T* [matRow];
	T* ptmp = new T [matRow*matCol];
	for(unsigned i=0; i<matRow; ++i)
	{
		matDt = &(ptmp[i*matCol]);
	}	
}

