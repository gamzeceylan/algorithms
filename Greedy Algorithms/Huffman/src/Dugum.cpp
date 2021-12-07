#include "Dugum.hpp"

Dugum::Dugum(char karakter, int frekans, Dugum *sol, Dugum *sag)
{
	this->karakter = karakter;
	this->frekans = frekans;
	this->sol = sol;
	this->sag = sag;
	kod = "";
}
bool Dugum::Yaprakmi() const
{
	return (sol == NULL && sag == NULL);
}
bool Dugum::operator==(Dugum &sag)
{
	return this->karakter == sag.karakter;
}
bool Dugum::operator!=(Dugum &sag)
{
	return this->karakter != sag.karakter;
}
bool Dugum::operator>(Dugum &sag)
{
	return this->frekans > sag.frekans;
}