#include <iostream>

#include "process.h"
int main(int argc, char** argv) {
	fullscreen();
	
	TREE_MATERIAL t;
	InitTreeMaterial(t);
//	LoadMaterialFromFile(t);
	
	PTR_LIST_STAFF ls = new LIST_STAFF;
	Main_Menu(ls, t);

//	SaveMaterialToFile(t);	
	return 0; 
}
