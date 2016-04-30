#include "physic/Physic.h"
#include "common.h"

void Gravity(RectanglePlayer *player){
	if(!player->colBottom){
		player->speedY += GRAVITY;
	}
}

void Moves(ListRectanglePlayer *playerList){
	ListRectanglePlayer *currentPlayer = playerList;
	RectanglePlayer *belowerPlayer;
	while(currentPlayer!=NULL){
		belowerPlayer = currentPlayer->belowPlayer;
			/*On applique la gravité sur l'élément*/
		
		Gravity(currentPlayer);
		
			/*Déplacement vertical*/
		
		currentPlayer->posY += currentPlayer->speedY;
		
			/*Déplacement horizontal*/
		
		if((!currentPlayer->colLeft && currentPlayer->speedX < 0) || (!currentPlayer->colRight && currentPlayer->speedX > 0)){
			currentPlayer->posX += currentPlayer->speedX;
		}
		
		if(belowerPlayer != NULL){
			if(belowerPlayer->speedX == 0){
				while(belowerPlayer->belowPlayer != NULL){
					belowerPlayer = belowerPlayer->belowPlayer;
				}
			}
			if((!belowerPlayer->colLeft && !currentPlayer->belowPlayer->colLeft && belowerPlayer->speedX < 0 && !currentPlayer->colLeft) || (!belowerPlayer->colRight && !currentPlayer->belowPlayer->colRight && belowerPlayer->speedX > 0 && !currentPlayer->colRight))
				currentPlayer->posX += belowerPlayer->speedX;
		}
		
		currentPlayer = currentPlayer->next;
	}
}

void Jump (RectanglePlayer *player){
	if(player->colBottom && !player->colTop){
		player->speedY = player->highJump;
	}
}

int isCollision(float R1X, float R1Y, float R1W, float R1H, float R2X, float R2Y, float R2W, float R2H){
	if((fabs(R1X - R2X) <= (R1W + R2W)/2) && (fabs(R1Y - R2Y) <= (R1H + R2H)/2))
		return 1;
	else
		return 0;
}

void Collision(ListRectanglePlayer **playerList, RectangleLevel **colliderList){
	RectangleLevel *collider;
	ListRectanglePlayer *player = *playerList;
	ListRectanglePlayer *testedPlayer = *playerList;

	while(player!=NULL){
		player->colBottom = 0;
		player->colRight = 0;
		player->colLeft = 0;
		player->colTop = 0;
		collider = *colliderList;
		while(collider!=NULL){
			if(isCollision(player->posX, player->posY, player->width, player->height, collider->posX, collider->posY, collider->width, collider->height) == 1){
				float wy = (collider->width + player->width) * (collider->posY - (player->posY - player->speedY));
				float hx = (collider->height + player->height) * (collider->posX - (player->posX - player->speedX));

				if (wy > hx){
					if (wy > -hx){
						if(!player->colTop && (fabs(player->posX - collider->posX) < player->width/2 + collider->width/2)){
							//printf("Collision haute\n");
							player->colTop = 1;
							player->speedY = 0;
							player->posY -= player->posY + player->height/2 - (collider->posY - collider->height/2);
						}
					}
					else{
						if(fabs(player->posY - collider->posY) < player->height/2 + collider->height/2){
							//printf("Collision gauche\n");
							player->colLeft = 1;		
							player->posX -= (player->posX - player->width/2) - (collider->posX + collider->width/2);
						}
					}
				}
				else{
					if (wy >= -hx){
						if(fabs(player->posY - collider->posY) < player->height/2 + collider->height/2){
							//printf("Collision droite\n");
							player->colRight = 1;		
							player->posX -= (player->posX + player->width/2) - (collider->posX - collider->width/2);
						}
					}
					else{
						if(!player->colBottom && (fabs(player->posX - collider->posX) < player->width/2 + collider->width/2)){
							//printf("Collision basse\n");
							player->colBottom = 1;
							player->posY -= (player->posY - player->height/2) - (collider->posY + collider->height/2);
							player->speedY = 0;
						}
					}
				}
			}
			collider = collider->next;
		}
		player = player->next;
	}
	
	player = *playerList;
	while(player!=NULL){
		testedPlayer = *playerList;
		player->belowPlayer = NULL;
		while(testedPlayer!=NULL){
			if(player != testedPlayer){
				if(isCollision(player->posX, player->posY, player->width, player->height, testedPlayer->posX, testedPlayer->posY, testedPlayer->width, testedPlayer->height) == 1){
					float wy = (testedPlayer->width + player->width) * (testedPlayer->posY - (player->posY - player->speedY));
					float hx = (testedPlayer->height + player->height) * (testedPlayer->posX - (player->posX - player->speedX));

					if (wy > hx){
						if (wy > -hx){
							if(!player->colTop && (fabs(player->posX - testedPlayer->posX) < player->width/2 + testedPlayer->width/2)){
								//printf("Collision haute\n");
								player->colTop = 1;
								player->speedY = 0;
								testedPlayer->posY -= (testedPlayer->posY - testedPlayer->height/2) - (player->posY + player->height/2);
							}
						}
						else{
							if(fabs(player->posY - testedPlayer->posY) < player->height/2 + testedPlayer->height/2){
								if(player->speedX !=0){
									//printf("Collision gauche\n");
									player->colLeft = 1;		
									player->posX -= (player->posX - player->width/2) - (testedPlayer->posX + testedPlayer->width/2);
								}
								else{
									//printf("Collision gauche\n");
									player->colLeft = 1;		
									testedPlayer->posX -= (testedPlayer->posX + testedPlayer->width/2) - (player->posX - player->width/2);
								}
							}
						}
					}
					else{
						if (wy >= -hx){
							if(fabs(player->posY - testedPlayer->posY) < player->height/2 + testedPlayer->height/2){
								if(player->speedX != 0){
									//printf("Collision droite\n");
									player->colRight = 1;		
									player->posX -= (player->posX + player->width/2) - (testedPlayer->posX - testedPlayer->width/2);
								}
								else{
									player->colRight = 1;		
									testedPlayer->posX -= (testedPlayer->posX - testedPlayer->width/2) - (player->posX + player->width/2);
								}
							}
						}
						else{
							if(!player->colBottom && (fabs(player->posX - testedPlayer->posX) < player->width/2 + testedPlayer->width/2)){
								//printf("Collision basse\n");
								player->colBottom = 1;
								player->posY -= (player->posY - player->height/2) - (testedPlayer->posY + testedPlayer->height/2);
								player->speedY = 0;
								player->belowPlayer = testedPlayer;
							}
						}
					}
				}
			}
			testedPlayer = testedPlayer->next;
		}
		player = player->next;
	}
}
