#include "Game.h"

int startGame(ScreenSize *size, const unsigned int FULL_WIDTH, const unsigned int FULL_HEIGHT){
	
	glLoadIdentity();
	
	SDL_Surface* background;
    
    background = IMG_Load("img/menu/background.png");
    if(background == NULL)
        fprintf(stderr, "Impossible de charger l'image\n");
        
    GLuint textureId;
    
    glGenTextures(1, &textureId);
	
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    GLenum format;
    switch(background->format->BytesPerPixel) {
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, background->w, background->h, 0, format, GL_UNSIGNED_BYTE, background->pixels);
	
	static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;
	
	int right = 0,
	left = 0;
	
	CamPosition camera;
	camera.X = 0;
	camera.Y = 0;
    
    //----------------------------------Ajout depuis fichier-------------------------------------------
    
    ListRectanglePlayer *listPlayers = CreatePlayerList();
    ListFinalPosition *listPositions = CreatePositionList();
    ListRectangleLevel *listLevel = CreateLevelList();
    
	initialiseFromFile("level.tson", &listPlayers, &listLevel, &listPositions);
    
    RectanglePlayer *currentPlayer = listPlayers;
    //-------------------------------------------------------------------------------------------------
    
    /*Fusion des deux listes*/
    
    ListRectangle *listRectangle = MergeListRectangle(listLevel, listPlayers);
    
    int loop = 1;
    
    while(loop) {
		/* temps au début de la boucle */
		Uint32 startTime = SDL_GetTicks();
		
		/*Dessin*/
        glClear(GL_COLOR_BUFFER_BIT);        
		
		glEnable(GL_TEXTURE_2D);
		
		glBindTexture(GL_TEXTURE_2D, textureId);

		glPushMatrix();
			gluOrtho2D(-size->w, size->w, -size->h, size->h);
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
		
		glBindTexture(GL_TEXTURE_2D, 0);
		
        glPushMatrix();
			cameraPosition(&camera, size, currentPlayer->posX, currentPlayer->posY, 0); //Placement de la caméra
			Moves(listPlayers);
			Collision(&listPlayers, &listLevel);
			onFinalPosition(&listPlayers, listPositions);
			DrawScene(listRectangle, currentPlayer, listPositions);
        glPopMatrix();
        
		drawHUD(size, listPlayers, currentPlayer);
        
		if(isLevelComplete(listPlayers))
			loop = 0;
        
        SDL_GL_SwapBuffers();
        
        glDisable(GL_TEXTURE_2D);
        
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                loop = 0;
                return 0;
            }
            
            switch(e.type) {

				case SDL_KEYDOWN:
				  switch(e.key.keysym.sym){

					case SDLK_LEFT :
						left = 1;
						currentPlayer->speedX = -PLAYER_SPEED;
					break;

					case SDLK_RIGHT :
						right = 1;
						currentPlayer->speedX = +PLAYER_SPEED;
					break;

					case SDLK_UP : 
					  Jump(currentPlayer);
					break;
					
					case SDLK_TAB :
						currentPlayer->speedX = 0;
						if(currentPlayer->next != NULL)
							currentPlayer = currentPlayer->next;
						else
							currentPlayer = listPlayers;
					break;
					
					case 'f' :
						if(size->w != FULL_WIDTH){
							*size = SetScreenSize(FULL_WIDTH, FULL_HEIGHT);
							glViewport(0, 0, size->w, size->h);
							SDL_SetVideoMode(size->w, size->h, 32, SDL_OPENGL | SDL_FULLSCREEN);
							SDL_ShowCursor(SDL_DISABLE);
						}
						else{
							*size = SetScreenSize(800, 600);
							glViewport(0, 0, size->w, size->h);
							SDL_SetVideoMode(size->w, size->h, 32, SDL_OPENGL);
							SDL_ShowCursor(SDL_ENABLE);
						}
					break;
					
					case 'm' : 
					case SDLK_ESCAPE : 
					  loop = 0;
					break;
					default : break;
				  }
				break;
				
				case SDL_KEYUP:
				  switch(e.key.keysym.sym){

					case SDLK_LEFT : 
						if(left && !right){
							currentPlayer->speedX = 0;
						}
						left = 0;
					break;

					case SDLK_RIGHT :
						if(right && !left){
							currentPlayer->speedX = 0;
						}
						right = 0;
					break;
					
					default : break;
				  }
				break;
				 
				default:
				  break;
			}
        }
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if(elapsedTime < FRAMERATE_MILLISECONDS) {
		  SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
    }
    return 1;
}
