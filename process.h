#ifndef _PROCESSS_H
#define _PROCESSS_H
#include <fstream>//doc ghi file

#include "staff.h"



// -----------------DOC GHI FILE VAT TU--------------------------
void SaveMaterial(TREE_MATERIAL t, fstream &file) // save vat tu
{
	file << t->_material.id << endl;
	file << t->_material.material_name << endl;
	file << t->_material.unit<< endl;
	file << t->_material.quantity_exists << endl;
}

void WriteMaterialToFile(TREE_MATERIAL t, fstream &file)
{
	if(t != NULL)
	{
		SaveMaterial(t, file);
		WriteMaterialToFile(t->pLeft, file);
		WriteMaterialToFile(t->pRight, file);
	}
}


void SaveMaterialToFile(TREE_MATERIAL t)
{
	
	fstream outFile;
	outFile.open("DSVT.txt", ios::out);
	if (outFile.is_open())
	{
		
		outFile << nMaterial << endl;
		WriteMaterialToFile(t, outFile);
	}
	else
	{
		cout << "KET NOI VOI FILE DSHK THAT BAI! ";
	}
	outFile.close();
}

void LoadMaterialFromFile(TREE_MATERIAL &t)
{
	fstream inFile;
	MATERIAL ma;
	int n;
	
	inFile.open("DSVT.txt", ios::in);
	if (inFile.is_open())
	{
		string temp;		
		inFile >> n;
		
		for(int i = 0; i <= n; i++)
		{
			getline(inFile, temp);
			inFile.getline(ma.id, 10, '\n');
			inFile.getline(ma.material_name, 30, '\n');
			inFile.getline(ma.unit, 10, '\n');
			inFile >> ma.quantity_exists;
			
			InsertMaterialToTree(t, ma);
		}
	}
	else {
		cout << "KET NOI VOI FILE DSHK THAT BAI! ";
	}

	inFile.close();
}

// ---------------------- DOC GHI FILE NHAN VIEN
void SaveStaff(PTR_STAFF st, fstream &file)
{
	file << st->id << endl;
	file << st->first_name << endl;
	file << st->last_name << endl;
	file << st->sex << endl;
	
	file << st->list_bill.n << endl;
	for(NODE_BILL* p = st->list_bill.pHead; p!= NULL; p = p->pNext)
	{
		file << p->_bill.id << endl;
		
		file << p->_bill.created_at.y << endl;
		file << p->_bill.created_at.m << endl;
		file << p->_bill.created_at.d << endl;
		file << p->_bill.created_at.h << endl;
		file << p->_bill.created_at.mi << endl;
		file << p->_bill.type << endl;
		
		file << p->_bill.list_billdetails.n << endl;
		for(NODE_BILLDETAILS* k = p->_bill.list_billdetails.pHead; k != NULL; k = k->pNext)
		{
			file << k->data.MaVT << endl;
			file << k->data.price << endl;
			file << k->data.quantity << endl;
			file << k->data.VAT << endl;
		}		
	}
}

void SaveStaffToFile(PTR_LIST_STAFF l)
{
	fstream outFile;
	outFile.open("DSNV.txt", ios::out );
	if (outFile.is_open())
	{
		outFile << l->n <<endl;
		for(int i = 0; i<= l->n;i++)
		{
			SaveStaff(l->listStaff[i], outFile);
		}
	}else
	{
		
		cout << "KET NOI VOI FILE THAT BAI! ";
	}
	
	outFile.close();
}

void LoadStaffFromFile(PTR_LIST_STAFF &l)
{
	fstream inFile;
	
	int nStaff, nBill, nBillDetail;
	
	inFile.open("DSNV.txt", ios::in);
	
	if(inFile.is_open())
	{
		string temp;		
		inFile >> nStaff;
		
		for(int i = 0; i <= nStaff; i++)
		{
			l->listStaff[i] = new STAFF;
			getline(inFile, temp);
			
			inFile.getline(l->listStaff[i]->id, 10, '\n');
			inFile.getline(l->listStaff[i]->first_name, 40, '\n');
			inFile.getline(l->listStaff[i]->last_name, 10, '\n');
			inFile >> l->listStaff[i]->sex;
			
			inFile >> nBill;
			
			InitListBill(l->listStaff[i]->list_bill);
			
			BILL bill;
			for(int j = 0; j < nBill; j++)
			{
				getline(inFile, temp);
				inFile.getline(bill.id, 20, '\n');
				
				inFile >> bill.created_at.y;
				inFile >> bill.created_at.m;
				inFile >> bill.created_at.d;
				inFile >> bill.created_at.h;
				inFile >> bill.created_at.mi;
				
				getline(inFile, temp);
				inFile.getline(bill.type, 2, '\n');
				
				
				
				inFile >> nBillDetail;
				InitListBillDetails(bill.list_billdetails);
				
				BILL_DETAILS bill_detail;
				for(int k = 0; k < nBillDetail ; k++)
				{
						getline(inFile, temp);
						inFile.getline(bill_detail.MaVT, 10, '\n');
						
						inFile >> bill_detail.price;
						inFile >> bill_detail.quantity;
						inFile >> bill_detail.VAT;
						
						AddTailListBillDetails(bill.list_billdetails, bill_detail);
				}
				
				AddTailListBill(l->listStaff[i]->list_bill, bill);
			}
		++l->n;
		}
	}
	
	inFile.close();
}

// Create Order

void InputBillDetail(LIST_BILLDETAILS &l, TREE_MATERIAL t, BILL bill, BILL_DETAILS &bd, bool isEdited = false)
{
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	bool idIsExist = false;
	string MAVT;
	
	int quantity, VAT, price;
	while (true)
	{
		//input
		switch (ordinal)
		{
			case 0:
			{	if(isEdited) break;			
				CheckMoveAndValidateID(MAVT, isMoveUp, ordinal, isSave, 10, 10);			
				if (FindBillDetail(l, (char *)MAVT.c_str()) == NULL)
				{
					idIsExist = false;
					break;
				}
				idIsExist = true;
				break;
			}
			case 1:
			{
				CheckMoveAndValidateNumber(quantity, isMoveUp, ordinal, isSave, 10, 1000000000);
				break;			
			}					
			case 2:
			{
				CheckMoveAndValidateNumber(price, isMoveUp, ordinal, isSave, 10, 1000000000);
				break;
			}
			case 3:
			{
				CheckMoveAndValidateNumber(VAT, isMoveUp, ordinal, isSave, 10, 1000000000);
				break;
			}
		
		}//end switch

		 //--move
		if (isMoveUp)
		{
			if (ordinal == 0)
				isMoveUp = false; //block move up
			ordinal--;
		}
		else
		{
			if (ordinal == 3)
				isMoveUp = true; //block move down
			ordinal++;
		}
		//--end move

		if (isSave)
		{
			//binding data
			strcpy(bd.MaVT, MAVT.c_str());
			bd.quantity = quantity;
			bd.price = price;
			bd.VAT = VAT;
			
			NODE_MATERIAL* VT = FindMaterial(t, bd.MaVT);
			
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";
			
			if(VT == NULL)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "MA VT khong ton tai ";
			}else if((strcmp(bill.type, "X") == 0) && VT->_material.quantity_exists < bd.quantity){
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "So luong ton hien co: " << VT->_material.quantity_exists << " " << VT->_material.unit;
			}
			else
			{
				int soluongton;
				if(strcmp(bill.type, "N") == 0)
				{
					soluongton = VT->_material.quantity_exists + bd.quantity;
					VT->_material.quantity_exists = soluongton;
				}else{
					soluongton =  VT->_material.quantity_exists - bd.quantity;
					VT->_material.quantity_exists = soluongton;
				}
				AddTailListBillDetails(l, bd);
				DeleteMenuAdd();
				return;
			}
			isSave = false;
		}
		else
			isSave = false;
	}
	ShowCur(false);
}

void OutputListBD(LIST_BILLDETAILS l)
{
	if (l.pHead == NULL && l.pTail == NULL) return;
	int count = -1;

	for (NODE_BILLDETAILS* q = l.pHead; q != NULL; q = q->pNext)
	{
		count++;
		OutputBillDetails(q->data, count * 2);
	}
}

//tim Flight theo thu tu truyen vao
NODE_BILLDETAILS* FindBillDetailByOridnal(LIST_BILLDETAILS l, int thuTu )
{
	if (l.pHead == NULL) return NULL;//rong
	if (l.n -1 < thuTu) return NULL;
	if (thuTu == 0) return l.pHead;//dung dau
	if (l.n - 1 == thuTu) return l.pTail;//dung cuoi
	

	NODE_BILLDETAILS *p = l.pHead;
	int count = 0;
	while (count != thuTu)//count == thuTu thi thoat khoi vong lap => tim ra duoc p
	{
		p = p->pNext;
		count++;
	}
	return p;
}
void SetDefaultChosenBillDetail(BILL_DETAILS bd, int ordinal)
{
	SetBGColor(1);
	OutputBillDetails(bd, ordinal  * 2);
	SetBGColor(0);
}
void  EffectiveMenuBillDetails(int ordinal, BILL_DETAILS flNew, BILL_DETAILS flOld)
{
	int current = ordinal;
	SetDefaultChosenBillDetail(flNew, current);
	OutputBillDetails(flOld, currposPrecBillDetail  * 2);
	currposPrecBillDetail = current;
}

NODE_BILLDETAILS* ChooseBillDetails(LIST_BILLDETAILS l)
{
	int keyboard_read = 0;
	ShowCur(false);

	currposBillDetail = 0;
	currposPrecBillDetail = 0;

	
	NODE_BILLDETAILS* newNodeBD = FindBillDetailByOridnal(l, currposBillDetail);
	NODE_BILLDETAILS* oldNodeBD = NULL;
	Display(keyDisplayBillDetail, sizeof(keyDisplayBillDetail) / sizeof(string));
	OutputListBD(l);
	SetDefaultChosenBillDetail(newNodeBD->data, currposBillDetail);
	while (true)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();
		switch (keyboard_read)
		{
		case KEY_UP:
			if (currposBillDetail > 0)
			{
				currposBillDetail = currposBillDetail - 1;
				oldNodeBD = newNodeBD;
				for (newNodeBD = l.pHead; newNodeBD->pNext != oldNodeBD; newNodeBD = newNodeBD->pNext);
				EffectiveMenuBillDetails(currposBillDetail, newNodeBD->data, oldNodeBD->data);
			}
			break;
		case KEY_DOWN:
			if (currposBillDetail  < l.n && newNodeBD->pNext != NULL) //&& currposFlight < 3)
			{
				currposBillDetail = currposBillDetail + 1;
				oldNodeBD = newNodeBD;
				newNodeBD = newNodeBD->pNext;
				EffectiveMenuBillDetails(currposBillDetail, newNodeBD->data, oldNodeBD->data);
			}
			break;
		
		case ENTER:  //enter
			ShowCur(true);
			return newNodeBD;
			break;
		case 27: 
			return NULL; 
			break;
		}//end switch  read key
	}
}

void MenuManageBillDetail(LIST_BILLDETAILS &l, BILL bill, TREE_MATERIAL t)
{
backMenu:
	system("cls");
	OutputListBD(l);
	Display(keyDisplayBillDetail, sizeof(keyDisplayBillDetail) / sizeof(string));

	Gotoxy(X_TITLE, Y_TITLE); cout << "Nhap CTHD cho HD: " << bill.id << " Loai: " << bill.type ;
	int key;
	while (true)
	{
		while (_kbhit())
		{
			key = _getch();
			if (key == 0 || key == 224)
			{
				key = _getch();
				
				if (key == KEY_F2) //f2
				{
					BILL_DETAILS bd;
					DisplayEdit(keyDisplayBillDetail, sizeof(keyDisplayBillDetail) / sizeof(string), 35);
					InputBillDetail(l, t, bill, bd, false);
					
					OutputListBD(l);
					
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Them thanh cong";
				}
				else if (key == KEY_F3) //f3
				{	
					clrscr();
					Gotoxy(X_TITLE, Y_TITLE); cout << "Nhap CTHD cho HD: " << bill.id << " Loai: " << bill.type ;
					
					NODE_BILLDETAILS* k = ChooseBillDetails(l);
					if(k == NULL) goto backMenu;

					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Ban co chan chan xoa? ENTER == dong y";
					key = _getch();
					if(key == ENTER)
					{
						clrscr();
						Gotoxy(X_TITLE, Y_TITLE); cout << "Nhap CTHD cho HD: " << bill.id << " Loai: " << bill.type ;
						Display(keyDisplayBillDetail, sizeof(keyDisplayBillDetail) / sizeof(string));
					    bool nodeDeleted = IsDeletedBillDetailWithId(l, k->data);
					    
					    if(nodeDeleted)
						{						    	
						    int soluongton;
						    NODE_MATERIAL* VT = FindMaterial(t, k->data.MaVT);
						    if(strcmp(bill.type, "N") == 0)
							{
								soluongton = VT->_material.quantity_exists - k->data.quantity;
								VT->_material.quantity_exists = soluongton;
							}else{
								soluongton =  VT->_material.quantity_exists + k->data.quantity;
								VT->_material.quantity_exists = soluongton;
							}						    	
						    Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa thanh cong";
							OutputListBD(l);
						}else
						{
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa that bai chon phim bat ki de tiep tuc";
							_getch();
							goto backMenu;
						}
					}
				}else{
					goto backMenu;
				}
			}else if (key == ESC)
				return;
		}//end while kbhit
	}
}
void InputBill (LIST_BILL &l, BILL &bl, PTR_LIST_STAFF lst, bool isEdited = false)
{
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	bool idIsExist = false;
	
	string id, type;
	DATETIME dt;
	
	Gotoxy(X_NOTIFY, Y_NOTIFY + 1);
	cout << "F10 luu ngay gio";
	

	
	while(true)
	{
		// input
		switch(ordinal)
		{
			case 0:
				CheckMoveAndValidateID(id, isMoveUp, ordinal, isSave, 20, 20);
				
				for(int i = 0; i <= lst->n; i++)
				{
					for(NODE_BILL* k = lst->listStaff[i]->list_bill.pHead; k != NULL; k = k->pNext)
					{
						if(strcmp(k->_bill.id, (char *)id.c_str()) == 0){
							idIsExist = true;
							break;
						}
					}
				}
				
			case 2:
				InputDatime(dt);
				break;
			case 1:
				CheckMoveAndValidateTypeBill(type, isMoveUp, ordinal, isSave, 20, 1);
				break;
		}
		
		if (isMoveUp)
		{
			if (ordinal == 0)
				isMoveUp = false; //block move up
			ordinal--;
		}
		else
		{
			if (ordinal == 2)
				isMoveUp = true; //block move down
			ordinal++;
		}
		//--end move
		
		if(isSave)
		{
			//binding data
			strcpy(bl.id, id.c_str());
			strcpy(bl.type, type.c_str());
			bl.created_at = dt;
			
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";
			if(!DateTimeIsValid(bl.created_at))
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ngay gio khong hop le. Phai lon hon gio he thong";
			}else if(strlen(bl.id) == 0 || strlen(bl.type) == 0)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Cac truong du lieu khong dc de trong";
			}
			else if (idIsExist)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ma HD khong duoc trung";
			}else
			{
				AddTailListBill(l, bl);
				DeleteMenuAdd();
				return;	
			}
			isSave = false;
		}else
			isSave = false;
	}
	ShowCur(false);
}

void CreateOrder(PTR_LIST_STAFF &l, TREE_MATERIAL &t)
{
	backMenu:
		
		string MaNV;
		Gotoxy(X_ADD, Y_ADD);
		cout << "Nhap vao ma nhan vien:   ";
		cin >> MaNV;
		
		PTR_STAFF st = FindStaffByID(l, (char *)MaNV.c_str());
		
		if(st == NULL)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << "Ma NV khong ton tai";
			Gotoxy(X_ADD, Y_ADD);
			cout << setw(60) << setfill(' ') << " ";
			goto backMenu;
		} 
		clrscr();
		
		BILL bill;
		DisplayEdit(keyDisplayBill, sizeof(keyDisplayBill) / sizeof(string), 35);
		InputBill(st->list_bill, bill, l, false);
		NODE_BILL* ptrBill = FindBill(st->list_bill, bill.id);
		
		InitListBillDetails(ptrBill->_bill.list_billdetails);
		clrscr();
		
		MenuManageBillDetail(ptrBill->_bill.list_billdetails, ptrBill->_bill, t);
}


void Main_Menu(PTR_LIST_STAFF &ls, TREE_MATERIAL &t)
{
	int chon; 
	
	do
	{
		chon = MenuDong(thucdon);
		clrscr();
		switch(chon)
		{
			case 1: MenuManageStaff(ls); break;
			case 2: MenuMaterialManager(t); break;
			case 3:  CreateOrder(ls, t);
			case 4:  break;
			case 5: break;
			case 6:  break;
			case 7: break;
			case 8: return;
		}
	}while(1);
}

#endif
