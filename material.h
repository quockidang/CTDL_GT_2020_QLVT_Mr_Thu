#ifndef _MATERIAL_H
#define _MATERIAL_H
#include<string.h>

#include "display.h"

struct Material{  // vat tu
	char id[11]; //ma VT
	char material_name[31]; // ten VT
	char unit[11]; // don vi tinh
	int quantity_exists; // so luong ton
};
typedef struct Material MATERIAL;

struct NodeMaterial{
	MATERIAL _material;
	struct NodeMaterial *pLeft, *pRight;
};
typedef struct NodeMaterial NODE_MATERIAL;

typedef NODE_MATERIAL* TREE_MATERIAL;
TREE_MATERIAL binaryTree = NULL;
TREE_MATERIAL rp;

int indexOutMaterial = -1;

MATERIAL arrMaterial[500];
// ------------------------------------ DEFINE TREE MATERIAL ------------------------------

// KHOI TAO CAY NHI PHAN
void InitTreeMaterial(TREE_MATERIAL &root)
{
	nMaterial = -1;
	root = NULL;	
}

// check emty
bool IsEmty(TREE_MATERIAL t)
{
	return (t == NULL ? true : false);	
}

// check ma VT da ton tai
bool CheckIDExists(TREE_MATERIAL t, char* id)
{
	if( t != NULL) // cay k rong
	{
		if(strcmp(id, t->_material.id) == 0) // string compare
			return true;
		else if( strcmp(id, t->_material.id) < 0)
			CheckIDExists(t->pLeft, id);
		else if( strcmp(id, t->_material.id) > 0)
			CheckIDExists(t->pRight, id);
	}
	
	return false;
}

// Tim Vat tu trong cay
NODE_MATERIAL* FindMaterial(TREE_MATERIAL t, char* id)
{
	if(t != NULL)
	{
		NODE_MATERIAL* p = t;
		while(p != NULL)
		{
			if(strcmp(id, p->_material.id) == 0)
				return p;
			else if(strcmp(id, p->_material.id) > 0)
				p = p->pRight;
			else
				p = p->pLeft;
		}
	}
	
	return NULL;
}

// them data vao cay
void InsertMaterialToTree(TREE_MATERIAL &t, MATERIAL data)
{
	// tree emty, data is root of tree
	if(t == NULL)
	{
		NODE_MATERIAL* p = new NODE_MATERIAL;
		p->_material = data;
		p->pLeft = p->pRight = NULL;
		t = p;
		
		arrMaterial[++nMaterial] = data;				
	}else{
		
		if(strcmp(data.id, t->_material.id) < 0)
			InsertMaterialToTree(t->pLeft, data);
		else if(strcmp(data.id, t->_material.id) > 0)
			InsertMaterialToTree(t->pRight, data);		
	}
}

void QuickSort(int left, int right, MATERIAL arr[]) {	
	MATERIAL key = arr[(left + right) / 2]; 
	MATERIAL temp;
	int i = left;
	int j = right;
	do {
		while(strcmpi(arr[i].material_name , key.material_name) < 0 ) i++;
	
		while(strcmpi(arr[j].material_name, key.material_name) > 0) j--;
		if (i <= j) {			
			if(i < j)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			i++; j--;
		}
	} while (i <= j);
	if (left < j) QuickSort(left, j, arr);
	if (right > i) QuickSort(i, right, arr);
}

void DeleteMaterialCase_3 ( TREE_MATERIAL &r )
{
	if (r->pLeft != NULL)
		DeleteMaterialCase_3 (r->pLeft);
	//den day r la nut cuc trai cua cay con ben phai co nut goc la rp}
	else
	{
		rp->_material = r->_material; //Chep noi dung cua r sang rp ; // de lat nua free(rp)
		rp = r;
		r = rp->pRight;
	}
}

void FindReplace(NODE_MATERIAL* &p, NODE_MATERIAL* &q)
{
	if (q->pRight != NULL)
	{
		FindReplace(p, q->pRight);
	}
	else
	{
		p->_material = q->_material;
		p = q;
		q = q->pLeft;
	}
}

// xoa vat tu trong tree
bool IsDeleteMaterial(TREE_MATERIAL &t, MATERIAL x)
{
	if(t == NULL)
	{
		return false;
	}
	else
	{
		if(strcmp(x.id,t->_material.id) > 0)
			IsDeleteMaterial(t->pRight, x);
		else if(strcmp(x.id,t->_material.id) < 0)
			IsDeleteMaterial(t->pLeft, x);
		else // data.id == t->data.id
		{
			NODE_MATERIAL* temp = t;
			if(t->pLeft == NULL)
				t = t->pRight;
			else if(t->pRight == NULL)
				t = t->pLeft;
			else // node co 2 child
			{
				DeleteMaterialCase_3(t->pRight);
			}
			delete temp;			
			return true;
		}
	}
}


void OutputMaterial(MATERIAL data, int locate) // vi tri == locate
{
	DeleteOldData(sizeof(keyDisplayMaterial) / sizeof(string), locate);	
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + locate); cout << data.id;
	Gotoxy(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + locate); cout << data.material_name;
	Gotoxy(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + locate); cout << data.unit;
	Gotoxy(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + locate); cout << data.quantity_exists;
}

void OutputListMaterial(TREE_MATERIAL t)
{
	if (t != NULL)
	{
		OutputListMaterial(t->pLeft);
		OutputMaterial(t->_material, ++indexOutMaterial);
		OutputListMaterial(t->pRight);
	}
}

void OutputListMaterialPerPage(TREE_MATERIAL t , int indexBegin)
{
	for(int i = 0; i + indexBegin <= nMaterial && i < QUANTITY_PER_PAGE; i++)
	{
		
		
		NODE_MATERIAL* m = FindMaterial(t, arrMaterial[i + indexBegin].id);
		//if(s == NULL) cout << "Fail";
		
		OutputMaterial(m->_material, i * 2);
	}
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang "<< pageNowMaterial << "/" << totalPageMaterial;
}

void SetDefaultChosenMaterial(MATERIAL p, int ordinal)
{
	SetBGColor(1);
	OutputMaterial(p, (ordinal % QUANTITY_PER_PAGE) * 2);
	SetBGColor(0);
}

void EffectiveMenuMaterial(int index, MATERIAL newMaterial, MATERIAL oldMaterial)
{
	int current = index;

	SetBGColor(1);
	OutputMaterial(newMaterial, (current % QUANTITY_PER_PAGE) * 2);
	SetBGColor(0);
	OutputMaterial(oldMaterial, (currposPrecMaterial % QUANTITY_PER_PAGE)  * 2);
	currposPrecMaterial = current;
}

void ChangePageMaterial(TREE_MATERIAL t)
{
	currposMaterial = (pageNowMaterial - 1) * QUANTITY_PER_PAGE;
	currposPrecMaterial = (pageNowMaterial - 1) * QUANTITY_PER_PAGE;
	clrscr();
	Display(keyDisplayMaterial, sizeof(keyDisplayMaterial) / sizeof(string));
	DeleteNote(sizeof(keyDisplayMaterial) / sizeof(string));
}

NODE_MATERIAL* ChooseMaterial(TREE_MATERIAL &t)
{
	if(t == NULL) return NULL;
	
	ShowCur(false);
	
	int key;
	int keyboard_read = 0;
	int PASS = 1;
	
	QuickSort(0, nMaterial, arrMaterial);
	Display(keyDisplayMaterial, sizeof(keyDisplayMaterial) / sizeof(string));
	
	pageNowMaterial = 1;
	currposMaterial = (pageNowMaterial - 1) * QUANTITY_PER_PAGE;
	currposPrecMaterial = (pageNowMaterial -1) * QUANTITY_PER_PAGE;
	
	NODE_MATERIAL* newMaterial = FindMaterial(t, arrMaterial[0].id);
	
	OutputListMaterialPerPage(t, 0);
	SetDefaultChosenMaterial(newMaterial->_material, currposMaterial);
	
	NODE_MATERIAL* oldMaterial = NULL;
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowMaterial << "/" << totalPageMaterial;
	
	while (PASS)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();

		switch (keyboard_read)
		{

		
			case KEY_UP:
				if(currposMaterial % QUANTITY_PER_PAGE > 0)
				{
					currposMaterial = currposMaterial - 1;
					oldMaterial = newMaterial;
					
					newMaterial = FindMaterial(t, arrMaterial[currposMaterial].id);
					EffectiveMenuMaterial(currposMaterial, newMaterial->_material, oldMaterial->_material);
				}							
				break;
				
			case KEY_DOWN:
				if (currposMaterial % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && currposMaterial < nMaterial)
				{
					currposMaterial = currposMaterial + 1;
					oldMaterial = newMaterial;
					
					newMaterial = FindMaterial(t, arrMaterial[currposMaterial].id);
					EffectiveMenuMaterial(currposMaterial, newMaterial->_material, oldMaterial->_material);
				}
				break;
			case PAGE_DOWN:
				if(pageNowMaterial < totalPageMaterial)
				{
					pageNowMaterial++;
					ChangePageMaterial(t);
					
					newMaterial = FindMaterial(t, arrMaterial[currposMaterial].id);
					oldMaterial = newMaterial;
					
					OutputListMaterialPerPage(t, (pageNowMaterial - 1) * QUANTITY_PER_PAGE);
					SetDefaultChosenMaterial(newMaterial->_material, currposMaterial);
				}
				break;
			case PAGE_UP:
				if(pageNowMaterial > 1)
				{
					pageNowMaterial--;
					ChangePageMaterial(t);
					
					newMaterial = FindMaterial(t, arrMaterial[currposMaterial].id);
					oldMaterial = newMaterial;
					
					OutputListMaterialPerPage(t, (pageNowMaterial - 1) * QUANTITY_PER_PAGE);
					SetDefaultChosenMaterial(newMaterial->_material, currposMaterial);
				}
				break;
			case ENTER:  //enter
				PASS = 0;
				ShowCur(true);
				return newMaterial;
				break;
			case ESC:
				ShowCur(true);
				return NULL;
				break;
		}
	}
}


void inputMaterial(TREE_MATERIAL &t, MATERIAL &data, bool isEdited = false)
{
	ShowCur(true);
	
	bool isMoveUp = false;
	bool isSave = false;
	int ordinal = 0;
	
	
	string id, material_name, unit;
	int quantity_exists = 0;
	
	bool idIsExits = false;
	
	if(isEdited)
	{
		id = data.id;
		material_name = data.material_name;
		unit = data.unit;
		quantity_exists = data.quantity_exists;
		
		Gotoxy(X_ADD + 10, 0 * 3 + Y_ADD);
		cout << id;
		Gotoxy(X_ADD + 10, 1 * 3 + Y_ADD);
		cout << material_name;
		Gotoxy(X_ADD + 10, 2 * 3 + Y_ADD);
		cout << unit;
		Gotoxy(X_ADD + 10, 3 * 3 + Y_ADD);
		cout << quantity_exists;		
	}
	
	while(true)
	{
		switch(ordinal)
		{
			case 0:
					if(isEdited) break;
					CheckMoveAndValidateID(id, isMoveUp, ordinal, isSave,10, 10);
					
					strcpy(data.id, id.c_str());
					
					if(FindMaterial(t, data.id) == NULL)
					{
						idIsExits = false;
						break;
					}
					
					idIsExits = true;
					break;
			case 1:
					CheckMoveAndValidateString(material_name, isMoveUp, ordinal, isSave,10, 30);
					break;
			case 2:
					CheckMoveAndValidateString(unit, isMoveUp, ordinal, isSave, 10, 10);
					break;
			case 3:
					if(isEdited) break;
					CheckMoveAndValidateNumber(quantity_exists, isMoveUp, ordinal, isSave, 10, 1000000000);
					break;
		}
		
		
		if (isMoveUp)
		{
			if (ordinal == 0)
				isMoveUp = false;
			ordinal--;

		}
		else
		{
			if (ordinal == 4)
				isMoveUp = true;
			ordinal++;
		}
		
		if(isSave)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";
			trim(material_name);
			StandarString(material_name);

			if (id.empty() || material_name.empty() || unit.empty() || quantity_exists == 0)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Cac truong du lieu khong dc de trong";
			}
			else if (idIsExits)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ma VT khong duoc trung";
			}else{
				
				strcpy(data.material_name, material_name.c_str());
				strcpy(data.unit, unit.c_str());
				data.quantity_exists = quantity_exists;
				
				if(isEdited)
				{
					NODE_MATERIAL* p = FindMaterial(t, data.id);
					p->_material = data;
					
					for(int i = 0; i < nMaterial; i++)
					{
						if(stricmp(arrMaterial[i].id, data.id) == 0)
						{
							arrMaterial[i] = data;
							break;
						}
					}
				}else{
					InsertMaterialToTree(t, data);
				}
				
				DeleteMenuAdd();
				Gotoxy(X_NOTIFY, Y_NOTIFY + 1);
				cout << "                    ";
				return;
			}
			
			isSave = false;
		}else{
			isSave = false;
		}
		
	}
	ShowCur(false);
}

void ChangePageMenuMaterial(TREE_MATERIAL t)
{
	Display(keyDisplayMaterial, sizeof(keyDisplayMaterial) / sizeof(string));
	Gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY DANH SACH VAT TU ";
	QuickSort(0, nMaterial, arrMaterial);
	OutputListMaterialPerPage(t, (pageNowMaterial - 1) * QUANTITY_PER_PAGE);
}


void MenuMaterialManager(TREE_MATERIAL &t)
{
	backMenu:
			totalPageMaterial = nMaterial / QUANTITY_PER_PAGE + 1; // tong so trang
			pageNowMaterial = 1;
			indexOutMaterial = -1;
			
			if(nMaterial != -1)
			{
				QuickSort(0, nMaterial, arrMaterial);
			}
			
			Display(keyDisplayMaterial, sizeof(keyDisplayMaterial) / sizeof(string));
			if(nMaterial != -1)
				OutputListMaterialPerPage(t, 0);
			Gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY DANH SACH VAT TU";
			
		int key;
		while(true)
		{
			while(_kbhit())
			{
				key = _getch();
				
				if(key == 0 || key == 224)
				{
					key = _getch();
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << setw(35) << setfill(' ') << " ";
					
					if(key == KEY_F2)
					{
						Material data;
						DisplayEdit(keyDisplayMaterial, sizeof(keyDisplayMaterial) / sizeof(string), 35);
						inputMaterial(t, data);
						ChangePageMenuMaterial(t);
						Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "Them thanh cong";
	
					}
					else if(key == KEY_F3)
					{
						clrscr();
						Gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY DANH SACH VAT TU ";                     
						Gotoxy(X_PAGE, Y_PAGE); cout << "Trang "<< pageNowMaterial << "/" << totalPageMaterial;
						
						NODE_MATERIAL* k = ChooseMaterial(t);
						if(k == NULL) goto backMenu;

						Gotoxy(X_NOTIFY, Y_NOTIFY);
						cout << "Ban co chan chan xoa? ENTER == dong y";
						key = _getch();
						if(key == ENTER)
						{
							clrscr();
							Gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY DANH SACH VAT TU ";
							Display(keyDisplayMaterial, sizeof(keyDisplayMaterial) / sizeof(string));
							for(int i = 0; i <= nMaterial; i++)
							{
								
								if(strcmp(k->_material.id, arrMaterial[i].id) == 0)
								{
									for(int j = i; j < nMaterial; j++)
										arrMaterial[j] = arrMaterial[j+1];
									nMaterial--;
									break;
								}
							}	
							if(IsDeleteMaterial(t, k->_material))
							{
								OutputListMaterialPerPage(t, (pageNowMaterial - 1) * QUANTITY_PER_PAGE);
								Gotoxy(X_NOTIFY, Y_NOTIFY);
								cout << "Xoa thanh cong";
							}
						}else
							goto backMenu;
					}
					else if(key == KEY_F4)
					{
						NODE_MATERIAL* k = ChooseMaterial(t);
						if(k == NULL) goto backMenu;
						
						DisplayEdit(keyDisplayMaterial, sizeof(keyDisplayMaterial) / sizeof(string), 35);
						inputMaterial(t, k->_material, true);
						Gotoxy(X_NOTIFY, Y_NOTIFY);
						cout << "Edit thanh cong";
						ChangePageMenuMaterial(t);						
					}
					else if( key == PAGE_DOWN && pageNowMaterial < totalPageMaterial)
					{
						clrscr();
						pageNowMaterial++;
						ChangePageMenuMaterial(t);
					}
					else if(key == PAGE_UP && pageNowMaterial > 1)
					{
						clrscr();					
						pageNowMaterial--;
						ChangePageMenuMaterial(t);
					}					
				}				
				else if(key == ESC)
				{
					return;	
				}
			}			
		}
}

#endif
