// Author: Zachary Lee
// Date: 2/8/2019
// Description: This program pupmps out gas and keeps track of prices
//and how much gas is in the tank. also prints out a recipt.
//---------------------------------------------------------------------

#include <iostream> 
#include <string>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <Windows.h>
#include <iosfwd>
using namespace std;
string rewardsAns,Octane, RO,nonsence;
double PPG,Fill,TLH,TLM,TLL,Total, Pump,PumpR,filled;
int CustNum;
double HO, MO, LO, LH, LM, LL, HP, MP, LP, discount;
int main()
{
	ifstream f;
	f.open("pumpin.txt");
	f >> LH;
	f >> LM;
	f >> LL;
	f >> HP;
	f >> MP;
	f >> LP;
	
		if (!f.fail())
		{
			cout << "Tank Readings : Hi = " << LH << "  Med = " << LM << "  Low = " << LL << endl;
			cout << "Today's PPG:   Hi=$ " << HP << "  Med=$ " << MP << "  Low=$ " << LP;
			cout << endl;

		}
		else
		{
			cout << "Unable to read input file.\n";
			system("pause");
			return 0;

		}
		f.close();
	while (rewardsAns != "shutdown")
	{

		cout << "+---------------------------------------------+\n";
		cout << "|  WELCOME TO ZACH LEE AND FRIENDS GAS & SIP  |\n";
		cout << "|              ZACHARY LEE, OWNER             |\n";
		cout << "+---------------------------------------------+\n";



		rewardsAns = "d";
		do
		{
			cout << "Are you a rewards customer? (Y/N):";
			cin >> rewardsAns;
			cout << endl;
		} while ((rewardsAns != "Y" && rewardsAns != "y") && (rewardsAns != "N" && rewardsAns != "n") && (rewardsAns != "shutdown"));
	
	

		if ((rewardsAns == "Y") || (rewardsAns == "y"))
		{
			cout << "Enter customer rewards number:";
			cin >> CustNum;
			discount = (double(CustNum % 10) + 1) / 100;
			cout << "Price Per Gallon Discount:" << fixed << setprecision(2) << discount << endl;
			HP -= discount;
			MP -= discount;
			LP -= discount;
		}
		else if ((rewardsAns == "N") || (rewardsAns == "n"))
		{
			discount = 0;
			cout << "Price Per Gallon Discount:" << fixed << setprecision(2) << discount<< endl;

		}
		else if (rewardsAns == "shutdown")
		{
			ofstream c;
			c.open("pumpout.txt");
			c << LH<<" ";
			c << LM<<" ";
			c << LL<< endl;
			c << HP<<" ";
			c << MP<<" ";
			c << LP;

			if (!c.fail())
			{
				cout << "Tank Readings : Hi = " << LH << "  Med = " << LM << "  Low = " << LL << endl;
				cout << "pump shut down."<< endl;
				system("pause");
				return 0;

			}
			else
			{
				cout << "Unable to read output file.\n";
				system("pause");
				return 0;

			}
			c.close();
			

		}

		cout << "Prices per Gallon:" << endl;
		cout << "High Octane:   $ " << HP << endl;
		cout << "Medium Octane: $ " << MP << endl;
		cout << "Low Octane:    $ " << LP << endl;
		do
		{
			cout << "Please enter H, M or L.";
			cin >> Octane;
		} while ((Octane != "h") && (Octane != "H") && (Octane != "M") && (Octane != "m") && (Octane != "L") && (Octane != "l"));

		Fill = 0;
		cout << "Enter number of gallons (-1 to Fill it up):";
		cin >> Fill;

		if (Fill < 0)
		{
			Fill = (rand() % 8) + 1;
			cout << " Sensor reports " << Fill << " gallons needed to fill up" << endl;
		}
		double Num = 0;
		if ((Octane == "h") || (Octane == "H"))
		{
			TLH = LH - Fill;
			if (TLH > 0)
			{

				cout << "Pumping Gas...\n";
				while (Num < Fill)
				{
					Num = Num + .5;
					cout << Num << " gallons pumped..." << endl;
					Sleep(2000);
				}
				LH = TLH;
			}
			else
			{

				cout << "Sorry, our tank is nearly empty. We only have " << LH << " gallons available." << endl;

				while (Num < LH)
				{
					Num = Num + .5;
					cout << Num << " gallons pumped..." << endl;
					Sleep(2000);
				}
				Fill = LH;

			}
		}
		if ((Octane == "m") || (Octane == "M"))
		{
			TLM = LM - Fill;
			if (TLM > 0)
			{
				cout << "Pumping Gas...\n";
				while (Num < Fill)
				{
					Num = Num + .5;
					cout << Num << " gallons pumped..." << endl;
					Sleep(2000);
					
				}
				LM = TLM;
			}
			else
			{
				cout << "Sorry, our tank is nearly empty. We only have " << LM << " gallons available." << endl;

				while (Num < LM)
				{
					Num = Num + .5;
					cout << Num << " gallons pumped..." << endl;
					Sleep(2000);
				}
				Fill = LM;
			}
		}
		if ((Octane == "l") || (Octane == "L"))
		{
			TLL = LL - Fill;
			if (TLL > 0)
			{
				cout << "Pumping Gas...\n";
				while (Num < Fill)
				{
					Num = Num + .5;
					cout << Num << " gallons pumped..." << endl;
					Sleep(2000);
					
				}
				LL = TLL;
			}
			else
			{
				cout << "Sorry, our tank is nearly empty. We only have " << LL << " gallons available." << endl;

				while (Num < LL)
				{
					Num = Num + .5;
					cout << Num << " gallons pumped..." << endl;
					Sleep(2000);
				}
				Fill = LL;
			}
		}

		if ((Octane == "h") || (Octane == "H"))
		{
			RO = "High";
			PPG = HP - discount;
			Total = PPG * Fill;
		}
		else if ((Octane == "m") || (Octane == "M"))
		{
			RO = "Medium";
			PPG = MP - discount;
			Total = PPG * Fill;
		}
		else if ((Octane == "l") || (Octane == "L"))
		{
			RO = "Low";
			PPG = LP - discount;
			Total = PPG * Fill;
		}
		
		

		cout << "------------------- Your Receiptc-----------------\n";
		cout << "Octane:             " << RO;
		cout << "\nPrice Per Gallon:   " << PPG;
		cout << "\nTotal:              " << Total;
		cout << "\nThank your for visiting Zach Lee and Friends!" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "Press any key to continue . . . ";
		cin >> rewardsAns;
		cout << endl;
	}
	
	
	
}