#ifndef HEAPTREE_HPP
#define HEAPTREE_HPP

#include <iostream>
using namespace std;

// Küçükten büyüğe sıralayan (Min Heap Tree)
class HeapTree{
	private:
		int *elemanlar; // dizi
		int dugumSayisi;
		int kapasite;
		
		int SolCocukIndeks(int);//2*i+1
		int SagCocukIndeks(int);//2*i+2
		int EbeveynDugumIndeks(int);//(i-1)/2
		void HeapYukari(int);//yeni bir düğüm eklendiğinde
		void HeapAsagi(int);//ağaçtan düğüm çıkartıldığında
	public:
		HeapTree(int);
		bool Bosmu();
		void Ekle(int)throw();
		int EnKucuguCikar()throw(); // sürekli olarak kökü çıkarma
		~HeapTree();
};

#endif