#include "level/Level.h"

ListRectangleLevel *CreateLevelList(){
	ListRectangleLevel *list = NULL;
	return list;
}

void AddLevel(float width, float height, float posX, float posY, ListRectangleLevel **list){
	if(*list == NULL){
		*list = (ListRectangleLevel*) malloc(sizeof(ListRectangleLevel));
		(*list)->width = width;
		(*list)->height = height;
		(*list)->posX = posX;
		(*list)->posY = posY;
		(*list)->next = NULL;
	}
	else{
		RectangleLevel *newLevel = (RectangleLevel*) malloc(sizeof(RectangleLevel));
		if(newLevel == NULL)
			exit(1);
		newLevel->width = width;
		newLevel->height = height;
		newLevel->posX = posX;
		newLevel->posY = posY;
		newLevel->next = *list;
		*list = newLevel;
	}
}
