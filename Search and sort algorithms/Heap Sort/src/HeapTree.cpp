#include "HeapTree.hpp"

int HeapTree::SolCocukIndeks(int dugumIndeks)
{
	return 2 * dugumIndeks + 1;
}

int HeapTree::SagCocukIndeks(int dugumIndeks)
{
	return 2 * dugumIndeks + 2;
}

int HeapTree::EbeveynDugumIndeks(int dugumIndeks)
{
	return (dugumIndeks - 1) / 2;
}

HeapTree::HeapTree(int kapasite)
{
	elemanlar = new int[kapasite];
	dugumSayisi = 0;
	this->kapasite = kapasite;
}

bool HeapTree::Bosmu()
{
	return (dugumSayisi == 0);
}

void HeapTree::HeapYukari(int dugumIndeks) //ebeveyn kendisinden daha büyükse yer değiştir.
{
	int ebeveynIndeks, tmpVeri;
	if (dugumIndeks != 0)
	{
		ebeveynIndeks = EbeveynDugumIndeks(dugumIndeks);
		if (elemanlar[ebeveynIndeks] > elemanlar[dugumIndeks])
		{										//ebeveyn çocuğundan büyükse çocukla yer değişsin
			tmpVeri = elemanlar[ebeveynIndeks]; //swap
			elemanlar[ebeveynIndeks] = elemanlar[dugumIndeks];
			elemanlar[dugumIndeks] = tmpVeri;
			HeapYukari(ebeveynIndeks);
		}
	}
}

void HeapTree::HeapAsagi(int dugumIndeks) //çocuğu kendisinden daha küçükse yer değiştir.
{
	int solCocukIndeks, sagCocukIndeks, kucukCocukIndeks, tmpVeri;
	solCocukIndeks = SolCocukIndeks(dugumIndeks);
	sagCocukIndeks = SagCocukIndeks(dugumIndeks);

	//aşağıdaki if-else bloğu küçük çocuğu belirler
	if (sagCocukIndeks >= dugumSayisi)
	{ //sağ çocuğu yoksa ve
		if (solCocukIndeks >= dugumSayisi)
			return; //sol çocuğu da yoksa çık
		else
			kucukCocukIndeks = solCocukIndeks; //sadece sol çocuğu varsa sol çocuk küçük olsun
	}
	else
	{																//sağ çocuğu varsa (aynı zamanda sol çocuğu olduğu anlamına da geliyor çünkü düğümler soldan sağa eklenir)
		if (elemanlar[solCocukIndeks] <= elemanlar[sagCocukIndeks]) //eğer sol çocuk sağ çocuktan küçükse veya eşitse sol çocuk küçük indis olsun
			kucukCocukIndeks = solCocukIndeks;
		else //eğer sağ çocuk daha küçükse sağ çocuk küçük indis olsun
			kucukCocukIndeks = sagCocukIndeks;
	}

	if (elemanlar[dugumIndeks] > elemanlar[kucukCocukIndeks])
	{ //yukarıda küçük değerli çocuğun indisini bulduk şimdi eğer bu çocuğun değeri ebeveyn düğümünkinden küçükse yer değişsinler
		tmpVeri = elemanlar[kucukCocukIndeks];
		elemanlar[kucukCocukIndeks] = elemanlar[dugumIndeks];
		elemanlar[dugumIndeks] = tmpVeri;
		HeapAsagi(kucukCocukIndeks); //heapleştirme işlemi aşağı yönde rekürsif olarak tekrar ediyor. Ta ki iki çocuğu da olmayan yaprak düğümle karşılaşana kadar.
	}
}

void HeapTree::Ekle(int sayi) throw()
{
	if (dugumSayisi == kapasite)
		throw string("Dizi tasma hatasi");
	elemanlar[dugumSayisi] = sayi;
	dugumSayisi++;
	HeapYukari(dugumSayisi - 1);
}

int HeapTree::EnKucuguCikar() throw()
{
	if (Bosmu())
		throw string("Heap bos");
	int enKucuk = elemanlar[0];
	elemanlar[0] = elemanlar[dugumSayisi - 1];
	dugumSayisi--;
	if (dugumSayisi > 0)
		HeapAsagi(0);

	return enKucuk;
}

HeapTree::~HeapTree()
{
	delete[] elemanlar;
}