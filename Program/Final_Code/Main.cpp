#include <stdio.h>
#include <iostream>
#include "Data.h"
#include "conio.h"

using namespace std;

int main(int argc, char *argv[])
{
	USER a;
	INFOUSER n;
	Reader d;
	BOOK e;
	INFOBOOK f;
	BorrowCard c;
	char ID[50];
	int x; //Biến chứa chức năng quay lại menu
	int y; //Biến chứa chức năng tuỳ chọn
	if (login(a, argc, argv, "User.bin") == 1)
	{
		if (checkActive(a, "Info.bin") == 1 || _stricmp(argv[1], "admin") == 0)
		{
			//Các chức năng sau khi đăng nhập
			system("cls");
			cout << "------------------------------LOGINED SUCCESSFULLY-------------------------" << endl;
		menu:  cout << "================================|MENU|================================" << endl;
			cout << "1. Dang xuat (logined)." << endl;
			cout << "2. Thay doi mat khau." << endl;
			cout << "3. Cap nhat thong tin ca nhan." << endl;
			cout << "4. Tao nguoi dung (Only admin)." << endl;
			cout << "5. Xem thong tin nguoi dung hien tai." << endl;
			cout << "=========================================================================" << endl;
			cout << "6. Xem danh sach doc gia trong thu vien." << endl;
			cout << "7. Them doc gia." << endl;
			cout << "8. Chinh sua thong tin mot doc gia." << endl;
			cout << "9. Xoa thong tin mot doc gia (Admin and Manager)." << endl;
			cout << "10. Tim kiem doc giai theo CMND." << endl;
			cout << "11. Tim kiem sach theo ho ten." << endl;
			cout << "=========================================================================" << endl;
			cout << "12. Xem danh sach cac sach trong thu vien." << endl;
			cout << "13. Them sach." << endl;
			cout << "14. Chinh sua thong tin cua mot quyen sach." << endl;
			cout << "15. Xem thong tin sach." << endl;
			cout << "16. Xoa thong tin sach." << endl;
			cout << "17. Tim kiem sach theo ISBN." << endl;
			cout << "18. Tim kiem sach theo ten sach." << endl;
			cout << "=========================================================================" << endl;
			cout << "19. Lap phieu muon sach." << endl;
			cout << "20. Lap phieu tra sach." << endl;
			cout << "=========================================================================" << endl;
			cout << "21. Thong ke so luong sach trong thu vien." << endl;
			cout << "22. Thong ke so luong sach theo the loai." << endl;
			cout << "23. Thong ke so luong doc gia." << endl;
			cout << "24. Thong ke so luong doc gia theo gioi tinh." << endl;
			cout << "25. Thong ke so luong sach da muon." << endl;
			cout << "26. Thong ke danh sach doc gia bi tre han." << endl;
			cout << "=========================================================================" << endl;
			int func; // Biến chức năng
			cout << "Hay lua chon chuc nang ban muon: " << endl;
			cout << "Chuc nang: "; 
			cin >> func;
			cin.ignore();
			switch (func)
			{
			case 1: //pass
				cout << "---------------------------------LOGOUT---------------------------------" << endl;
				cout << "Please press any key to LOGOUT. . ." << endl;
				fflush(stdin);
				_getch();
				system("cls");
				return 0;
				break;
			case 2: //pass
				system("cls");
				cout << "----------------------------CHANGE PASSWORD-----------------------------" << endl;
				changePass(a, "User.bin");
				cout << "Press 0 to comeback menu: ";
				cin >> x;
				cin.ignore();
				system("cls");
				cout << endl;
			
				if (x == 0) goto menu;
				break;				
			case 3:
				system("cls");
				cout << "------- ------------------INFOMATION OF USER-----------------------------" << endl;
				inputInfo(n);
				if (n.userkind == 0)
					a.kind = 0;
				if (n.userkind == 1)
					a.kind = 1;
				inputFile(n, "Info.bin", a);
				changeLocal(a, "User.bin");
				cout << "Press 0 to comeback menu: "; cin >> x;
				system("cls");
				cout << endl;
		
				if (x == 0) goto menu;
				break;
			case 4:
				if (_stricmp(argv[1], "admin") != 0)
				{
					system("cls");
					cout << "You are not permited. . ." << endl << endl;
					
					goto menu;
				}
				system("cls");
				cout << "--------------------------------ADD USER---------------------------------" << endl;
				addUser(a, "User.bin");
				cout << "Creat Successfully" << endl;
				cout << "\nPress 0 to comeback menu or 1 to logout: "; cin >> x; cin.ignore();
				if (x == 1)
					return 0;
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 5:
				system("cls");
				cout << "-----------------------------SHOW INFO USER------------------------------" << endl;
				if (_stricmp(argv[1], "admin") == 0)
				{
					system("cls");
					cout << "Admin dont have infomation in here :D. . ." << endl << endl;
					goto menu;
				}
				outUser(a, "Info.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				if (x == 0) goto menu;
				break;
				//====================================PASS CN1=============================================
			case 6:
				system("cls");
				cout << "----------------------------SHOW LIST READER-----------------------------" << endl;
				ExportReaderInfo("Reader.bin");
				showInfoReader("Reader.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 7:
				system("cls");
				cout << "-----------------------------ADD NEW READER------------------------------" << endl;
				inputChange(d);
				if (isExistedNTIDOfReader(d, "Reader.bin") == 0)
				{
					d.IsDeleted = 0;
					WriteReader(d, "Reader.bin");
				}
				else
				{
					cout << "Reader is existed of deleted, Do you want update info or re-initialize?" << endl;
					cout << "1. Re-initialize data" << endl;
					cout << "2. Update info of reader" << endl;
					cout << "Fill in here: " << endl;
					cin >> y;
					cin.ignore();
					if (y == 1)
					{
						d.IsDeleted = 0;
						changeInfoReader(d, "Reader.bin");
					}
					if (y == 2)
						changeInfoReader(d, "Reader.bin");
				}
				cout << endl;
				cout << "New reader has been save" << endl << endl;
				cout << "Press 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 8:
				system("cls");
				cout << "--------------------------CHANGE INFO OF READER---------------------------" << endl;
				readerCur(d, "Reader.bin");
				inputChange(d);
				changeInfoReader(d, "Reader.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 9:
				if (a.kind == 1)  //Cần phân quyền
				{
					system("cls");
					cout << "You are not permited. . ." << endl << endl;
					goto menu;
				}
				system("cls");
				cout << "---------------------------DELETE INFO OF READER--------------------------" << endl;
				readerCur(d, "Reader.bin");
				Delete(d);
				changeInfoReader(d, "Reader.bin");
				cout << "All has been save. . ." << endl << endl;
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 10:
				system("cls");
				cout << "---------------------------SEARCH BY ID CARD(RD)--------------------------" << endl;
				searchByNTIDRD("Reader.bin", d);
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 11:
				system("cls");
				cout << "----------------------------SEARCH BY NAME(RD)-----------------------------" << endl;
				SearchReaderByName("Reader.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
				//======================================PASS CN2==========================================
			case 12:
				system("cls");
				cout << "-----------------------------SHOW LIST BOOK--------------------------------" << endl;
				if (a.kind == 1)
				{
					system("cls");
					cout << "You are not permited. . ." << endl << endl;
				
					goto menu;
				}
				ExportBookInfo("Book.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 13:
				system("cls");
				cout << "-------------------------------ADD BOOK------------------------------------" << endl;
				if (a.kind == 1)  //Cần phân quyền
				{
					system("cls");
					cout << "You are not permited. . ." << endl << endl;
					
					goto menu;
				}
				inBook(e);
				if (isExistedOfBook(e, "Book.bin") == 0)
					addBook(e, "Book.bin");
				else
				{
					cout << "Book is existed of deleted, Do you want update info or re-initialize?" << endl;
					cout << "1. Re-initialize data" << endl;
					cout << "2. Update info of book" << endl;
					cout << "Fill in here: " << endl;
					cin >> y;
					if (y == 1)
					{
						e.isDeleted = 0;
						changeBookInFile(e, "Book.bin");
					}
					if (y == 2)
						changeBookInFile(e, "Book.bin");
				}
				cout << "\nPress 0 to comeback menu: "; cin >> x;
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 14:
				system("cls");
				cout << "----------------------------CHANGE INFO OF BOOK----------------------------" << endl;
				if (a.kind == 1)  //Cần phân quyền
				{
					system("cls");
					cout << "You are not permited. . ." << endl << endl;
					
					goto menu;
				}
				bookCur(e, "Book.bin");
				inputInfoBook(f);
				infoFileBook(f, "Infobook.bin", e);
				changeBookInFile(e, "Book.bin");
				cout << "Press 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 15:
				system("cls");
				cout << "-----------------------------SHOW INFO OF BOOK------------------------------" << endl;
				bookCur(e, "Book.bin");
				showInfo(e, f, "Infobook.bin");
				cout << "Press 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 16:
				system("cls");
				cout << "-------------------------------DELETE BOOK----------------------------------" << endl;
				if (a.kind == 1)  //Cần phân quyền
				{
					system("cls");
					cout << "You are not permited. . ." << endl << endl;
					
					goto menu;
				}
				bookCur(e, "Book.bin");
				DeletedBook(e);
				changeBookInFile(e, "Book.bin");
				cout << "All has been save. . ." << endl << endl;
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 17:
				system("cls");
				cout << "------------------------------SEARCH BY ISBN--------------------------------" << endl;
				SearchByISBN("Book.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 18:
				system("cls");
				cout << "----------------------------SEARCH BOOK BY NAME------------------------------" << endl;
				SearchByBName("Book.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
				//===================================================================================================
			case 19:
				system("cls");
				cout << "----------------------------CREATE BORROWCARD--------------------------------" << endl;
				cout << "Ma doc gia: ";
				gets_s(c.IDReader);
				fflush(stdin);
				if (BorrowMore(c, "Borrow.bin") == 0)
				{
					cout << "\nYou are only available to borrow when you return the borrowed books" << endl;
					_getch();
					goto menu;  
				}
				borrow("Borrow.bin", "ListISBN.bin", "Book.bin", c);
				cout << "All has been saved. . ." << endl;
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 20:
				system("cls");
				cout << "---------------------------CREATE RETURNCARD----------------------------------" << endl;
				cout << "Ma doc gia: ";
				gets_s(ID);
				fflush(stdin);
				c = SearchBorrowcard(ID, "Borrow.bin");
				if (BorrowMore(c, "Borrow.bin") == 1)
				{
					cout << "\nYou are only available to borrow when you return the borrowed books" << endl;
					_getch();
					goto menu;  
				}
				pay("Borrow.bin", "ListISBN.bin", "Book.bin", c, "Infobook.bin");
				cout << "All has been saved. . ." << endl;
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
				//============================================================================================
			case 21:
				system("cls");
				cout << "----------------------------BOOK STATISTIC-----------------------------------" << endl;
				if (a.kind == 1)  //Cần phân quyền
				{
					system("cls");
					cout << "You are not permited. . ." << endl << endl;
					
					goto menu;
				}
				BookStatistic("Book.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 22:
				system("cls");
				cout << "------------------------BOOK GENRE STATISTIC----------------------------------" << endl;
				if (a.kind == 1)  //Cần phân quyền
				{
					system("cls");
					cout << "You are not permited. . ." << endl << endl;
					
					goto menu;
				}
				BookGenreStatistic("Infobook.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 23:
				system("cls");
				cout << "-----------------------------READER STATISTIC---------------------------------" << endl;
				if (a.kind == 1)  //Cần phân quyền
				{
					system("cls");
					cout << "You are not permited. . ." << endl << endl;
					
					goto menu;
				}
				ReaderStatistic("Reader.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 24:
				system("cls");
				cout << "---------------------------SEX READER STATISTIC---------------------------------" << endl;
				if (a.kind == 1)  //Cần phân quyền
				{
					system("cls");
					cout << "You are not permited. . ." << endl << endl;
					
					goto menu;
				}
				genderStatistics("Reader.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 25:
				system("cls");
				cout << "------------------------BORROWED BOOK STATISTIC----------------------------------" << endl;
				BorrowedBookStatistics("Borrow.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			case 26:
				system("cls");
				cout << "----------------------DELAY BORROWED BOOK STATISTIC------------------------------" << endl;
				DelayStatistics("Borrow.bin");
				cout << "\nPress 0 to comeback menu: "; cin >> x; cin.ignore();
				system("cls");
				cout << endl;
				
				if (x == 0) goto menu;
				break;
			default:
				break;
			}
		}
		else
		{
			cout << "Tai khoan cua ban da bi khoa. Lien he admin de xin cap lai !!!" << endl << endl;
			_getch();
			return 0;
		}
	}
	else
		cout << "------------------------------LOGIN FAILED------------------------------------" << endl;
	_getch();
	return 0;
}