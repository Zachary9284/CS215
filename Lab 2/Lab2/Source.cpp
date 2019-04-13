// Author: Zachary Lee
// Date: 1/23/2019
// Description: My second C++ program. It Sorts 3 numbers for lowest 
//to greatest and also tells you the value of Scovilles of heat on each 
//listed pepper
//---------------------------------------------------------------------

#include <iostream> 
#include <string>
using namespace std;
int main()
{
	cout << "+--------------------------------------------+\n";
	cout << "|     0       Vv          0       (v   v)    |\n";
	cout << "|   o=|=o    (  )>      o=|=o   o==|___|==o  |\n";
	cout << "|    | |    [    ]       | |        | |      |\n";
	cout << "|            |_|_            By: Zachary Lee |\n";
	cout << "+--------------------------------------------+\n";

	int Num1, Num2, Num3, Low, Mid, High;
	Low = 0;
	Mid = 0;
	High = 0;
	string Pepper;
	cout << "Enter number 1: ";
	cin >> Num1;
	cout << "Enter number 2: ";
	cin >> Num2;
	cout << "Enter number 3: ";
	cin >> Num3;
	if ((Num1 < Num2) && (Num1 < Num3)) {
		Low = Num1;
	}
	else if ((Num2 < Num1) && (Num2 < Num3)) {
		Low = Num2;
	}
	else if ((Num3 < Num1) && (Num3 < Num2)) {
		Low = Num3;
	}
	else {}

	if ((Num1 > Num2) && (Num1 > Num3)) {
		High = Num1;
	}
	else if ((Num2 > Num1 && Num2 > Num3)) {
		High = Num2;
	}
	else if ((Num3 > Num2) && (Num3 > Num1)) {
		High = Num3;
	}
	else {}

	if ((Num1 > Low) && (Num1 < High)) {
		Mid = Num1;
	}
	else if ((Num2 > Low && Num2 < High)) {
		Mid = Num2;
	}
	else if ((Num3 > Low) && (Num3 < High)) {
		Mid = Num3;
	}
	else {}


	cout << "Sorted they are ";
	cout << Low;
	cout << " ";
	cout << Mid;
	cout << " ";
	cout << High;

	cout << "\n\A.Aleppo Pepper";
	cout << "\n\B.Banana Pepper";
	cout << "\n\C.Cayenne Pepper";
	cout << "\n\D.Dragon's Breath";
	cout << "\n\Enter a letter to choose a pepper: ";
	cin >> Pepper;
	if (Pepper == "A" || Pepper == "a") {
		cout << "That\'\s 30,000 Scovilles of heat!\n";
	}
	else if (Pepper == "B" || Pepper == "b") {
		cout << "That\'\s 1000 Scovilles of heat!\n";
	}
	else if (Pepper == "C" || Pepper == "c") {
		cout << "That\'\s 40,000 Scovilles of heat!\n";
	}
	else if (Pepper == "D" || Pepper == "d") {
		cout << "That\'\s 2,480,000 Scovilles of heat!\n";
	}
	else {
		cout << "That pepper is not on the list\n";
	}
	system("pause");
	return 0;
}