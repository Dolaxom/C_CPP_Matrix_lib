#include "s21_matrix.h"

/*
 * CONSTRUCTORS && DESTRUCTOR
*/

S21Matrix::S21Matrix()
{
    _rows = 0;
    _columns = 0;
    _matrix = nullptr;
}

S21Matrix::S21Matrix(int rows, int columns)
{
    this->_rows = rows;
    this->_columns = columns;

    S21MemoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix &other)
{
    S21CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
{
    S21CopyMatrix(other);
    other.S21FreeMatrix();
}

S21Matrix::~S21Matrix()
{
    S21FreeMatrix();
}

/*
 * OPERATORS
*/

double& S21Matrix::operator()(int i, int j)
{
    assert(i < _rows && j < _columns);

    return _matrix[i][j];
}

S21Matrix S21Matrix::operator=(const S21Matrix &other)
{
    if (_matrix != nullptr)
    {
        S21FreeMatrix();
    }
    this->S21CopyMatrix(other);

    return *this;
}

bool S21Matrix::operator==(const S21Matrix &other)
{
    if (other._rows == _rows && other._columns == _columns)
    {
        if (this->S21EqMatrix(other)) return true;
    }

    return false;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other)
{
    assert(other._rows == _rows && other._columns == _columns);

    S21Matrix MatrixTmp(*this);
    MatrixTmp.S21SumMatrix(other);

    return MatrixTmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other)
{
    assert(other._rows == _rows && other._columns == _columns);

    S21Matrix MatrixTmp(*this);
    MatrixTmp.S21SubMatrix(other);

    return MatrixTmp;
}

S21Matrix S21Matrix::operator*(double other)
{
    S21Matrix MatrixTmp(*this);
    MatrixTmp.S21MulNumber(other);

    return MatrixTmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other)
{
    assert(_columns == other._rows);

    S21Matrix MatrixTmp(*this);
    return MatrixTmp.S21MulMatrix(other);
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other)
{
    assert(other._rows == _rows && other._columns == _columns);

    S21SumMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other)
{
    assert(other._rows == _rows && other._columns == _columns);

    S21SubMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator*=(double other)
{
    S21MulNumber(other);

    return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other)
{
    assert(_columns == other._rows);
    S21Matrix MatrixTmp(*this);
    *this = MatrixTmp.S21MulMatrix(other);
    return *this;
}

S21Matrix S21Matrix::S21Transpose() {
    S21Matrix ResultMatrix(this->_columns, this->_rows);
    for (int i = 0; i < ResultMatrix._rows; i++)
    {
        for (int j = 0; j < ResultMatrix._columns; j++)
        {
            ResultMatrix._matrix[i][j] = this->_matrix[j][i];
        }
    }

    return ResultMatrix;
}

S21Matrix S21Matrix::S21CalcComplements() {
    S21Matrix ResultMatrix(this->_columns, this->_rows);
    S21Matrix Buffer(this->_columns, this->_rows);
    Buffer = S21MinorMatrix();
    ResultMatrix = Buffer.S21ChessSignMatrix();

    return ResultMatrix;
}

double S21Matrix::S21Determinant() {
    assert(_rows == _columns);
    S21Matrix Buffer(this->_columns, this->_rows);
    double Result = 0.0;

    if (_rows == 1) {
        Result = _matrix[0][0];
    } else if (_rows == 2) {
        Result = S21DeterminantSimple2X2();
    } else if (_rows == 3) {
        Buffer = S21CalcComplements();
        for (int j = 0; j < _rows; j++) {
            Result += _matrix[0][j] * Buffer._matrix[0][j];
        }

    } else {
        double Det = 0.0f;
        for (int j = 0; j < _rows; j++) {
            Buffer.S21MinorElement(0, j);
            Det = Buffer.S21Determinant();
            Det *= _matrix[0][j];
            if (j % 2) {
                Result -= Det;
            } else {
                Result += Det;
            }
        }
    }

    return Result;
}


/*
 * HELPERS
*/

bool S21Matrix::S21MemoryAllocation()
{
    if (_rows < 1 || _columns < 1)
    {
        return false;
    }

    _matrix = new double *[_rows];
    for (int i = 0; i < _rows; i++)
    {
        _matrix[i] = new double[_columns];
    }
    S21ZeroedMatrix();

    return true;
}

void S21Matrix::S21FreeMatrix()
{
    for (int i = 0; i < _rows; i++)
    {
        delete []_matrix[i];
    }
    delete []_matrix;

    _columns = 0;
    _rows = 0;
    _matrix = nullptr;
}

bool S21Matrix::S21EqMatrix(const S21Matrix &other) const
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            if (fabs(_matrix[i][j] - other._matrix[i][j]) > EPS)
            {
                return false;
            }
        }
    }

    return true;
}

void S21Matrix::S21CopyMatrix(const S21Matrix &other)
{
    this->_rows = other._rows;
    this->_columns = other._columns;
    S21MemoryAllocation();
    for (int i = 0; i < other._rows; i++)
    {
        for (int j = 0; j < other._columns; j++)
        {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}

void S21Matrix::S21ZeroedMatrix()
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            this->_matrix[i][j] = 0.0;
        }
    }
}

void S21Matrix::S21SumMatrix(const S21Matrix &other)
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            _matrix[i][j] += other._matrix[i][j];
        }
    }
}

void S21Matrix::S21SubMatrix(const S21Matrix &other)
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            _matrix[i][j] -= other._matrix[i][j];
        }
    }
}

void S21Matrix::S21MulNumber(double other)
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            _matrix[i][j] *= other;
        }
    }
}

S21Matrix S21Matrix::S21MulMatrix(const S21Matrix &other)
{
    S21Matrix ResultMatrix(_rows, other._columns);

    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < other._columns; j++)
        {
            for (int k = 0; k < other._rows; k++)
            {
                ResultMatrix._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
            }
        }
    }
    return ResultMatrix;
}

void S21Matrix::S21OutputMatrix() const
{
    std::cout << "Output matrix(" << _rows << ", " << _columns << ")\n";
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            std::cout << _matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

S21Matrix S21Matrix::S21MinorElement(int row, int column) {
    int ResultRows = this->_rows - 1;
    int ResultColumns = this->_columns - 1;
    S21Matrix ResultMatrix(ResultRows, ResultColumns);
    ResultRows = 0;
    ResultColumns = 0;

    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_columns; j++) {
            if (i == row || j == column) continue;
            ResultMatrix._matrix[ResultRows][ResultColumns] = this->_matrix[i][j];
            ResultColumns++;
        }
        if (i != row) ResultRows++;
        ResultColumns = 0;
    }

    return ResultMatrix;
}

S21Matrix S21Matrix::S21MinorMatrix() {
    S21Matrix ResultMatrix(this->_rows, this->_columns);
    S21Matrix Buffer(this->_rows, this->_columns);
    double det = 0.0;
    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_columns; j++) {
            Buffer = S21MinorElement(i, j);
            double Det = Buffer.S21Determinant();
            ResultMatrix._matrix[i][j] = Det;
//            Buffer.S21FreeMatrix();
        }
    }

    return ResultMatrix;
}

S21Matrix S21Matrix::S21ChessSignMatrix() {
    S21Matrix ResultMatrix(this->_rows, this->_columns);
    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_columns; j++) {
            ResultMatrix._matrix[i][j] = this->_matrix[i][j] * pow(-1, (i+j));
        }
    }

    return ResultMatrix;
}

double S21Matrix::S21DeterminantSimple2X2() {
    return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
}
