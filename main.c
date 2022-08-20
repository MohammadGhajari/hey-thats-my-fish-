/*
	Name : game (Hey,that's my fish!)
	Authors : mohammad ghajari & soheil babaee
	Date : 1400 / 11 / 13
	Description : proge payan term mabani (dr. mostafa nori baigi)
*/

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//----------------------->rouse mostatil
typedef struct       
{
	int x1, y1, x2, y2;
} noghat_mostatil;

//---------------------->mokhtasat har khane az arraye map
typedef struct      
{
	int x, y;
}mokhtasat_map;

//---------------------->namayesh safhe entekhab tedad player
void Preview() 
{
	//font define
	ALLEGRO_FONT *font= al_load_ttf_font("arial.ttf", 30, 0);
	ALLEGRO_FONT *font1 = al_load_ttf_font("Hypeblox-L3YGZ.ttf", 80, 0);
	ALLEGRO_FONT *font2= al_load_ttf_font("SillerPersonalUse-9Y3wn.otf", 30, 0);
	ALLEGRO_BITMAP *bitmap = al_load_bitmap("background.jpg");
	al_draw_bitmap(bitmap, 0, 0, 0);
	
	//color define
	ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR ice_blue = al_map_rgb(165, 242, 255);
	
	al_draw_text(font2, black, 150, 320, 0, "Please select the number of your players");	
	al_draw_text(font1, ice_blue, 400, 50, 0, "Hey! that's my fish!!!");	
	
	al_draw_filled_rounded_rectangle(300, 380, 400, 420,10, 10, ice_blue);
	al_draw_text(font,black,340,385,0, "2");
	
	al_draw_filled_rounded_rectangle(450, 380, 550, 420, 10, 10, ice_blue);
	al_draw_text(font,black,495,385,0, "3");
	
	al_draw_filled_rounded_rectangle(600, 380, 700, 420, 10, 10, ice_blue);
	al_draw_text(font,black,645,385,0, "4");
	al_flip_display();
}

//---------------------->entekhab tplayeredad 
int choose_number_of_player()
{
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	int x, y;
	while(1) /*entekhab tedad player*/
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button == 1)
			{
				x = ev.mouse.x;
    			y = ev.mouse.y;
			}
		}
		if(x >= 300 && x <= 400 && y >= 380 && y <= 420)
			return 2;
		if(x >= 450 && x <= 550 && y >= 380 && y <= 420)
			return 3;
		if(x >= 600 && x <= 700 && y >= 380 && y <= 420)
			return 4;
	}	
}

//---------------------->taeen tedad mahi haye har khane
void meghdar_dehi_map(int map[8][8]) 
{
	int  x, y, i, j;
	srand(time(0));
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
			map[i][j] = 0;
	/* tain khane haye daraye 3 mahi*/
	for(i = 0; i < 10; i++)
	{
		x = rand() % 8;
		y = rand() % 8;
		if(y % 2 == 0 && x == 0)
		{
			i--;
			continue;
		}
		if(map[y][x] == 3)
		{
			i--;
			continue;
		}
		map[y][x] = 3;
	}
	/*tain khane haye daraye 2 mahi*/
	for(i = 0; i < 20; i++)
	{	
		x = rand() % 8;
		y = rand() % 8;
		if(y % 2 == 0 && x == 0)
		{
			i--;
			continue;
		}
		if(map[y][x] == 3 || map[y][x] == 2)
		{
			i--;
			continue;
		}
		map[y][x] = 2;
	}	
	/*tain khane haye daraye 1 mahi*/
	for(i = 0; i < 30; i++)
	{
		x = rand() % 8;
		y = rand() % 8;
		if(y % 2 == 0 && x == 0)
		{
			i--;
			continue;
		}
		if(map[y][x] == 3 || map[y][x] == 2 || map[y][x] == 1)
		{
			i--;
			continue;
		}
		map[y][x] = 1;
	}
}

//---------------------->rasm map
void Draw_map(int map[8][8], mokhtasat_map map_m[8][8])  
{
	
	ALLEGRO_BITMAP *One_fish = al_load_bitmap("1fish.png");
	ALLEGRO_BITMAP *Two_fish = al_load_bitmap("2fish.png");
	ALLEGRO_BITMAP *Three_fish = al_load_bitmap("3fish.png");
	
	al_clear_to_color(al_map_rgb(68, 167, 196)); /*background color*/
	int i, j;
	for(i = 0; i < 8; i++) /*mokhtasat markaz har 6 zelee*/
	{
		for(j = 0; j < 8; j++)
		{
			if(i % 2 == 0 )
				map_m[i][j].x = j * 200 + 200;
			else
				map_m[i][j].x = j * 200 + 100;
			map_m[i][j].y = i * 113	 + 125;
		}
	}
	
	for(i = 0; i < 8; i++) /* rasm mahiha dar markaz har 6 zelee*/
	{
		for(j = 0; j < 8; j++)
		{
			if(i % 2 == 0)
			{
				if(map[i][j] == 1)
					al_draw_bitmap(One_fish, map_m[i][j].x - 300, map_m[i][j].y - 70, 0);
				if(map[i][j] == 2)
					al_draw_bitmap(Two_fish, map_m[i][j].x - 300, map_m[i][j].y - 70, 0);
				if(map[i][j] == 3)
					al_draw_bitmap(Three_fish, map_m[i][j].x - 300, map_m[i][j].y - 70, 0);
			}else
			{
				if(map[i][j] == 1)
					al_draw_bitmap(One_fish, map_m[i][j]. x - 100, map_m[i][j].y - 70, 0);
				if(map[i][j] == 2)
					al_draw_bitmap(Two_fish, map_m[i][j].x - 100, map_m[i][j].y - 70, 0);
				if(map[i][j] == 3)
					al_draw_bitmap(Three_fish, map_m[i][j].x - 100, map_m[i][j].y - 70, 0);
			}
			al_flip_display();
		}
	}
}

//--------------------->agar tedad player ha 2 bashaad
int Two_player(int map[8][8], noghat_mostatil mokhtasat[8][8], mokhtasat_map map_m[8][8], int emtiaz[2][2])
{
	/*bitmap define*/
	ALLEGRO_BITMAP *penguins_p2 = al_load_bitmap("penguins_p2.png");
	ALLEGRO_BITMAP *penguins_p1 = al_load_bitmap("penguins_p1.png");
	ALLEGRO_FONT *font = al_load_ttf_font("arial.ttf", 35, 0);
	ALLEGRO_FONT *font1 = al_load_ttf_font("arial.ttf", 45, 0);
	ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue(); 
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR white = al_map_rgb(225, 255, 255);
	ALLEGRO_COLOR red = al_map_rgb(233, 48, 48);
	ALLEGRO_COLOR green = al_map_rgb(59, 255, 53);
	ALLEGRO_COLOR yellow = al_map_rgb(248,255,4);
	al_register_event_source(event_queue1, al_get_mouse_event_source());
	
	int i, j, k, l, flag, flag1, h, q1, q2, o;
	
	
	Draw_map(map, map_m);
	al_draw_filled_rounded_rectangle(1620, 260, 1900, 410, 10, 10, white);
	al_draw_filled_rounded_rectangle(1620, 440, 1900, 590, 10, 10, red);
	al_draw_text(font1, black, 1670, 200, 0, "Scores :");
	al_flip_display();
	for(i = 0; i < 8; i++)
	{	
		al_draw_filled_rounded_rectangle(1620, 260, 1900, 410, 10, 10, white);
		al_draw_textf(font, black, 1650, 290, 0, "Fishes: %d", emtiaz[0][0]);
		al_draw_textf(font, black, 1650, 340, 0, "Tiles: %d", emtiaz[0][1]);
		al_draw_filled_rounded_rectangle(1620, 440, 1900, 590, 10, 10, red);
		al_draw_textf(font, black, 1650, 470, 0, "Fishes: %d", emtiaz[1][0]);
		al_draw_textf(font, black, 1650, 520, 0, "Tiles: %d", emtiaz[1][1]);
		al_flip_display();
		if(i % 2 == 0)
		{
			al_draw_filled_rounded_rectangle(1620 ,40 ,1900 ,190 ,10, 10,white );
			al_draw_text(font,black,1650 ,50 ,0, "Player Turn :");
	    	al_draw_text(font,black,1700 ,120 ,0, "White");
			al_flip_display();
			while(1)
			{
				ALLEGRO_EVENT ev;
				al_wait_for_event(event_queue1, &ev);
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{	
					if(ev.mouse.button == 1)
					{
						flag = 1;
						flag1 = 1;
						int x_m = ev.mouse.x;
						int y_m = ev.mouse.y;
						o = mokhtasat_arr(mokhtasat, x_m, y_m);
						q1 = o/10;
						q2 = o%10;
						if(q1%2==0)
						   q2++;
						if(!(map[q1][q2]>=1 && map[q1][q2]<=3))
						    continue;    
						for(k = 0; k < 8; k++)
						{
							if(k % 2 == 0)
							    h=7;
							else
							    h=8;
							for(l = 0; l < h; l++)
							{	
								if(x_m > mokhtasat[k][l].x1 && x_m < mokhtasat[k][l].x2 && y_m > mokhtasat[k][l].y1 && y_m < mokhtasat[k][l].y2)
								{
									al_draw_bitmap(penguins_p1,(mokhtasat[k][l].x1 + mokhtasat[k][l].x2) / 2 - 60, (mokhtasat[k][l].y1 + mokhtasat[k][l].y2) / 2 - 60, 0);
									al_flip_display();
									if(k % 2 == 0)
									{
										emtiaz[0][0] += map[k][l + 1];
										emtiaz[0][1]++;
										map[k][l + 1] = 4;
									}else
									{
										emtiaz[0][0] += map[k][l];
										emtiaz[0][1]++;
										map[k][l] = 4;
									}
									flag = 0;	
									break;	
								}
							}
							if(flag == 0)
							{
								flag1 = 0;
								break;
							}
						}
						if(flag1 == 0)
						{
							break;
						}
					}
				}	
			}
		}else
		{
			al_draw_filled_rounded_rectangle(1620 ,40 ,1900 ,190 ,10, 10,red );
			al_draw_text(font,black,1650 ,50 ,0, "Player Turn :");
	    	al_draw_text(font,black,1700 ,120 ,0,"Red");
			al_flip_display();
			while(1)
			{
				ALLEGRO_EVENT ev;
				al_wait_for_event(event_queue1, &ev);
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					if(ev.mouse.button == 1)
					{
						flag = 1;
						flag1 = 1;
						int x_m = ev.mouse.x;
						int y_m = ev.mouse.y;
						o = mokhtasat_arr(mokhtasat, x_m, y_m);
						q1 = o/10;
						q2 = o%10;
						if(q1%2==0)
						   q2++;
						if(!(map[q1][q2]>=1 && map[q1][q2]<=3))
						    continue;
						    
						for(k = 0; k < 8; k++)
						{
							if(k % 2 == 0)
							    h=7;
							else
							    h=8;
							for(l = 0; l < h; l++)
							{
								if(x_m > mokhtasat[k][l].x1 && x_m < mokhtasat[k][l].x2 && y_m > mokhtasat[k][l].y1 && y_m < mokhtasat[k][l].y2)
								{
									al_draw_bitmap(penguins_p2,(mokhtasat[k][l].x1 + mokhtasat[k][l].x2) / 2 - 60, (mokhtasat[k][l].y1 + mokhtasat[k][l].y2) / 2 - 60, 0);
									al_flip_display();
									if(k % 2 == 0)
									{
										emtiaz[1][0] += map[k][l + 1];
										emtiaz[1][1]++;
										map[k][l + 1] = 5;
									
									}else
									{
										emtiaz[1][0] += map[k][l];
										emtiaz[1][1]++;
										map[k][l] = 5;	
									}
									flag = 0;
									break;			
								}
							}
						}
						if(flag == 0)
						{
							flag1 = 0;
							break;
						}
					}
				}	
			}
		}
	}
	al_draw_filled_rounded_rectangle(1620, 440, 1900, 590, 10, 10, red);
	al_draw_textf(font, black, 1650, 470, 0, "Fishes: %d", emtiaz[1][0]);
	al_draw_textf(font, black, 1650, 520, 0, "Tiles: %d", emtiaz[1][1]);
	al_flip_display();
}

//---------------------->agar tedad player ha 3 bashaad
int Three_player(int map[8][8], noghat_mostatil mokhtasat[8][8], mokhtasat_map map_m[8][8], int emtiaz[3][2])
{
	
	/*bitmap define*/
	ALLEGRO_BITMAP *penguins_p3 = al_load_bitmap("penguins_p3.png");
	ALLEGRO_BITMAP *penguins_p2 = al_load_bitmap("penguins_p2.png");
	ALLEGRO_BITMAP *penguins_p1 = al_load_bitmap("penguins_p1.png");
	ALLEGRO_FONT *font= al_load_ttf_font("arial.ttf", 35, 0);
	ALLEGRO_FONT *font1 = al_load_ttf_font("arial.ttf", 45, 0);
	ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue(); 
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR white = al_map_rgb(225, 255, 255);
	ALLEGRO_COLOR red = al_map_rgb(233, 48, 48);
	ALLEGRO_COLOR green = al_map_rgb(59, 255, 53);
	ALLEGRO_COLOR yellow = al_map_rgb(248,255,4);
	al_register_event_source(event_queue1, al_get_mouse_event_source());
	
	int i, j, k, l, flag, flag1, h, q1, q2, o;
	
	al_clear_to_color(black);
	Draw_map(map, map_m);
	al_draw_filled_rounded_rectangle(1620, 260, 1900, 410, 10, 10, white);
	al_draw_filled_rounded_rectangle(1620, 440, 1900, 590, 10, 10, red);
	al_draw_filled_rounded_rectangle(1620, 620, 1900, 770, 10, 10, green);
	al_draw_text(font1, black, 1670, 200, 0, "Scores :");
	al_flip_display();
	for(i = 0; i < 9; i++)
	{	
		al_draw_filled_rounded_rectangle(1620, 260, 1900, 410, 10, 10, white);
		al_draw_textf(font, black, 1650, 290, 0, "Fishes: %d", emtiaz[0][0]);
		al_draw_textf(font, black, 1650, 340, 0, "Tiles: %d", emtiaz[0][1]);
		al_draw_filled_rounded_rectangle(1620, 440, 1900, 590, 10, 10, red);
		al_draw_textf(font, black, 1650, 470, 0, "Fishes: %d", emtiaz[1][0]);
		al_draw_textf(font, black, 1650, 520, 0, "Files: %d", emtiaz[1][1]);
		al_draw_filled_rounded_rectangle(1620, 620, 1900, 770, 10, 10, green);
		al_draw_textf(font, black, 1650, 650, 0, "Fishes: %d", emtiaz[2][0]);
		al_draw_textf(font, black, 1650, 700, 0, "Files: %d", emtiaz[2][1]);
		al_flip_display();
		if(i % 3 == 0)
		{
			al_draw_filled_rounded_rectangle(1620 ,40 ,1900 ,190 ,10, 10,white );
			al_draw_text(font,black,1650 ,50 ,0, "Player Turn :");
	    	al_draw_text(font,black,1700 ,120 ,0, "White");
			al_flip_display();
			while(1)
			{
				ALLEGRO_EVENT ev;
				al_wait_for_event(event_queue1, &ev);
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{	
					if(ev.mouse.button == 1)
					{
						flag = 1;
						flag1 = 1;
						int x_m = ev.mouse.x;
						int y_m = ev.mouse.y;
						o = mokhtasat_arr(mokhtasat, x_m, y_m);
						q1 = o/10;
						q2 = o%10;
						if(q1%2==0)
						   q2++;
						if(!(map[q1][q2]>=1 && map[q1][q2]<=3))
						    continue;
						
						for(k = 0; k < 8; k++)
						{
							if(k % 2 == 0)
							    h=7;
							else
							    h=8;
							for(l = 0; l < h; l++)
							{
								if(x_m > mokhtasat[k][l].x1 && x_m < mokhtasat[k][l].x2 && y_m > mokhtasat[k][l].y1 && y_m < mokhtasat[k][l].y2)
								{
									al_draw_bitmap(penguins_p1,(mokhtasat[k][l].x1 + mokhtasat[k][l].x2) / 2 - 60, (mokhtasat[k][l].y1 + mokhtasat[k][l].y2) / 2 - 60, 0);
									al_flip_display();
									if(k % 2 == 0)
									{
										emtiaz[0][0] += map[k][l + 1];
										emtiaz[0][1]++;
										map[k][l + 1] = 4;
									}else
									{
										emtiaz[0][0] += map[k][l];
										emtiaz[0][1]++;
										map[k][l] = 4;
									}
									flag = 0;
									break;			
								}
							}
							if(flag == 0)
							{
								flag1 = 0;
								break;
							}
						}
						if(flag1 == 0)
						{
							break;
						}
					}
				}	
			}
		}else if(i % 3 == 1)
		{
			al_draw_filled_rounded_rectangle(1620 ,40 ,1900 ,190 ,10, 10,red );
			al_draw_text(font,black,1650 ,50 ,0, "Player Turn :");
	    	al_draw_text(font,black,1700 ,120 ,0,"Red");
	    	al_flip_display();
			while(1)
			{
				ALLEGRO_EVENT ev;
				al_wait_for_event(event_queue1, &ev);
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					if(ev.mouse.button == 1)
					{
						flag = 1;
						flag1 = 1;
						int x_m = ev.mouse.x;
						int y_m = ev.mouse.y;
						o = mokhtasat_arr(mokhtasat, x_m, y_m);
						q1 = o/10;
						q2 = o%10;
						if(q1%2==0)
						   q2++;
						if(!(map[q1][q2]>=1 && map[q1][q2]<=3))
						    continue;
						for(k = 0; k < 8; k++)
						{
							if(k % 2 == 0)
							    h=7;
							else
							    h=8;
							for(l = 0; l < h; l++)
							{
								if(x_m > mokhtasat[k][l].x1 && x_m < mokhtasat[k][l].x2 && y_m > mokhtasat[k][l].y1 && y_m < mokhtasat[k][l].y2)
								{
									al_draw_bitmap(penguins_p2,(mokhtasat[k][l].x1 + mokhtasat[k][l].x2) / 2 - 60, (mokhtasat[k][l].y1 + mokhtasat[k][l].y2) / 2 - 60, 0);
									al_flip_display();
									if(k % 2 == 0)
									{
										emtiaz[1][0] += map[k][l + 1];
										emtiaz[1][1]++;
										map[k][l + 1] = 5;
									}else
									{
										emtiaz[1][0] += map[k][l];
										emtiaz[1][1]++;
										map[k][l] = 5;
									}
									flag = 0;
									break;			
								}
							}
							if(flag == 0)
							{
								flag1 = 0;
								break;
							}
						}
						if(flag1 == 0)
						{
							break;
						}
					}
				}	
			}
		}else if(i % 3 == 2)
		{
			al_draw_filled_rounded_rectangle(1620 ,40 ,1900 ,190 ,10, 10,green );
			al_draw_text(font,black,1650 ,50 ,0, "Player Turn :");
	    	al_draw_text(font,black,1700 ,120 ,0,"Green");
	    	al_flip_display();
			while(1)
			{
				ALLEGRO_EVENT ev;
				al_wait_for_event(event_queue1, &ev);
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					if(ev.mouse.button == 1)
					{
						flag = 1;
						flag1 = 1;
						int x_m = ev.mouse.x;
						int y_m = ev.mouse.y;
						o = mokhtasat_arr(mokhtasat, x_m, y_m);
						q1 = o/10;
						q2 = o%10;
						if(q1%2==0)
						   q2++;
						if(!(map[q1][q2]>=1 && map[q1][q2]<=3))
						    continue;
						for(k = 0; k < 8; k++)
						{
							if(k % 2 == 0)
							    h=7;
							else
							    h=8;
							for(l = 0; l < h; l++)
							{
								if(x_m > mokhtasat[k][l].x1 && x_m < mokhtasat[k][l].x2 && y_m > mokhtasat[k][l].y1 && y_m < mokhtasat[k][l].y2)
								{
									al_draw_bitmap(penguins_p3,(mokhtasat[k][l].x1 + mokhtasat[k][l].x2) / 2 - 60, (mokhtasat[k][l].y1 + mokhtasat[k][l].y2) / 2 - 60, 0);
									al_flip_display();
									if(k % 2 == 0)
									{
										emtiaz[2][0] += map[k][l + 1];
										emtiaz[2][1]++;
										map[k][l + 1] = 6;
									}else
									{
										emtiaz[2][0] += map[k][l];
										emtiaz[2][1]++;
										map[k][l] = 6;
									}
									flag = 0;
									break;			
								}
							}
							if(flag == 0)
							{
								flag1 = 0;
								break;
							}
						}
						if(flag1 == 0)
						{
							break;
						}
					}
				}	
			}
		}
	}
	al_draw_filled_rounded_rectangle(1620, 620, 1900, 770, 10, 10, green);
	al_draw_textf(font, black, 1650, 650, 0, "Fishes: %d", emtiaz[2][0]);
	al_draw_textf(font, black, 1650, 700, 0, "Files: %d", emtiaz[2][1]);
	al_flip_display();
}

//---------------------->agar tedad player ha 4 bashaad
int Four_player(int map[8][8], noghat_mostatil mokhtasat[8][8], mokhtasat_map map_m[8][8], int emtiaz[4][2])
{
  
    /*bitmap define*/
    ALLEGRO_BITMAP *penguins_p4 = al_load_bitmap("penguins_p4.png");
    ALLEGRO_BITMAP *penguins_p3 = al_load_bitmap("penguins_p3.png");
  	ALLEGRO_BITMAP *penguins_p2 = al_load_bitmap("penguins_p2.png");
  	ALLEGRO_BITMAP *penguins_p1 = al_load_bitmap("penguins_p1.png");
  	ALLEGRO_FONT *font1 = al_load_ttf_font("arial.ttf", 45, 0);
  	ALLEGRO_FONT *font= al_load_ttf_font("arial.ttf", 35, 0);
  	ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue(); 
  	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
  	ALLEGRO_COLOR white = al_map_rgb(225, 255, 255);
 	ALLEGRO_COLOR red = al_map_rgb(233, 48, 48);
	ALLEGRO_COLOR green = al_map_rgb(59, 255, 53);
  	ALLEGRO_COLOR yellow = al_map_rgb(248,255,4);
  	al_register_event_source(event_queue1, al_get_mouse_event_source());
  
  	int i, j, k, l, flag, flag1, h, q1, q2, o;
  
  	al_clear_to_color(black);
  	Draw_map(map ,map_m);
  	al_draw_filled_rounded_rectangle(1620, 260, 1900, 410, 10, 10, white);
  	al_draw_filled_rounded_rectangle(1620, 440, 1900, 590, 10, 10, red);
  	al_draw_filled_rounded_rectangle(1620, 620, 1900, 770, 10, 10, green);
  	al_draw_filled_rounded_rectangle(1620, 800, 1900, 950, 10, 10, yellow);\
  	al_draw_text(font1, black, 1670, 200, 0, "Scores :");
  	al_flip_display();
  	for(i = 0; i < 8; i++)
  	{	  
  		al_draw_filled_rounded_rectangle(1620, 260, 1900, 410, 10, 10, white);
		al_draw_textf(font, black, 1650, 290, 0, "Fishes: %d", emtiaz[0][0]);
		al_draw_textf(font, black, 1650, 340, 0, "Tiles: %d", emtiaz[0][1]);
		al_draw_filled_rounded_rectangle(1620, 440, 1900, 590, 10, 10, red);
		al_draw_textf(font, black, 1650, 470, 0, "Fishes: %d", emtiaz[1][0]);
		al_draw_textf(font, black, 1650, 520, 0, "Tiles: %d", emtiaz[1][1]);
		al_draw_filled_rounded_rectangle(1620, 620, 1900, 770, 10, 10, green);
		al_draw_textf(font, black, 1650, 650, 0, "Fishes: %d", emtiaz[2][0]);
		al_draw_textf(font, black, 1650, 700, 0, "Tiles: %d", emtiaz[2][1]);
		al_draw_filled_rounded_rectangle(1620, 800, 1900, 950, 10, 10, yellow);
		al_draw_textf(font, black, 1650, 830, 0, "Fishes: %d", emtiaz[3][0]);
		al_draw_textf(font, black, 1650, 880, 0, "Tiles: %d", emtiaz[3][1]);
		al_flip_display();
    	if(i % 4 == 0)
    	{
    		al_draw_filled_rounded_rectangle(1620 ,40 ,1900 ,190 ,10, 10,white );
    		al_draw_text(font,black,1650 ,50 ,0, "Player Turn :");
	    	al_draw_text(font,black,1700 ,120 ,0, "White");
		    al_flip_display();
    	  	while(1)
    	  	{
        		ALLEGRO_EVENT ev;
        		al_wait_for_event(event_queue1, &ev);
        		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        		{  
          			if(ev.mouse.button == 1)
          			{
            			flag = 1;
            			flag1 = 1;
            			int x_m = ev.mouse.x;
            			int y_m = ev.mouse.y; 
            			o = mokhtasat_arr(mokhtasat, x_m, y_m);
						q1 = o/10;
						q2 = o%10;
						if(q1%2==0)
							q2++;
						if(!(map[q1][q2]>=1 && map[q1][q2]<=3))
							continue;
            			for(k = 0; k < 8; k++)
            			{
              				if(k % 2 == 0)
                				h = 7;
              				else
               					h = 8;
              				for(l = 0; l < h; l++)
              				{
               					if(x_m > mokhtasat[k][l].x1 && x_m < mokhtasat[k][l].x2 && y_m > mokhtasat[k][l].y1 && y_m < mokhtasat[k][l].y2)
                				{
                  					al_draw_bitmap(penguins_p1,(mokhtasat[k][l].x1 + mokhtasat[k][l].x2) / 2 - 60, (mokhtasat[k][l].y1 + mokhtasat[k][l].y2) / 2 - 60, 0);
                  					al_flip_display();
                  					if(k % 2 == 0)
                  					{
                    					emtiaz[0][0] += map[k][l + 1];
                    					emtiaz[0][1]++;
                    					map[k][l + 1] = 4;  
                  					}else
                  					{
                    					emtiaz[0][0] += map[k][l];
                    					emtiaz[0][1]++;
                    					map[k][l] = 4;
                  					}
                  					flag = 0;
                  					break;      
                				}
              				}
              				if(flag == 0)
              				{
                				flag1 = 0;
                				break;
              				}
            			}
            			if(flag1 == 0)
            			{
            	  			break;
            			}
          			}
        		}  
      		}
    	}else if(i % 4 == 1)
    	{
    		al_draw_filled_rounded_rectangle(1620 ,40 ,1900 ,190 ,10, 10,red );
    		al_draw_text(font,black,1650 ,50 ,0, "Player Turn :");
	    	al_draw_text(font,black,1700 ,120 ,0,"Red");
	    	al_flip_display();
      		while(1)
      		{
        		ALLEGRO_EVENT ev;
        		al_wait_for_event(event_queue1, &ev);
        		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        		{
        			if(ev.mouse.button == 1)
          			{
            			flag = 1;
            			flag1 = 1;
            			int x_m = ev.mouse.x;
            			int y_m = ev.mouse.y;
            			o = mokhtasat_arr(mokhtasat, x_m, y_m);
						q1 = o/10;
						q2 = o%10;
						if(q1%2==0)
							q2++;
						if(!(map[q1][q2]>=1 && map[q1][q2]<=3))
							continue;     
		       	    	for(k = 0; k < 8; k++)
        			    {
              				if(k % 2 == 0)
               	 			h = 7;
            			  	else
               	 			h = 8;
              				for(l = 0; l < h; l++)
              				{
                				if(x_m > mokhtasat[k][l].x1 && x_m < mokhtasat[k][l].x2 && y_m > mokhtasat[k][l].y1 && y_m < mokhtasat[k][l].y2)
                				{
                 					al_draw_bitmap(penguins_p2,(mokhtasat[k][l].x1 + mokhtasat[k][l].x2) / 2 - 60, (mokhtasat[k][l].y1 + mokhtasat[k][l].y2) / 2 - 60, 0);
                  					al_flip_display();
                  					if(k % 2 == 0)
                  					{
                    					emtiaz[1][0] += map[k][l + 1];
                    					emtiaz[1][1]++;
                    					map[k][l + 1] = 5;
                  					}else
                  					{
                    					emtiaz[1][0] += map[k][l];
                    					emtiaz[1][1]++;
                    					map[k][l] = 5; 
                			  		}
                  					flag = 0;
                  					break;      
                				}
              				}
              				if(flag == 0)
              				{
                				flag1 = 0;
                				break;
              				}
            			}
            			if(flag1 == 0)
            			{
              				break;
            			}
          			}
        		}  
      		}
    	}else if(i % 4 == 2)
    	{
    		al_draw_filled_rounded_rectangle(1620 ,40 ,1900 ,190 ,10, 10,green );
    		al_draw_text(font,black,1650 ,50 ,0, "Player Turn :");
	    	al_draw_text(font,black,1700 ,120 ,0,"Green");
	    	al_flip_display();
      		while(1)
      		{
        		ALLEGRO_EVENT ev;
        		al_wait_for_event(event_queue1, &ev);
        		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        		{
          			if(ev.mouse.button == 1)
          			{
            			flag = 1;
            			flag1 = 1;
            			int x_m = ev.mouse.x;
            			int y_m = ev.mouse.y;
        			    o = mokhtasat_arr(mokhtasat, x_m, y_m);
						q1 = o/10;
						q2 = o%10;
						if(q1%2==0)
							q2++;
						if(!(map[q1][q2]>=1 && map[q1][q2]<=3))
							continue;
            			for(k = 0; k < 8; k++)
            			{
            				if(k % 2 == 0)
                				h = 7;
              				else
                				h = 8;
              				for(l = 0; l < h; l++)
              				{
               	 				if(x_m > mokhtasat[k][l].x1 && x_m < mokhtasat[k][l].x2 && y_m > mokhtasat[k][l].y1 && y_m < mokhtasat[k][l].y2)
                				{
                  					al_draw_bitmap(penguins_p3,(mokhtasat[k][l].x1 + mokhtasat[k][l].x2) / 2 - 60, (mokhtasat[k][l].y1 + mokhtasat[k][l].y2) / 2 - 60, 0);
                  					al_flip_display();
                  					if(k % 2 == 0)
                  					{
                    					emtiaz[2][0] += map[k][l + 1];
                    					emtiaz[2][1]++;
                    					map[k][l + 1] = 6;
                  					}else
                  					{
                    					emtiaz[2][0] += map[k][l];
                    					emtiaz[2][1]++;
                    					map[k][l] = 6;
                  					}
                  					flag = 0;
                  					break;      
                				}
              				}
              				if(flag == 0)
              				{
                				flag1 = 0;
                				break;
             	 			}
            			}
            			if(flag1 == 0)
            			{
              				break;
            			}
          			}
        		}  
      		}
    	}else if(i % 4 == 3)
    	{
    		al_draw_filled_rounded_rectangle(1620 ,40 ,1900 ,190 ,10, 10,yellow );
    		al_draw_text(font,black,1650 ,50 ,0, "Player Turn :");
	    	al_draw_text(font,black,1700 ,120 ,0,"Yellow");
	    	al_flip_display();
      		while(1)
      		{
        		ALLEGRO_EVENT ev;
        		al_wait_for_event(event_queue1, &ev);
        		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        		{
         	 		if(ev.mouse.button == 1)
          			{
            			flag = 1;
            			flag1 = 1;
            			int x_m = ev.mouse.x;
            			int y_m = ev.mouse.y;
            			o = mokhtasat_arr(mokhtasat, x_m, y_m);
						q1 = o/10;
						q2 = o%10;
						if(q1%2==0)
							q2++;
						if(!(map[q1][q2]>=1 && map[q1][q2]<=3))
							continue;
            			for(k = 0; k < 8; k++)
            			{
              				if(k % 2 == 0)
            				    h = 7;
            				else
            				    h = 8;
            			  	for(l = 0; l < h; l++)
              				{
                				if(x_m > mokhtasat[k][l].x1 && x_m < mokhtasat[k][l].x2 && y_m > mokhtasat[k][l].y1 && y_m < mokhtasat[k][l].y2)
                				{
                			  		al_draw_bitmap(penguins_p4,(mokhtasat[k][l].x1 + mokhtasat[k][l].x2) / 2 - 60, (mokhtasat[k][l].y1 + mokhtasat[k][l].y2) / 2 - 60, 0);
                  					al_flip_display();
                  					if(k % 2 == 0)
                  					{
                    					emtiaz[3][0] += map[k][l + 1];
                    					emtiaz[3][1]++;
                    					map[k][l + 1] = 7;
                  					}else
                  					{
                					    emtiaz[3][0] += map[k][l];
            				    	    emtiaz[3][1]++;
                    					map[k][l] = 7;  
                  					}
                  					flag = 0;
                  					break;      
                				}
              				}
              				if(flag == 0)
              				{
                				flag1 = 0;
                				break;
              				}
            			}
            			if(flag1 == 0)
            			{
              				break;
            			}
          			}
        		}  
      		}
    	}
  	}
  	al_draw_filled_rounded_rectangle(1620, 800, 1900, 950, 10, 10, yellow);
	al_draw_textf(font, black, 1650, 830, 0, "Fishes: %d", emtiaz[3][0]);
	al_draw_textf(font, black, 1650, 880, 0, "Tiles: %d", emtiaz[3][1]);
	al_flip_display();
}

//----------------------->taeen mokhtasat rouse mostatil ha
void mokhtasat_mostatil(noghat_mostatil mokhtasat[8][8])
{
	int i, j;
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			if(i % 2 == 0)
			{
				mokhtasat[i][j].x1 = j * 200 + 100; 	
				mokhtasat[i][j].y1 = i * 113 + 90;
				mokhtasat[i][j].x2 = mokhtasat[i][j].x1 + 200;
				mokhtasat[i][j].y2 = mokhtasat[i][j].y1 + 75;
			}else
			{
				mokhtasat[i][j].x1 = j * 200; 	
				mokhtasat[i][j].y1 = i * 113 + 90;
				mokhtasat[i][j].x2 = mokhtasat[i][j].x1 + 200;
				mokhtasat[i][j].y2 = mokhtasat[i][j].y1 + 75;
			}	
		}
	}
}

//------------------------>tabdil mokhtasat be shomare khane araye
int mokhtasat_arr(noghat_mostatil mokhtasat[8][8], int x_m, int y_m)
{
	int g, z, h;
	for(g = 0; g < 8; g++)
	{
		if(g % 2 == 0)
			h = 7;
		else
	        h = 8;
		for(z = 0; z < h; z++)
		{
			if(x_m > mokhtasat[g][z].x1 && x_m < mokhtasat[g][z].x2 && y_m > mokhtasat[g][z].y1 && y_m < mokhtasat[g][z].y2)
				return (g * 10 + z);
		}
	}
}

//----------------------->tabdil shomare khane arraye be mokhtasat markaz mostatil
long int arr_mokhtasat(int i, int j)
{
	int x, y;
	if(i % 2 == 0)
	    x = 200 * (j);
	else
	    x = 100 * (2 * j + 1);
	y = 113 * i + 127;
	return (x * 1000 + y);
}

//--------------------------->agar bazikoni hame pangoan hash ghofl bashand nobatsh ra rad mikonad.
int hazf(int p, int map[8][8])
{
	int i, j, hazf = 1;
	for(i = 0; i < 8; i++)
	{
	    for(j = 0; j < 8; j++)
		{
	    	if(map[i][j] == p + 4)
			{
	    	    hazf = 0;
				break;	
			}
		}
		if(hazf == 0)
		   break;
	}
	if(hazf == 1)
	    return 1;
	else
	    return 0;
}

//------------------------------>pangoani ke ghofl shode ra pak mikonad(aksash baghi mimanad).
int ghofl(int i, int j, int map[8][8])
{
	int ghofl = 0;
	if(!(map[i][j - 1] > 0 && map[i][j - 1] < 4) || j == 0)
	   ghofl++;
	if(!(map[i][j + 1] > 0 && map[i][j + 1] < 4) || j == 7)
	    ghofl++;
	    
	    
	if(i % 2 == 0)
	{
		if(!(map[i - 1][j - 1] > 0 && map[i - 1][j - 1] < 4) || i == 0 || j == 0)
	        ghofl++;
	    if(!(map[i - 1][j] > 0 && map[i - 1][j] < 4) || i == 0)
	        ghofl++;
	    if(!(map[i + 1][j - 1] > 0 && map[i + 1][j - 1] < 4) || i == 7 || j == 0)
	        ghofl++;
	    if(!(map[i + 1][j] > 0 && map[i + 1][j] < 4) || i == 7)
	        ghofl++;
	}
	
	
	if(i % 2 == 1)
	{
		if(!(map[i - 1][j] > 0 && map[i - 1][j] < 4) || i == 0)
	        ghofl++;
	    if(!(map[i - 1][j + 1] > 0 && map[i - 1][j + 1] < 4) || i == 0 || j == 7)
	        ghofl++;
	    if(!(map[i + 1][j] > 0 && map[i + 1][j] < 4) || i == 7)
	        ghofl++;
	    if(!(map[i + 1][j + 1] > 0 && map[i + 1][j + 1] < 4) || i == 7 || j == 7)
	        ghofl++;
	}
	return ghofl;
}

//------------------------------>mojaz bodane harekate pangoan ra barrasi mikonad.
int mojaz(int i, int j, int x, int y, int map[8][8])
{
	int error = 0;
//+++++++++++++++++ 	
	if((j == y && x + 1 == i) || (j == y && x - 1 == i))
		error = 0;	
//++++++++++++++++++
	if(j == y && abs(x - i) != 1)
		error = 1;
//++++++++++++++++++
	if(x == i && j > y)
	{
		while(j != y)
		{
			j--;
			if(!(map[x][j] < 4 && map[x][j] > 0))
			{
			   	error = 1;
			   	break;
			}
		}
	}	
//++++++++++++++++++
	if(x == i && j < y)
	{
		while(j != y){
			j++;
			if(!(map[x][j] < 4 && map[x][j] > 0))
			{
			   	error = 1;
			   	break;
			}
		}
	}
//++++++++++++++++++
    if(y > j && x < i)
	{	
	    while(i != x)
		{	
			if(i % 2 == 1)
			    j++;	
			i--;
			if(!(map[i][j] < 4 && map[i][j] > 0))
			{
			   	error = 1;
			   	break;
			}
			if((x == i) && (j != y))
			{
			    error = 1;
			   	break;	
			}
		}
    }
//++++++++++++++++++
    if(y < j && x > i)
	{
		while(i != x)
		{
		    if(i % 2 == 0)
		        j--;	
			i++;
			if(!(map[i][j] < 4 && map[i][j] > 0))
			{
			   	error = 1;
			   	break;
			}
			if((x == i) && (j != y))
			{
			   	error = 1;
			   	break;	
			}
		}
	}
//+++++++++++++++++
    if(j > y && i > x)
	{
		while(i != x)
		{
			if(i % 2 == 0)
				j--;
			i--;
			if(!(map[i][j] < 4 && map[i][j] > 0))
			{
			   	error = 1;
			   	break;
			}
			if(x == i && j != y)
			{
			   	error = 1;
			   	break;	
			}
		}
	}
//+++++++++++++++++	    
	if(j < y && i < x)
	{
		while(i != x)
		{
			if(i % 2 == 1)
				j++;
			i++;
			if(!(map[i][j] < 4 && map[i][j] > 0))
			{
			   	error = 1;
			   	break;
			}
			if(x == i && j != y)
			{
			   	error = 1;
			   	break;	
			}
			
		}
	}
//++++++++++++++++++
	if(error == 1)
		return 0;
	else
		return 1;
}
//******************************************************************************************************************
int main ()
{
	//initialization
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_ttf_addon();
	al_init_font_addon();
	al_install_audio(); 
	al_install_mouse();
	al_init_acodec_addon();
	
	//color define
	ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
	ALLEGRO_COLOR white = al_map_rgb(225, 255, 255);
	ALLEGRO_COLOR red = al_map_rgb(233, 48, 48);
	ALLEGRO_COLOR green = al_map_rgb(59, 255, 53);
	ALLEGRO_COLOR yellow = al_map_rgb(248,255,4);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR background_color = al_map_rgb(68, 167, 196);
	
	//display define
	ALLEGRO_DISPLAY *display = al_create_display(1920, 1000);
	
	//font define
	ALLEGRO_FONT *font= al_load_ttf_font("arial.ttf", 35, 0);
	ALLEGRO_FONT *font1 = al_load_ttf_font("GOT.ttf", 60, 0);
	ALLEGRO_BITMAP *empty = al_load_bitmap("empty.png");
	ALLEGRO_BITMAP *penguins_p4 = al_load_bitmap("penguins_p4.png");
	ALLEGRO_BITMAP *penguins_p3 = al_load_bitmap("penguins_p3.png");
	ALLEGRO_BITMAP *penguins_p2 = al_load_bitmap("penguins_p2.png");
	ALLEGRO_BITMAP *penguins_p1 = al_load_bitmap("penguins_p1.png");
	
	//sample define
	ALLEGRO_SAMPLE *song;
	ALLEGRO_SAMPLE_INSTANCE *songinstance;
		
	al_reserve_samples(1);
	
	song = al_load_sample("9-tickgraphic-cute (online-audio-converter.com).ogg");
	songinstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songinstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songinstance, al_get_default_mixer());
	al_play_sample_instance(songinstance);
	
	//declare variables
	noghat_mostatil mokhtasat[8][8];
	int map[8][8];
	mokhtasat_map map_m[8][8];
	int n, i, j, end = 0, x, y, p = 0, max = -1, winner = 0, t, r, e, x_c, y_c, x_m, y_m, adad;
	long int centre;
	
	//call functions
	Preview(); 					  /* namayesh safhe entekhab tedad player*/
	meghdar_dehi_map(map);        /*taeen tedad mahi haye har khane*/
	mokhtasat_mostatil(mokhtasat);/*mokhtasat 2 ras mostatil*/
	n = choose_number_of_player();/* n = tedad player*/
	int emtiaz[n][2];
	for(i = 0; i < n; i++)
		for(j = 0; j < 2; j++)
			emtiaz[i][j] = 0;
	
	if(n == 2)
	{
		end=8;
		Two_player(map, mokhtasat, map_m, emtiaz);
	}
	else if(n == 3)
	{
		end=9;
		Three_player(map, mokhtasat, map_m, emtiaz);
	}else if(n == 4)
	{
		end=8;
		Four_player(map, mokhtasat, map_m, emtiaz);
	}
	
//------------------------------------------------>halghe asli bazi
	while(end != 0)
	{	 
	
	    //--->pangoane gir oftade ra hazf mikonad.   
        for(t = 0; t < n; t++)
		{
    	    for(i = 0; i < 8 ; i++)
			{
    		    for(j = 0; j < 8; j++)
				{
    		        if(map[i][j] == t + 4)
					{
    		    	    if(ghofl(i, j, map) == 6)
						{
		                    end--;
		                    map[i][j] = 0;
		                    centre = arr_mokhtasat(i, j);
		    				x_c = centre / 1000;
		   	 				y_c = centre % 1000;
    	                }	
				    }
    	        }
		    }
	    }  
	    
	    //----->tabe hazf bazikon
	    if(hazf(p, map) == 1)
	    {
		    p++;
		    if(p == n)
		        p = 0;
		    continue;
	    }
	    
		//----->neshan dadane nobat bazikon
	    if(p == 0)
		{
	    	al_draw_filled_rounded_rectangle(1620, 40, 1900, 190, 10, 10, white);
	    	al_draw_text(font, black, 1650, 50, 0, "Player Turn :");
	    	al_draw_text(font ,black ,1700, 120, 0, "White");
	    	al_flip_display();
		}
		
		if(p == 1)
		{
	    	al_draw_filled_rounded_rectangle(1620, 40, 1900, 190, 10, 10, red);
	    	al_draw_text(font, black, 1650, 50, 0, "Player Turn :");
	    	al_draw_text(font, black, 1700, 120, 0,"Red");
	    	al_flip_display();
		}
		
		if(p == 2)
		{
	   		al_draw_filled_rounded_rectangle(1620, 40, 1900, 190, 10, 10, green);
	   		al_draw_text(font, black, 1650, 50, 0, "Player Turn :");
	    	al_draw_text(font, black, 1700, 120, 0, "Green");
	    	al_flip_display();
		}
		
		if(p == 3)
		{
	    	al_draw_filled_rounded_rectangle(1620, 40, 1900, 190, 10, 10, yellow);
	    	al_draw_text(font, black, 1650, 50, 0, "Player Turn :");
			al_draw_text(font, black, 1700, 120, 0, "Yellow");
	    	al_flip_display();
		}
	    
		//------>daryaft address pangoan dar <i> & <j> 
	    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	    al_register_event_source(event_queue, al_get_mouse_event_source());
	    
	    while(1) 
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if(ev.mouse.button == 1)
				{
					x_m = ev.mouse.x;
    				y_m = ev.mouse.y;
					break;
				}
			}
		}
		adad = mokhtasat_arr(mokhtasat, x_m, y_m);
		j = adad % 10;
		i = adad / 10;
		if(i % 2 == 0)
			j++;
			
		//--->har bazikon pangoan khod ra mitavanad harekat bedahad.
		if(map[i][j] != p + 4)
		{
		    printf("\a");
		    al_draw_text(font, black, 670 ,10 , 0, "Please select your penguine.");
	    	al_flip_display();
	    	al_rest(2);
	    	al_draw_filled_rectangle(0, 0, 1620, 50, background_color);
		    continue;
	    }
	    
		//namayesh noghte ghermez roy pangoane entekhab shode 
	    int f1, f2, flage = 1, k, l;
	    for(k = 0; k < 8; k++)
	    {
	    	for(l = 0; l < 8; l++)
	    	{
	    		if(x_m > mokhtasat[k][l].x1 && x_m < mokhtasat[k][l].x2 && y_m > mokhtasat[k][l].y1 && y_m < mokhtasat[k][l].y2)
	    		{
	    			f1 = (mokhtasat[k][l].x1 + mokhtasat[k][l].x2) / 2;
	    			f2  = (mokhtasat[k][l].y1 + mokhtasat[k][l].y2) / 2;
	    			flage = 0;
	    			break;
				}
			}
			if(flage == 0)
				break;
		}
		al_draw_filled_circle(f1, f2 - 50, 5, red);
	    al_flip_display();
	    
	    //daryafte address mahi dar <x> & <y>
		while(1) 
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if(ev.mouse.button == 1)
				{
					x_m = ev.mouse.x;
    				y_m = ev.mouse.y;
    				break;
				}
			}
		}
		adad = mokhtasat_arr(mokhtasat, x_m, y_m);
		y = adad % 10;
		x = adad / 10;
		if(x % 2 == 0)
			y++;
	    
		//--->khane maghsad bayad daraye mahi bashad.
	    if(!(map[x][y] > 0 && map[x][y] < 4) || (x > 7) || (y > 7))
		{
	    	al_draw_filled_circle(f1, f2 - 50, 5, al_map_rgb(32, 189 ,190));
	    	printf("\a");
		    al_draw_text(font, black, 670 ,10 , 0, "Not allowed here");
	    	al_flip_display();
	    	al_rest(2);
	    	al_draw_filled_rectangle(0, 0, 1620, 50, background_color);
		    continue;
	    }
	      
	    //--->barresi mojaz bodane harekate pangoan	
	   if(mojaz(i, j, x, y, map) == 1)
	   {
		    emtiaz[p][0] += map[x][y];
		    emtiaz[p][1]++;
		    if(p == 0)
		    {
		    	al_draw_filled_rounded_rectangle(1620, 260, 1900, 410, 10, 10, white);
		    	al_draw_textf(font, black, 1650, 290, 0, "Fishes: %d", emtiaz[p][0]);
		    	al_draw_textf(font, black, 1650, 340, 0, "Tiles: %d", emtiaz[p][1]);
			}
			if(p == 1)
			{
				al_draw_filled_rounded_rectangle(1620, 440, 1900, 590, 10, 10, red);
				al_draw_textf(font, black, 1650, 470, 0, "Fishes: %d", emtiaz[p][0]);
		    	al_draw_textf(font, black, 1650, 520, 0, "Tiles: %d", emtiaz[p][1]);
			}
			if(p == 2)
			{
				al_draw_filled_rounded_rectangle(1620, 620, 1900, 770, 10, 10, green);
				al_draw_textf(font, black, 1650, 650, 0, "Fishes: %d", emtiaz[p][0]);
		    	al_draw_textf(font, black, 1650, 700, 0, "Tiles: %d", emtiaz[p][1]);
			}
			if(p == 3)
			{
				al_draw_filled_rounded_rectangle(1620, 800, 1900, 950, 10, 10, yellow);
				al_draw_textf(font, black, 1650, 830, 0, "Fishes: %d", emtiaz[p][0]);
		    	al_draw_textf(font, black, 1650, 880, 0, "Tiles: %d", emtiaz[p][1]);
			}
		    map[x][y] = map[i][j];
		    map[i][j] = 0;
		    centre = arr_mokhtasat(i, j);
		    x_c = centre / 1000;
		    y_c = centre % 1000;
		    al_draw_bitmap(empty, x_c - 100, y_c - 75, 0);
			al_flip_display();
			if(p == 0)
			{
				centre = arr_mokhtasat(x, y);
				x_c = centre / 1000 ;
		    	y_c = centre % 1000;
				al_draw_bitmap(penguins_p1, x_c - 60, y_c  - 60, 0);
				al_flip_display();
			}
			if(p == 1)
			{
				centre = arr_mokhtasat(x, y);
				x_c = centre / 1000 ;
		    	y_c = centre % 1000;
				al_draw_bitmap(penguins_p2, x_c - 60, y_c  - 60, 0);
				al_flip_display();
			}
			if(p == 2)
			{
				centre = arr_mokhtasat(x, y);
				x_c = centre / 1000 ;
		    	y_c = centre % 1000;
				al_draw_bitmap(penguins_p3, x_c - 60, y_c  - 60, 0);
				al_flip_display();
			}
			if(p == 3)
			{
				centre = arr_mokhtasat(x, y);
				x_c = centre / 1000;
		    	y_c = centre % 1000;
				al_draw_bitmap(penguins_p4, x_c - 60, y_c  - 60, 0);
				al_flip_display();
			}
	    }
	   else
	   {
	    	al_draw_filled_circle(f1, f2 - 50, 5, al_map_rgb(32, 189 ,190));
	    	printf("\a");
	    	al_draw_text(font, black, 600 ,10 , 0, "Please select another cell.");
	    	al_flip_display();
	    	al_rest(2);
	    	al_draw_filled_rectangle(0, 0, 1620, 50, background_color);
		    continue;
	    }
	    
	    //--->avaz kardane nobate bazikon.                
	    p++;
	    if(p == n)
	        p=0;
	}/*akhar halghe asli bazi*/
   
   //taeen barande bazi.
    for(i = 0; i < n; i++)
	{
    	if(emtiaz[i][0] == max)
		{
    	    if(emtiaz[i][1] > emtiaz[t][1])
			    winner = i + 1;
			if(emtiaz[i][1] == emtiaz[t][1])
			    winner = 0;
	    }
        if(emtiaz[i][0] > max)
		{
       	    max = emtiaz[i][0];
       	    winner = i + 1;
       	    t = i;
	    }	
	}
	
	if(winner == 0)
	{
		al_clear_to_color(blue);
		al_draw_text(font1, black, 680, 400, 0, "Tie");
	   	al_flip_display();	
	}
	if(winner == 1)
	{
		al_clear_to_color(white);
	   	al_draw_text(font1, black, 480, 400, 0, "Player White Is Winner");
	   	al_flip_display();	
	}
	if(winner == 2)
	{
		al_clear_to_color(red);
	   	al_draw_text(font1, black, 490, 400, 0, "Player Red Is Winner");
	   	al_flip_display();
	}
	if(winner == 3)
	{
		al_clear_to_color(green);
	   	al_draw_text(font1, black, 480, 400, 0, "Player green Is Winner");
	   	al_flip_display();
	}
	if(winner == 4)
	{
		al_clear_to_color(yellow);
	   	al_draw_text(font1, black, 480, 400, 0, "player yellow Is Winner");
	   	al_flip_display();
	}
	al_rest(5);
    
	al_destroy_display(display);
	al_destroy_font(font);
	al_destroy_font(font1);
	al_uninstall_mouse();
	
	return 0;
}