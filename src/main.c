#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "common.h"

#include "Game.h"
#include "level/Level.h"
#include "player/Player.h"
#include "physic/Physic.h"
#include "drawer/Drawer.h"
#include "file/File.h"

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(int argc, char** argv) {
	
	const unsigned int WIN_WIDTH = 800;
    const unsigned int WIN_HEIGHT = 600;
    
    Menu game,
    commands,
    rules,
    quit;
    
    int menuState = 0;
    
    SetMenu(&game, 0, &game, &commands, &game, &rules);
    SetMenu(&commands, 1, &quit, &rules, &quit, &game);
    SetMenu(&rules, 2, &quit, &game, &quit, &commands);
    SetMenu(&quit, 3, &commands, &game, &rules, &game);
    
    Menu *selectedMenu = &game;
	
	ScreenSize size = SetScreenSize(WIN_WIDTH, WIN_HEIGHT);
	
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    if(SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 ) == -1)
		printf("impossible d'initialiser SDL_GL_MULTISAMPLEBUFFERS à 1\n");
	else{
		if(SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 6) == -1)
			printf("impossible d'initialiser SDL_GL_MULTISAMPLEBUFFERS à 1\n");
		else
			printf("anti-aliasing démarré\n");
	}
    
    const unsigned int FULL_WIDTH = SDL_GetVideoInfo()->current_w;
    const unsigned int FULL_HEIGHT = SDL_GetVideoInfo()->current_h;
    
    SDL_SetVideoMode(size.w, size.h, 32, SDL_OPENGL);
 
    SDL_WM_SetCaption("Thomas", NULL);
    
    //-----------------------------Chargement images-------------------------------------
    
    
    
    //-------------------------Fin chargement images-------------------------------------
    
    glViewport(0, 0, size.w, size.h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-size.w, size.w, -size.h, size.h);
    
    int loop = 1;
    while(loop) {
		/* temps au début de la boucle */
		Uint32 startTime = SDL_GetTicks();
		
		/*Dessin*/
        glClear(GL_COLOR_BUFFER_BIT);

        DrawMenu(&size, WIN_WIDTH, WIN_HEIGHT, FULL_WIDTH, FULL_HEIGHT, selectedMenu, menuState);
        
        SDL_GL_SwapBuffers();
        
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                loop = 0;
            }
            
            switch(e.type) {
				case SDL_MOUSEBUTTONDOWN:
					
				break;
				  
				case SDL_MOUSEBUTTONUP:
					
				break;
				  
				case SDL_MOUSEMOTION:
					/*if((e.motion.x > 909.5*(size.w/FULL_WIDTH)) && (e.motion.x < 1179.5*(size.w/FULL_WIDTH)) && (e.motion.y > 256.5*(size.h/FULL_HEIGHT)) && (e.motion.y < 540*(size.h/FULL_HEIGHT)))
						command_hover = 1;
					else
						command_hover = 0;*/
				break;

				case SDL_KEYDOWN:
				  switch(e.key.keysym.sym){

					case SDLK_LEFT :
						if(menuState == 0)
							selectedMenu = selectedMenu->left;
					break;

					case SDLK_RIGHT :
						if(menuState == 0)
							selectedMenu = selectedMenu->right;
					break;

					case SDLK_UP :
						if(menuState == 0)
							selectedMenu = selectedMenu->up;
					break;
					
					case SDLK_DOWN :
						if(menuState == 0)
							selectedMenu = selectedMenu->down;
					break;
					
					case SDLK_RETURN :
						if(menuState == 0){
							switch(selectedMenu->id){
								case 0:
									loop = startGame(&size, FULL_WIDTH, FULL_HEIGHT);
								break;
								
								case 1:
									menuState = 1;
								break;
								
								case 2:
									menuState = 2;
								break;
								
								case 3:
									loop = 0;
								break;
								
								default: break;
							}
						}
						else
							menuState = 0;
					break;
					
					case 'f' :
						if(size.w != FULL_WIDTH){
							size = SetScreenSize(FULL_WIDTH, FULL_HEIGHT);
							glViewport(0, 0, size.w, size.h);
							SDL_SetVideoMode(size.w, size.h, 32, SDL_OPENGL | SDL_FULLSCREEN);
							SDL_ShowCursor(SDL_DISABLE);
						}
						else{
							size = SetScreenSize(800, 600);
							glViewport(0, 0, size.w, size.h);
							SDL_SetVideoMode(size.w, size.h, 32, SDL_OPENGL);
							SDL_ShowCursor(SDL_ENABLE);
						}
					break;
					
					case 'q' : 
						loop = 0;
					break;
					
					case SDLK_ESCAPE :
						menuState = 0;
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
	
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
