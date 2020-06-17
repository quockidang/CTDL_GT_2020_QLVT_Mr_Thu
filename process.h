#ifndef _PROCESSS_H
#define _PROCESSS_H
#include <fstream>//doc ghi file
#include "bill.h"
#include "staff.h"
#include "material.h"


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
			file << k->data.id << endl;
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
						inFile.getline(bill_detail.id, 10, '\n');
						
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
		InputBill(st->list_bill, bill, false);
	
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
