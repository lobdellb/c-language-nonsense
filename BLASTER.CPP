// by: Frank Rossa
// BLASTER.CPP

#include <iostream.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>

struct ship {
	int x,y;
};

ship player;
ship target;

int numhit=0;

int star_x[400], star_y[400];

unsigned long int round;

int colisions(void)
{
	if( (target.x+12 > player.x - 19) && (target.x+12 < player.x+19) ) {
		if( (target.y+12>player.y-16) && (target.y-12<player.y+16) ) {
			return(1);
		}
	}

	else if( (target.x-12 > player.x - 19) && (target.x-12 < player.x+19) ) {
		if( (target.y+12>player.y-16) && (target.y-12<player.y+16)) {
			return(1);
		}
	}

	return(0);
}

void draw_target(void)
{
	int count;

	for(count = 12; count > 0; count--) {
		setcolor(rand() % 15);
		circle(target.x, target.y, count);
	}

	return;
}

void erase_target(void)
{
	int count;

	setcolor(BLACK);
	for(count = 12; count > 0; count--) {
		circle(target.x, target.y, count);
	}

	return;
}

void move_target(void)
{
	int neg=1;

	if(rand() % 2 == 1)
		neg = -1;

	target.y += rand() % 30;
	target.x -= neg * rand() % 30;

	if(target.y>getmaxy())
		target.y = 0;

	if( (target.x >= getmaxx()) | (target.x <= 0) ) {
		target.y = 0;
		target.x = rand() % getmaxx();
	}

	return;
}

void calculate_stars(void)
{
	int count;

	for(count = 0; count < 400; count++) {
		star_x[count] = rand() % getmaxx();
		star_y[count] = rand() % getmaxy();
	}

	return;
}

void draw_stars(void)
{
	int count;

	for(count =0; count < 400; count++) {
		setcolor(rand() % getmaxcolor());

		line(star_x[count],star_y[count],star_x[count],star_y[count]);
	}

	return;
}


void dead(void)
{
	int count;

	for(count = 1; count <= 80; count++) {
		draw_stars();
		if(count % 2 == 0)
			setcolor(RED);
		else
			setcolor(YELLOW);

		circle(player.x, player.y, count);
		delay(20);
	}

	for(count = 80; count > 0; count--) {
		draw_stars();
		setcolor(BLACK);
		circle(player.x, player.y, count);
		delay(20);
	}

}


void draw_ship(void)
{
	int count;

	setcolor(LIGHTGRAY);
	for(count = 15; count >= 0; count--) {
		if(count == 4)
			setcolor(BLUE);
		circle(player.x,player.y,count);
	}

	line(player.x-3,player.y-16,player.x-3,player.y-19);
	line(player.x+3,player.y-16,player.x+3,player.y-19);

	for(count = 0; count <= 4; count++) {
		line(player.x+16+count,player.y-4,player.x+16+count,player.y+12);
		line(player.x-16-count,player.y-4,player.x-16-count,player.y+12);
	}

	return;
}

void erase_ship(void)
{
	int count;

	setcolor(BLACK);
	for(count = 15; count >= 0; count--) {
		circle(player.x,player.y,count);
	}

	line(player.x-3,player.y-16,player.x-3,player.y-19);
	line(player.x+3,player.y-16,player.x+3,player.y-19);

	for(count = 0; count <= 4; count++) {
		line(player.x+16+count,player.y-4,player.x+16+count,player.y+12);
		line(player.x-16-count,player.y-4,player.x-16-count,player.y+12);
	}

	return;
}

void draw_lazers(void)
{
	setcolor(RED);
	line(player.x+3,player.y-20,player.x+3,0);
	line(player.x-3,player.y-20,player.x-3,0);

	return;
}

void erase_lazers(void)
{
	setcolor(BLACK);
	line(player.x+3,player.y-20,player.x+3,0);
	line(player.x-3,player.y-20,player.x-3,0);

	return;
}


void control(int key)
{

	switch(key) {

	case 32:
		draw_lazers();
		delay(80);
		erase_lazers();
		break;

	case 72:
		if(player.y > 20) {
			erase_ship();
			player.y -= 20;
		}
		break;

	case 80:
		if(player.y<getmaxy()-20) {
			erase_ship();
			player.y += 20;
		}
		break;

	case 75:
		if(player.x > 20) {
			erase_ship();
			player.x -= 20;
		}
		break;

	case 77:
		if(player.x < getmaxx() -20) {
			erase_ship();
			player.x += 20;
		}
		break;
	}

	return;
}

void kill(void)
{
	int count;

	setcolor(YELLOW);
	for(count = 1; count <= 25; count++) {
		draw_stars();
		if(count % 2 == 0)
			setcolor(RED);
		else
			setcolor(YELLOW);

		circle(target.x, target.y, count);
		delay(30);
	}

	for(count = 25; count > 0; count--) {
		draw_stars();
		setcolor(BLACK);
		circle(target.x, target.y, count);
		delay(30);
	}

	target.y = 0;
	target.x = rand() % getmaxx();
	numhit++;

	return;
}

void shot(int key)
{
	if(player.y-22 > target.y) {
		if( (player.x+3 > target.x-12) && (player.x+3 < target.x + 12) ) {
			if(key == 32) {
				kill();
				return;
			}
		}
		else if(  (player.x-3 > target.x-12) && (player.x-3 < target.x + 12) ) {
			if(key == 32) {
				kill();
				return;
			}
		}
	}
	return;
}


void main()
{
	begin:

	int gdrivers = VGA,
		 gmode=VGAHI,
		 key=97;

	char check;

	initgraph( &gdrivers, &gmode, "c:\\tc\\bgi");

	randomize();

	player.x = getmaxx() / 2;
	player.y = getmaxy() * .75;

	target.x = rand() % getmaxx();
	target.y = 0;

	calculate_stars();
	draw_stars();

	draw_ship();
	draw_target();

	round = 0;
	while(key != 27) {
		round++;

		if(kbhit()) {
			key = getch();
			control(key);
			draw_stars();
			draw_ship();
		}

		draw_stars();
		draw_ship();
		shot(key);
		delay(40);
		erase_target();
		move_target();
		draw_target();

		if(colisions() == 1) {
			erase_ship();
			erase_target();
			dead();
			key = 27;
			draw_stars();
			getch();
		}

		if(key != 27)
			key = 0;

	}

	closegraph();

	cout << "\n\n\n\n\n\n\n\n\t\t\t\tYou hit " << numhit << " targets.";
	cout << "\n\t\t    Press Esc to exit or Enter to play again.";
	recheck:
	check = getch();

	if( check == 13 )
		goto begin;
	else if( check == 27)
		clrscr();
	else
		goto recheck;

	return;
}