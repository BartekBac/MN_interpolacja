#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
#define M_PI 3.141592653589

void Wejscie(int &n,int &np,int &a,int &b,bool &optymalnie)
{
	cout <<	"Podaj n: ";
	
	cin >> n;
	
	cout <<	"Podaj np: ";
	
	cin >> np;
	
	cout <<	"Podaj a: ";
	
	cin >> a;
	
	cout <<	"Podaj b: ";
	
	cin >> b;
	
	cout << "Jak wyznaczyc wezly:\n 1 - optymalnie\n 0 - rownoodlegle\n";
	
	cin >> optymalnie;
	
}
double funkcjaInterpolowana(double x)
{
	double result = cos(x)*x;
	
	if(result<0)
	{
		result = result*(-1.0);
	}
	return result;
}
vector<double> wyznaczWezly(int n,int a,int b,bool optymalne)
{
	vector<double> vectorDoZwrotu;
	if(optymalne)
	{
		const double pi = M_PI;
		double p1 = (double)(a+b)/2; 
		double p2 = (double)(b-a)/2;
		for(int i=0;i<(n+1);i++)
		{
			double pom1 = cos(2 * i + 1);
			double pom2 = (2 * n + 2);
			double x = (p1 + p2*cos(((2*i+1)/(double)(2*n+2))*pi));
			vectorDoZwrotu.push_back(x);
		}
	}
	else
	{
		double p = (double)(b-a)/n;
		//cout << p<< endl;
		for(int i =0;i<(n+1);i++)
		{
			
			double x = a + (i*p);
			//cout << x<< endl;
			vectorDoZwrotu.push_back(x);
		}
	}
	return vectorDoZwrotu;
}
vector<double> wyznaczWartosciFunkcjiInterpolowanej(vector<double> &wezly)
{
	vector<double> vectorDoZwrotu;
	for(int i =0;i<wezly.size();i++)
	{
		vectorDoZwrotu.push_back(funkcjaInterpolowana(wezly[i]));
	}
	return vectorDoZwrotu;
}
vector<double> wyznaczWartosciWielomanuLagrange(vector<double> punkty,int n,vector<double> wartosciFunkcjiInterpolowanej,vector<double> wezly)	
{
	vector<double> vectorDoZwrotu;
	for(int k =0;k<punkty.size();k++)
	{
		double wynik=0;
		for(int i=0;i<n;i++)
		{
			double wynikIloczynu = 1;
			for(int j=0;j<n;j++)
			{
				if(i!=j)
				{
					wynikIloczynu *= (punkty[k]-wezly[j])/(wezly[i]-wezly[j]);			
				}		
			}
			wynik +=wartosciFunkcjiInterpolowanej[i]*wynikIloczynu;
						
		}
		vectorDoZwrotu.push_back(wynik);
	}
	return vectorDoZwrotu;
}
void Wyjscie(int n,int np,int a,int b,bool optymalnie)
{
	string nazwa = "raport_n=";
	nazwa += to_string(n);
	nazwa += "_ab=";
	nazwa += to_string(a);
	nazwa += to_string(b);
	if (optymalnie)
	{
		nazwa+= "_opt";
	}
	else
	{
		nazwa+= "_row";
	}
	//nazwa += ".txt";
	fstream plik, plik2;
	plik.open(nazwa+".txt", ios_base::out);
	plik2.open(nazwa + ".csv", ios_base::out);
	if(!plik.good())
	{
		cout <<"LIPA";
		return;
	}
	plik << "n="<<n<<", "<< "np="<<np<<", "<< "a="<<a<<", "<< "b="<<b<<", ";
	if(optymalnie)
	{
		plik << "optymanie";
	}
	else
	{
		plik << "rownoodlegle";
	}
	plik <<endl;
	
	
	vector<double> punktyX = wyznaczWezly(np,a,b,false);
	vector<double> wartosciFunkcjiInterpolowanej=wyznaczWartosciFunkcjiInterpolowanej(punktyX);
	vector<double> wezly = wyznaczWezly(n,a,b,optymalnie);
	vector<double> wartosciFunkcjiInterpolowanejDlaWezlow = wyznaczWartosciFunkcjiInterpolowanej(wezly); 
	vector<double> wartosciWielomianuLagrange = wyznaczWartosciWielomanuLagrange(punktyX,n,wartosciFunkcjiInterpolowanejDlaWezlow,wezly);
	
	//plik << "punktyX | wartoœci funkcji interpolowanej | wartoœci wielomianu Lagrange'a'"<< endl;
	plik2 << "x,y,L\n";
	for(int i=0;i<np+1;i++)
	{
		plik2 << punktyX[i] << "," << wartosciFunkcjiInterpolowanej[i] << "," << wartosciWielomianuLagrange[i] << endl;
		plik << setprecision(4) << punktyX[i] <<" | " << wartosciFunkcjiInterpolowanej[i]<<" | " << wartosciWielomianuLagrange[i] <<endl;
	}
	plik.close();
	plik2.close();
	
		
}
int main()
{
	//int n;
	//int np;
	//int a;
	//int b;
	//bool optymalnie;
	
	//cout<< (double)abs(cos(-3.0)*(-3.0)) <<endl;
	
	//Wejscie(n,np,a,b,optymalnie);
	//Wyjscie(n, np, a, b, optymalnie);
	vector<int> n = { 7, 8, 15, 16 };
	vector<int> ab = { 3, 6 };
	vector<string> punkty = { "opt", "row" };
	for (auto i_n : n)
	{
		for (auto i_ab : ab)
		{
			for (auto i_punkty : punkty)
			{
				int _a = i_ab*(-1);
				bool optymalnie = false;
				if (i_punkty == "opt") optymalnie = true;
				Wyjscie(i_n, 150, _a, i_ab, optymalnie);
			}
		}
	}
	//Wyjscie(7,150,-3,3,true);
}

