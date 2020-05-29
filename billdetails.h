#ifndef _BILLDETAILS_H
#define _BILLDETAILS_H



struct BillDetails {
	char id[11];
	int quantity;
	float price;
	int VAT;
};

typedef struct BillDetails BILL_DETAILS;  // khai bao cau truc chi tiet hoa don

// node CTHD
struct NodeBill_Details{
	BILL_DETAILS data;
	struct NodeBill_Details *pNext;
};

typedef struct NodeBill_Details NODE_BILLDETAILS;

// danh sach chi tiet hoa don

struct ListBillDetails{
	int n = 0;
	NODE_BILLDETAILS *pHead, *pTail;
};

typedef struct ListBillDetails LIST_BILLDETAILS;

//khoi tao danh sach lien ket don
void InitListBillDetails(LIST_BILLDETAILS &l)
{
	l.pHead = l.pTail = NULL;
}

// khoi tao moi BILL DETAILS de them vao danh sach

NODE_BILLDETAILS* GetNodeBillDetails( BILL_DETAILS data){
	NODE_BILLDETAILS *p = new NODE_BILLDETAILS; //cap phat 1 NODE_BILLDETAILS cho dslk, tra ve dia chi cho nut vua cap phat
	if (p == NULL)
	{
		cout<<"Cap phat vung nho that bai!";
		return NULL;
	}		
	p->data = data; // dua DATA vao data cua p
	p->pNext = NULL;//node p chua co lien ket voi node nao het
	return p;
}

// check ds CTHD co rong hay khong
bool ListBillDTIsEmty(LIST_BILLDETAILS l){
	return l.pHead == NULL;
}


void AddHeadListStudent(LIST_BILLDETAILS &l, BILL_DETAILS data)
{

	NODE_BILLDETAILS *p = GetNodeBillDetails(data);
	p->pNext = l.pHead;
	l.pHead = p;

	++l.n;
}

void AddTailListBillDetails(LIST_BILLDETAILS &l, BILL_DETAILS data)
{
	NODE_BILLDETAILS *p = GetNodeBillDetails(data);
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

NODE_BILLDETAILS* FindBill(LIST_BILLDETAILS l, char* id)
{
	if(l.pHead == NULL) return NULL;
	
	for(NODE_BILLDETAILS* p = l.pHead; p != NULL; p = p->pNext)
		if (strcmp(p->data.id, id) == 0)
			return p;
	return NULL;
}

void InsertAfter(NODE_BILLDETAILS* p, BILL_DETAILS &data)
{
	if(p == NULL) return;
	NODE_BILLDETAILS* q = new NODE_BILLDETAILS;
	
	q->data = data;
	q->pNext = p->pNext;
	p->pNext = q;
}

bool IsDeletedHead(LIST_BILLDETAILS &l)
{
	if(ListBillDTIsEmty(l)) return false;
	NODE_BILLDETAILS *p =l.pHead; 
	
	l.pHead = p->pNext;
	delete p;
	--l.n;
	return true;
}

bool IsDeletedTail(LIST_BILLDETAILS &l)
{
	if(ListBillDTIsEmty(l)) return false;
	
	NODE_BILLDETAILS *beforeP = NULL;
	for (NODE_BILLDETAILS *p = l.pHead; p != NULL; p = p->pNext)
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

bool IsDeletedAfter(LIST_BILLDETAILS &l, NODE_BILLDETAILS*p)
{
	if (p == NULL || p->pNext == NULL) return false;
	NODE_BILLDETAILS* nodeDeleted = p->pNext;
	p->pNext = nodeDeleted->pNext;
	delete nodeDeleted;
	--l.n;
	return true;
}



#endif

