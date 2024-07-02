#include <iostream>
#pragma warning(disable:4996)
using namespace std;
const int N = 100;
int T = 0;
void ob(int A[N][N], int B[N][N], int C[N][N])
{
	int i, j, k;
	T = 0;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (k = 0; k < N; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
				T++;
			}
		}
	}
}

void add_sub(int** A, int** B, int** c, int n, bool f)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (f)
				c[i][j] = A[i][j] + B[i][j];
			else
				c[i][j] = A[i][j] - B[i][j];
		}
	}
}

void strassen(int** A, int** B, int** C, int n)
{
	int i, j, k, hn = n / 2, ** a, ** b, M[7],
		** M1, ** M2, ** M3, ** M4, ** M5, ** M6, ** M7,
		** A11, ** A12, ** A21, ** A22,
		** B11, ** B12, ** B21, ** B22,
		** C11, ** C12, ** C21, ** C22;
	a = new int* [n]; b = new int* [n];
	M1 = new int* [n]; M2 = new int* [n]; M3 = new int* [n]; M4 = new int* [n];
	M5 = new int* [n]; M6 = new int* [n]; M7 = new int* [n];
	A11 = new int* [n]; A12 = new int* [n]; A21 = new int* [n]; A22 = new int* [n];
	B11 = new int* [n]; B12 = new int* [n]; B21 = new int* [n]; B22 = new int* [n];
	C11 = new int* [n]; C12 = new int* [n]; C21 = new int* [n]; C22 = new int* [n];
	for (i = 0; i < n; i++)
	{
		a[i] = new int[n]; b[i] = new int[n];
		M1[i] = new int[n]; M2[i] = new int[n]; M3[i] = new int[n]; M4[i] = new int[n];
		M5[i] = new int[n]; M6[i] = new int[n]; M7[i] = new int[n];
		A11[i] = new int[n]; A12[i] = new int[n]; A21[i] = new int[n]; A22[i] = new int[n];
		B11[i] = new int[n]; B12[i] = new int[n]; B21[i] = new int[n]; B22[i] = new int[n];
		C11[i] = new int[n]; C12[i] = new int[n]; C21[i] = new int[n]; C22[i] = new int[n];
	}



	//if (n <= 2)
	if (n < 2)
	{
		/*M[0] = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
		M[1] = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
		M[2] = (A[0][0] - A[1][0]) * (B[0][0] + B[0][1]);
		M[3] = (A[0][0] + A[0][1]) * B[1][1];
		M[4] = A[0][0] * (B[0][1] - B[1][1]);
		M[5] = A[1][1] * (B[1][0] - B[0][0]);
		M[6] = (A[1][0] + A[1][1]) * B[0][0];

		C[0][0] = M[0] + M[1] - M[3] + M[5];
		C[0][1] = M[3] + M[4];
		C[1][0] = M[5] + M[6];
		C[1][1] = M[1] - M[2] + M[4] - M[6];*/
		C[0][0] = A[0][0] * B[0][0];
	}
	else
	{
		for (i = 0; i < hn; i++)
		{
			for (j = 0; j < hn; j++)
			{
				A11[i][j] = A[i][j];
				A12[i][j] = A[i][j + hn];
				A21[i][j] = A[i + hn][j];
				A22[i][j] = A[i + hn][j + hn];

				B11[i][j] = B[i][j];
				B12[i][j] = B[i][j + hn];
				B21[i][j] = B[i + hn][j];
				B22[i][j] = B[i + hn][j + hn];
			}
		}
		add_sub(A12, A22, a, hn, false);
		add_sub(B21, B22, b, hn, true);
		strassen(a, b, M1, hn);
		T++;

		add_sub(A11, A22, a, hn, true);
		add_sub(B11, B22, b, hn, true);
		strassen(a, b, M2, hn);
		T++;

		add_sub(A11, A21, a, hn, false);
		add_sub(B11, B12, b, hn, true);
		strassen(a, b, M3, hn);
		T++;

		add_sub(A11, A12, a, hn, true);
		strassen(a, B22, M4, hn);
		T++;

		add_sub(B12, B22, b, hn, false);
		strassen(A11, b, M5, hn);
		T++;

		add_sub(B21, B11, b, hn, false);
		strassen(A22, b, M6, hn);
		T++;

		add_sub(A21, A22, a, hn, true);
		strassen(a, B11, M7, hn);
		T++;



		add_sub(M1, M2, a, hn, true);
		add_sub(a, M4, b, hn, false);
		add_sub(b, M6, C11, hn, true);

		add_sub(M4, M5, C12, hn, true);

		add_sub(M6, M7, C21, hn, true);

		add_sub(M2, M3, a, hn, false);
		add_sub(a, M5, b, hn, true);
		add_sub(b, M7, C22, hn, false);

		for (i = 0; i < hn; i++)
		{
			for (j = 0; j < hn; j++)
			{
				C[i][j] = C11[i][j];
				C[i][j + hn] = C12[i][j];
				C[i + hn][j] = C21[i][j];
				C[i + hn][j + hn] = C22[i][j];
			}
		}
	}



	for (i = 0; i < n; i++)
	{
		delete[] a[i]; delete[] b[i];
		delete[] M1[i]; delete[] M2[i]; delete[] M3[i]; delete[] M4[i];
		delete[] M5[i]; delete[] M6[i]; delete[] M7[i];
		delete[] A11[i]; delete[] A12[i]; delete[] A21[i]; delete[] A22[i];
		delete[] B11[i]; delete[] B12[i]; delete[] B21[i]; delete[] B22[i];
		delete[] C11[i]; delete[] C12[i]; delete[] C21[i]; delete[] C22[i];
	}
	delete[] a; delete[] b;
	delete[] M1; delete[] M2; delete[] M3; delete[] M4;
	delete[] M5; delete[] M6; delete[] M7;
	delete[] A11; delete[] A12; delete[] A21; delete[] A22;
	delete[] B11; delete[] B12; delete[] B21; delete[] B22;
	delete[] C11; delete[] C12; delete[] C21; delete[] C22;
}

int main()
{
	FILE* f;
	setlocale(LC_ALL, "Russian");
	int i, j, M, A[N][N], B[N][N], C1[N][N] = { 0 }, ** A2, ** B2, ** C2;

	for (M = 1; M < N; M *= 2);
	A2 = new int* [M];
	B2 = new int* [M];
	C2 = new int* [M];
	for (i = 0; i < M; i++)
	{
		A2[i] = new int[M];
		B2[i] = new int[M];
		C2[i] = new int[M];
	}

	for (i = 0; i < M; i++)
	{
		for (j = 0; j < M; j++)
		{
			A2[i][j] = 0;
			B2[i][j] = 0;
		}
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] = pow(-1, (i + j));
			B[i][j] = i - j;
			A2[i][j] = pow(-1, (i + j));
			B2[i][j] = i - j;
		}
	}

	f = fopen("file.txt", "w");
	//cout << " A:\n";
	fprintf(f, "A:\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			//cout << " " << A[i][j];
			fprintf(f, " %d", A[i][j]);
		//cout << endl;
		fprintf(f, "\n");
	}
	//cout << "\n B:\n";
	fprintf(f, "\n B:\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			//cout << " " << B[i][j];
			fprintf(f, " %d", B[i][j]);
		//cout << endl;
		fprintf(f, "\n");
	}

	ob(A, B, C1);
	//cout << "\n C:\n";
	fprintf(f, "\n C (ob):\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			//cout << " " << C1[i][j];
			fprintf(f, " %d", C1[i][j]);
		//cout << endl;
		fprintf(f, "\n");
	}
	fprintf(f, " Tr: T = %d", T);
	cout << " Трудоемкость: T = " << T;

	T = 0;
	strassen(A2, B2, C2, M);
	//cout << "\n\n C: " << endl;
	fprintf(f, "\n\n C (str):\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			//cout << " " << C2[i][j];
			fprintf(f, " %d", C2[i][j]);
		//cout << endl;
		fprintf(f, "\n");
	}
	fprintf(f, " Tr: T = %d", T);
	cout << "\n Трудоемкость: T = " << T;



	for (i = 0; i < M; i++)
	{
		delete[] A2[i];
		delete[] B2[i];
		delete[] C2[i];
	}
	delete[] A2;
	delete[] B2;
	delete[] C2;
	fclose(f);
	return 0;
}