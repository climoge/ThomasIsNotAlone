#include "drawer/Drawer.h"

void DrawMenu(ScreenSize *size, const unsigned int WIN_WIDTH, const unsigned int WIN_HEIGHT, const unsigned int FULL_WIDTH, const unsigned int FULL_HEIGHT, Menu *currentMenu, int menuState){
	SDL_Surface* images[50];
    
    images[0] = IMG_Load("img/menu/background.png");
    if(images[0] == NULL) {
        fprintf(stderr, "Impossible de charger l'image\n");
        
    }
    
	images[1] = IMG_Load("img/menu/commands.png");
    if(images[1] == NULL) {
        fprintf(stderr, "Impossible de charger l'image\n");
        
    }
    
    images[2] = IMG_Load("img/menu/rules.png");
    if(images[2] == NULL) {
        fprintf(stderr, "Impossible de charger l'image\n");
        
    }
    
    images[3] = IMG_Load("img/menu/thomas_was_not_alone.png");
    if(images[3] == NULL) {
        fprintf(stderr, "Impossible de charger l'image\n");
        
    }
    
    images[4] = IMG_Load("img/menu/quit.png");
    if(images[4] == NULL) {
        fprintf(stderr, "Impossible de charger l'image\n");
        
    }
    
    images[5] = IMG_Load("img/commands/commands.png");
    if(images[5] == NULL) {
        fprintf(stderr, "Impossible de charger l'image\n");
        
    }
    
    images[6] = IMG_Load("img/rules/rules.png");
    if(images[6] == NULL) {
        fprintf(stderr, "Impossible de charger l'image\n");
        
    }
    
    GLuint textureId[7];
    
    glGenTextures(7, textureId);
	
    glBindTexture(GL_TEXTURE_2D, textureId[0]);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    GLenum format;
    switch(images[0]->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image non pris en charge\n");
            
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, images[0]->w, images[0]->h, 0, format, GL_UNSIGNED_BYTE, images[0]->pixels);
    
    //SDL_FreeSurface(images[0]);
    
    glBindTexture(GL_TEXTURE_2D, textureId[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, images[1]->w, images[1]->h, 0, format, GL_UNSIGNED_BYTE, images[1]->pixels);
	
	glBindTexture(GL_TEXTURE_2D, textureId[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, images[2]->w, images[2]->h, 0, format, GL_UNSIGNED_BYTE, images[2]->pixels);
	
	glBindTexture(GL_TEXTURE_2D, textureId[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, images[3]->w, images[3]->h, 0, format, GL_UNSIGNED_BYTE, images[3]->pixels);
	
	glBindTexture(GL_TEXTURE_2D, textureId[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, images[5]->w, images[5]->h, 0, format, GL_UNSIGNED_BYTE, images[5]->pixels);
	
	glBindTexture(GL_TEXTURE_2D, textureId[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, images[6]->w, images[6]->h, 0, format, GL_UNSIGNED_BYTE, images[6]->pixels);
	
	glBindTexture(GL_TEXTURE_2D, textureId[4]);
	switch(images[4]->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image non pris en charge\n");
            
    }
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, images[4]->w, images[4]->h, 0, format, GL_UNSIGNED_BYTE, images[4]->pixels);
	
	SDL_FreeSurface(images[0]);
	SDL_FreeSurface(images[1]);
	SDL_FreeSurface(images[2]);
	SDL_FreeSurface(images[3]);
	SDL_FreeSurface(images[4]);
	SDL_FreeSurface(images[5]);
	SDL_FreeSurface(images[6]);
	
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(-size->w, size->w, -size->h, size->h);
		
		glEnable(GL_TEXTURE_2D);
		
		glBindTexture(GL_TEXTURE_2D, textureId[0]);
		glScalef(size->w/WIN_WIDTH, size->w/WIN_WIDTH,1);
		glPushMatrix();
			glScalef(FULL_WIDTH*size->h/FULL_HEIGHT*2, size->h*2,1);
			glBegin(GL_QUADS);
				glColor3f(1, 1, 1);
				
				glTexCoord2f(0, 1);
				glVertex2f(-0.5, -0.5);
				
				glTexCoord2f(1, 1);
				glVertex2f(0.5, -0.5);
				
				glTexCoord2f(1, 0);
				glVertex2f(0.5, 0.5);
				
				glTexCoord2f(0, 0);
				glVertex2f(-0.5, 0.5);
			glEnd();
		glPopMatrix();
		
		if(menuState == 0){
			glBindTexture(GL_TEXTURE_2D, textureId[2]);
			
			glPushMatrix();
				glTranslatef(414, 277.5 - 135, 0);
				glScalef(270, 270,1);
				glBegin(GL_QUADS);
					glColor3f(1, 1, 1);
					
					glTexCoord2f(0, 1);
					glVertex2f(-0.5, -0.5);
					
					glTexCoord2f(1, 1);
					glVertex2f(0.5, -0.5);
					
					glTexCoord2f(1, 0);
					glVertex2f(0.5, 0.5);
					
					glTexCoord2f(0, 0);
					glVertex2f(-0.5, 0.5);
				glEnd();
			glPopMatrix();
			
			glBindTexture(GL_TEXTURE_2D, textureId[1]);
			
			glPushMatrix();
				glTranslatef(84.5 , 277.5 - 135, 0);
				glScalef(270, 270,1);
				glBegin(GL_QUADS);
					glColor3f(1, 1, 1);
					
					glTexCoord2f(0, 1);
					glVertex2f(-0.5, -0.5);
					
					glTexCoord2f(1, 1);
					glVertex2f(0.5, -0.5);
					
					glTexCoord2f(1, 0);
					glVertex2f(0.5, 0.5);
					
					glTexCoord2f(0, 0);
					glVertex2f(-0.5, 0.5);
				glEnd();
			glPopMatrix();
			
			glBindTexture(GL_TEXTURE_2D, textureId[3]);
			
			glPushMatrix();
				glTranslatef(-696.5 + 292, 0, 0);
				glScalef(584, 555,1);
				glBegin(GL_QUADS);
					glColor3f(1, 1, 1);
					
					glTexCoord2f(0, 1);
					glVertex2f(-0.5, -0.5);
					
					glTexCoord2f(1, 1);
					glVertex2f(0.5, -0.5);
					
					glTexCoord2f(1, 0);
					glVertex2f(0.5, 0.5);
					
					glTexCoord2f(0, 0);
					glVertex2f(-0.5, 0.5);
				glEnd();
			glPopMatrix();
			
			glBindTexture(GL_TEXTURE_2D, textureId[4]);
			
			glPushMatrix();
				glTranslatef(597/2 - 50, -162, 0);
				glScalef(597, 231,1);
				glBegin(GL_QUADS);
					glColor3f(1, 1, 1);
					
					glTexCoord2f(0, 1);
					glVertex2f(-0.5, -0.5);
					
					glTexCoord2f(1, 1);
					glVertex2f(0.5, -0.5);
					
					glTexCoord2f(1, 0);
					glVertex2f(0.5, 0.5);
					
					glTexCoord2f(0, 0);
					glVertex2f(-0.5, 0.5);
				glEnd();
			glPopMatrix();
			
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0, 0, 0, 0.25);
			
			switch(currentMenu->id){

				case 0 :
					glPushMatrix();
						glTranslatef(-696.5 + 292, 0, 1);
						glScalef(584, 555,1);
						DrawSquare(1);
					glPopMatrix();
				break;

				case 1 :
					glPushMatrix();
						glTranslatef(84.5 , 277.5 - 135, 0);
						glScalef(270, 270,1);
						DrawSquare(1);
					glPopMatrix();
				break;

				case 2 :
					glPushMatrix();
						glTranslatef(414, 277.5 - 135, 0);
						glScalef(270, 270,1);
						DrawSquare(1);
					glPopMatrix();
				break;

				case 3 :
					glPushMatrix();
						glTranslatef(597/2 - 50, -162, 0);
						glScalef(597, 231,1);
						DrawSquare(1);
					glPopMatrix();
				break;

				default : break;
			}
		}
		
		if(menuState == 1){
			glBindTexture(GL_TEXTURE_2D, textureId[5]);
		
			glPushMatrix();
				glScalef(1236, 727, 1);
				glBegin(GL_QUADS);
					glColor3f(1, 1, 1);
					
					glTexCoord2f(0, 1);
					glVertex2f(-0.5, -0.5);
					
					glTexCoord2f(1, 1);
					glVertex2f(0.5, -0.5);
					
					glTexCoord2f(1, 0);
					glVertex2f(0.5, 0.5);
					
					glTexCoord2f(0, 0);
					glVertex2f(-0.5, 0.5);
				glEnd();
			glPopMatrix();
		}
		
		if(menuState == 2){
			glBindTexture(GL_TEXTURE_2D, textureId[6]);
		
			glPushMatrix();
				glScalef(1236, 727, 1);
				glBegin(GL_QUADS);
					glColor3f(1, 1, 1);
					
					glTexCoord2f(0, 1);
					glVertex2f(-0.5, -0.5);
					
					glTexCoord2f(1, 1);
					glVertex2f(0.5, -0.5);
					
					glTexCoord2f(1, 0);
					glVertex2f(0.5, 0.5);
					
					glTexCoord2f(0, 0);
					glVertex2f(-0.5, 0.5);
				glEnd();
			glPopMatrix();
		}
		
		glDisable(GL_TEXTURE_2D);
		
	glPopMatrix();
	glDeleteTextures(7, textureId);
}

void DrawSquare(int filled){
	if(filled)
		glBegin(GL_QUADS);
	else
		glBegin(GL_LINE_LOOP);
		
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
    glEnd();
}

void DrawTriangle(){
	glBegin(GL_TRIANGLES);
		glVertex2f(-0.5, 0.0);
		glVertex2f(0.5, 0.0);
		glVertex2f(0.0, -0.5);
    glEnd();
}

void DrawCursor(RectanglePlayer *player){
	glPushMatrix();
		if(player->speedY > 0)
			glTranslatef(player->posX, player->posY + player->height*(1+player->speedY/15) / 2 + 50, 0);
		else
			glTranslatef(player->posX, player->posY + player->height / 2 + 50, 0);
		glScalef(30,30,1);
		DrawTriangle();
	glPopMatrix();
}

void DrawRectangle(float width, float height, int filled){
	glPushMatrix();
		glScalef(width,height, 1);
		DrawSquare(filled);
	glPopMatrix();
}

ListRectangle *MergeListRectangle(ListRectangleLevel *listLevel, ListRectanglePlayer *listPlayer){
	ListRectangle *list = (ListRectangle*) malloc(sizeof(ListRectangle));
	
	list->level = listLevel;
	list->players = listPlayer;
	
	return list;
}

void DrawScene(ListRectangle *list, RectanglePlayer *currentPlayer, ListFinalPosition *listPositions){
	ListRectangleLevel *listLevel = list->level;
	ListRectanglePlayer *listPlayers = list->players;
	ListFinalPosition *currentPosition = listPositions;
	
	glColor3f(0, 0, 0);
	
	while(listLevel != NULL){
		glPushMatrix();
			glTranslatef(listLevel->posX,listLevel->posY,0);
			DrawRectangle(listLevel->width, listLevel->height, 1);
		glPopMatrix();
		listLevel = listLevel->next;
	}
	
	glColor3f(1, 1, 1);
	
	while(currentPosition != NULL){
		glPushMatrix();
			glTranslatef(currentPosition->posX, currentPosition->posY, 0);
			DrawRectangle(currentPosition->width, currentPosition->height, 0);
		glPopMatrix();
		currentPosition = currentPosition->next;
	}
	
	while(listPlayers != NULL){
		if(listPlayers->isFinalPosition)
			glColor3f(1, 1, 1);
		else
			glColor3f(listPlayers->color.R, listPlayers->color.G, listPlayers->color.B);
		
		glPushMatrix();
			glTranslatef(listPlayers->posX,listPlayers->posY,0);
			if(listPlayers->speedY > 0)
				DrawRectangle(listPlayers->width/(1+listPlayers->speedY/15), listPlayers->height*(1+listPlayers->speedY/15), 1);
			else
				DrawRectangle(listPlayers->width, listPlayers->height, 1);
		glPopMatrix();
		listPlayers = listPlayers->next;
	}
	
	glColor3f(1, 1, 1);
	
	DrawCursor(currentPlayer);
}

void cameraPosition(CamPosition *actualPos, ScreenSize *size, float X, float Y, float angle){
	glLoadIdentity();
	if(fabs(actualPos->X - X) < CAM_SPEED)
		actualPos->X = X;
	else{
		if(actualPos->X > X)
			actualPos->X = actualPos->X - CAM_SPEED;
		else if(actualPos->X < X)
			actualPos->X = actualPos->X + CAM_SPEED;
	}
	
	if(fabs(actualPos->Y - Y) < CAM_SPEED * ((fabs(actualPos->X - X) >= 1) ? fabs((actualPos->Y - Y) / (actualPos->X - X)) : 1))
		actualPos->Y = Y;
	else{
		//if(CAM_SPEED * ((fabs(actualPos->X - X) >= 1) ? fabs((actualPos->Y - Y) / (actualPos->X - X)) : 1) > actualPos->Y - Y)
		if(actualPos->Y > Y)
			actualPos->Y = actualPos->Y - CAM_SPEED * ((fabs(actualPos->X - X) >= 1) ? fabs((actualPos->Y - Y) / (actualPos->X - X)) : 1);
		else if(actualPos->Y < Y)
			actualPos->Y = actualPos->Y + CAM_SPEED * ((fabs(actualPos->X - X) >= 1) ? fabs((actualPos->Y - Y) / (actualPos->X - X)) : 1);
	}
	
	gluOrtho2D(-size->w + actualPos->X, size->w + actualPos->X, -size->h + actualPos->Y, size->h + actualPos->Y);
	//gluLookAt(actualPos->X, actualPos->Y, 0, actualPos->X, actualPos->Y, 0, 0, 0, 1);
	glRotatef(angle, 0, 0, 1);
	
	//gluOrtho2D(-size->w + X, size->w + X, -size->h + Y, size->h + Y);
	
}

void drawHUD(ScreenSize *size, ListRectanglePlayer *listPlayers, RectanglePlayer *focus){
	RectanglePlayer *currentPlayer = listPlayers;
	while(currentPlayer != NULL){
		glColor3f(currentPlayer->color.R, currentPlayer->color.G, currentPlayer->color.B);
		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(-size->w, size->w, -size->h, size->h);
			glTranslatef(size->w -150 - (90 * currentPlayer->id), -size->h + 150, 0);
			DrawRectangle(90, 90, 1);
			if(currentPlayer->id == focus->id){
				glColor3f(1,1,1);
				glTranslatef(0, 75 , 0);
				glScalef(30,30,1);
				DrawTriangle();
			}
		glPopMatrix();
		currentPlayer = currentPlayer->next;
	}
}
