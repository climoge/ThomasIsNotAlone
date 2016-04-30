#include "file/File.h"

void initialiseFromFile(char *path, ListRectanglePlayer **listPlayers, ListRectangleLevel **listLevel, ListFinalPosition **listPositions){
	/*------------------------------------------------------*/
	//Read a CSV file and create a list from it
	/*------------------------------------------------------*/
	FILE* file = fopen(path, "r");
    if(file == NULL){
		fprintf(stderr,"File doesn't exist\n");
		exit(1);
	}
	
    char key[1025];
    char buffer[1025];
    float value;
    
    int state = 0;
    
    int id=-1,
    index = -1;
    
    float width,
	height,
	posX,
	posY,
	highJump;
	
	RectanglePlayer *currentPlayer;
	
	Color3f color;
	
	while(fgets(buffer, 1024, file) != NULL){
		sscanf(buffer, "%[^':']: %f", key, &value);
		strtok(key, "\n");
		if(!strcmp(key, "players")){
			state = 0;
		}
		else if(!strcmp(key, "finalPositions")){
			state = 1;
		}
			else if(!strcmp(key, "colliders"))
				state = 2;
			else{
				if(state == 0){
					if(!strcmp(key, "{"))
						id++;
					else if(!strcmp(key, "width"))
						width = value;
						else if(!strcmp(key, "height"))
							height = value;
							else if(!strcmp(key, "posX"))
								posX = value;
								else if(!strcmp(key, "posY"))
									posY = value;
									else if(!strcmp(key, "highJump"))
										highJump = value;
										else if(!strcmp(key, "r"))
											color.R = value;
											else if(!strcmp(key, "g"))
												color.G = value;
												else if(!strcmp(key, "b"))
													color.B = value;
													else if(!strcmp(key, "}"))
														AddPlayer(id, color, width, height, posX, posY, highJump, listPlayers);
				}
				else if(state == 1){
					currentPlayer = *listPlayers;
					if(!strcmp(key, "{"))
						index++;
					else if(!strcmp(key, "posX"))
						posX = value;
						else if(!strcmp(key, "posY"))
							posY = value;
								else if(!strcmp(key, "}")){
									//printf("index : %d\n", index);
									while(currentPlayer->id != index){
										currentPlayer = currentPlayer->next;
									}
									//printf("Position id : %d, posX : %f, posY : %f\n", currentPlayer->id, posX, posY);
									AddFinalPosition(currentPlayer, posX, posY, listPositions);
								}
				}
				else if(state == 2){
					if(!strcmp(key, "width"))
						width = value;
					else if(!strcmp(key, "height"))
						height = value;
						else if(!strcmp(key, "posX"))
							posX = value;
							else if(!strcmp(key, "posY"))
								posY = value;
									else if(!strcmp(key, "}"))
										AddLevel(width, height, posX, posY, listLevel);
				}
			}
		
		
    }
    fclose(file);
}
