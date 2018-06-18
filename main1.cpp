#include <curses.h>
#include "object.h"
#include <stdlib.h>

int game_win_height=20;
int game_win_width=10;
int score_win_height=10;
int score_win_width=10;
int score_win_starty=0;
int score_win_startx=50;
int next_win_height=10;
int next_win_width=10;
int next_win_starty=20;
int next_win_startx=50;
WINDOW* createWindow(int height,int width,int starty,int startx);
void destroyWindow(WINDOW* window);
int getRand(int min,int max);

int getRand(int min, int max){
    return (min+rand()%(max-min));
}

WINDOW* createWindow(int height, int width, int starty, int startx){
        WINDOW *local_win;
        local_win = newwin(height, width, starty, startx);
        box(local_win,0,0);
        wrefresh(local_win);
        return local_win;
}

int main(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    refresh();
    WINDOW* game_win=createWindow(game_win_height,game_win_width,0,0);
    wborder(game_win,'*','*','*','*','*','*','*','*');
    wrefresh(game_win);

    WINDOW* score_win=createWindow(score_win_height,score_win_width,score_win_starty,score_win_startx);
    wborder(score_win,'*','*','*','*','*','*','*','*');
    wrefresh(score_win);

    WINDOW* next_win=createWindow(next_win_height,next_win_width,next_win_starty,next_win_startx);
    wborder(next_win,'*','*','*','*','*','*','*','*');
    wrefresh(next_win);
    int x=1,y=1;
    char ch;
    Table* table=new Table(game_win,game_win_height-1,game_win_width-1,0,0);
    Shape* shape=new Shape(3,3,game_win,TYPE2);
    shape->show();
    table->show();
    wrefresh(game_win);
    while(1){
        while((ch=getch())==-1);
        switch(ch){
        case 2:
            if(table->downAvailable(shape))
                shape->move_down();
            else{
                table->addShape(shape);
                delete shape;
                int randtype=getRand(0,4);
                Shape* shape=new Shape(3,3,game_win,(ShapeType)randtype);
            }
            break;
        case 4:
            if(table->leftAvailable(shape))
                shape->move_left();
            break;
        case 5:
            if(table->rightAvailable(shape))
                shape->move_right();
            break;
        case 3:
            if(table->rotateAvailable(shape))
                shape->rotate();
            break;
        }
        shape->show();
        table->show();
        wrefresh(game_win);
    }

    endwin();
    delete table;
    delete shape;
}

