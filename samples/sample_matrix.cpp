// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"


void main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Тестирование класс работы с матрицами" << endl;
	int size;
	cout << "Введите размер матрицы A: ";
	cin >> size;
	TDynamicMatrix<int> a(size);
	cout << "Введите элементы матрицы А:" << endl;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			cin >> a[i][j];
		}

	cout << "Введите размер матрицы B: ";
	cin >> size;
	TDynamicMatrix<int> b(size);
	cout << "Введите элементы матрицы B:" << endl;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			cin >> b[i][j];
		}
	int act;
	cout << endl << "1. Сложить"<<endl<< "2. Вычесть"<<endl << "3. Умножить"<< endl;
	cout << "Введите номер операции: ";
	cin >> act;
	switch (act)
	{
	case 1:
		cout << "A + B:" << endl << a + b << endl;
		break;
	case 2:
		cout << "A - B:" << endl << a - b << endl;
		break;
	case 3:
		cout << "A * B:" << endl << a * b << endl;
		break;
	default:
		break;
	}
}

