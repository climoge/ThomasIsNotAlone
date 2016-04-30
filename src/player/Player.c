#include "player/Player.h"

ListRectanglePlayer *CreatePlayerList(){
	ListRectanglePlayer *list = NULL;
	return list;
}

ListFinalPosition *CreatePositionList(){
	ListFinalPosition *list = NULL;
	return list;
}

void AddPlayer(int id, Color3f color, float width, float height, float posX, float posY, float highJump, ListRectanglePlayer **list){
	if(*list == NULL){
		*list = (ListRectanglePlayer*) malloc(sizeof(ListRectanglePlayer));
		(*list)->id = id;
		(*list)->color = color;
		(*list)->colTop = 0;
		(*list)->colBottom = 0;
		(*list)->colLeft = 0;
		(*list)->colRight = 0;
		(*list)->isFinalPosition = 0;
		(*list)->belowPlayer = NULL;
		(*list)->width = width;
		(*list)->height = height;
		(*list)->posX = posX;
		(*list)->posY = posY;
		(*list)->highJump = highJump;
		(*list)->speedX = 0;
		(*list)->speedY = 0;
		(*list)->next = NULL;
	}
	else{
		RectanglePlayer *newPlayer = (RectanglePlayer*) malloc(sizeof(RectanglePlayer));
		if(newPlayer == NULL)
			exit(1);
		newPlayer->id = id;
		newPlayer->color = color;
		newPlayer->colTop = 0;
		newPlayer->colBottom = 0;
		newPlayer->colLeft = 0;
		newPlayer->colRight = 0;
		newPlayer->isFinalPosition = 0;
		newPlayer->belowPlayer = NULL;
		newPlayer->width = width;
		newPlayer->height = height;
		newPlayer->posX = posX;
		newPlayer->posY = posY;
		newPlayer->highJump = highJump;
		newPlayer->speedY = 0;
		newPlayer->speedX = 0;
		newPlayer->next = (*list);
		*list = newPlayer;
	}
}

void AddFinalPosition(RectanglePlayer *player, float posX, float posY, ListFinalPosition **list){
	if(*list == NULL){
		*list = (ListFinalPosition*) malloc(sizeof(ListFinalPosition));
		(*list)->id = player->id;
		(*list)->width = player->width;
		(*list)->height = player->height;
		(*list)->posX = posX;
		(*list)->posY = posY;
		(*list)->next = NULL;
	}
	else{
		FinalPosition *newPosition = (FinalPosition*) malloc(sizeof(FinalPosition));
		if(newPosition == NULL)
			exit(1);
		newPosition->id = player->id;
		newPosition->width = player->width;
		newPosition->height = player->height;
		newPosition->posX = posX;
		newPosition->posY = posY;
		newPosition->next = (*list);
		*list = newPosition;
	}
}

int isPositionCollision(RectanglePlayer *player, FinalPosition *position){
	if((fabs(player->posX - position->posX) <= player->width/2 + position->width/2) && (fabs(player->posY - position->posY) <= player->height/2 + position->height/2))
		return 1;
	else
		return 0;
}

void onFinalPosition(ListRectanglePlayer **listPlayers, ListFinalPosition *listPositions){
	RectanglePlayer *currentPlayer = *listPlayers;
	FinalPosition *currentPosition;
	while(currentPlayer !=NULL){
		currentPosition = listPositions;
		while(currentPosition !=NULL){
			if(currentPlayer->id == currentPosition->id){
				if(isPositionCollision(currentPlayer, currentPosition))
					currentPlayer->isFinalPosition = 1;
				else
					currentPlayer->isFinalPosition = 0;
				break;
			}
			currentPosition = currentPosition->next;
		}
		currentPlayer = currentPlayer->next;
	}
}

int isLevelComplete(ListRectanglePlayer *listPlayers){
	RectanglePlayer *currentPlayer = listPlayers;

	while(currentPlayer != NULL){
		if(currentPlayer->isFinalPosition == 0){
			return 0;
		}
		currentPlayer = currentPlayer->next;
	}
	return 1;
}
