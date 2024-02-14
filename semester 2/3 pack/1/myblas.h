#pragma once
# pragma once
//====== уровень 1 ======
// (все векторы длины n)

//скопировать вектор из X в Y
void dcopy(int n, const double* X, double* Y);

//обмен€ть местами содержимое векторов X и Y
void dswap(int n, double* X, double* Y);

//домножить вектор X на коэффициент alpha
void dscal(int n, double alpha, double* X);

//прибавить к вектору Y вектор X, умноженный на коэффициент alpha
void daxpy(int n, double alpha, const double* X, double* Y);

//вычислить скал€рное произведение векторов X и Y
double ddot(int n, const double* X, const double* Y);
//====== уровень 2 ======
//вычислить вектор (alpha*A*X + beta*Y) длины m, и записать его в Y
//здесь A Ц- матрица размера m на n, X Ц- вектор длины n, а Y Ц- вектор длины m
void dgemv(
	int m, int n,
	double alpha, const double* A, const double* X,
	double beta, double* Y
);

//вычислить матрицу (alpha*X*Yt + A) и записать еЄ в A
//здесь Yt Ц- это транспонированный вектор Y, то есть записанный как вектор-строка
// A Ц- матрица размера m на n, X Ц- вектор длины m, а Y Ц- вектор длины n
void dger(
	int m, int n,
	double alpha, const double* X, const double* Y,
	double* A
);

//====== уровень 3 ======
//вычислить матрицу (alpha*A*B + beta*C) и записать еЄ в C
//здесь A Ц- матрица размера m на k, B Ц- матрица размера k на n,
// C Ц- матрица размера m на n
void dgemm(
	int m, int n, int k,
	double alpha, const double* A, const double* B,
	double beta, double* C
);
