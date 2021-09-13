
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define USERNAME_SIZE	126 
#define MOVES_SIZE	32

#define WINNER 	 10
#define EXIT 	 5
#define CORRECT  1
#define BLOCK_OK 2
#define WRONG 	 0

int flag_default_grid = 0;

typedef struct{
	int n;
	int m;
	char ** grid_space;
}grid_t;

// player functions
typedef struct{
	char name[USERNAME_SIZE];
	int player_n;
	int player_m;
} player;

void place_player_1(player *the_player, grid_t *display); // sinartisi gia tin thesi tou protou pekti
void place_player_2(player *the_player, grid_t *display); // sinartisi gia ton thesi deterou pekti
void place_player_3(player *the_player, grid_t *display); // sinartisi gia ton thesi tritou  pekti
void place_player_4(player *the_player, grid_t *display); // sinartisi gia ton thesi tetartou pekti

// grid functions
char **create_grid(int n, int m);
void display_grid(grid_t *grid);
void place_blokcs(grid_t *display);

// game funvtions
int initialise_game(player *the_player, grid_t *display);
void start_game(grid_t *display);
void start_game_default(player *the_player);
int make_move(player *the_players, grid_t *display, char symbol, int blocks);
int checkWinner(grid_t display, char symbol, player the_player);

int main(void)
{
	int i, j;
	int state = 0;
	int malloc_state;
	int nowPlays;
	int choice = -1;
	int choice_players = -1;
	int choice_grid = -1;
	int blocks = -1 ;
	grid_t display;
	player the_player[4];
	char symbol[4];
	int players_blocks[] = {5,5,5,5};
	
	printf("    _     _            _     \n");
	printf("   | |   | |          | |    \n");
	printf("   | |__ | | ___   ___| | __  \n");
	printf("   | '_ \| |/ _ \ / __| |/ / \n");
	printf("   | |_) | | (_) | (__|   <  \n");
	printf("   |_.__/|_|\___/ \___|_|\_\ \n");
	printf("              ____  \n");
	printf("             |___ \ \n");
	printf("    _ __ ___   __) |\n");
	printf("   | '_ ` _ \ |__ < \n");
	printf("   | | | | | |___) |\n");
	printf("   |_| |_| |_|____/ \n");
	do{
	   printf("MENU\n");
        printf("=====================\n");
        printf("1. play\n");
        printf("0. EXIT\n");
        printf("=====================\n");
        printf("GIVE A CHOICE:");
        scanf("%d",&choice);
        printf("\n\n\n");
        switch(choice)
        {
         case 1:{
	          do{
				printf("	MENU\n");
                printf("=====================\n");
                printf("1. DEFAULT GRID 10x10\n");
                printf("2. CUSTOM GRID\n");
                printf("0. EXIT\n");
                printf("=====================\n");
                printf("GIVE A CHOICE:");
                scanf("%d",&choice_grid);
                printf("\n\n\n");
                switch(choice_grid){
                 case 1:{
				  flag_default_grid = -1;
                    do{
						printf("	MENU\n");
                        printf("=====================\n");
                        printf(" DEFAULT GRID 10x10\n");
     	                printf("=====================\n");
     	                printf("1. 2 PLAYERS\n");
     	                printf("2. 4 PLAYERS\n");
     	                printf("0. EXIT\n");
     	                printf("=====================\n");
     	                printf("GIVE A CHOICE:");
     	                scanf("%d",&choice_players);
     	                printf("\n\n\n");
     	                switch(choice_players){
                           case 1:{
                            symbol[0] = '#';
                            symbol[1] = '@';
                             do{
						        printf("MENU\n");
		        				printf("=====================\n");
		        				printf(" DEFAULT GRID 10x10\n");
		        				printf("  2 PLAYERS\n");
		        				printf("=====================\n");
		        				printf("1. blocks\n");
		        				printf("2. no blocks\n");
		        				printf("0. EXIT\n");
		        				printf("=====================\n");
		        				printf("GIVE A CHOICE:");
		        				scanf("%d",&blocks);
		        				printf("\n\n\n");
		        				switch(blocks){
	        					 case 1:{
        							printf("with blocks for 2 players 10x10\n");
        							nowPlays = 0;
						            while(1){
                                      start_game_default(&the_player[0]);
			                          start_game_default(&the_player[1]);
																							
                                      malloc_state = initialise_game(the_player, &display);
																							
                                      place_player_1(&the_player[0], &display);
						              place_player_2(&the_player[1], &display);
				                      place_blokcs(&display);
						              if(malloc_state < 0){
						                printf("\n\nNot enough memory.\n\n");
					                    break;
				                      }
				                      do{
						               display_grid(&display);
						               state = make_move(&(the_player[nowPlays]), &display, symbol[nowPlays], players_blocks[nowPlays]);
			  	                       if (state == BLOCK_OK) players_blocks[nowPlays]--;
			  	                       if (state == CORRECT && checkWinner(display, symbol[nowPlays], the_player[nowPlays])){
		  		                       printf("Winner %s\n", the_player[nowPlays].name);
	  			                       for(i = 0; i < display.n; i++){
						                 free(display.grid_space[i]);
						               }
						               free(display.grid_space);											  	
		  		                       return 1;
				                      }
				                      if (state != WRONG){
	                                    nowPlays = (nowPlays+1) % (2 * choice_players);
		                              }
				                      if (state == EXIT) {
				                        for(i = 0; i < display.n; i++){
						                    free(display.grid_space[i]);
						                }
						                free(display.grid_space);
		  		                      return 1;
	                                 }
						        } while((WINNER != 1) && (EXIT != -2));//As long as the player hasn't  quit (1) the game and did not win
						        if(state == EXIT)//Player quit the game
      						    {
						             printf("Player %s game over \n\n", the_player[nowPlays].name);
					                 break;
				                }
				                }
       							break;
						      }
				              case 2:{
						       printf("without blocks for 2 players 10x10\n");
				               nowPlays = 0;
				               while(1){
			                     start_game_default(&the_player[0]);
                                 start_game_default(&the_player[1]);
																							
                                 malloc_state = initialise_game(the_player, &display);
																							
			                     place_player_1(&the_player[0], &display);
						         place_player_2(&the_player[1], &display);
				                 if(malloc_state < 0){
	                               printf("\n\nNot enough memory.\n\n");
                                   break;
                                 }
                                 do{
                                  display_grid(&display);
                                  state = make_move(&(the_player[nowPlays]), &display, symbol[nowPlays], players_blocks[nowPlays]);
                                  if (state == BLOCK_OK) players_blocks[nowPlays]--;
                                  if (state == CORRECT && checkWinner(display, symbol[nowPlays], the_player[nowPlays])){
                                     printf("Winner %s\n", the_player[nowPlays].name);
                                     for(i = 0; i < display.n; i++){
		                              free(display.grid_space[i]);
                                      }
                                        free(display.grid_space);
                                      return 1;
                                  }
						          if (state != WRONG){
						          nowPlays = (nowPlays+1) % (2 * choice_players);
                                  }
						          if (state == EXIT){
						           for(i = 0; i < display.n; i++){
				                    free(display.grid_space[i]);
                                    }
					               free(display.grid_space);
			  	                   return 1;
                                   }
                                  } while((WINNER != 1) && (EXIT != -2));//As long as the player hasn't  quit (1) the game and did not win
                                  if(state == EXIT){//Player quit the game
                                   printf("Player %s game over \n\n", the_player[nowPlays].name);
                                   break;
                                   }
                                  }
                                  break;
						        }
				              }
						}while(blocks != 0);
                       break;
				   }
                   case 2:{
				        symbol[0] = '#';
   				        symbol[1] = '*';
        				symbol[2] = '@';
   				        symbol[3] = '&';
						do{
						 printf("MENU\n");
  				         printf("=====================\n");
                         printf(" DEFAULT GRID 10x10\n");
                         printf("  4 PLAYERS\n");
                         printf("=====================\n");
                         printf("1. blocks\n");
                         printf("2. no blocks\n");
                         printf("0. EXIT\n");
                         printf("=====================\n");
                         printf("GIVE A CHOICE:");
                         scanf("%d",&blocks);
                         printf("\n\n\n");
    			
                         switch(blocks){
                           case 1:{
							printf(" with blocks for 4 players 10x10\n");
							nowPlays = 0;
							while(1){
							start_game_default(&the_player[0]);
							start_game_default(&the_player[1]);
							start_game_default(&the_player[2]);
							start_game_default(&the_player[3]);
																							
							malloc_state = initialise_game(the_player, &display);
																							
							place_player_1(&the_player[0], &display);
							place_player_2(&the_player[1], &display);
							place_player_3(&the_player[2], &display);
							place_player_4(&the_player[3], &display);
							place_blokcs(&display);
							if(malloc_state < 0){
                              printf("\n\nNot enough memory.\n\n");
							  break;
							}
							do{
						     display_grid(&display);
					         state = make_move(&(the_player[nowPlays]), &display, symbol[nowPlays], players_blocks[nowPlays]);
				  	         if (state == BLOCK_OK) players_blocks[nowPlays]--;
				  	         if (state == CORRECT && checkWinner(display, symbol[nowPlays], the_player[nowPlays])){
			  		           printf("Winner %s\n", the_player[nowPlays].name);
                               for(i = 0; i < display.n; i++){
                                     free(display.grid_space[i]);
							   }
							   free(display.grid_space);
						  		 return 1;
					         }
						    if (state != WRONG){
							  nowPlays = (nowPlays+1) % (2 * choice_players);
							}
						    if (state == EXIT) {
							  for(i = 0; i < display.n; i++){
									free(display.grid_space[i]);
							  }
							   free(display.grid_space);
																							  	
					  		 return 1;
							}
				} while((WINNER != 1) && (EXIT != -2));//As long as the player hasn't  quit (1) the game and did not win
			    if(state == EXIT){//Player quit the game
				  printf("Player %s game over \n\n", the_player[nowPlays].name);
				  break;
				}
	           }
	           break;
	          }
        case 2:{
				printf("without blocks for 4 players 10x10\n");
				nowPlays = 0;
				while(1){
				start_game_default(&the_player[0]);
				start_game_default(&the_player[1]);
				start_game_default(&the_player[2]);
				start_game_default(&the_player[3]);
																							
				malloc_state = initialise_game(the_player, &display);
																							
				place_player_1(&the_player[0], &display);
				place_player_2(&the_player[1], &display);
				place_player_3(&the_player[2], &display);
				place_player_4(&the_player[3], &display);
				if(malloc_state < 0){
				 printf("\n\nNot enough memory.\n\n");
                 break;
				}
				do{
				 display_grid(&display);
                 state = make_move(&(the_player[nowPlays]), &display, symbol[nowPlays], players_blocks[nowPlays]);
		  	     if (state == BLOCK_OK) players_blocks[nowPlays]--;
		  	     if (state == CORRECT && checkWinner(display, symbol[nowPlays], the_player[nowPlays])){
	  		       printf("Winner %s\n", the_player[nowPlays].name);
                   for(i = 0; i < display.n; i++){
					free(display.grid_space[i]);
				   }
				   free(display.grid_space);
	  		      return 1;
			     }
				 if (state != WRONG){
					nowPlays = (nowPlays+1) % (2 * choice_players);
				 }
				 if (state == EXIT) {
				  for(i = 0; i < display.n; i++){
				   free(display.grid_space[i]);
				  }
				  free(display.grid_space);
		  	     return 1;
				}
                   } while((WINNER != 1) && (EXIT != -2));//As long as the player hasn't  quit (1) the game did not win
        	           if(state == EXIT){//Player quit the game
                         printf("Player %s game over \n\n", the_player[nowPlays].name);
        				 break;
                    }
    	           }
                   break;
                 }
               }
    	     }while(blocks != 0);
               break;
    	    }
           }
         }while(choice_players != 0);
    	flag_default_grid = 0;
       }
	case 2:{
	  do{
	  printf("MENU\n");
      printf("=====================\n");
      printf("1. 2 players\n");
      printf("2. 4 players\n");
      printf("0. EXIT\n");
      printf("=====================\n");
      printf("GIVE A CHOICE:");
      scanf("%d",&choice_players);
      printf("\n\n\n");
      switch(choice_players){
     	case 1:{
   			symbol[0] = '#';
   			symbol[1] = '@';
   			do{
			  printf("MENU\n");
              printf("=====================\n");
			  printf(" CUSTOM GRID\n");
			  printf("  2 PLAYERS\n");
			  printf("=====================\n");
			  printf("1. blocks\n");
			  printf("2. no blocks\n");
			  printf("0. EXIT\n");
			  printf("=====================\n");
			  printf("GIVE A CHOICE:");
			  scanf("%d",&blocks);
			  printf("\n\n\n");
			  switch(blocks){
			   case 1:{
			     printf(" with blocks for players custom grid\n");
                 nowPlays = 0;
                 start_game(&display);
                 while(1){	
					start_game_default(&the_player[0]);
					start_game_default(&the_player[1]);
					malloc_state = initialise_game(the_player, &display);
																							
					place_player_1(&the_player[0], &display);
					place_player_2(&the_player[1], &display);
					place_blokcs(&display);
					if(malloc_state < 0){
					 printf("\n\nNot enough memory.\n\n");
					 break;
					}	
					do{
					 display_grid(&display);
					 state = make_move(&(the_player[nowPlays]), &display, symbol[nowPlays], players_blocks[nowPlays]);
			  	     if (state == BLOCK_OK) players_blocks[nowPlays]--;
			  	     if (state == CORRECT && checkWinner(display, symbol[nowPlays], the_player[nowPlays])){
                       printf("Winner %s\n", the_player[nowPlays].name);
                       for(i = 0; i < display.n; i++){
					     free(display.grid_space[i]);
						}
					   free(display.grid_space);
																							  	
		  		    return 1;
				    }
					if (state != WRONG){
					   nowPlays = (nowPlays+1) % (2 * choice_players);
					}
					if (state == EXIT){
					 for(i = 0; i < display.n; i++){
					   free(display.grid_space[i]);
					 }
					 free(display.grid_space);
			  	    return 1;
					}
					} while((WINNER != 1) && (EXIT != -2));//As long as the player hasn't  quit (1) the game and did not win
					if(state == EXIT){//Player quit the game
                     printf("Player %s game over \n\n", the_player[nowPlays].name);
                     break;
			        }
                  }
		  	     break;
	            }
			    case 2:{
					printf("without blocks for 2 players custom grid\n");
					nowPlays = 0;
					start_game(&display);
					while(1){
					  start_game_default(&the_player[0]);
					  start_game_default(&the_player[1]);
					  malloc_state = initialise_game(the_player, &display);
																							
					  place_player_1(&the_player[0], &display);
					  place_player_2(&the_player[1], &display);
					  if(malloc_state < 0){
							printf("\n\nNot enough memory.\n\n");
							break;
				      }	
					  do{
																								
					  display_grid(&display);
					  state = make_move(&(the_player[nowPlays]), &display, symbol[nowPlays], players_blocks[nowPlays]);
				  	  if (state == BLOCK_OK) players_blocks[nowPlays]--;
				  	  if (state == CORRECT && checkWinner(display, symbol[nowPlays], the_player[nowPlays])){
					  		printf("Winner %s\n", the_player[nowPlays].name);
				  		    for(i = 0; i < display.n; i++){
							  free(display.grid_space[i]);
							}
					        free(display.grid_space);
																							  	
			  		      return 1;
					     }																						
					 if (state != WRONG){ 
						nowPlays = (nowPlays+1) % (2 * choice_players);
					 }
					 if (state == EXIT){
						for(i = 0; i < display.n; i++){
						  free(display.grid_space[i]);
						}
					   free(display.grid_space);
																							  	
	  			      return 1;
					}
					} while((WINNER != 1) && (EXIT != -2));//As long as the player hasn't  quit (1) the game and did not win
					if(state == EXIT){//Player quit the game{
					  printf("Player %s game over \n\n", the_player[nowPlays].name);
					  break;
					}
			       }
					break;
			      }
			     }
			    }while(blocks != 0);
  			    break;
			   }
	case 2:{
	 symbol[0] = '#';
	 symbol[1] = '*';
	 symbol[2] = '@';
	 symbol[3] = '&';
     do{
		printf("MENU\n");
	    printf("=====================\n");
        printf(" CUSTOM GRID\n");
   		printf("  4 PLAYERS\n");
   		printf("=====================\n");
   		printf("1. blocks\n");
		printf("2. no blocks\n");
		printf("0. EXIT\n");
		printf("=====================\n");
		printf("GIVE A CHOICE:");
		scanf("%d",&blocks);
		printf("\n\n\n");
		switch(blocks){
		 case 1:{
			printf(" with blocks for 4 players custom grid\n");
			nowPlays = 0;
			start_game(&display);
			while(1){
																							
			 start_game_default(&the_player[0]);
			 start_game_default(&the_player[1]);
			 start_game_default(&the_player[2]);
			 start_game_default(&the_player[3]);
																							
			 malloc_state = initialise_game(the_player, &display);
																							
			 place_player_1(&the_player[0], &display);
			 place_player_2(&the_player[1], &display);
			 place_player_3(&the_player[2], &display);
			 place_player_4(&the_player[3], &display);
			 place_blokcs(&display);
			 if(malloc_state < 0){
				printf("\n\nNot enough memory.\n\n");
				break;
			 }
			 do{
				display_grid(&display);
				state = make_move(&(the_player[nowPlays]), &display, symbol[nowPlays], players_blocks[nowPlays]);
                if (state == BLOCK_OK) players_blocks[nowPlays]--;
	  	        if (state == CORRECT && checkWinner(display, symbol[nowPlays], the_player[nowPlays]))
            {
      		printf("Winner %s\n", the_player[nowPlays].name);
  		    for(i = 0; i < display.n; i++){
				free(display.grid_space[i]);
			}
			free(display.grid_space);
 		   return 1;
	      }
		  if (state != WRONG) {
			nowPlays = (nowPlays+1) % (2 * choice_players);
		  }
		  if (state == EXIT) {
				for(i = 0; i < display.n; i++){
				 free(display.grid_space[i]);
				}
			free(display.grid_space);
  	      return 1;
		 }
		 } while((WINNER != 1) && (EXIT != -2));//As long as the player hasn't  quit (1) the game and did not win
		     if(state == EXIT){//Player quit the game
              printf("Player %s game over \n\n", the_player[nowPlays].name);
			  break;
		    }
		}
	break;
   }
  case 2:{
		printf("without blocks for 4 players custom grid\n");
		nowPlays = 0;
		start_game(&display);
		while(1){
		start_game_default(&the_player[0]);
		start_game_default(&the_player[1]);
		start_game_default(&the_player[2]);
		start_game_default(&the_player[3]);
																							
		malloc_state = initialise_game(the_player, &display);
																							
		place_player_1(&the_player[0], &display);
		place_player_2(&the_player[1], &display);
		place_player_3(&the_player[2], &display);
		place_player_4(&the_player[3], &display);
																							
		if(malloc_state < 0){
		  printf("\n\nNot enough memory.\n\n");
	      break;
		}
		do{
		 display_grid(&display);
		 state = make_move(&(the_player[nowPlays]), &display, symbol[nowPlays], players_blocks[nowPlays]);
  	     if (state == BLOCK_OK) players_blocks[nowPlays]--;
  	     if (state == CORRECT && checkWinner(display, symbol[nowPlays], the_player[nowPlays])){
 		   printf("Winner %s\n", the_player[nowPlays].name);
 		   for(i = 0; i < display.n; i++){
			free(display.grid_space[i]);
		   }
		  free(display.grid_space);
 		return 1;
       }
       if (state != WRONG){
			nowPlays = (nowPlays+1) % (2 * choice_players);
	   }
	   if (state == EXIT){
				for(i = 0; i < display.n; i++){
				      free(display.grid_space[i]);
				}
				free(display.grid_space);
	 	return 1;
		}
		} while((WINNER != 1) && (EXIT != -2));//As long as the player hasn't  quit (1) the game and did not win
		if(state == EXIT){//Player quit the game
		         printf("Player %s game over \n\n", the_player[nowPlays].name);
		         break;
        		}
        	   }
                   break;
            	 }
            	}
               }while(blocks !=0);
            	break;	
               }
              }
            }while(choice_players != 0);
        	break;
           }
          }
         }while(choice_grid != 0);
        break;
        }
	    case 0:{
         // to normal exit the game
	     return 0;
	     }
      }
	}while(choice != 0);

	//free memory
	for(i = 0; i < display.n; i++)
	{
		free(display.grid_space[i]);
	}
	free(display.grid_space);
}


//function for checking the winnner who won the game for all 4 players
int checkWinner(grid_t display, char symbol, player the_player)
{
	if (symbol == '#' && the_player.player_n == 0) return 1;
	if (symbol == '*' && the_player.player_m == display.m-1) return 1;
	if (symbol == '@' && the_player.player_n == display.m - 1) return 1;
	if (symbol == '&' && the_player.player_m == 0) return 1;
	return 0;
}

//function that place the player 1
void place_player_1(player *the_player, grid_t *display)
{
	int n,m;

	//Choose the mid-bottom possition 
	n = display->n-1;
	m = (display->m-1)/2; 
	display->grid_space[n][m] = '#';

	//Update players's position
	//the_player-> player_n= n;
	//the_player-> player_m = m;
}


//function that place the player 3
void place_player_3(player *the_player, grid_t *display)
{
	int n,m;

	//left-mid possition
	n = (display->n-1)/2; 
	m = 0;
	display->grid_space[n][m] = '*';

	//Update players's position
	//the_player-> player_1= n;
	//the_player-> player_1 = m;
	
}



//function that place the player 2
void place_player_2(player *the_player, grid_t *display)
{
	int n,m;

	//Choose the mid-top possition 
	n = 0; 
	m = (display->m-1)/2; 
	display->grid_space[n][m] = '@';

	//Update players's position
	//the_player-> player_1= n;
	//the_player-> player_1 = m;
}


//function that place the player 4
void place_player_4(player *the_player, grid_t *display)
{
	int n,m;

	//right-mid possition
	n = (display->n-1)/2; // pame stin mesi tis diastasis n 
	m = display->m-1; // pame stin akri tou m
	//Put player_1 in it
	display->grid_space[n][m] = '&';

	//Update players's position
	//the_player-> player_1= n;
	//the_player-> player_1 = m;
}

// function for default case 10x10
void start_game_default(player *the_player)
{
	char c;
	getchar();
	fflush(stdin);

	printf("Enter your name : ");
	scanf("%s", the_player->name);
}


//function that place blocks on grid and also puts different number of blocks depends on grid size
void place_blokcs(grid_t *display)
{
	
	srand(time(NULL));
	
	int n, m,rand_pos_xy;
	int i = 0;
	
	
	
	if((display->n * display->m >= 25) && (display->n * display->m <= 49))
	{
		// if the grid size is >=5 and <=7 then place 1 block (XX)
		for(i=0;i<1;i++)
		{
			printf("place blocks 1\n");
			rand_pos_xy = rand();
			if ( rand_pos_xy <= RAND_MAX/2 )
			{
				// place blocks horizontal					
				n = rand() % display->n;
				m = rand() % display->m;
				if (m > 0 && display->grid_space[n][m] == '.' && display->grid_space[n][m-1] == '.'){
					display->grid_space[n][m] = 'X';
					display->grid_space[n][--m] = 'X';
				}
				else i--;
			
			}
			else
			{
				// place blocks vertical	
				n = rand() % display->n;
				m = rand() % display->m;
				if (n > 0 && display->grid_space[n][m] == '.' && display->grid_space[n-1][m] == '.'){
					display->grid_space[n][m] = 'X';
					display->grid_space[--n][m] = 'X';
				}
				else i--;
			
			}
		}
	}
	else if((display->n * display->m >= 50) && (display->n * display->m <= 100))
	{
		printf("place blocks 2\n");
		// if the grid size is >=8 and <=10 then place 3 block (XX)x3
		for(i=0;i<3;i++)
		{
			rand_pos_xy = rand();
			if ( rand_pos_xy <= RAND_MAX/2 )
			{					
			 	// place blocks horizontal
				n = rand() % display->n;
				m = rand() % display->m;
				if (m > 0 && display->grid_space[n][m] == '.' && display->grid_space[n][m-1] == '.'){
					display->grid_space[n][m] = 'X';
					display->grid_space[n][--m] = 'X';
				}
				else i--;
			}
			else
			{
				// place blocks vertical
				n = rand() % display->n;
				m = rand() % display->m;
				if (n > 0 && display->grid_space[n][m] == '.' && display->grid_space[n-1][m] == '.'){
					display->grid_space[n][m] = 'X';
					display->grid_space[--n][m] = 'X';
				}
				else i--;
			}			
		}
	}
	else if ((display->n * display->m >= 101) && (display->n * display->m <= 667))
	{
		printf("place blocks 3\n");
		// if the grid size is >10 and <=26 then place 5 block (XX)x5
		for(i=0;i<5;i++)
		{
			rand_pos_xy = rand();
			if ( rand_pos_xy <= RAND_MAX/2 )
			{					
			 	// place blocks horizontal
				n = rand() % display->n;
				m = rand() % display->m;
				if (m > 0 && display->grid_space[n][m] == '.' && display->grid_space[n][m-1] == '.'){
					display->grid_space[n][m] = 'X';
					display->grid_space[n][--m] = 'X';
				}
				else i--;
			
			}
			else
			{
				// place blocks vertical
				n = rand() % display->n;
				m = rand() % display->m;
				if (n > 0 && display->grid_space[n][m] == '.' && display->grid_space[n-1][m] == '.'){
					display->grid_space[n][m] = 'X';
					display->grid_space[--n][m] = 'X';
				}
				else i--;
			
			}
		}
	}				
}


// function that start the game in case the grid is not default (grid !=10x10)
void start_game(grid_t *display)
{
	while(1)
	{
		printf("Enter the dimensions of the grid : ");
		scanf("%d",&display->n);
		display->m = display->n;
		if(((display->n >= 5 && display->n <= 26)) && (display->m >= 5 && display->m <= 26))
		{
			break;
		}
	} 
	
	//COMMENTS//
	/*
	to idio komati kodika me do-while den litourgi gia ton deuftero periorismo diladi mpori na pari timi kai megaliteri tou 26 an kai
	den tha eprepe
	
	do
	{
		printf("Enter the dimensions of the grid : ");
		scanf("%d",&display->n);
		display->m = display->n; 
	} while( (((display->n * display->m)) != ((display->n < 5 && display->n < 26)) && (display->m < 5 && display->m < 26)));
	
	*/

}

// initialise the game with NxM 
int initialise_game(player *the_player, grid_t *display)
{
	srand(time(NULL));

	int i, j;
	int random_n, random_m;
									// when the flag_default_grid == -1 then the array will be the defaul array 10x10 and not custom array
	if (flag_default_grid == -1)   // otan i metavliti flag_default_grid tha gini = -1 tote tha imaste stin periptosi pou o pektis exi dosi tin default diastasi NxM = 10
	{
									  // in defaul case NxM must be 10 
		display->n = display->m = 10; // anathesi timis gia tin NxM diastasi tou pinaka pou ine stin default periptosi =10 
		display->grid_space = create_grid(display->n, display->m);
		if(display->grid_space == NULL)
			return -1;

		for(i = 0; i < display->n; i++)
		{
			for(j = 0; j < display->m; j++)
				display->grid_space[i][j] = '.';
		}
	}
	
	else
	{
		display->grid_space = create_grid(display->n, display->m);
		if(display->grid_space == NULL)
			return -1;

		for(i = 0; i < display->n; i++)
		{
			for(j = 0; j < display->m; j++)
				display->grid_space[i][j] = '.';
		}
	}
	
	return 0;
}

// fucntion that creates grid with malloc
char **create_grid(int n, int m)
{
	int i, j;
	char **temp_grid;
	
	if (flag_default_grid == -1) // check if we are in default case 10x10
	{

		n = m = 10; //  NxM == 10
		
		//Create the first dimension of the array
		temp_grid = (char**)malloc(n * sizeof(char*));
		if(temp_grid == NULL)
			return NULL;

		//Create the second dimension of the array
		for(i = 0; i < n; i++)
		{
			temp_grid[i] = (char*)malloc(m * sizeof(char));
				if(temp_grid[i] == NULL)
					return NULL;
		}
		
	}
	else // if we are not in default case 10x10
	{
		//Create the first dimension of the array
		temp_grid = (char**)malloc(n * sizeof(char*));

		if(temp_grid == NULL)
			return NULL;

		//Create the second dimension of the array
		for(i = 0; i < n; i++)
		{
			temp_grid[i] = (char*)malloc(m * sizeof(char));
				if(temp_grid[i] == NULL)
					return NULL;
		}
	}
	return temp_grid;
}


// function that displays the grid only 
void display_grid(grid_t *grid)
{
	int i, j;

	//Print the header (column numbers)
	printf("   ");
	for(i = 0; i <grid->m ; i++)
	{
			printf("  %c", i+'a'); // print the ASCII Codes Table from "a" to "z"
	}

	printf("\n");

	for(i = 0; i <= grid->m; i++)
		printf("---", i);

	printf("\n");

	//For each line of the array
	for(i = 0; i < grid->n; i++)
	{
		//Display the number of the line
		if(i < 9)
			printf(" %d|", i + 1);
		else
			printf("%d|", i + 1);

		//And the contents of the line
		for(j = 0; j < grid->m; j++)
			printf("  %c", grid->grid_space[i][j]);

		printf("\n");
	}

}

// function that moves player 
int make_move(player *the_player, grid_t *display, char symbol, int blocks)
{
	char moves[MOVES_SIZE] = {0};
	int i;
	int jump_squares = 1;
	int decide;
	int tmp_char = 1;
	int array_size = 0;
	int r1, c1, r2, c2; // rows , cols

	printf("Player %s (%c) (blocks left: %d) make your move(s):\n", the_player->name, symbol, blocks);
	scanf("%s",moves);
	
	if (strcmp(moves, "exit") == 0){
		return EXIT;
	}
	else if (strcmp(moves, "help") == 0){
		printf("No help available!!!\n");
		return WRONG;
	}
	
	if (strlen(moves) < 2 || strlen(moves) > 6){
		printf("Wrong move!\n");
		return WRONG;
	}
	
	if (strlen(moves) == 2){ //  if the sting length == 2 (e2)
		c1 = tolower(moves[0]) - 'a';
		r1 = moves[1] - '1';
		
		if (c1 < 0 || c1 >= display->n){
			printf("%s: column out of bounds!\n", moves);
			return WRONG;
		}
		
		if (r1 < 0 || r1 > display->m){
			printf("%s: row out of bounds!\n", moves);
			return WRONG;
		}
		
		if (display->grid_space[r1][c1] != '.'){
			printf("%s: position already taken!\n", moves);
			return WRONG;
		}
		
		if (r1 > 0 && display->grid_space[r1-1][c1] == symbol) {
			display->grid_space[r1-1][c1] = '.'; // leave the . when the player was
			display->grid_space[r1][c1] = symbol; // leave the symbol of player
			the_player->player_m = c1; // updates player position m
			the_player->player_n = r1; // updates player possition n
			return CORRECT;
		}
		
		if (r1 < display->n - 1 && display->grid_space[r1+1][c1] == symbol) {
			display->grid_space[r1+1][c1] = '.';
			display->grid_space[r1][c1] = symbol;
			the_player->player_m = c1;
			the_player->player_n = r1;
			return CORRECT;
		}
		
		if (c1 > 0 && display->grid_space[r1][c1-1] == symbol) {
			display->grid_space[r1][c1-1] = '.';
			display->grid_space[r1][c1] = symbol;
			the_player->player_m = c1;
			the_player->player_n = r1;
			return CORRECT;
		}
		
		if (c1 < display->m - 1 && display->grid_space[r1][c1+1] == symbol) {
			display->grid_space[r1][c1+1] = '.';
			display->grid_space[r1][c1] = symbol;
			the_player->player_m = c1;
			the_player->player_n = r1;
			return CORRECT;
		}
		
		printf("%s: new position is not next to %c\n!", moves, symbol);
		return WRONG;
	}
	else if (strlen(moves) == 3){ //if the sting length == 3 (b10)
		c1 = tolower(moves[0]) - 'a';
		r1 = 10 * ( moves[1] - '0') + moves[2] - '1';
		
		if (c1 < 0 || c1 >= display->n){
			printf("%s: column out of bounds!\n", moves);
			return WRONG;
		}
		
		if (r1 < 0 || r1 > display->m){
			printf("%s: row out of bounds!\n", moves);
			return WRONG;
		}
		
		if (display->grid_space[r1][c1] != '.'){
			printf("%s: position already taken!\n", moves);
			return WRONG;
		}
		
		if (r1 > 0 && display->grid_space[r1-1][c1] == symbol) {
			display->grid_space[r1-1][c1] = '.';
			display->grid_space[r1][c1] = symbol;
			the_player->player_m = c1;
			the_player->player_n = r1;
			return CORRECT;
		}
		
		if (r1 < display->n - 1 && display->grid_space[r1+1][c1] == symbol) {
			display->grid_space[r1+1][c1] = '.';
			display->grid_space[r1][c1] = symbol;
			the_player->player_m = c1;
			the_player->player_n = r1;
			return CORRECT;
		}
		
		if (c1 > 0 && display->grid_space[r1][c1-1] == symbol) {
			display->grid_space[r1][c1-1] = '.';
			display->grid_space[r1][c1] = symbol;
			the_player->player_m = c1;
			the_player->player_n = r1;
			return CORRECT;
		}
		
		if (c1 < display->m - 1 && display->grid_space[r1][c1+1] == symbol) {
			display->grid_space[r1][c1+1] = '.';
			display->grid_space[r1][c1] = symbol;
			the_player->player_m = c1;
			the_player->player_n = r1;
			return CORRECT;
		}
		
		printf("%s: new position is not next to %c\n!", moves, symbol);
		return WRONG;
	}
	else if (strlen(moves) == 4){ //if the sting length == 4  (a1b1), (a1a2)
		if (blocks == 0){
			printf("No more block!!\n");
			return WRONG;
		}
		c1 = tolower(moves[0]) - 'a';
		r1 = moves[1] - '1';
		c2 = tolower(moves[2]) - 'a';
		r2 = moves[3] - '1';
		
		
		if (c1 < 0 || c1 >= display->n){
			printf("%s: first column out of bounds!\n", moves);
			return WRONG;
		}
		
		if (r1 < 0 || r1 > display->m){
			printf("%s: first row out of bounds!\n", moves);
			return WRONG;
		}
		
		if (c2 < 0 || c2 >= display->n){
			printf("%s: second column out of bounds!\n", moves);
			return WRONG;
		}
		
		if (r2 < 0 || r2 > display->m){
			printf("%s: second row out of bounds!\n", moves);
			return WRONG;
		}
		
		if (display->grid_space[r1][c1] != '.'){
			printf("%s: first position already taken!\n", moves);
			return WRONG;
		}
		
		if (display->grid_space[r2][c2] != '.'){
			printf("%s: second position already taken!\n", moves);
			return WRONG;
		}
		
		if ( (r1 == r2 && abs(c1-c2) == 1)  ||  (c1 == c2 && abs(r1-r2) == 1) ){
			display->grid_space[r2][c2] = 'X';
			display->grid_space[r1][c1] = 'X';
			return BLOCK_OK;
		}
		
		printf("%s: block positions are not neighbours in straight line\n!", moves);
		return WRONG;
	}
	else if (strlen(moves) == 5 && isalpha(moves[2])){ //if the sting length == 5 (a9a10)
		if (blocks == 0){
			printf("No more block!!\n");
			return WRONG;
		}
		c1 = tolower(moves[0]) - 'a';
		r1 = moves[1] - '1';
		c2 = tolower(moves[2]) - 'a';
		r2 = 10 * ( moves[3] - '0') + moves[4] - '1';
		
		
		if (c1 < 0 || c1 >= display->n){
			printf("%s: first column out of bounds!\n", moves);
			return WRONG;
		}
		
		if (r1 < 0 || r1 > display->m){
			printf("%s: first row out of bounds!\n", moves);
			return WRONG;
		}
		
		if (c2 < 0 || c2 >= display->n){
			printf("%s: second column out of bounds!\n", moves);
			return WRONG;
		}
		
		if (r2 < 0 || r2 > display->m){
			printf("%s: second row out of bounds!\n", moves);
			return WRONG;
		}
		
		if (display->grid_space[r1][c1] != '.'){
			printf("%s: first position already taken!\n", moves);
			return WRONG;
		}
		
		if (display->grid_space[r2][c2] != '.'){
			printf("%s: second position already taken!\n", moves);
			return WRONG;
		}
		
		if ( (r1 == r2 && abs(c1-c2) == 1)  ||  (c1 == c2 && abs(r1-r2) == 1) ){
			display->grid_space[r2][c2] = 'X';
			display->grid_space[r1][c1] = 'X';
			return BLOCK_OK;
		}
		
		printf("%s: block positions are not neighbours in straight line\n!", moves);
		return WRONG;
	}
	else if (strlen(moves) == 5 && isalpha(moves[3])){ // a10a9
		if (blocks == 0){
			printf("No more block!!\n");
			return WRONG;
		}
		c1 = tolower(moves[0]) - 'a';
		r1 = 10 * ( moves[1] - '0') + moves[2] - '1';
		c2 = tolower(moves[3]) - 'a';
		r2 = moves[4] - '1';
		
		
		if (c1 < 0 || c1 >= display->n){
			printf("%s: first column out of bounds!\n", moves);
			return WRONG;
		}
		
		if (r1 < 0 || r1 > display->m){
			printf("%s: first row out of bounds!\n", moves);
			return WRONG;
		}
		
		if (c2 < 0 || c2 >= display->n){
			printf("%s: second column out of bounds!\n", moves);
			return WRONG;
		}
		
		if (r2 < 0 || r2 > display->m){
			printf("%s: second row out of bounds!\n", moves);
			return WRONG;
		}
		
		if (display->grid_space[r1][c1] != '.'){
			printf("%s: first position already taken!\n", moves);
			return WRONG;
		}
		
		if (display->grid_space[r2][c2] != '.'){
			printf("%s: second position already taken!\n", moves);
			return WRONG;
		}
		
		if ( (r1 == r2 && abs(c1-c2) == 1)  ||  (c1 == c2 && abs(r1-r2) == 1) ){
			display->grid_space[r2][c2] = 'X';
			display->grid_space[r1][c1] = 'X';
			return BLOCK_OK;
		}
		
		printf("%s: block positions are not neighbours in straight line\n!", moves);
		return 0;
	}
	else if (strlen(moves) == 6){ // a12a13, b12c12
		if (blocks == 0){
			printf("No more block!!\n");
			return WRONG;
		}
		c1 = tolower(moves[0]) - 'a';
		r1 = 10 * ( moves[1] - '0') + moves[2] - '1';
		c2 = tolower(moves[3]) - 'a';
		r2 = 10 * ( moves[4] - '0') + moves[5] - '1';
		
		
		if (c1 < 0 || c1 >= display->n){
			printf("%s: first column out of bounds!\n", moves);
			return WRONG;
		}
		
		if (r1 < 0 || r1 > display->m){
			printf("%s: first row out of bounds!\n", moves);
			return WRONG;
		}
		
		if (c2 < 0 || c2 >= display->n){
			printf("%s: second column out of bounds!\n", moves);
			return WRONG;
		}
		
		if (r2 < 0 || r2 > display->m){
			printf("%s: second row out of bounds!\n", moves);
			return WRONG;
		}
		
		if (display->grid_space[r1][c1] != '.'){
			printf("%s: first position already taken!\n", moves);
			return WRONG;
		}
		
		if (display->grid_space[r2][c2] != '.'){
			printf("%s: second position already taken!\n", moves);
			return WRONG;
		}
		
		if ( (r1 == r2 && abs(c1-c2) == 1)  ||  (c1 == c2 && abs(r1-r2) == 1) ){
			display->grid_space[r2][c2] = 'X';
			display->grid_space[r1][c1] = 'X';
			return BLOCK_OK;
		}
		
		printf("%s: block positions are not neighbours in straight line\n!", moves);
		return WRONG;
	}

	return 0;
}













