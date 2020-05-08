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

//Hàm xuất
string QInt::PrintQInt()
{
	string sum = "0";
	if (getBit(127) == 0)
	{
		for (int i = 0; i < 128; i++)
		{
			int bit = getBit(i);
			if (bit == 1)
			{
				sum = SumString(sum, ExpString("2", i));
			}
		}

	}
	else
	{
		QInt a = *this;
		a.data[0] = ~a.data[0];
		a.data[1] = ~a.data[1];
		a.data[2] = ~a.data[2];
		a.data[3] = ~a.data[3];
		QInt b = 1;
		a = a + 1;
		for (int i = 0; i < 128; i++)
		{
			int bit = a.getBit(i);
			if (bit == 1)
			{
				sum = a.SumString(sum, ExpString("2", i));
			}
		}
		sum.insert(sum.begin(), '-');
	}
	return sum;
}

//>>, <<, rol, ror
QInt QInt::operator<<(int value)
{
	QInt ans;
	for (int i = 127; i >= value; i--)
	{
		int bit = getBit(i - value);
		ans.setBit(bit, i);
	}
	return ans;
}

QInt QInt::operator>>(int value)
{
	QInt ans;
	for (int i = 0; i < 128 - value; i++)
	{
		int bit = getBit(i + value);
		ans.setBit(bit, i);
	}
	return ans;
}

QInt QInt::rol(int value)
{
	QInt ans;
	for (int i = 0; i < value; i++)
	{
		int bit = getBit(127);
		ans = *this << 1;
		ans.setBit(bit, 0);
		*this = ans;
	}
	return ans;
}

QInt QInt::ror(int value)
{
	QInt ans;
	for (int i = 0; i < value; i++)
	{
		int bit = getBit(0);
		ans = *this >> 1;
		ans.setBit(bit, 127);
		*this = ans;
	}
	return ans;
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

//Chuan hoa chuoi
int QInt::ChuanHoa(string& s)
{
	int Dau;
	string temp = "";
	if (s[0] == '-') {
		Dau = 1;
		s = s.substr(1, s.length());
	}
	else Dau = 0;
	do {
		if (s[0] == '0') s = s.substr(1, s.length());
		if (s[0] != '0') break;
	} while (true);
	if (Dau == 1) temp = temp + "-" + s;
	if (temp != "") s = temp;
	for (int i = Dau; i < s.length(); i++) {
		if (s[i] < 47 || s[i] > 58)
			return -1;
	}
	return 0;
}


QInt QInt::operator+(QInt a)
{
	QInt c;
	int nho = 0;
	for (int i = 0; i <= 127; i++) {
		int t = getBit(i) + a.getBit(i) + nho;
		if (t == 3) {
			c.setBit(1, i);
			nho = 1;
		}
		else
		{
			if (t == 2) {
				c.setBit(0, i);
				nho = 1;
			}
			else {
				c.setBit(t, i);
				nho = 0;
			}
		}
	}
	return c;
}

QInt QInt::operator-(QInt a)
{
	QInt c;
	a.data[0] = ~a.data[0];
	a.data[1] = ~a.data[1];
	a.data[2] = ~a.data[2];
	a.data[3] = ~a.data[3];
	//Cộng 1 ra số bù 2
	for (int j = 0; j < 128; j++)
	{
		int bit = a.getBit(j);
		if (bit == 1)
		{
			a.setBit(0, j);
		}
		else
		{
			a.setBit(1, j);
			break;
		}
	}
	int nho = 0;
	for (int i = 0; i <= 127; i++) {
		int t = getBit(i) + a.getBit(i) + nho;
		if (t == 3) {
			c.setBit(1, i);
			nho = 1;
		}
		else
		{
			if (t == 2) {
				c.setBit(0, i);
				nho = 1;
			}
			else {
				c.setBit(t, i);
				nho = 0;
			}
		}
	}
	return c;
}

QInt QInt::operator/(QInt divisor) {
  if (divisor == QInt(0))
	throw DividedByZero();
  int size = 128;
  int sign = this->getBit(size - 1) ^ divisor.getBit(size - 1);
  int count = 0;
  if (divisor.getBit(size - 1) == 1)
	divisor = (~divisor) + QInt(1);
  while (divisor.getBit(size - 2) != 1) {
	divisor = divisor << 1;
	count++;
  }
  QInt remainder = *this;
  if (remainder.getBit(size - 1) == 1)
	remainder = (~remainder) + QInt(1);
  QInt quotion;
  for (int i = 0; i <= count; i++) {
	remainder = remainder - divisor;
	quotion = quotion << 1;
	if (remainder.getBit(size - 1) == 1)
	  remainder = remainder + divisor;
	else
	  quotion = quotion + QInt(1);
	divisor = divisor >> 1;
  }
  if (sign) {
	quotion = (~quotion) + QInt(1);
  }
  return QInt(quotion);
}

QInt QInt::operator%(QInt divisor) {
  if (divisor == QInt(0))
	throw DividedByZero();
  int size = 128;
  int sign = this->getBit(size - 1);
  int count = 0;
  if (divisor.getBit(size - 1) == 1)
	divisor = (~divisor) + QInt(1);
  while (divisor.getBit(size - 2) != 1) {
	divisor = divisor << 1;
	count++;
  }
  QInt remainder = *this;
  if (remainder.getBit(size - 1) == 1)
	remainder = (~remainder) + QInt(1);
  QInt quotion;
  for (int i = 0; i <= count; i++) {
	remainder = remainder - divisor;
	quotion = quotion << 1;
	if (remainder.getBit(size - 1) == 1)
	  remainder = remainder + divisor;
	else
	  quotion = quotion + QInt(1);
	divisor = divisor >> 1;
  }
  if (sign) {
	remainder = (~remainder) + QInt(1);
  }
  return QInt(remainder);
}

//Hàm cộng 2 số nguyên dạng string

string QInt::SumString(string a, string b)
{
	string ans;
	if (a.length() > b.length())
	{
		int x = a.length() - b.length();
		string temp;
		for (int i = 0; i < x; i++)
		{
			temp.push_back('0');
		}
		temp += b;
		b = temp;
	}
	else if (a.length() < b.length())
	{
		int x = b.length() - a.length();
		string temp;
		for (int i = 0; i < x; i++)
		{
			temp.push_back('0');
		}
		temp += a;
		a = temp;
	}
	int nho = 0;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		int sum = (a[i] - 48) + (b[i] - 48) + nho;
		if (sum < 10)
		{
			ans.insert(ans.begin(), sum + 48);
			nho = 0;
		}
		else
		{
			ans.insert(ans.begin(), sum + 48 - 10);
			nho = 1;
		}
	}
	if (nho == 1)
	{
		ans.insert(ans.begin(), '1');
	}
	return ans;
}

string QInt::DoubleString(string a)
{
	string ans;
	ans = SumString(a, a);
	return ans;
}

string QInt::ExpString(string a, int n)
{
	string ans = a;
	if (n == 0)
	{
		return "1";
	}
	for (int i = 1; i < n; i++)
	{
		ans = DoubleString(ans);
	}
	return  ans;
}


QInt QInt::operator*(QInt a)
{
	QInt ans;								//Kết quả trả về
	int x, y;								// x lưu dấu của số thứ 1 (QInt this), y lưu dấu của số thứ 2(QInt a)
	x = getBit(127);
	y = getBit(127);

	char* ketQua;
	ketQua = new char[258];
	ketQua[0] = '0';
	ketQua[257] = '\0';

	if (x == 0 && y == 0)					// Nhân hai số dương
	{
		for (int i = 1; i < 129; i++)		// chuyển bit nhớ, số thứ 1, số thứ 2 vào ketQua
		{
			ketQua[i] = '0';
			ketQua[i + 128] = a.getBit(128 - i) + '0';
		}

		for (int i = 0; i < 128; i++)
		{
			if (ketQua[256] == '1')
			{
				plusInMulti(ketQua);		//cộng (QInt this) vào chuỗi ketQua
				shrInMulti(ketQua);			//dịch phải chuỗi ketQua
			}
			else
			{
				shrInMulti(ketQua);		//dịch phải chuỗi ketQua
			}
		}

		for (int i = 0; i < 128; i++)			// lưu chuỗi ketQua vào ans
		{
			if (ketQua[256 - i] == '0')
				ans.setBit(0, i);
			else
				ans.setBit(1, i);
		}
	}
	else
		if ((x == 0 && y == 1) || (x == 1 && y == 0))		//nhân số dương với âm, ngược lại
		{
			if (y == 1)									//số thứ 2 âm, chuyển nó sang dương
			{
				QInt temp;
				temp.setBit(1, 0);
				a = ~a;
				a = a + temp;
			}
			else
			{
				QInt temp;								//số thứ 1 âm, chuyển sang dương
				temp.setBit(1, 0);
				*this = ~(*this);
				*this = *this + temp;
			}

			for (int i = 1; i < 129; i++)				// chuyển bit nhớ, số thứ 1, số thứ 2 vào ketQua
			{
				ketQua[i] = '0';
				ketQua[i + 128] = a.getBit(128 - i) + '0';
			}

			for (int i = 0; i < 128; i++)
			{
				if (ketQua[256] == '1')
				{
					plusInMulti(ketQua);
					shrInMulti(ketQua);
				}
				else
				{
					shrInMulti(ketQua);
				}
			}

			transBit(ketQua);					// kết quả dương -> âm
			QInt temp;
			temp.setBit(1, 0);
			temp.plusInMulti(ketQua);			//chuyển sang bù 2

			for (int i = 0; i < 128; i++)		//lưu kết quả vào ans
			{
				if (ketQua[256 - i] == '0')
					ans.setBit(0, i);
				else
					ans.setBit(1, i);
			}
		}
		else
			if (x == 1 && y == 1)			// nhân hai số âm
			{
				QInt temp;
				temp.setBit(1, 0);
				a = ~a;						// chuyển hai số âm sang dương
				a = a + temp;
				*this = ~(*this);
				*this = *this + temp;

				for (int i = 1; i < 129; i++) // chuyen bit nho, so thu 1, so thu 2 vao ketQua
				{
					ketQua[i] = '0';
					ketQua[i + 128] = a.getBit(128 - i) + '0';
				}

				for (int i = 0; i < 128; i++)
				{
					if (ketQua[256] == '1')
					{
						plusInMulti(ketQua);
						shrInMulti(ketQua);
					}
					else
					{
						shrInMulti(ketQua);
					}
				}

				for (int i = 0; i < 128; i++)
				{
					if (ketQua[256 - i] == '0')
						ans.setBit(0, i);
					else
						ans.setBit(1, i);
				}
				return ans;
			}


	for (int i = 0; i < 128; i++)
	{
		if (ketQua[256 - i] == '0')
			ans.setBit(0, i);
		else
			ans.setBit(1, i);
	}
	return ans;
}

void QInt::plusInMulti(char*& a)
{
	int bitNho = 0;
	for (int i = 0; i < 128; i++)
	{
		if (bitNho == 1 && getBit(i) == 0 && a[128 - i] == '0')
		{
			a[128 - i] = '1';
			bitNho = 0;
		}
		else
			if (bitNho == 0 && getBit(i) == 1 && a[128 - i] == '0')
			{
				a[128 - i] = '1';
			}
			else
				if (bitNho == 1 && (getBit(i) == 0 && a[128 - i] == '1'))
				{
					a[128 - i] = '0';
				}
				else
					if (bitNho == 0 && getBit(i) == 1 && a[128 - i] == '1')
					{
						a[128 - i] = '0';
						bitNho = 1;
					}
	}
	if (bitNho == 1)
		a[0] = '1';
}

void QInt::shrInMulti(char*& a)
{
	for (int i = 256; i > 0; i--)
	{
		a[i] = a[i - 1];
	}
	a[0] = '0';
}

void QInt::transBit(char*& a)
{
	for (int i = 129; i < 257; i++)
	{
		if (a[i] == '0')
		{
			a[i] = '1';
		}
		else
			a[i] = '0';
	}
}

