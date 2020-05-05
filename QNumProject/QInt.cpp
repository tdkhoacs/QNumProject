﻿#include "QInt.h"

int QInt::getBit(int pos)
{
	int a = pos / 32; //xác định bit nằm trong phần tử nào của mảng QInt
	int b = pos % 32; //xác định bit nằm ở trị trí thứ mấy trong phần tử vừa tìm 
	return (data[a] >> (31 - b)) & 1;
}

void QInt::setBit(int value, int pos)
{
	int a = pos / 32; //xác định bit nằm trong phần tử nào của mảng QInt
	int b = pos % 32; //xác định bit nằm ở trị trí thứ mấy trong phần tử vừa tìm 
	if (value == 0) //Trường hợp set bit 0
	{
		data[a] = ~(1 << (31 - b)) & data[a];
	}
	else //Trường hợ set bit 1
	{
		data[a] = (1 << (31 - b)) | data[a];
	}

}

QInt::QInt()
{
	//Khởi tạo bằng 0
	for (int i = 0; i < 128; i++)
	{
		setBit(0, i);
	}
}

//Hàm này để test trong phạm vi số int
QInt::QInt(int a)
{
	for (int i = 0; i < 128; i++)
	{
		setBit(0, i);
	}
	int pos = 0;//vị trí gán bit tiếp theo
	int tam = a;
	while (tam != 0)
	{
		int value = tam % 2;
		setBit(value, pos);
		tam /= 2;
		pos++;

	}

}

//Operator
bool QInt::operator>(QInt a)
{
	for (int i = 127; i >= 0; i--)
	{
		int x = getBit(i);
		int y = a.getBit(i);
		if (x > y)
		{
			return true;
		}
		else if (x < y)
		{
			return false;
		}
	}
	return false;
}

bool QInt::operator<(QInt a)
{
	for (int i = 127; i >= 0; i--)
	{
		int x = getBit(i);
		int y = a.getBit(i);
		if (x < y)
		{
			return true;
		}
		else if (x > y)
		{
			return false;
		}
	}
	return false;
}

bool QInt::operator==(QInt a)
{
	for (int i = 127; i >= 0; i--)
	{
		int x = getBit(i);
		int y = a.getBit(i);
		if (x > y)
		{
			return false;
		}
		else if (x < y)
		{
			return false;
		}
	}
	return true;
}

bool QInt::operator>=(QInt a)
{
	for (int i = 127; i >= 0; i--)
	{
		int x = getBit(i);
		int y = a.getBit(i);
		if (x > y)
		{
			return true;
		}
		else if (x < y)
		{
			return false;
		}
	}
	return true;
}

bool QInt::operator<=(QInt a)
{
	for (int i = 127; i >= 0; i--)
	{
		int x = getBit(i);
		int y = a.getBit(i);
		if (x < y)
		{
			return true;
		}
		else if (x > y)
		{
			return false;
		}
	}
	return true;
}

void QInt::operator=(QInt a)
{
	for (int i = 0; i < 128; i++)
	{
		int bit = a.getBit(i);
		setBit(bit, i);
	}
}

//Operator AND, OR, XOR, NOT
QInt QInt::operator&(QInt a)
{
	QInt ans;
	for (int i = 0; i < 128; i++)
	{
		int x = getBit(i);
		int y = a.getBit(i);
		if (x == 1 && y == 1)
		{
			ans.setBit(1, i);
		}
		else
		{
			ans.setBit(0, i);
		}
	}
	return ans;
}

QInt QInt::operator|(QInt a)
{
	QInt ans;
	for (int i = 0; i < 128; i++)
	{
		int x = getBit(i);
		int y = a.getBit(i);
		if (x == 0 && y == 0)
		{
			ans.setBit(0, i);
		}
		else
		{
			ans.setBit(1, i);
		}
	}
	return ans;
}

QInt QInt::operator^(QInt a)
{
	QInt ans;
	for (int i = 0; i < 128; i++)
	{
		int x = getBit(i);
		int y = a.getBit(i);
		if (x == y)
		{
			ans.setBit(0, i);
		}
		else
		{
			ans.setBit(1, i);
		}
	}
	return ans;
}

QInt QInt::operator~()
{
	QInt ans;
	for (int i = 0; i < 128; i++)
	{
		int x = getBit(i);
		if (x == 0)
		{
			ans.setBit(1, i);
		}
		else
		{
			ans.setBit(0, i);
		}
	}
	return ans;
}
//Hàm nhập
void QInt::ScanQInt()
{
	int am = 0;
	string a;
	cout << "Nhap so: ";
	cin >> a;
	int pos = 0;
	if (a[0] == '-')
	{
		a.erase(a.begin());
		am = 1;
	}
	while (a[0] != '0')
	{
		int du = HalfString(a);
		setBit(du, pos);
		pos++;
	}
	if (am == 1)
	{
		//Đảo bit ra số bù 1
		data[0] = ~data[0];
		data[1] = ~data[1];
		data[2] = ~data[2];
		data[3] = ~data[3];
		//Cộng 1 ra số bù 2
		for (int j = 0; j < 128; j++)
		{
			int bit = this->getBit(j);
			if (bit == 1)
			{
				setBit(0, j);
			}
			else
			{
				setBit(1, j);
				break;
			}
		}
		
	}
}



int QInt::HalfString(string& a)
{
	string ans;
	int sodu = a[a.length() - 1] % 2;
	if (a.length() == 1 && a[0] == 49)
	{
		a = '0';
		return 1;
	}
	if (a.length() == 1 && a[0] == 48)
	{
		a = '0';
		return 0;
	}
	while (a.length() > 1 || (a[0] != 48 && a[0] != 49))
	{
		if (a[0] > '1' )
		{
			int value = a[0] - 48;
			int du = value % 2;
			value /= 2;

			ans.push_back(value + 48);
			if (du == 0)
			{
				if (a[1] == '1')
				{
					a[0] = 48;
				}
				else if (a[1] == '0')
				{
					a[0] = 48;
				}
				else
				{
					a.erase(a.begin());
				}
			}
			else
			{
				a[0] = 49;
			}
		}
		else
		{
			int value = (a[0] - 48) * 10 + (a[1] - 48);
			int du = value % 2;
			value /= 2;
			ans.push_back(value + 48);
			if (du == 0)
			{

				a[1] = '0';
				a.erase(a.begin());

			}
			else
			{
				a.erase(a.begin());
				a[0] = 49;
			}
		}
		if (a.length() == 0)
		{
			break;
		}
	}
	a = ans;
	return sodu;
}