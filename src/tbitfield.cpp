// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = (len / (sizeof(TELEM) * 8) + 1);
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else throw "Error";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0 && n < BitLen)
	{
		return (n / (sizeof(TELEM) * 8));
	}
	else
	{
		throw "Error";
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n >= 0 && n < BitLen)
	{
		TELEM mask = 1;
		TELEM pos = n % (sizeof(TELEM)*8);
		mask = mask << pos;
		return mask;
	}
	else
	{
		throw "Error";
	}
}

//// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen)
	{
		int ind;
		ind = n / (sizeof(TELEM) * 8);
		pMem[ind] = pMem[ind] | GetMemMask(n);
	}
	else
	{
		throw "Index out of bounds";
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
	{
		int ind;
		ind = n / (sizeof(TELEM) * 8);
		pMem[ind] = pMem[ind] & (~GetMemMask(n));
	}
	else
	{
		throw "Index out of bounds";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n < BitLen)
	{
		int ind;
		ind = n / (sizeof(TELEM) * 8);
		if ((pMem[ind] & GetMemMask(n)) == GetMemMask(n))
			return 1;
		else return 0;
	}
	else
	{
		throw "Index out of bounds";
	}
}

//// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[]pMem;
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < bf.MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < bf.MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	for (int i = 0; i < bf.MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 1;
	return 0;
}


TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField Tmp(len);
	for (int i = 0; i < MemLen; i++)
		Tmp.pMem[i] |= this->pMem[i] | bf.pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		Tmp.pMem[i] |= bf.pMem[i];
	return Tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField Tmp(len);
	for (int i = 0; i < MemLen; i++)
		Tmp.pMem[i] |= pMem[i];
	for (int i = 0; i < MemLen; i++)
		Tmp.pMem[i] &= bf.pMem[i];
	return Tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField Tmp(*this);
	for (int i = 0; i < BitLen; i++)
		Tmp.pMem[GetMemIndex(i)] ^= GetMemMask(i);
	return Tmp;
	//int tmp = 0;
	//int index = BitLen % (sizeof(TELEM) * 8);
	//for (int i = 0; i < index; i++)
	//	tmp = tmp + pow(2, i);
	//for (int i = 0; i < MemLen; i++)
	//{
	//	if (i == MemLen - 1)
	//		pMem[i] = ~pMem[i] & tmp;
	//	else
	//		pMem[i] = ~pMem[i];
	//}
	//return *this;
}

//// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}

