// Author: Zachary Lee
// Date: 3/20/2019
// Description: Inputs fractions and outputs highest fraction
//---------------------------------------------------------------------

#include <iostream> 
#include <string>
#include <iomanip>

using namespace std;
const int maxFract = 10;
struct fraction
{
	int Num;
	int Den;
	double Decimal;
};
fraction askFraction()
{
	int Num, Den;
	string Valid = "Invalid";
	while (Valid == "InValid")
	{
		cout << "Enter Numerator: ";
		cin >> Num;
		cout << "Enter Denominator: ";
		cin >> Den;
		if (Den == 0)
		{
			cout << "Error: Divide by zero Enter a number bigger than 0 to continue" << endl;
		}
		else
		{
			Valid = "Valid";
		}
	}
	fraction f;
	f.Num = Num;
	f.Den = Den;
	return f;
}
void calcDecimal(fraction & f)
{
	int Decimal;
	f.Decimal = f.Num / f.Den;
}
void printFrac(fraction f)
{
	cout << f.Num << " / " << f.Den << " (" << f.Decimal << ")" << endl;
}
fraction askFractionList(fraction F[], int & FraN)
{
	string Valid2 = "Invalid";

	while (Valid2 == "Invalid")
	{
		cout << "How many fractions are in your list? ";
		cin >> FraN;
		if ((FraN < 1) || (FraN > 10))
		{
			cout << "Enter a number between 1-10" << endl;

		}
		else
		{
			Valid2 = "Valid";
		}

	}


	int i;
	for (i = 1;i < FraN;i++) {
		cout << "For fraction " << i << ":" << endl;
		F[i] = askFraction();
		calcDecimal(F[i]);
	}

}
void printFracList(fraction F[maxFract], int FraN) {
	int y;
	for (y = 0;y < FraN;y++)
	{
		printFrac(F[y]);
	}
}
fraction findMaxFrac(fraction F[maxFract], int FraN)
{
	int z;
	int maxN = 0;

	for (z = 1; z < FraN; z++) {
		if (F[z].Decimal > F[maxN].Decimal) {
			maxN = z;
		}
	}
	return maxN;
}

int main()
{

	int FractN = 0;
	fraction F[maxFract];
	askFractionList(F, FractN);
	printFracList(F, FractN);
	cout << "THe highest value is fraction is: ";
	fraction Max = findMaxFrac(F, FractN);
	printFrac(Max);
	system("pause");
	return 0;
}