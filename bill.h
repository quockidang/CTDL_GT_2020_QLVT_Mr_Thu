#ifndef _BILL_H
#define _BILL_H

#include "display.h"
#include "billdetails.h"

struct Bill {
	char id[21];
	DateTime created_at;
	char type[2]; // "X" hoac "N";
	
	LIST_BILLDETAILS list_billdetails; // danh sach chi tiet hoa don.
};

typedef struct Bill BILL;

struct NodeBill{
	BILL _bill;
	struct NodeBill *pNext;
};
typedef struct NodeBill NODE_BILL;

// danh sachhoa don
struct ListBill{
	int n = 0;
	NODE_BILL *pHead, *pTail;
};

typedef struct ListBill LIST_BILL;

//
NODE_BILL* GetNodeBill(BILL _bill)
{
	NODE_BILL *p = new NODE_BILL;
	if(p == NULL) return NULL;
	p->_bill = _bill;
	p->pNext = NULL;
	
	return p;
}

void InitListBill(LIST_BILL &l)
{
	l.pHead = l.pTail = NULL;
}

void AddHeadListBill(LIST_BILL &l, BILL bill)
{
	NODE_BILL *p = GetNodeBill(bill);
	p->pNext = l.pHead;
	l.pHead = p;
	++l.n;
}

bool ListBillIsEmty(LIST_BILL l)
{
	return l.pHead = NULL;
}

void AddTailListBill(LIST_BILL &l, BILL bill)
{
	NODE_BILL *p = GetNodeBill(bill);
	if(l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
	++l.n;
}

NODE_BILL* FindBill(LIST_BILL l, char* id)
{
	if(l.pHead == NULL) return NULL;
	
	for(NODE_BILL* p =l.pHead; p != NULL; p = p->pNext)
	{
		if(strcmp(p->_bill.id, id) == 0)
		{
			return p;
		}
	}
	
	return NULL;
}

int FindIndexBill(LIST_BILL l, char* id)
{
	int index = -1;
	if(l.pHead == NULL) return NULL;
	for(NODE_BILL *p = l.pHead; p != NULL; p = p->pNext)
	{
		++index;
		if(strcmp(p->_bill.id, id) == 0)
		{
			return index;
		}
	}
	return 0;
}

NODE_BILL* FindBillByOrdinal(LIST_BILL l, int ordinal)
{
	if (l.pHead == NULL) return NULL;
	if (l.n -1 < ordinal) return NULL;
	if (l.n - 1 == ordinal) return l.pTail;
	if (ordinal == 0) return l.pHead;
	
	NODE_BILL* p = l.pHead;
	int count = 0;
	while(count != ordinal)
	{
		p = p->pNext;
		count++;
	}
	return p;
}

void InsertAffter(NODE_BILL* p, BILL &data)
{
	if(p == NULL) return;
	NODE_BILL* q = new NODE_BILL;
	
	q->_bill = data;
	q->pNext = p->pNext;
	p->pNext = q;
}

void InsertOrderForListBill (LIST_BILL &l, BILL data)
{
	if(l.pHead == NULL)
	{
		AddHeadListBill(l, data);
		return;
	}
	
	NODE_BILL *p, *pAffter, *pBefore;
	
	p = GetNodeBill(data);
	
	for(pAffter = l.pHead; pAffter != NULL && (strcmp(pAffter->_bill.id, data.id) < 0); pBefore = pAffter, pAffter = pAffter->pNext);
	
	if(pAffter == l.pHead)
	{
		AddHeadListBill(l, p->_bill);
		return;
	}
	else
	{
		p->pNext = pAffter;
		p->pNext = p;
		l.n++;
		return;
	}
}

bool IsDeletedHead(LIST_BILL &l)
{
	if(ListBillIsEmty(l)) return false;
	NODE_BILL *p =l.pHead; 
	
	l.pHead = p->pNext;
	delete p;
	--l.n;
	return true;
}

bool IsDeletedTail(LIST_BILL &l)
{
	if(ListBillIsEmty(l)) return false;
	
	NODE_BILL *beforeP = NULL;
	for (NODE_BILL *p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p == l.pTail)
		{
			l.pTail = beforeP;
			beforeP->pNext = NULL;
			delete p;
						
			--l.n;
			return true;
		}
		beforeP = p;
	}
}

bool IsDeleteAffter(ListBill &l, NODE_BILL *p)
{
	if (p == NULL || p->pNext == NULL) return false;
	NODE_BILL* nodeDeleted = p->pNext;
	p->pNext = nodeDeleted->pNext;
	delete nodeDeleted;
	--l.n;
	return true;
}

bool IsDeleteBillById(LIST_BILL &l, BILL data)
{
	NODE_BILL* nodeDeleted = FindBill(l, data.id);
	if (nodeDeleted == NULL) return false;
	if (nodeDeleted == l.pHead) return IsDeletedHead(l);
	if (nodeDeleted == l.pTail) return IsDeletedTail(l);
	else
	{
		NODE_BILL* temp = l.pHead;
		while (temp->pNext != nodeDeleted)
			temp = temp->pNext;
		return IsDeleteAffter(l,temp);
	}
}


NODE_BILL* FindBillByOridnal(LIST_BILL l, int thuTu )
{
	if (l.pHead == NULL) return NULL;//rong
	if (l.n -1 < thuTu) return NULL;
	if (thuTu == 0) return l.pHead;//dung dau
	if (l.n - 1 == thuTu) return l.pTail;//dung cuoi
	
	/*int count = -1;
	for (NODE_FLIGHT *p = l.pHead; p != NULL; p = p->pNext)
	{
		++count;
		if (count == ordinal) return p;
	}*/
	NODE_BILL *p = l.pHead;
	int count = 0;
	while (count != thuTu)//count == thuTu thi thoat khoi vong lap => tim ra duoc p
	{
		p = p->pNext;
		count++;
	}
	return p;
}

//nhap Thoi gian
void InputDatime(DATETIME &dt)
{
	int newOrdinal = 0;
	bool newIsMoveUp = false;
	bool newIsSave = false;
	Gotoxy(X_ADD + 12 + 2, 3 * 2 + Y_ADD);
	cout << ":";
	Gotoxy(X_ADD + 12 + 8, 3 * 2 + Y_ADD);
	cout << "/";
	Gotoxy(X_ADD + 12 + 11, 3 * 2 + Y_ADD);
	cout << "/";
	while (true)
	{
 		switch (newOrdinal)
		{
		case 0://check gio
			CheckMoveAndValidateDateTime(dt.h, newIsMoveUp, newOrdinal, newIsSave, 23, 12);
			break;
		case 1://check phut
			CheckMoveAndValidateDateTime(dt.mi, newIsMoveUp, newOrdinal, newIsSave, 59, 12);
			break;
		case 2://check ngay
			CheckMoveAndValidateDateTime(dt.d, newIsMoveUp, newOrdinal, newIsSave, 31, 12);
			break;
		case 3://check thang
			CheckMoveAndValidateDateTime(dt.m, newIsMoveUp, newOrdinal, newIsSave, 12, 12);
			break;
		case 4://check nam
			CheckMoveAndValidateDateTime(dt.y, newIsMoveUp, newOrdinal, newIsSave, 10000, 12);
			break;
		} // end switch newordinal
		
		//check move
		if (newIsMoveUp)
		{
			if (newOrdinal == 0)
				newIsMoveUp = false;
			else
				newOrdinal--;
		}
		else
		{
			if (newOrdinal == 4)
			{
				newIsMoveUp = true;
				return;
			}
			else
				newOrdinal++;
		}
		//--end check move

		if (newIsSave)
			return;
		else
			newIsSave = false;
	} // end while
}

void OutputBill(BILL bill, int locate)
{
	DeleteOldData(sizeof(keyDisplayBill) /sizeof(string), locate);
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + locate); cout << bill.id;
	Gotoxy(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + locate); OutputDateTime(bill.created_at);
	Gotoxy(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + locate);
	if(strcmp(bill.id, "N") == 0)
		cout << "Nhap";
	else
		cout << "Xuat";
}

void OutputListBill (LIST_BILL l)
{
	if(l.pHead == NULL && l.pTail  == NULL) return;
	int count = -1;
	for(NODE_BILL* k = l.pHead; k != NULL; k = k->pNext)
	{
		count++;
		OutputBill(k->_bill, count);
	}
}

void OutputListBillPerPage (LIST_BILL l, int indexBegin)
{
	if (l.pHead == NULL && l.pTail == NULL) return;
	int count = -1;
	
	for(NODE_BILL* k = l.pHead; k != NULL; k = k->pNext)
	{
		count++;
		if(count == indexBegin)
		{
			int i = -1;
			while(k != NULL && i < QUANTITY_PER_PAGE -1)
			{
				OutputBill(k->_bill, (++i) * 2);
				k = k->pNext;
			}
			break;
		}
	}
	
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowBill << "/" << totalPageBill;
	return;
}

void InputBill (LIST_BILL &l, BILL &bl, bool isEdited = false)
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
				if(FindBill(l, (char*)id.c_str()) == NULL)
				{
					idIsExist = false;
					break;
				}
				idIsExist = true;
				break;
			case 1:
				InputDatime(dt);
				break;
			case 2:
				CheckMoveAndValidateTypeBill(type, isMoveUp, ordinal, isSave, 20, 21);
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
			if (ordinal == 4)
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
				InsertOrderForListBill(l, bl);
				DeleteMenuAdd();
				return;	
			}
			isSave = false;
		}else
			isSave = false;
	}
	ShowCur(false);
}
#endif
