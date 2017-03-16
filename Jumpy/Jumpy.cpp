// Jumpy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//This is 100% written by me i.e. Ashish Saini
#include<iostream>
#include<stdlib.h>
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"ConsoleFont.h"
#include<fstream>
using namespace std;
//Global variables
struct doodle
{
    int x,y;
}doodle_position,current_platform;

struct data
{
    char name[10];
    int score;
}player1,player2,current;

bool upward=true,downward=false;
char all_data[500],names_extracted[300],initial[20],score_extracted_in_char[300];
int total_data = 0, score_extracted[20], position[2000][80], z = 0, flag = 0, score = 0, l = 0, match_type;

struct for_high_score_players
{
   char name[10];
}p1,p2,p3,p4,p5,p6,p7,p8,p9,p10;

/**
It takes x-y coordinates and position the output handle to that coordinate
*/
void gotoxy(int x, int y)
{
    COORD set;
    set.X=x;
    set.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),set);
}

/**
It uses standard windows console function to set the position and area of console window.
*/
void consol_size_setter(int x_co,int y_co,int width,int height,bool redraw_window)
{
    HWND console = GetConsoleWindow();
    MoveWindow(console, x_co, y_co, width, height, TRUE);

}

/**
It can set the color of console using color's int value.
*/
void color_setter(int n)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),n);
}

/**
This function convert scores char value to int and store it in global score_extracted array
*/
void char_to_int()
{
    int lm=0;
    	for(int i=0;score_extracted_in_char[i]!='\0';i++)
	{
		int lop=0,mn;
		if(score_extracted_in_char[i]=='<')
			{
				for(int k=i+1;score_extracted_in_char[k]!='>';k++)
			{
				initial[lop]=score_extracted_in_char[k];
				lop++;
				initial[lop]='\0';
			}
				mn=strlen(initial);
				if(mn==7)
				{
					score_extracted[lm]=(((initial[0]-'0')*1000000)+((initial[1]-'0')*100000)+((initial[2]-'0')*10000)+((initial[3]-'0')*1000)+((initial[4]-'0')*100)+((initial[5]-'0')*10)+(initial[6]-'0'));
				}
				if(mn==6)
				{
					score_extracted[lm]=(((initial[0]-'0')*100000)+((initial[1]-'0')*10000)+((initial[2]-'0')*1000)+((initial[3]-'0')*100)+((initial[4]-'0')*10)+(initial[5]-'0'));
				}
				if(mn==5)
				{
					score_extracted[lm]=(((initial[0]-'0')*10000)+((initial[1]-'0')*1000)+((initial[2]-'0')*100)+((initial[3]-'0')*10)+((initial[4]-'0')));
				}
				if(mn==4)
				{
					score_extracted[lm]=(((initial[0]-'0')*1000)+((initial[1]-'0')*100)+((initial[2]-'0')*10)+(initial[3]-'0'));
				}
				if(mn==3)
				{
					score_extracted[lm]=(((initial[0]-'0')*100)+((initial[1]-'0')*10)+(initial[2]-'0'));
				}
				if(mn==2)
				{
					score_extracted[lm]=(((initial[0]-'0')*10)+(initial[1]-'0'));
				}
				if(mn==1)
				{
					score_extracted[lm]=(initial[0]-'0');
				}
				lm++;
		}
	}
}
/**
It breakes different names and stores it in global names_extracted array
*/
void names_to_different_variables()
{

    int cnt=1;
    for(int i=0;names_extracted[i]!='\0';i++)
	{
		if(names_extracted[i]=='<')
			{
				for(int k=i+1,m=0;names_extracted[k]!='>';k++,m++)
			{
			    switch(cnt)
			    {
			        case 1:
						p1.name[m]=names_extracted[k];
						p1.name[m+1]='\0';
						break;
			        case 2:
						p2.name[m]=names_extracted[k];
						p2.name[m+1]='\0';
						break;
			        case 3:
						p3.name[m]=names_extracted[k];
						p3.name[m+1]='\0';
						break;
			        case 4:
						p4.name[m]=names_extracted[k];
						p4.name[m+1]='\0';
						break;
			        case 5:
						p5.name[m]=names_extracted[k];
						p5.name[m+1]='\0';
						break;
			        case 6:
						p6.name[m]=names_extracted[k];
						p6.name[m+1]='\0';
						break;
			        case 7:
						p7.name[m]=names_extracted[k];
						p7.name[m+1]='\0';
						break;
			        case 8:
						p8.name[m]=names_extracted[k];
						p8.name[m+1]='\0';
						break;
			        case 9:
						p9.name[m]=names_extracted[k];
						p9.name[m+1]='\0';
						break;
			        case 10:
						p10.name[m]=names_extracted[k];
						p10.name[m+1]='\0';
						break;
			    }
			}cnt++;
			}

	}
}
/**
Starter function to extract data from file
*/
void all_data_extracter()
{
    int counter=0,nc=0,scc=0;
      for(int k=0;all_data[k]!='/';k++)
        {
            if(all_data[k]=='<')
             {
                 counter++;
            if(counter%2==1)
            {

                for(int n=k;all_data[n]!='>';n++)
                {
                    names_extracted[nc]=all_data[n];
                    nc++;
                    names_extracted[nc]='>';

                }nc++;
            }
            else
            {

                for(int n=k;all_data[n]!='>';n++)
                {
                    score_extracted_in_char[scc]=all_data[n];
                    scc++;
                    score_extracted_in_char[scc]='>';

                }scc++;
            }
            }
        }
    names_extracted[nc+1]='\0';score_extracted_in_char[scc+1]='\0';
    char_to_int();
    names_to_different_variables();
}
/**
It saves scores in score.dat file

*/
void high_score_to_file(char player_name[],int score)
{
    int n;
    n=total_data/2;
    fstream score_dat;
    score_dat.open("SCORE.dat",fstream::in|fstream::out|fstream::trunc);
    switch(n)
    {
        case 1:score_dat<<"<"<<player_name<<"><"<<score<<"><"<<p1.name<<"><"<<score_extracted[0]<<">/";break;
        case 2:score_dat<<"<"<<player_name<<"><"<<score<<"><"<<p1.name<<"><"<<score_extracted[0]<<"><"<<p2.name<<"><"<<score_extracted[1]<<">/";break;
        case 3:score_dat<<"<"<<player_name<<"><"<<score<<"><"<<p1.name<<"><"<<score_extracted[0]<<"><"<<p2.name<<"><"<<score_extracted[1]<<"><"<<p3.name<<"><"<<score_extracted[2]<<">/";break;
        case 4:score_dat<<"<"<<player_name<<"><"<<score<<"><"<<p1.name<<"><"<<score_extracted[0]<<"><"<<p2.name<<"><"<<score_extracted[1]<<"><"<<p3.name<<"><"<<score_extracted[2]<<"><"<<p4.name<<"><"<<score_extracted[3]<<">/";break;
        case 5:score_dat<<"<"<<player_name<<"><"<<score<<"><"<<p1.name<<"><"<<score_extracted[0]<<"><"<<p2.name<<"><"<<score_extracted[1]<<"><"<<p3.name<<"><"<<score_extracted[2]<<"><"<<p4.name<<"><"<<score_extracted[3]<<"><"<<p5.name<<"><"<<score_extracted[4]<<">/";break;
        case 6:score_dat<<"<"<<player_name<<"><"<<score<<"><"<<p1.name<<"><"<<score_extracted[0]<<"><"<<p2.name<<"><"<<score_extracted[1]<<"><"<<p3.name<<"><"<<score_extracted[2]<<"><"<<p4.name<<"><"<<score_extracted[3]<<"><"<<p5.name<<"><"<<score_extracted[4]<<"><"<<p6.name<<"><"<<score_extracted[5]<<">/";break;
        case 7:score_dat<<"<"<<player_name<<"><"<<score<<"><"<<p1.name<<"><"<<score_extracted[0]<<"><"<<p2.name<<"><"<<score_extracted[1]<<"><"<<p3.name<<"><"<<score_extracted[2]<<"><"<<p4.name<<"><"<<score_extracted[3]<<"><"<<p5.name<<"><"<<score_extracted[4]<<"><"<<p6.name<<"><"<<score_extracted[5]<<"><"<<p7.name<<"><"<<score_extracted[6]<<">/";break;
        case 8:score_dat<<"<"<<player_name<<"><"<<score<<"><"<<p1.name<<"><"<<score_extracted[0]<<"><"<<p2.name<<"><"<<score_extracted[1]<<"><"<<p3.name<<"><"<<score_extracted[2]<<"><"<<p4.name<<"><"<<score_extracted[3]<<"><"<<p5.name<<"><"<<score_extracted[4]<<"><"<<p6.name<<"><"<<score_extracted[5]<<"><"<<p7.name<<"><"<<score_extracted[6]<<"><"<<p8.name<<"><"<<score_extracted[7]<<">/";break;
        case 9:score_dat<<"<"<<player_name<<"><"<<score<<"><"<<p1.name<<"><"<<score_extracted[0]<<"><"<<p2.name<<"><"<<score_extracted[1]<<"><"<<p3.name<<"><"<<score_extracted[2]<<"><"<<p4.name<<"><"<<score_extracted[3]<<"><"<<p5.name<<"><"<<score_extracted[4]<<"><"<<p6.name<<"><"<<score_extracted[5]<<"><"<<p7.name<<"><"<<score_extracted[6]<<"><"<<p8.name<<"><"<<score_extracted[7]<<"><"<<p9.name<<"><"<<score_extracted[8]<<">/";break;
        case 10:score_dat<<"<"<<player_name<<"><"<<score<<"><"<<p1.name<<"><"<<score_extracted[0]<<"><"<<p2.name<<"><"<<score_extracted[1]<<"><"<<p3.name<<"><"<<score_extracted[2]<<"><"<<p4.name<<"><"<<score_extracted[3]<<"><"<<p5.name<<"><"<<score_extracted[4]<<"><"<<p6.name<<"><"<<score_extracted[5]<<"><"<<p7.name<<"><"<<score_extracted[6]<<"><"<<p8.name<<"><"<<score_extracted[7]<<"><"<<p9.name<<"><"<<score_extracted[8]<<">/";break;
    }
    score_dat.close();
}

/**
Shows high score to console
*/
void high_score_viewer()
{
	consol_size_setter(100,1,380,300,true);
    system("cls");
    gotoxy(9,0);cout<<"HIGHSCORES";
    gotoxy(6,2);cout<<"1. "<<p1.name;gotoxy(17,2);cout<<score_extracted[0];
    gotoxy(6,3);cout<<"2. "<<p2.name;gotoxy(17,3);cout<<score_extracted[1];
    gotoxy(6,4);cout<<"3. "<<p3.name;gotoxy(17,4);cout<<score_extracted[2];
    gotoxy(6,5);cout<<"4. "<<p4.name;gotoxy(17,5);cout<<score_extracted[3];
    gotoxy(6,6);cout<<"5. "<<p5.name;gotoxy(17,6);cout<<score_extracted[4];
    gotoxy(6,7);cout<<"6. "<<p6.name;gotoxy(17,7);cout<<score_extracted[5];
    gotoxy(6,8);cout<<"7. "<<p7.name;gotoxy(17,8);cout<<score_extracted[6];
    gotoxy(6,9);cout<<"8. "<<p8.name;gotoxy(17,9);cout<<score_extracted[7];
    gotoxy(6,10);cout<<"9. "<<p9.name;gotoxy(17,10);cout<<score_extracted[8];
    gotoxy(6,11);cout<<"10. "<<p10.name;gotoxy(17,11);cout<<score_extracted[8];
ups:  gotoxy(0,13);cout<<"Press backspace to continue";_getch();
	if(GetAsyncKeyState(VK_RETURN))
	{
		_getch();
		goto ups;
	}
	if(!GetAsyncKeyState(VK_BACK))
	{
		goto ups;
	}
	system("cls");
}
/**
Starter function to show and check high score
*/
int high_score(char player_name[],int score,bool see)
{
    fstream score_dat;
    score_dat.open("SCORE.dat");
    if(!score_dat.is_open())
    {
        fstream score("SCORE.dat",fstream::in|fstream::out|fstream::app);
        score<<"/";
        score.close();
    }
    score_dat.close();
    score_dat.open("SCORE.dat");
    score_dat>>all_data;
    score_dat.close();
    int i;total_data=0;
    for(i=0;all_data[i]!='/';i++)
        {
            if(all_data[i]=='<')
                total_data++;
        }
        all_data[i+1]='\0';
    if(total_data==0)
    {
        if(see==false)
        {
            score_dat.open("SCORE.dat");
        score_dat<<"<"<<player_name<<">"<<"<"<<score<<">/";
        score_dat.close();
         return 1;
        }
        else
            {
				consol_size_setter(100,1,380,100,true);
				upy:
				system("cls");
				cout<<"No data available to show\n";cout<<"Press backspace to continue";_getch();if(GetAsyncKeyState(VK_RETURN)){_getch();goto upy;}if(!GetAsyncKeyState(VK_BACK)){goto upy;}
				return 0;
		}
    }
    else
    {

        all_data_extracter();
    if((score>score_extracted[0])&&(see==false))
    {
        high_score_to_file(player_name,score);
        return 1;
    }
    if(see==true)
    {
        high_score_viewer();
    }
    }
}

/**
It creates boundary on console for game
*/
void boundary()
{
	consol_size_setter(100,1,1280,740,true);
    color_setter(5);
    for(int q=0;q<80;q++)
    {
        gotoxy(q,0);
        cout<<char(177);
        gotoxy(q,42);
        cout<<char(177);
    }
    for(int q=1;q<43;q++)
    {
        gotoxy(0,q);
        cout<<char(177);
        gotoxy(79,q);
        cout<<char(177);
    }
}
/**
It creates platform where character will jump and save it in position 2D array
*/
void platform_maker()
{
    int y;


cout<<"Loading";
    {
        for(int i=0;i<2000;i=i+4)
    {
        y=rand()%80;
        if(y>73)
            y=73;
            if(y<5)
                y=5;
        {for(int k=y;k<y+6;k++)position[i][k]='%';}
    }
}
system("cls");
}

/**
It prints platform to console
*/
void platform_print()
{

color_setter(10);
        for(int i=z,k=0;i<z+41;i++,k++)
       {
           for(int j=0;j<80;j++)
		   {
			 if(position[i][j]=='%')
			 {

				gotoxy(j,41-k);
				cout<<char(223);
				if(flag==0)
				{
					current_platform.x=j;
					current_platform.y=41-(k+1);
					flag=1;
				}
			 }
		 }
       }
}

/**
It prints score after gameplay
*/
void score_printer()
{
    char ch;
    system("cls");
	sk:
				gotoxy(0,0);cout<<"Press backspace to continue";_getch();if(GetAsyncKeyState(VK_RETURN)){_getch();goto sk;}if(!GetAsyncKeyState(VK_BACK)){goto sk;}
				system("cls");
	system("cls");
	consol_size_setter(100,1,480,200,true);
	gotoxy(0,2);cout<<current.name<<" you have scored: "<<score;
	if(high_score(current.name,score,false)==1)
	{
		_getch();
		system("cls");
		gotoxy(0,3);cout<<"You have made a new high score";_getch();
		(high_score(current.name,score,true));
		consol_size_setter(100,1,480,200,true);
	}
	else if(l==0)
	{sjk:
		gotoxy(0,4);cout<<"Press backspace to continue";_getch();if(GetAsyncKeyState(VK_RETURN)){_getch();goto sjk;}if(!GetAsyncKeyState(VK_BACK)){goto sjk;}
	}
	if(match_type==1)
	{
	int zl=0;
	ml:
	consol_size_setter(100,1,440,200,true);
	system("cls");
    color_setter(2);gotoxy(2,3);cout<<"Do you want to play it again ";
	if(zl==0)color_setter(114);else color_setter(2);gotoxy(12,5);cout<<"Yes";if(zl==1)color_setter(114);else color_setter(2);gotoxy(18,5);cout<<"No";
		color_setter(2);gotoxy(2,7);cout<<"*****************************";
		_getch();
		if(GetAsyncKeyState(VK_RIGHT))
			{
				if(zl==0)
				zl++;
		}

		if(GetAsyncKeyState(VK_LEFT))
		{
			if(zl==1)
				zl--;

		}
		if(GetAsyncKeyState(VK_RETURN))
		{
			if(zl==0)
			{
				flag=0;
				score=0;
				 l=1;
				 z=0;
				 system("cls");
				 return;
			}
			else if(zl==1)
			{
				kplk:
				system("cls");
				 gotoxy(2,2);cout<<"BYE BYE!";
				gotoxy(2,4);cout<<"Press backspace to continue";_getch();if(GetAsyncKeyState(VK_RETURN)){_getch();goto kplk;}if(!GetAsyncKeyState(VK_BACK)){goto kplk;}
				system("cls");
				flag=0;
				score=0;
				 z=0;
				 l=0;
				return;
			}
		}
		else
		{
			goto ml;
			_getch();
		}}
	if((match_type==2)&&(l==1))
	{
		system("cls");
		if(player1.score>player2.score)
		{
			gotoxy(0,2);cout<<player1.name<<" you have scored more than "<<player2.name;
		}
		else if (player2.score>player1.score)
		{
			gotoxy(0,2);cout<<player2.name<<" you have scored more than "<<player1.name;
		}
		else
			{
				gotoxy(0,2);cout<<"You both have scored equal";
		}
		kplkp:
				gotoxy(0,4);cout<<"Press backspace to continue";
				_getch();
				if(GetAsyncKeyState(VK_RETURN))
				{
					_getch();
					goto kplkp;
				}
				if(!GetAsyncKeyState(VK_BACK))
				{
					goto kplkp;
				}
				system("cls");
				flag=0;
				score=0;
				 z=0;
				 l=0;
				return;
	}

}

/**
It erases the path after character go ups
*/
void path_eraser()
{
     if(doodle_position.y!=current_platform.y)
        {
            gotoxy(doodle_position.x,doodle_position.y+1);cout<<char(255);
            if(doodle_position.x!=2)
            gotoxy(doodle_position.x-2,doodle_position.y+1);cout<<char(255);
            if(doodle_position.x!=77)
                gotoxy(doodle_position.x+2,doodle_position.y+1);cout<<char(255);
        }
        gotoxy(doodle_position.x,doodle_position.y-1);cout<<char(255);
        if(doodle_position.x!=2)
        gotoxy(doodle_position.x-2,doodle_position.y-1);cout<<char(255);
        if(doodle_position.x!=77)
            gotoxy(doodle_position.x+2,doodle_position.y-1);cout<<char(255);
            if(doodle_position.x==1)
            {
                gotoxy(78,doodle_position.y+1);cout<<char(255);
                gotoxy(78,doodle_position.y-1);cout<<char(255);
            }
            else if(doodle_position.x==78)
            {
                gotoxy(2,doodle_position.y+1);cout<<char(255);
                gotoxy(2,doodle_position.y-1);cout<<char(255);
				gotoxy(1,doodle_position.y-1);cout<<char(255);
            }
}

/**
Helper function to take user inputs and make character jumps
*/
void doodle_jumper()
{
    int sl=80;

    platform_print();
    if(GetAsyncKeyState(VK_LEFT))
    {
        doodle_position.x-=2;
    }
    if(GetAsyncKeyState(VK_RIGHT))
    {
        doodle_position.x+=2;
    }
    if(doodle_position.x>78)
                doodle_position.x=1;
    if(doodle_position.x<1)
                doodle_position.x=78;
    if(upward==true)
        {
            doodle_position.y--;
            if(doodle_position.y==current_platform.y-13)
                {
                    upward=false;
                    downward=true;
                }
                if(doodle_position.y<=current_platform.y-8)
                sl+=30;
            else
                sl=50;
            Sleep(sl);
        }
    else if(downward==true)
        {
            doodle_position.y++;
            if(position[(41-(doodle_position.y+1))+z][doodle_position.x]=='%')

                {
                    upward=true;
                    downward=false;
                    current_platform.y=doodle_position.y;
                    current_platform.x=doodle_position.x;

                }
                if(doodle_position.y<=current_platform.y-8)
                sl-=30;
            else
                sl=50;
            Sleep(sl);
        }

        if(doodle_position.y==10)
            {
                z=z+10;
                doodle_position.y+=10;
                current_platform.y+=10;
                score+=41;
                system("cls");
                boundary();
            }
        color_setter(13);gotoxy(doodle_position.x,doodle_position.y);cout<<char(1);
		gotoxy(2,0);cout<<score;gotoxy(38,0);cout<<"JUMPY";gotoxy(64,0);cout<<"Player: "<<current.name;
       path_eraser();
        if(doodle_position.y==42)
            {
                return;
            }
        doodle_jumper();
}
/**
Function to control game
*/
void game_controler()
{
	int x=2;
up:
	consol_size_setter(100,1,340,240,true);
	system("cls");
		if(x==1)color_setter(114);else color_setter(2);gotoxy(2,2);cout<<"Wellcome to the jumpy";
		if(x==2)color_setter(114);else color_setter(2);gotoxy(2,3);cout<<"1. Play";
		if(x==3)color_setter(114);else color_setter(2);gotoxy(2,4);cout<<"2. Multiplayer";
		if(x==4)color_setter(114);else color_setter(2);gotoxy(2,5);cout<<"3. High scores";
		if(x==5)color_setter(114);else color_setter(2);gotoxy(2,6);cout<<"4. Options";
		if(x==6)color_setter(114);else color_setter(2);gotoxy(2,7);cout<<"5. Help";
		if(x==7)color_setter(114);else color_setter(2);gotoxy(2,8);cout<<"6. EXIT";
		color_setter(2);gotoxy(2,9);cout<<"**********************";
		_getch();
		if(GetAsyncKeyState(VK_DOWN)!=0)
			{
				x++;_getch();
		}
		if((GetAsyncKeyState(VK_UP))&&(x!=2))
			{
				x--;_getch();
		}
	if(x>7)
		x=2;
	Sleep(200);
	system("cls");if(GetAsyncKeyState(VK_RETURN));else goto up;

	if(x==2)
	{
		match_type=1;
		consol_size_setter(100,1,380,100,true);
		system("pause");
		system("cls");
		consol_size_setter(100,1,1280,200,true);
		gotoxy(32,4);cout<<"Your name please ";cin>>player1.name;player1.name[0]=toupper(player1.name[0]);
		strcpy_s(current.name,player1.name);
		gag:
		system("cls");
		consol_size_setter(100,1,1280,740,true);
		platform_print();
        boundary();
        doodle_position.x=current_platform.x+3;
        doodle_position.y=current_platform.y-1;
        doodle_jumper();
		score_printer();
		if(l==1)
			{
				l=0;
				goto gag;
		}
	}
	if(x==3)
	{
		match_type=2;
		consol_size_setter(100,1,380,100,true);
		system("pause");
		system("cls");
		consol_size_setter(100,1,1280,200,true);
		gotoxy(13,2);cout<<" Give some exercise to your fingers. Please enter names ";
		gotoxy(34,4);cout<<"Player 1 ";cin>>player1.name;player1.name[0]=toupper(player1.name[0]);
		gotoxy(34,6);cout<<"Player 2 ";cin>>player2.name;player2.name[0]=toupper(player2.name[0]);
		system("cls");
		strcpy_s(current.name,player1.name);
		platform_print();
        boundary();
        doodle_position.x=current_platform.x+3;
        doodle_position.y=current_platform.y-1;
        doodle_jumper();
		system("cls");
		consol_size_setter(100,1,380,100,true);
		system("cls");
		score_printer();
		l=1;
		player1.score=score;
		flag=0;
        z=0;
		score=0;
		system("cls");
		strcpy_s(current.name,player2.name);
		platform_print();
        boundary();
        doodle_position.x=current_platform.x+3;
        doodle_position.y=current_platform.y-1;
        doodle_jumper();
		player2.score=score;
		consol_size_setter(100,1,380,100,true);
		score_printer();
		system("cls");

	}
	if(x==4)
	{
		high_score("df",2,true);
	}
	if(x==7)
	{

		int zm=0;
lk:
		consol_size_setter(100,1,440,240,true);
		system("cls");
		color_setter(2);gotoxy(2,3);cout<<"Are you sure you want to exit";
		if(zm==0)color_setter(114);else color_setter(2);gotoxy(12,5);cout<<"Yes";if(zm==1)color_setter(114);else color_setter(2);gotoxy(18,5);cout<<"No";
		color_setter(2);gotoxy(2,7);cout<<"*****************************";
		_getch();
		if(GetAsyncKeyState(VK_RIGHT))
			{
				if(zm==0)
				zm++;
		}

		if(GetAsyncKeyState(VK_LEFT))
		{
			if(zm==1)
				zm--;

		}
		if(GetAsyncKeyState(VK_RETURN))
		{
			if(zm==0)
			{exit(0);}
			if(zm==1)
			{
				zpk:
				system("cls");
				gotoxy(2,3);cout<<"Press backspace to continue";_getch();if(GetAsyncKeyState(VK_RETURN)){_getch();goto zpk;}if(!GetAsyncKeyState(VK_BACK)){goto zpk;}

			}
		}
		else
			goto lk;
	}
	game_controler();
}
/**
Here all starts
*/
int main()
{
	SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE),8);
	SetConsoleTitle(L"JUMPY");
        system("cls");
        platform_maker();
            game_controler();

}

