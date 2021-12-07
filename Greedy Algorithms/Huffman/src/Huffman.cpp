#include "Huffman.hpp"

Huffman::Huffman(string dosyaYolu) throw()
{
	harfler = 256;
	girdi = "";
	try
	{
		DosyaOku(dosyaYolu);
	}
	catch (string ex)
	{
		throw ex;
	}
	root = NULL;
}

void Huffman::DosyaOku(string dosyaYolu) throw()
{
	string satir;
	ifstream dosya(dosyaYolu.c_str());
	if (dosya.is_open())
	{
		while (getline(dosya, satir))
		{
			girdi += satir;
			girdi += '\n';
		}
		dosya.close();
	}
	else
		throw "Dosya acilamadi";
}

void Huffman::Kodla()
{
	char karakterler[girdi.size() - 1];

	//string char dizisine çevirilmiş
	strcpy(karakterler, girdi.c_str());

	// frekansların tutulacağı diziyi tanımla

	int frek[harfler];

	// frekansları sıfıra eşitle
	for (int i = 0; i < harfler; i++)
		frek[i] = 0;
	// frekansları say
	for (int i = 0; i < girdi.size() - 1; i++)
		frek[karakterler[i]]++;

	// Huffman ağacını oluştur
	root = AgacOlustur(frek);

	// kodlar oluşturuluyor
	KodOlustur(root, "");
}

// Huffman ağacı oluşturup en son kök düğümü döner
Dugum *Huffman::AgacOlustur(int frek[])
{
	// dosyada var olan karakterler için düğüm dizisi oluştur.
	Dugum *dugumler[harfler];

	for (int i = 0; i < harfler; i++)
	{
		if (frek[i] > 0)
		{
			dugumler[i] = new Dugum((char)i, frek[i]);
		}
		else// frekansı sıfır olan karakterler için düğüm oluşturmaya gerek yok
		{
			dugumler[i] = NULL;
		}
	}

	while (true)
	{
		int ilkIndeks = MinDugumIndeks(dugumler);
		Dugum *min1 = dugumler[ilkIndeks];
		dugumler[ilkIndeks] = NULL;
		int ikinciIndeks = MinDugumIndeks(dugumler);
		if (ikinciIndeks == -1)
		{
			return min1;
		}
		Dugum *min2 = dugumler[ikinciIndeks];
		dugumler[ikinciIndeks] = NULL;
		dugumler[ilkIndeks] = new Dugum(0, min1->frekans + min2->frekans, min1, min2);
	}
}

int Huffman::MinDugumIndeks(Dugum *dugumler[])
{
	Dugum *min;
	int minIndeks = -1;

	// ilk null olmayan düğümü min olarak al
	for (int i = 0; i < harfler; i++)
	{
		if (dugumler[i] != NULL)
		{
			min = dugumler[i];
			minIndeks = i;
			break;
		}
	}

	for (int i = 0; i < harfler; i++)
	{
		if (dugumler[i] == NULL)
			continue;

		if (*min > *(dugumler[i]))
		{
			min = dugumler[i];
			minIndeks = i;
		}
	}
	return minIndeks;
}

void Huffman::KodOlustur(Dugum *alt_dugum, string kod)
{
	if (!alt_dugum->Yaprakmi())
	{
		KodOlustur(alt_dugum->sol, kod + '0');
		KodOlustur(alt_dugum->sag, kod + '1');
	}
	else
	{
		alt_dugum->kod = kod;
	}
}

ostream &operator<<(ostream &ekran, Huffman &sag)
{
	ekran << "Huffman Agacindaki Karakterler ve Kodlari:" << endl;
	sag.inorder(sag.root);
	return ekran;
}

void Huffman::inorder(Dugum *alt_dugum)
{
	if (alt_dugum != NULL)
	{
		inorder(alt_dugum->sol);
		if (alt_dugum->Yaprakmi())
			cout << alt_dugum->karakter << ":" << alt_dugum->kod << endl;
		inorder(alt_dugum->sag);
	}
}

void Huffman::SilDugum(Dugum *&alt_dugum)
{
	if (alt_dugum == NULL)
		return;
	SilDugum(alt_dugum->sol);
	SilDugum(alt_dugum->sag);
	delete alt_dugum;
	alt_dugum = NULL;
}

Huffman::~Huffman()
{
	// çöp oluşmaması için ağaç temizleniyor.
	SilDugum(root);
}