#include "object.h"

void swap(int& a,int& b){
    int t=a;
    a=b;
    b=t;
}

Table::Table(WINDOW *win, int height, int width,int heady,int headx){
    this->win=win;
    h=height;
    w=width;
    this->heady=heady;
    this->headx=headx;
    M=new int*[height+1];
    for(int i=0;i<=height;i++)
        M[i]=new int[width+1];
    for(int i=0;i<=height;i++){
        M[i][0]=1;
        M[i][width]=1;
    }
    for(int i=0;i<=width;i++){
        M[0][i]=1;
        M[height][i]=1;
    }
}
void Table::addShape(Shape * shape){
    for(Block* block:shape->getBlocks()){
        this->addBlock(block);
    }
}
void Table::addBlock(Block * block){
    blocks.push_back(block);
}
bool Table::downAvailable(Block *block){
    int newx=block->getX()-headx;
    int newy=block->getY()+1-heady;
    if(M[newy][newx]==1)
        return false;
    else return true;
}
bool Table::leftAvailable(Block *block){
    int newx=block->getX()-1-headx;
    int newy=block->getY()-heady;
    if(M[newy][newx]==1)
        return false;
    else return true;
}
bool Table::rightAvailable( Block *block){
    int newx=block->getX()+1-headx;
    int newy=block->getY()-heady;
    if(M[newy][newx]==1)
        return false;
    else return true;
}
bool Table::leftAvailable(Shape *shape){
    bool flag=true;
    for(Block* block:shape->getBlocks()){
        if(!leftAvailable(block)){
            flag=false;
            break;
        }
    }
    return flag;
}
bool Table::rightAvailable(Shape *shape){
    bool flag=true;
    for(Block* block:shape->getBlocks()){
        if(!rightAvailable(block)){
            flag=false;
            break;
        }
    }
    return flag;
}
bool Table::downAvailable(Shape *shape){
    bool flag=true;
    for(Block* block:shape->getBlocks()){
        if(!downAvailable(block)){
            flag=false;
            break;
        }
    }
    return flag;
}
bool Table::rotateAvailable(Shape *shape){
    bool flag=true;
    for(auto block:shape->getBlocks()){
        int newx=block->getY()-shape->getHeady()+shape->getHeadx();
        int newy=block->getX()-shape->getHeadx()+shape->getHeady();
        if(M[newy][newx]==1){
            flag=false;
            break;
        }
    }
    return flag;
}
void Table::showBlock(Block *block){
    int newx=block->getX();
    int newy=block->getY();
    mvwaddch(win,newy,newx,'%');
}
void Table::show(){

    for(int i=1;i<h;i++)
        for(int j=1;j<w;j++)
            M[i][j]=0;
    for(Block* block:blocks){
        int newx=block->getX()-headx;
        int newy=block->getY()-heady;
        M[newy][newx]=1;
        showBlock(block);
    }

}

Block::Block(int newy, int newx,WINDOW* win,Color color){
    this->x=newx;
    this->y=newy;
    this->color=color;
    this->win=win;
    mvwaddch(win,y,x,'%');
}
bool Block::move_down(){
    mvwaddch(win,y,x,' ');
    wrefresh(win);
    y=y+1;
    return true;
}
bool Block::move_left(){
    mvwaddch(win,y,x,' ');
    x--;
    return true;
}
bool Block::move_right(){
    mvwaddch(win,y,x,' ');
    x++;
    return true;
}
void Block::show(){
    mvwaddch(win,y,x,'%');

}
Shape::Shape(int heady, int headx, WINDOW* win,ShapeType type){
    this->headx=headx;
    this->heady=heady;
    this->type=type;
    this->win=win;
    Block* block1,*block2,*block3,*block4;
    switch(type){
    case TYPE1:
        block1=new Block(heady,headx,win);
        block2=new Block(heady,headx+1,win);
        block3=new Block(heady,headx+2,win);
        block4=new Block(heady,headx+3,win);
        break;
    case TYPE2:
        block1=new Block(heady,headx,win);
        block2=new Block(heady,headx+1,win);
        block3=new Block(heady+1,headx+1,win);
        block4=new Block(heady+1,headx+2,win);
        break;
    case TYPE3:
        block1=new Block(heady,headx,win);
        block2=new Block(heady,headx+1,win);
        block3=new Block(heady+1,headx+1,win);
        block4=new Block(heady+2,headx+1,win);
        break;
    case TYPE4:
        block1=new Block(heady,headx,win);
        block2=new Block(heady+1,headx+1,win);
        block3=new Block(heady,headx+1,win);
        block4=new Block(heady+1,headx,win);
        break;
    }
    blocks.push_back(block1);
     blocks.push_back(block2);
      blocks.push_back(block3);
       blocks.push_back(block4);
}
bool Shape::move_down(){
    heady++;
    for(auto block:blocks){
        block->move_down();
    }
}
bool Shape::move_left(){
    headx--;
    for(auto block:blocks){
        block->move_left();
    }
}
bool Shape::move_right(){
    headx++;
    for(auto block:blocks){
        block->move_right();
    }
}

void Shape::rotate(){
    for(auto block:blocks){
        int oldx=block->getX();
        int oldy=block->getY();
        mvwaddch(win,oldy,oldx,' ');
        block->setX(oldy-heady+headx);
        block->setY(oldx-headx+heady);
    }
}
void Shape::show(){
    for(auto block:blocks)
        block->show();
}
Shape::~Shape(){
    //shape包含的block由table释放
}
