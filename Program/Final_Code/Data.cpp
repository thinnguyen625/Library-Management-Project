#include "Data.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>
#define _CRT_SECURE_NO_WARINGS

using namespace std;

int login(USER &a, int argc, char *argv[], const char *filename)
{
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
		return 0;
	if (_stricmp(argv[1], "admin") == 0 && _stricmp(argv[2], "admin") == 0)
		return 1;
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(USER);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(USER), 1, f);
		if (_stricmp(argv[1], a.username) == 0 && _stricmp(argv[2], a.password) == 0)
			return 1;
	}
	return 0;
}

int date(int ngay, int thang, int nam)
{
	int ngaymax;
	if (nam<0 || thang<0 || thang> 12 || ngay<0 || ngay> 31)
	{
		return 0;
	}
	else
	{
		switch (thang)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			ngaymax = 31;
			break;
		case 2:
			if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0))
				ngaymax = 29;
			else
				ngaymax = 28;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			ngaymax = 30;
			break;
		}
		if (ngay <= ngaymax)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

void inputLogin(USER &a)
{
	cout << "Username: ";
	gets_s(a.username);
	fflush(stdin);
	cout << "PassWord: ";
	gets_s(a.password);
	fflush(stdin);
}

int isExisted(USER a, const char *filename)
{
	USER b;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(USER);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&b, sizeof(USER), 1, f);
		if (_stricmp(a.username, b.username) == 0)
			return 1;
		if (_stricmp(a.username, "admin") == 0)
			return 1;
	}
	return 0;
}

USER addUser(USER &a, const char *filename)
{
	FILE *f = fopen(filename, "r+");
	fseek(f, 0, SEEK_END);
	a.local = -1;
input:inputLogin(a);
	if (isExisted(a, filename) == 1)
	{
		system("cls");
		cout << "Tai khoan da ton tai. . ." << endl;
		goto input;
	}
	fwrite(&a, sizeof(USER), 1, f);
	fclose(f);
	return a;
}

void outUser(USER a, const char *filename) //Sửa lại hàm này + Xuất info. Viết thêm hàm info 
{
	cout << "Username: " << a.username << endl;
	cout << "Password: " << a.password << endl;
	//cout << "" <<a.local << endl;
	//cout << "" <<a.kind << endl;
	INFOUSER b;
	FILE *f = fopen(filename, "rb");
	if (a.local != -1)
	{
		fseek(f, a.local, SEEK_SET);
		fread(&b, sizeof(INFOUSER), 1, f);
		outputInfo(b);
	}
	else
		cout << "Infomation of current user is unavailable" << endl;
	fclose(f);
}

void outputInfo(INFOUSER a)
{
	cout << "Ho ten: "<< a.nameUser << endl;
	cout << "Ngay sinh: " << a.birthday.day << "/" << a.birthday.month << "/" << a.birthday.year << endl;
	cout << "CMND: "<< a.idCard << endl;
	cout << "Nam(0) or Nu(1): " << a.gender << endl;
	cout << "Dia chi: " << a.address << endl;
	cout << "Active(0) or block(1): " << a.ActiveOrBlock << endl;
	cout << "Manager(0) or staff(1): " << a.userkind << endl;
}

void inputDate(DATE d)
{
	cout << "Day: ";
	cin >> d.day;
	cin.ignore();
	cout << "Month: ";
	cin >> d.month;
	cin.ignore();
	cout << "Year: ";
	cin >> d.year;
	cin.ignore();
}

void inputInfo(INFOUSER &a)
{
	cout << "Ho ten: ";
	gets_s(a.nameUser);
	fflush(stdin);

date:cout << "Ngay sinh: " << endl;
	cout << "Day:";
	cin >> a.birthday.day;
	cin.ignore();
	cout << "Month:";
	cin >> a.birthday.month;
	cin.ignore();
	cout << "Year: ";
	cin >> a.birthday.year;
	cin.ignore();
	
	if (date(a.birthday.day, a.birthday.month, a.birthday.year) == 0) goto date;

	cout << "CMND: ";
	gets_s(a.idCard);
	fflush(stdin);
	cout << "Dia chi: ";
	gets_s(a.address);
	fflush(stdin);

gender:cout << "Nam(0) or Nu(1): ";
	cin >> a.gender; cin.ignore();
	if (a.gender != 0 && a.gender != 1) goto gender;

active:cout << "Active(0) or block(1): "; // Phân quyền 1.6
	cin >> a.ActiveOrBlock; cin.ignore();
	   if (a.ActiveOrBlock != 0 && a.ActiveOrBlock != 1) goto active;

kind: cout << "Manager(0) or staff(1): ";
	   cin >> a.userkind; cin.ignore();
	  if (a.userkind != 0 && a.userkind != 1) goto kind;

	cout << endl;
	cout << "All has been saved. . ." << endl;
}

void changePass(USER &a, const char *filename)
{
matkhaucu:char b[50];
	system("cls");
	cout << "Mat khau cu: ";
	gets_s(b);
	fflush(stdin);
	if (_stricmp(b, a.password) != 0)
		goto matkhaucu;
	else
	{
		cout << "Mat khau moi: ";
		gets_s(b);
		fflush(stdin);
		strcpy_s(a.password, 50, b);
	}
	system("cls");
	changePasswordInFileUser(a, filename);
	printf("Your password has been changed successfully. . .\n");
}

void changePasswordInFileUser(USER a, const char *filename)
{
	USER b;
	long int z;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(USER);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&b, sizeof(USER), 1, f);
		if (_stricmp(a.username, b.username) == 0)
		{
			z = ftell(f);
			break;
		}
	}
	fclose(f);
	// Mở để ghi
	f = fopen(filename, "r+");
	fseek(f, z - sizeof(USER), SEEK_SET);
	fwrite(&a, sizeof(USER), 1, f);
	fclose(f);
}

void inputFile(INFOUSER a, const char *filename, USER &b)
{
	FILE *f = fopen(filename, "r+");
	if (b.local == -1)
	{
		fseek(f, 0, SEEK_END);
		b.local = ftell(f);
		fwrite(&a, sizeof(INFOUSER), 1, f);
	}
	else
	{
		fseek(f, b.local, SEEK_SET);
		fwrite(&a, sizeof(INFOUSER), 1, f);
	}
	fclose(f);
}

void changeLocal(USER a, const char *filename)
{
	USER b;
	int local;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(USER);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&b, sizeof(USER), 1, f);
		if (_stricmp(a.username, b.username) == 0)
			local = ftell(f);
	}
	fclose(f);
	f = fopen(filename, "r+");
	fseek(f, local - sizeof(USER), SEEK_SET);
	fwrite(&a, sizeof(USER), 1, f);
	fclose(f);
}

int checkActive(USER b, const char *filename)
{
	INFOUSER a;
	FILE *f = fopen(filename, "rb");
	if (b.local != -1)
	{
		fseek(f, b.local, SEEK_SET);
		fread(&a, sizeof(INFOUSER), 1, f);
		fclose(f);
		if (a.ActiveOrBlock == 0)
			return 1;
		else
			return 0;
	}
	return 1;
}

//==========================================================READER================================================================

Reader InPut(Reader &m, const char *filename)
{
id:cout << "Ma doc gia: ";
	gets_s(m.ID);
	fflush(stdin);
	if (isExistedIDOfReader(m, filename) == 1)
	{
		cout << "ID is existed, input again. . ." << endl;
		goto id;
	}
    //---------------------
	cout << "Ho ten doc gia: ";
	gets_s(m.Name);
	fflush(stdin);
    //---------------------
ntid: cout << "CMND: ";
	gets_s(m.NationID);
	fflush(stdin);
	if (isExistedNTIDOfReader(m, filename) == 1)
	{
		cout << "CMND is existed, input again" << endl;
		goto ntid;
	}
    //---------------------
	cout << "Email: ";
	gets_s(m.Email);
	fflush(stdin);
	//---------------------
	cout << "Dia chi: ";
	gets_s(m.Address);
	fflush(stdin);
	//---------------------
birthday:cout << "Ngay sinh: " << endl;
	cout << "Day:";
	cin >> m.Birthday.day;
	cin.ignore();
	cout << "Month:";
	cin >> m.Birthday.month;
	cin.ignore();
	cout << "Year: ";
	cin >> m.Birthday.year;
	cin.ignore();
	if (date(m.Birthday.day, m.Birthday.month, m.Birthday.year) == 0) 	// if else(kiem tra ngay, quay lai birthday neu sai)
		goto birthday;
	//---------------------
start:cout << "Ngay tao the:   " << endl;
	cout << "Day:";
	cin >> m.CreateDay.day;
	cin.ignore();
	cout << "Month:";
	cin >> m.CreateDay.month;
	cin.ignore();
	cout << "Year: ";
	cin >> m.CreateDay.year;
	cin.ignore();
	if (date(m.CreateDay.day, m.CreateDay.month, m.CreateDay.year) == 0) 	//if else(kiem tra ngay quay lai start neu sai)
		goto start;

	if (m.CreateDay.day == 29 && m.CreateDay.month == 2)
	{
		m.ExpDay.day = 28; m.ExpDay.month = 2; m.ExpDay.year = m.CreateDay.year + 2;
	}
	else
	{
		m.ExpDay.day = m.CreateDay.day; m.ExpDay.month = m.CreateDay.month; m.ExpDay.year = m.CreateDay.year + 2;
	}
	if (isExistedIDOfReader(m, filename) == 0)
		m.IsDeleted = 0; //bang 0 la chua xoa
	return m;
} 

void inputChange(Reader &m)
{
	cout << "Ma doc gia: "; 
	gets_s(m.ID);
	fflush(stdin);

	cout << "Ho ten doc gia: "; 
	gets_s(m.Name);
	fflush(stdin);
	
	cout << "CMND: ";
	gets_s(m.NationID);
	fflush(stdin);

birthday1:cout << "Ngay sinh: " << endl;
	cout << "Day: ";
	cin >> m.Birthday.day;
	cin.ignore();
	cout << "Month: ";
	cin >> m.Birthday.month;
	cin.ignore();
	cout << "Year: ";
	cin >> m.Birthday.year;
	cin.ignore();
	if (date(m.Birthday.day, m.Birthday.month, m.Birthday.year) == 0) 	// if else(kiem tra ngay, quay lai birthday neu sai)
		goto birthday1;

	cout << "Gioi tinh (Nam [0] or Nu [1]): ";
	cin >> m.Gender;
	cin.ignore();

	cout << "Email: ";
	gets_s(m.Email);
	fflush(stdin);

	cout << "Dia chi: ";
	gets_s(m.Address);
	fflush(stdin);

start:cout << "Ngay tao the:   " << endl;
	cout << "Day:";
	cin >> m.CreateDay.day;
	cin.ignore();
	cout << "Month:";
	cin >> m.CreateDay.month;
	cin.ignore();
	cout << "Year: ";
	cin >> m.CreateDay.year;
	cin.ignore();
	if (date(m.CreateDay.day, m.CreateDay.month, m.CreateDay.year) == 0) 	//if else(kiem tra ngay quay lai start neu sai)
		goto start;

	if (m.CreateDay.day == 29 && m.CreateDay.month == 2)
	{
		m.ExpDay.day = 28; m.ExpDay.month = 2; m.ExpDay.year = m.CreateDay.year + 2;
	}
	else
	{
		m.ExpDay.day = m.CreateDay.day; m.ExpDay.month = m.CreateDay.month; m.ExpDay.year = m.CreateDay.year + 2;
	}
}

void showInfo(Reader a)
{
	cout << "Ma doc gia: " << a.ID << endl;
	cout << "Ho ten doc gia: " << a.Name << endl;
	cout << "CMND: " << a.NationID << endl;
	cout << "Ngay sinh: " << a.Birthday.day << "/" << a.Birthday.month << "/" << a.Birthday.year << endl;
	cout << "Gioi tinh (Nam [0] or Nu [1]): " << a.Gender << endl;
	cout << "Email: " << a.Email << endl;
	cout << "Dia chi: " << a.Address << endl;
	cout << "Ngay lap the: " << a.CreateDay.day << "/" << a.CreateDay.month << "/" << a.CreateDay.year << endl;
	cout << "Ngay het han: " << a.ExpDay.day << "/" << a.ExpDay.month << "/" << a.ExpDay.year << endl;
}

void showInfoReader(const char *filename)
{
	Reader a;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(Reader), 1, f);
		cout << "====================" << i + 1 << "====================" << endl;
		showInfo(a);
		
	}
	fclose(f);
}

void WriteReader(Reader a, const char *filename)
{
	FILE *f = fopen(filename, "a+b");
	fwrite(&a, sizeof(Reader), 1, f);
	fclose(f);
}

void changeInfoReader(Reader a, const char *filename)
{
	int local;
	Reader b;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&b, sizeof(Reader), 1, f);
		if (_stricmp(a.ID, b.ID) == 0)
			local = ftell(f);
	}
	fclose(f);
	f = fopen(filename, "r+");
	fseek(f, local - sizeof(Reader), SEEK_SET);
	fwrite(&a, sizeof(Reader), 1, f);
	fclose(f);
}

void Delete(Reader &m)
{
	m.IsDeleted = 1;//bang 1 la da xoa
}

//Sửa ID
void readerCur(Reader &m, const char *filename)
{
	FILE *f = fopen(filename, "rb");
	char s[50], t[50];
	cout << "Pls choose reader you want. . ." << endl;
	cout << "Ho ten doc gia: ";
	gets_s(s);
	fflush(stdin);
	cout << "Ma doc gia: ";
	gets_s(t);
	fflush(stdin);

	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&m, sizeof(Reader), 1, f);
		if (_stricmp(m.Name, s) == 0 && _stricmp(m.ID, t) == 0)
			break;
	}
	fclose(f);
}

int isExistedIDOfReader(Reader a, const char *filename)
{
	Reader b;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&b, sizeof(Reader), 1, f);
		if (_stricmp(a.ID, b.ID) == 0)
			return 1;
	}
	return 0;
}

int isExistedNTIDOfReader(Reader a, const char *filename)
{
	Reader b;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&b, sizeof(Reader), 1, f);
		if (_stricmp(a.NationID, b.NationID) == 0)
			return 1;
	}
	return 0;
}

void searchByNTIDRD(const char *filename, Reader &a)
{
	char NationID[12];
	cout << "CMND: ";
	gets_s(NationID);
	fflush(stdin);

	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(Reader), 1, f);
		if (_stricmp(NationID, a.NationID) == 0 && a.IsDeleted == 0)
		{
			cout << "========================================" << endl;
			showInfo(a);
		}
	}
	fclose(f);
}

void ExportReaderInfo(const char *filename)
{
	Reader a;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(Reader), 1, f);
		if (a.IsDeleted == 0)
			cout << a.Name << "\t\t" << a.ID << "\t\t" << a.NationID << "\t\t" << a.Gender << endl;
	}
	fclose(f);
}

void SearchReaderByName(const char *filename)
{
	char b[50];
	Reader a;
	cout << "Ho ten doc gia can tim: ";
	gets_s(b);
	fflush(stdin);

	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(Reader), 1, f);
		if (_stricmp(a.Name, b) == 0 && a.IsDeleted == 0)
		{
			cout << "========================================" << endl;
			showInfo(a);
		}
	}
	fclose(f);
}


//=============================================================BOOK=================================================================

void inBook(BOOK &a)
{
	cout << "Ten sach: ";
	gets_s(a.NameB);
	fflush(stdin);

	cout << "Ma sach: ";
	gets_s(a.ISBN);
	fflush(stdin);
}

void addBook(BOOK &a, const char *filename)
{
	FILE *f = fopen(filename, "a+b");
	a.local = -1;
	a.isDeleted = 0;
	fwrite(&a, sizeof(BOOK), 1, f);
	fclose(f); 
}

void changeBookInFile(BOOK a, const char *filename)
{
	int local;
	BOOK b;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BOOK);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&b, sizeof(BOOK), 1, f);
		if (_stricmp(a.ISBN, b.ISBN) == 0)
			local = ftell(f);
	}
	fclose(f);
	f = fopen(filename, "r+");
	fseek(f, local - sizeof(BOOK), SEEK_SET);
	fwrite(&a, sizeof(BOOK), 1, f);
	fclose(f);
}

int isExistedOfBook(BOOK a, const char *filename)
{
	FILE *f = fopen(filename, "rb");
	BOOK b;
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BOOK);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&b, sizeof(BOOK), 1, f);
		if (_stricmp(a.ISBN, b.ISBN) == 0)
			return 1;
	}
	fclose(f);
	return 0;
}

void DeletedBook(BOOK &a)
{
	a.isDeleted = 1;
}

void bookCur(BOOK &m, const char *filename)
{
	FILE *f = fopen(filename, "rb");
	char s[50], t[50];
	cout << "Pls choose book you want" << endl;
	cout << "Ten sach: ";
	gets_s(s);
	fflush(stdin);
	
	cout << "Ma sach: ";
	gets_s(t);
	fflush(stdin);
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BOOK);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&m, sizeof(BOOK), 1, f);
		if (_stricmp(m.NameB, s) == 0 && _stricmp(m.ISBN, t) == 0)
			break;
	}
	fclose(f);
}

void inputInfoBook(INFOBOOK &a)
{
	cout << "Tac gia: " << endl;
	gets_s(a.Author);
	fflush(stdin);

	cout << "Nha xuat ban: " << endl;
	gets_s(a.publisher);
	fflush(stdin);

	cout << "Nam xuat ban: " << endl;
	cin >> a.publishingYear;
	cin.ignore();

	cout << "The loai: " << endl;
	gets_s(a.kindB);
	fflush(stdin);

	cout << "Gia: " << endl;
	cin >> a.price;
	cin.ignore();
	
	cout << "So quyen sach: " << endl;
	cin >> a.number;
	cin.ignore();
}

void showInfoBook(INFOBOOK a)
{
	cout << "Tac gia: " << a.Author << endl;
	cout << "Nha xuat ban: " << a.publisher << endl;
	cout << "Nam xuat ban: " << a.publishingYear << endl;
	cout << "The loai: " << a.kindB << endl;
	cout << "Gia: " << a.price << endl;
	cout << "So quyen sach: " << a.number << endl;
}

void showBook(BOOK a)
{
	cout << "Ma sach: " << a.ISBN << endl;
	cout << "Ten sach: " << a.NameB << endl;
}

void infoFileBook(INFOBOOK a, const char *filename, BOOK &b)
{
	FILE *f = fopen(filename, "r+");
	b.cur = a.number;
	if (b.local == -1)
	{
		fseek(f, 0, SEEK_END);
		b.local = ftell(f);
		fwrite(&a, sizeof(INFOBOOK), 1, f);
	}
	else
	{
		fseek(f, b.local, SEEK_SET);
		fwrite(&a, sizeof(INFOBOOK), 1, f);
	}
	fclose(f);
}

void SearchByISBN(const char *filename)
{
	BOOK a;
	char b[50];
	FILE *f = fopen(filename, "rb");
	cout << "Ma sach: ";
	gets_s(b);
	fflush(stdin);
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BOOK);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(BOOK), 1, f);
		if (_stricmp(b, a.ISBN) == 0)
		{
			cout << "=======================================" << endl;
			showBook(a);
		}
	}
	fclose(f);
}

void SearchByBName(const char *filename)
{
	BOOK a;
	char b[50];
	FILE *f = fopen(filename, "rb");
	
	printf("Ten sach: ");
	gets_s(b);
	fflush(stdin);
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BOOK);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(BOOK), 1, f);
		if (_stricmp(b, a.NameB) == 0)
		{
			cout << "=======================================" << endl;
			showBook(a);
		}
	}
	fclose(f);
}

void ExportBookInfo(const char *filename)
{
	BOOK a;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BOOK);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(BOOK), 1, f);
		if (a.isDeleted == 0)
		{
			cout << "=======================================" << endl;
			showBook(a);
		}
	}
	fclose(f);
}

void showInfo(BOOK a, INFOBOOK &b, const char *filename)
{
	FILE *f = fopen(filename, "rb");
	fseek(f, a.local, SEEK_SET);
	fread(&b, sizeof(INFOBOOK), 1, f);
	if (a.isDeleted == 0)
	{
		cout << "=======================================" << endl;
		showBook(a);
		showInfoBook(b);
	}
	fclose(f);
}

//=========================================================BORROW===============================================================
// them BOOK.current de luu so sach con lai

// 3 hàm thời gian
int LeapYear(int year)
{
	if (year % 400 == 0) return 1;
	else if (year % 100 != 0 && year % 4 == 0) return 1;
	return 0;
};

int dateToDate(int date1, int month1, int year1, int date2, int month2, int year2)
{
	int dateOfYear = 0, dateOfMonth = 0, date = 0;
	/* Tinh khoang cach so ngay giua 2 nam */
	for (int i = year1; i<year2; i++)
	if (LeapYear(i)) dateOfYear += 366;
	else dateOfYear += 365;
	/* Tinh khoang cach so ngay giua 2 thang */
	int a[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (LeapYear(year2)) a[1] = 29;           /////
	if (month1>month2)
	{
		for (int i = month2; i < month1; i++)
			dateOfMonth -= a[i - 1];
	}
	else
	{
		for (int i = month1; i < month2; i++)
			dateOfMonth += a[i - 1];
	}
	/* Tinh khoang cach giua 2 ngay */
	date = date2 - date1 + 1;       //Ket qua tinh ca ngay cuoi cung
	return dateOfYear + dateOfMonth + date - 1;
};

int IsLate(int date1, int month1, int year1, int date2, int month2, int year2)
{
	if (dateToDate(date1, month1, year1, date2, month2, year2) > 7) return 1;
	return 0;
};

// Các hàm khác

BOOK TraceByISBN(char ISBN[15], const char *filename)
{
	BOOK a;
	char b[15];
	FILE *f = fopen(filename, "rb");
	strcpy(b, ISBN);
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BOOK);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(BOOK), 1, f);
		if (_stricmp(b, a.ISBN) == 0)
		{
			fclose(f);
			return a;
		}
	}
	fclose(f);
	return a;
}

int BorrowMore(BorrowCard a, const char *filename1) // 0 neu khong duoc muon nua(da muon chua tra), 1 neu duoc muon
{
	char b[50];
	FILE *f = fopen(filename1, "rb");
	strcpy(b, a.IDReader);
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BorrowCard);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(BorrowCard), 1, f);
		if (_stricmp(b, a.IDReader) == 0 && a.Return == 0)
		{
			fclose(f);
			return 0;
		}
	}
	fclose(f);
	return 1;
};

void borrow(const char *filename1, const char *filename2, const char *filename3, BorrowCard a) // file 1 chua phieu muon; file 2 chua list sach, file 3 la file book
{
day1:	cout << "\nNgay muon: " << endl;;
	cout << "Day:";
	cin >> a.borrowDay.day;
	cin.ignore();
	cout << "Month:";
	cin >> a.borrowDay.month;
	cin.ignore();
	cout << "Year: ";
	cin >> a.borrowDay.year;
	cin.ignore();
	if (date(a.borrowDay.day, a.borrowDay.month, a.borrowDay.year) == 0) goto day1;
day2:	cout << "\nNgay tra du kien: " << endl;
	cout << "Day:";
	cin >> a.returnDay1.day;
	cin.ignore();
	cout << "Month:";
	cin >> a.returnDay1.month;
	cin.ignore();
	cout << "Year: ";
	cin >> a.returnDay1.year;
	cin.ignore();
	if (date(a.returnDay1.day, a.returnDay1.month, a.returnDay1.year) == 0) goto day2;
	if (dateToDate(a.borrowDay.day, a.borrowDay.month, a.borrowDay.year, a.returnDay1.day, a.returnDay1.month, a.returnDay1.year)>7)
	{
		cout << "\nYou typed the wrong date, please type again . . ." << endl;
			goto day2;
	}
	a.Return = 0;
	cout << "\nSo luong sach muon: ";
	cin >> a.N;
	cin.ignore();

	FILE *f = fopen(filename2, "r+"); //Mở file danh sách mượn ISBN
	fseek(f, 0, SEEK_END);
	a.local = ftell(f);
	rewind(f);
	BOOK b;
	for (int i = 1; i <= a.N; i++)
	{
	ISBN: cout << "Ma sach: ";
		gets_s(b.ISBN);
		fflush(stdin);
		if (isExistedOfBook(b, filename3) == 0) goto ISBN;
		b = TraceByISBN(b.ISBN, filename3);
		if (b.cur>0)
		{
			b.cur = b.cur - 1;
			changeBookInFile(b, filename3);
			fwrite(&b.ISBN, sizeof(b.ISBN), 1, f);
		}
		else
		{
			a.N = a.N - 1;
			cout << "You can't borrow this book now, type the next book: " << endl;
			if (i < a.N)
				goto ISBN;
			else
				break;
		}
	}
	fclose(f);
	f = fopen(filename1, "a+b"); //Mở file ghi phiếu mượn
	fwrite(&a, sizeof(BorrowCard), 1, f);
	fclose(f);
};

BorrowCard SearchBorrowcard(char ReaderID[50], const char *filename1)
{
	BorrowCard empty;
	BorrowCard a;
	char b[50];
	FILE *f = fopen(filename1, "rb");
	strcpy(b, ReaderID);
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BorrowCard);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(BorrowCard), 1, f);
		if (_stricmp(b, a.IDReader) == 0 && a.Return == 0)
		{
			fclose(f);
			return a;
		}
	}
	fclose(f);
	return empty;
};

int localBCard(char ReaderID[50], const char*filename1)
{
	BorrowCard a;
	char b[50];
	FILE *f = fopen(filename1, "rb");
	strcpy(b, ReaderID);
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BorrowCard);
	rewind(f);
	for (int i = 0; i < n; i++)
	{
		fread(&a, sizeof(BorrowCard), 1, f);
		if (_stricmp(b, a.IDReader) == 0 && a.Return == 0)
			return ftell(f) - sizeof(BorrowCard);
	}
	fclose(f);
	return -1;
};

void pay(const char *filename1, const char *filename2, const char *filename3, BorrowCard a, const char* filename4) // file 1 chua phieu muon; file 2 chua list sach, file 3 la file book, file 4 là info book
{
	a.Return = 1;
day3:	cout << "\nNgay tra thuc te(day month year): " << endl;
	cout << "Day:";
	cin >> a.returnDay2.day;
	cin.ignore();
	cout << "Month:";
	cin >> a.returnDay2.month;
	cin.ignore();
	cout << "Year: ";
	cin >> a.returnDay2.year;
	cin.ignore();
	if (date(a.returnDay2.day, a.returnDay2.month, a.returnDay2.year) == 0) goto day3;
	if (dateToDate(a.borrowDay.day, a.borrowDay.month, a.borrowDay.year, a.returnDay2.day, a.returnDay2.month, a.returnDay2.year) > 7)
	{
		a.IsLate = 1;
		cout << "Money for delay: " << (dateToDate(a.borrowDay.day, a.borrowDay.month, a.borrowDay.year, a.returnDay2.day, a.returnDay2.month, a.returnDay2.year) - 7 + 1) * 5 << "k VND" << endl << endl;
	}
	else a.IsLate = 0;
	int x;
	BOOK k;
	INFOBOOK v;
	FILE *f = fopen(filename2, "r+");
	// fseek den a.local, 
	fseek(f, a.local, SEEK_SET);
	for (int i = 0; i < a.N; i++)
	{
		fread(&k.ISBN, sizeof(k.ISBN), 1, f);
		cout << "Is book (" << k.ISBN << ") losted? Yes(1), No(0): "; cin >> x;
		if (x == 0)
		{
			k = TraceByISBN(k.ISBN, filename3);
			k.cur = k.cur + 1;
			// mo file book (filename3), ghi k xuong vi tri co ISBN tuong ung roi dong file lai
			changeBookInFile(k, filename3);
		}
		if (x == 1)
		{
			k = TraceByISBN(k.ISBN, filename3);
			FILE *f = fopen(filename4, "rb");
			fseek(f, k.local, SEEK_SET);
			fread(&v, sizeof(INFOBOOK), 1, f);
			cout << "Pay 200% cost for book losted:" << v.price * 2 << "k VND" << endl;
			fclose(f);
		}
	}
	fclose(f);
	//mo filename1, tim den vi tri co IDReader tuong ung, ghi BorrowCard a xuong	
	BorrowCard b;
	f = fopen(filename1, "r+");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BorrowCard);
	rewind(f);
	int z;
	for (int i = 0; i < n; i++)
	{
		fread(&b, sizeof(BorrowCard), 1, f);
		if (_stricmp(a.IDReader, b.IDReader) == 0)
			z = ftell(f);
	}
	fseek(f, z - sizeof(BorrowCard), SEEK_SET);
	fwrite(&a, sizeof(BorrowCard), 1, f);
	fclose(f);
}

//========================================================STATISTIC===============================================================

void BookStatistic(const char *filename)
{
	int count = 0;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		cout << "Can not open this file";
		return;
	}
	fseek(f, 0, SEEK_END);
	count = ftell(f) / sizeof(BOOK);
	rewind(f);
	fclose(f);
	cout <<"So luong sach: "<< count <<" quyen.";
}

void BookGenreStatistic(const char *filename)
{
	INFOBOOK A;
	FILE *f	= fopen(filename, "rb");
	char genre[50];
	int count = 0;
	cout << "Nhap the loai: ";
	gets_s(genre);
	fflush(stdin);
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(INFOBOOK);
	rewind(f);
	for (int i = 1; i <= n; i++)
	{
		fread(&A, sizeof(INFOBOOK), 1, f);
		if (_stricmp(genre, A.kindB) == 0)
			count++;
	}
	fclose(f);
	cout << "The loai " << genre << ": " << count << " quyen.";
}

void ReaderStatistic(const char *filename)
{
	Reader A;
	int count = 0;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	rewind(f);
	for (int i = 1; i <= n; i++)
	{
		if (fread(&A, sizeof(Reader), 1, f) == 1)
		if (A.IsDeleted == 0)
			count++;
	}
	fclose(f);
	cout << "So luong doc gia: "<< count;
}

void genderStatistics(const char *filename)
{
	int male = 0, female = 0;
	Reader A;
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	rewind(f);
	for (int i = 1; i <= n; i++)
	{
		fread(&A, sizeof(Reader), 1, f);
		if (A.IsDeleted == 0)
		if (A.Gender == 0) 
			male++;
		else female++;
	}
	fclose(f);
	cout << "Nam: "<< male;
	cout << "Nu: "<< female;
}

void BorrowedBookStatistics(char*filename)
{
	int count = 0;
	BorrowCard c;
	FILE *f = fopen(filename, "a+b");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BorrowCard);
	rewind(f);
	for (int i = 1; i <= n; i++)
	{
		fread(&c, sizeof(BorrowCard), 1, f);
		if (c.Return == 0)
			count += c.N;
	}
	fclose(f);
	cout << "So luong sach da muon: "<< count << " quyen.";
}

void DelayStatistics(char*filename)
{
	int count = 0;
	BorrowCard C;
	FILE *f = fopen(filename, "a+b");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(BorrowCard);
	rewind(f);
	for (int i = 1; i <= n; i++)
	{
		fread(&C, sizeof(BorrowCard), 1, f);
		if (C.Return == 1)
			if (dateToDate( C.borrowDay.day, C.borrowDay.month, C.borrowDay.year, C.returnDay2.day, C.returnDay2.month, C.returnDay2.year) > 7)
				count++;
	}
	fclose(f);
	cout << "So luong doc gia bi tre han: "<< count;
}