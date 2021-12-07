#ifndef DUGUM_HPP
#define DUGUM_HPP

#include <iostream>
using namespace std;

class Dugum
{
public:
	char karakter;
	int frekans; // Dosyada kaç kez tekrarlandı
	string kod;	 // 01 kod karşılığı
	Dugum *sol;
	Dugum *sag;
	Dugum(char karakter, int frekans, Dugum *sol = NULL, Dugum *sag = NULL);
	bool Yaprakmi() const;
	bool operator==(Dugum &);
	bool operator!=(Dugum &);
	bool operator>(Dugum &);
};
#endif