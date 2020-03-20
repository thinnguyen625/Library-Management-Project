#pragma once

//========================================USERS==================================================
struct DATE
{
	int day;
	int month;
	int year;
};
struct USER
{
	char username[50];
	char password[50];
	int kind, local;
};

struct DATAUS
{
	USER *pHead;
	USER *pTail;
};

struct INFOUSER
{
	char nameUser[50];
	DATE birthday;
	char idCard[15];
	char address[50];
	int gender;
	int ActiveOrBlock;
	int userkind;
};

void inputDate(DATE d);
int date(int ngay, int thang, int nam);
USER addUser(USER &a, const char *filename);
void outUser(USER a, const char *filename);
void changePass(USER &a);
void inputLogin(USER &a);
int isExisted(USER a, const char *filename);
void changePass(USER &a, const char *filename);
void inputInfo(INFOUSER &a);
void changePasswordInFileUser(USER a, const char *filename);
void inputFile(INFOUSER a, const char *filename, USER &b);
void outputInfo(INFOUSER a);
int login(USER &a, int argc, char *argv[], const char *filename);
void changeLocal(USER a, const char *filename);
int checkActive(USER b, const char *filename);
//========================================READER==================================================

struct Reader
{
	char ID[12];
	char Name[50];
	char NationID[12];
	DATE Birthday;
	int Gender;
	char Email[50];
	char Address[50];
	DATE CreateDay;//ngay lam the
	DATE ExpDay;//ngay het han
	int IsDeleted;
};

Reader InPut(Reader &m, const char *filename);
void WriteReader(Reader m, const char *filename);
void Delete(Reader &m);
void readerCur(Reader &m, const char *filename);
int isExistedIDOfReader(Reader a, const char *filename);
void searchByNTIDRD(const char *filename, Reader &a);
void ExportReaderInfo(const char *filename);
void SearchReaderByName(const char *filename);
int isExistedNTIDOfReader(Reader a, const char *filename);
void changeInfoReader(Reader a, const char *filename);
void inputChange(Reader &m);
void showInfoReader(const char *filename);
void showInfo(Reader a);

//========================================BOOK==================================================
struct BOOK
{
	char ISBN[15];
	char NameB[30];
	int local;
	int isDeleted;
	int cur;
};

struct INFOBOOK
{
	char Author[30];
	char publisher[30];
	int publishingYear;
	int number;
	int price;
	char kindB[30];
};

void inBook(BOOK &a);
int isExistedOfBook(BOOK a, const char *filename);
void addBook(BOOK &a, const char *filename);
void DeletedBook(BOOK &a);
void SearchByISBN(const char *filename);
void SearchByBName(const char *filename);
void ExportBookInfo(const char *filename);
void changeBookInFile(BOOK a, const char *filename);
void bookCur(BOOK &m, const char *filename);
void inputInfoBook(INFOBOOK &a);
void infoFileBook(INFOBOOK a, const char *filename, BOOK &b);
void showInfo(BOOK a, INFOBOOK &b, const char *filename);
void showBook(BOOK a);
void showInFo(INFOBOOK a);


//=========================================BORROW================================================

struct BorrowCard
{
	char IDReader[50];
	DATE borrowDay; // ngay muon
	DATE returnDay1; // ngay tra du kien
	DATE returnDay2; // ngay tra thuc te 
	int N; // so sach muon 
	int local;
	int IsLate; // 0 neu ko tre; 1 neu tre 
	int Return = -1; // 0 neu chua tra; 1 neu tra roi
};

int LeapYear(int year);
int dateToDate(int date1, int month1, int year1, int date2, int month2, int year2);
int IsLate(int date1, int month1, int year1, int date2, int month2, int year2);
int BorrowMore(BorrowCard a, const char *filename1);
BOOK TraceByISBN(char ISBN[15], const char *filename);
void borrow(const char *filename1, const char *filename2, const char *filename3, BorrowCard a);
BorrowCard SearchBorrowcard(char ReaderID[50], const char *filename1);
int localBCard(char ReaderID[50], const char*filename1);
void pay(const char *filename1, const char *filename2, const char *filename3, BorrowCard a, const char* filename4);

//========================================STATISTIC===============================================

void BookStatistic(const char *filename);
void BookGenreStatistic(const char *filename);
void ReaderStatistic(const char *filename);
void genderStatistics(const char *filename);
void BorrowedBookStatistics(char*filename);
void DelayStatistics(char*filename);
