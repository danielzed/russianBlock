#ifndef OBJECT_H
#define OBJECT_H

#include <curses.h>
#include <map>
#include <vector>
using namespace std;
class Block;
class Shape;
class Table{
private:
    WINDOW* win;
    int h,w;
    int heady,headx;
    vector<Block*> blocks;
    int** M;
public:
    Table(WINDOW* win,int height,int width,int heady,int headx);
    void showBlock(Block* block);
    void show();
    bool leftAvailable(Block* block);
    bool rightAvailable(Block* block);
    bool downAvailable(Block* block);
    bool leftAvailable(Shape* shape);
    bool rightAvailable(Shape* shape);
    bool downAvailable(Shape* shape);
    bool rotateAvailable(Shape* shape);
    void addBlock(Block*);
    void addShape(Shape*);
    ~Table();
};

enum Color{
    red,orange,yellow,green,blue,black
};
class Block{
private:
    int x,y;
    Color color;
    WINDOW* win;
public:
    Block(int y,int x,WINDOW* win,Color color=black);
    int getX(){return x;}
    int getY(){return y;}
    void setX(int newx){x=newx;}
    void setY(int newy){y=newy;}
    bool move_left();
    bool move_right();
    bool move_down();
    void show();
};
enum ShapeType{
    TYPE1,TYPE2,TYPE3,TYPE4,TYPE5
};

class Shape{
private:
    //static map<ShapeType,vector<Block>> shapeMap;
    int headx,heady;//mark the left-top of the shape,important in rotate
    vector<Block*> blocks;
    ShapeType type;
    WINDOW* win;
public:
    Shape(int heady,int headx,WINDOW* win,ShapeType=TYPE1);
    virtual ~Shape();
    vector<Block*>& getBlocks(){return blocks;}
    int getHeadx(){return headx;}
    int getHeady(){return heady;}
    bool move_left();
    bool move_right();
    bool move_down();
    void show();
    void rotate();
};




#endif // OBJECT_H
