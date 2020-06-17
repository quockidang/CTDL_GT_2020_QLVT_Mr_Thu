#ifndef _STAFF_H
#define _STAFF_H

#include "bill.h"
#include "display.h"
struct Staff {
	char id[11]; // ma nhan vien.
	char first_name[41];
	char last_name[11];
	int sex;
	
	LIST_BILL list_bill;
};
typedef struct Staff STAFF;

typedef STAFF* PTR_STAFF;

// xay dung cau truc danh sach nhan vien la mang con tro
struct ListStaff{
	int n = -1; // so phan tu cua danh sach
	PTR_STAFF *listStaff = new PTR_STAFF[500]; // khoi tao mang con tro;
};

typedef struct ListStaff LIST_STAFF;
typedef LIST_STAFF* PTR_LIST_STAFF;

// tìm nhanh vien theo ma nhân viên.
PTR_STAFF FindStaffByID( PTR_LIST_STAFF l, char id[])
{
	if(l->n < 0) return NULL; // ds rong;
	for(int i = 0; i <= l->n; i++)
		if(_strcmpi(l->listStaff[i]->id, id) == 0)
			return l->listStaff[i]; // tim ra dia chi cua nhan vien thu i trong ds.
	
	return NULL;
}

// find index staff
int FindIndexStaff(PTR_LIST_STAFF l, char* id)
{
	if( l->n < 0) return -1;
	for(int i = 0; i <= l->n; i++)
		if(_strcmpi(l->listStaff[i]->id, id) == 0)
			return i;
	
	return -1;
	
}

bool DataStaffIsEmty(PTR_STAFF st)
{
	if(strlen(st->first_name) == 0 || strlen(st->last_name) == 0 || strlen(st->id) == 0 || st->sex < 0)
		return true;
	return false;
}

bool DeleteStaffIsSuccess(PTR_LIST_STAFF &l, char* id)
{
	int index = FindIndexStaff(l, id);
	if(index == -1) return false;
	
	for(int i = index; i < l->n; i++)
		l->listStaff[i] = l->listStaff[i+ 1];
	
	l->n--;
	return true;
}
void SwapStaff(PTR_STAFF &a, PTR_STAFF &b)
{
	PTR_STAFF temp = a;
	a = b;
	b = temp;
}
void SortStaff(PTR_LIST_STAFF &l)
{
	if(l->n < 0) return; // ds rong;
	for(int i = 0; i < l->n; i++)
	{
		for(int j = i + 1; j <= l->n; j++)
		{
			if(strcmp(l->listStaff[i]->last_name, l->listStaff[j]->last_name) > 0){
				SwapStaff(l->listStaff[i], l->listStaff[j]);
			}
			
			if(strcmp(l->listStaff[i]->last_name, l->listStaff[j]->last_name) == 0){
				if(strcmp(l->listStaff[i]->first_name, l->listStaff[j]->first_name) > 0){
					SwapStaff(l->listStaff[i], l->listStaff[j]);
				}
			}
		}
	}
}

void OutputStaff(PTR_STAFF st, int thuTu)
{
	DeleteOldData(sizeof(keyDisplayStaff) / sizeof(string), thuTu);//xoa hang dau truoc 
	Gotoxy(xKeyDisplay[0] + 3, Y_DISPLAY + 3 + thuTu); cout << st->id;
	Gotoxy(xKeyDisplay[1] + 3, Y_DISPLAY + 3 + thuTu); cout << st->first_name;
	Gotoxy(xKeyDisplay[2] + 8, Y_DISPLAY + 3 + thuTu); cout << st->last_name;
	Gotoxy(xKeyDisplay[3] + 8, Y_DISPLAY + 3 + thuTu);
	if(st->sex == 1) cout << "Nam";
	else cout << "Nu";
}

void OutputListStaffPerPage(PTR_LIST_STAFF l, int indexBegin)
{
	if(l == NULL) return;
	for(int i = 0; i + indexBegin <= l->n && i < QUANTITY_PER_PAGE; i++)
		OutputStaff(l->listStaff[i + indexBegin], i * 2);
	
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowStaff << "/" << totalPageStaff;
}

void SetDefaultChosenStaff(PTR_LIST_STAFF l, int ordinal)
{
	SetBGColor(1); // dark blue;
	OutputStaff(l->listStaff[ordinal], (ordinal % QUANTITY_PER_PAGE) * 2);
	SetBGColor(0); // black;
}

void EffecttiveMenuStaff(int index, PTR_LIST_STAFF l)
{
	int current = index;
	SetDefaultChosenStaff(l, current);
	OutputStaff(l->listStaff[currposPrecStaff], (currposPrecStaff % QUANTITY_PER_PAGE) * 2);
	 currposPrecStaff = current;
}

void ChangePageStaff(PTR_LIST_STAFF l)
{
	clrscr();
	Display(keyDisplayStaff, sizeof(keyDisplayStaff) / sizeof(string));
	DeleteNote(sizeof(keyDisplayStaff) / sizeof(string));
	
	currposStaff = (pageNowStaff -1) * QUANTITY_PER_PAGE;
	currposPrecStaff = (pageNowStaff -1) * QUANTITY_PER_PAGE;
	
	Gotoxy(X_PAGE, Y_PAGE);
		cout << "Trang " << pageNowStaff << "/" << totalPageStaff;
}

int ChoseStaff(PTR_LIST_STAFF l)
{
	ShowCur(false);
	int key;
	int keyboard_read = 0;
	pageNowStaff = 1;
	currposPrecStaff = 0;
	currposStaff = 0;
	if(l->n != -1)
	{
		OutputListStaffPerPage(l, 0);
		SetDefaultChosenStaff(l, currposStaff);
	}
	
	while(true)
	{
		while(_kbhit())
		{
			keyboard_read = _getch();
			if (keyboard_read == 0)
				keyboard_read = _getch();//cho nhan gia tri nhap vao
			switch (keyboard_read)
			{
				case KEY_UP:
					if(currposStaff % QUANTITY_PER_PAGE > 0)
					{
						currposStaff = currposStaff - 1;
						EffecttiveMenuStaff(currposStaff, l);
					}
					break;
				case KEY_DOWN:
					if (currposStaff % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && currposStaff < l->n)
					{
						currposStaff = currposStaff + 1;
						EffecttiveMenuStaff(currposStaff, l);
					}
					break;
				case PAGE_UP:
					if(pageNowStaff > 1)
					{
						pageNowStaff--;
						ChangePageStaff(l);
						OutputListStaffPerPage(l, (pageNowStaff -1) * QUANTITY_PER_PAGE);
						SetDefaultChosenStaff(l, currposStaff);
					}
					break;
				case PAGE_DOWN:
					if(pageNowStaff < totalPageStaff)
					{
						pageNowStaff++;
						ChangePageStaff(l);
						OutputListStaffPerPage(l, (pageNowStaff -1) * QUANTITY_PER_PAGE);
						SetDefaultChosenStaff(l, currposStaff);
					}
					break;
				case ESC:
					ShowCur(false);
					return -1;
					break;
				case ENTER:
					ShowCur(false);
					return currposStaff;
					break;
			}
		}
	}
}

void inputStaff(PTR_LIST_STAFF &l, PTR_STAFF &st, bool isEdited = false)
{
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	string id, first_name, last_name;
	int sex = 0;

	bool idIsExist = false;
	
	if(isEdited)
	{
		id = st->id;
		first_name = st->first_name;
		last_name = st->last_name;
		sex = st->sex;
		
		//binding data
		Gotoxy(X_ADD + 10, 0 * 3 + Y_ADD);
		cout << id;
		Gotoxy(X_ADD + 10, 1 * 3 + Y_ADD);
		cout << first_name;
		Gotoxy(X_ADD + 10, 2 * 3 + Y_ADD);
		cout << last_name;
		Gotoxy(X_ADD + 10, 3 * 3 + Y_ADD);
		cout << sex;
	}
	
	while(true)
	{
		switch(ordinal)
		{
			case 0:
				if(isEdited) break;
				CheckMoveAndValidateID(id, isMoveUp, ordinal, isSave, 10, 10);
				if(_stricmp(st->id, id.c_str()) == 0)
				{
					idIsExist = true;
					break;
				}else if(FindStaffByID(l, (char *)id.c_str()) == NULL)
				{
					idIsExist = false;
					break;
				}else idIsExist = true;
				break;
			case 1:
				CheckMoveAndValidateString(first_name, isMoveUp, ordinal, isSave,10, 40);
				break;
			case 2:
				CheckMoveAndValidateString(last_name, isMoveUp, ordinal, isSave, 10, 10);
				break;
			case 3:
				CheckMoveAndValidateNumber(sex, isMoveUp, ordinal, isSave,10, 2);
				break;	
		}
		
		if(isMoveUp)
		{
			if(ordinal == 0)
				isMoveUp = false;
			ordinal--;
		}
		else
		{
			if(ordinal == 3)
				isMoveUp = true;
			ordinal++;	
		}
		
		if(isSave)
		{
			if(idIsExist)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ma NV nhap vao khong duoc trung";	
			}else
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << setw(50) << setfill(' ') << " ";
				
				PTR_STAFF temp = new STAFF;
				strcpy(temp->id, id.c_str());
				strcpy(temp->first_name, first_name.c_str());
				strcpy(temp->last_name, last_name.c_str());
				temp->sex = sex;
				
				if(FindStaffByID(l, temp->id) != NULL)
				{
					Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "Nhan Vien da ton tai";
				}else if(DataStaffIsEmty(temp) == true)
				{
					Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "Cac truong du lieu khong duoc de trong";
				}else
				{
					strcpy(st->id, id.c_str());
					strcpy(st->first_name, first_name.c_str());
					strcpy(st->last_name, last_name.c_str());
					st->sex = sex;
					
					if(isEdited)
					{
						int index = FindIndexStaff(l, st->id);
						l->listStaff[index] = st; 
					}
					else
					{
						l->listStaff[++l->n] = new STAFF;
						l->listStaff[l->n] = st;
					}
					
					DeleteMenuAdd();
					totalPageStaff = l->n / QUANTITY_PER_PAGE + 1;
					delete temp;
					return;
				}
			}	
			isSave = false;		
		}else
			isSave = false;
	}
	ShowCur(false);
}

void ChangePageManageStaff(PTR_LIST_STAFF l)
{
	clrscr();
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY NHAN VIEN";
	SortStaff(l);
	OutputListStaffPerPage(l, (pageNowStaff -1) * QUANTITY_PER_PAGE);
	Display(keyDisplayStaff, sizeof(keyDisplayStaff) / sizeof(string));
}

void MenuManageStaff(PTR_LIST_STAFF &l)
{
	backMenu:
		clrscr();
		pageNowStaff = 1;
		totalPageStaff = (l->n - 1) / QUANTITY_PER_PAGE + 1;
		SortStaff(l);
		OutputListStaffPerPage(l, 0);
		
		Display(keyDisplayStaff, sizeof(keyDisplayStaff) / sizeof(string));
		int key;
		Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY NHAN VIEN";
		Gotoxy(X_PAGE, Y_PAGE);
		cout << "Trang " << pageNowStaff << "/" << totalPageStaff;
		
		while(true)
		{
			while(_kbhit)
			{
				key = _getch();
				if(key == 0 || key == 224)
				{
					key = _getch();
					if(key == KEY_F2)
					{
						PTR_STAFF st = new STAFF;
						DisplayEdit(keyDisplayStaff, sizeof(keyDisplayStaff) / sizeof(string), 35);
						inputStaff(l, st);
						pageNowStaff = 1;
						totalPageStaff = (l->n - 1) / QUANTITY_PER_PAGE + 1;
						ChangePageManageStaff(l);
						Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "Them thanh cong";
					}
					else if(key == KEY_F3)
					{
						int k = ChoseStaff(l);
						if(k == -1) goto backMenu;
						Gotoxy(X_NOTIFY, Y_NOTIFY);
						cout << "Ban co chac chan xoa? Enter dong y!";
						key = _getch();
						
						Gotoxy(X_NOTIFY, Y_NOTIFY);
						cout << setw(50) << setfill(' ') << " ";
						if(key == ENTER)
						{
							if(!DeleteStaffIsSuccess(l, l->listStaff[k]->id))
							{
								Gotoxy(X_NOTIFY, Y_NOTIFY);
								cout << "Xoa that bai."<<endl;
								Gotoxy(X_NOTIFY, Y_NOTIFY+2);
								cout << "Nhap phim bat ky de tiep tuc ";
								_getch();
								goto backMenu;	
							}
							else
							{
								clrscr();
								if((l->n + 1) % QUANTITY_PER_PAGE == 0) pageNowStaff--;
								totalPageStaff = (l->n + 1) / QUANTITY_PER_PAGE + 1;
								ChangePageManageStaff(l);
								Gotoxy(X_NOTIFY, Y_NOTIFY);
								cout << "Xoa thanh cong";
							}
						}
						else goto backMenu;
					}
					else if( key == KEY_F4)
					{
						int k = ChoseStaff(l);
						if(k == -1) goto backMenu;
						
						DisplayEdit(keyDisplayStaff, sizeof(keyDisplayStaff) / sizeof(string), 35);
						inputStaff(l, l->listStaff[k], true);
						ChangePageManageStaff(l);
						Gotoxy(X_NOTIFY, Y_NOTIFY);
						cout << "Sua thanh cong";
					}
					else if (key == PAGE_DOWN && pageNowStaff < totalPageStaff)
					{
						
						pageNowStaff++;
						ChangePageManageStaff(l);
					}
					else if (key == PAGE_UP && pageNowStaff > 1)
					{
						
						pageNowStaff--;
						ChangePageManageStaff(l);	
					}
				}
				else if( key == ESC) return;
			}
		}
}

#endif


