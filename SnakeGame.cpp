#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int x, y, score;
int fx, fy;
int width = 40, height = 20;
int tailX[100], tailY[100], tail;
//allot keys to play
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
bool gameOver;

void init(){
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fx = rand() % width;
    fy = rand() % height;
    score = 0;
}
   
void print(){
    system("cls");
    //print the top wall
    for(int i = 0; i < width + 2; i++){
        cout << "#";
    }
    cout << endl;
    
    //print the left and right walls, snake and food
    //i along the height (y)
    for(int i = 0; i < height; i++){
        
        //j along the width (x)
        for(int j = 0; j < width; j++){
            
            //print # at corners and ' ' in the middle
            //cout << " ";
            if(j == 0){
                cout << "#";
            } 
                  
            //snake's head and tail if not walls
            if(i == y && j == x){
                cout << "O";
            }
            
            //print the food
            else if(i == fy && j == fx){
                cout << "F";
            }
            
            //blank space if nothing
            else{
                bool istail = false;
                for(int k = 0; k < tail; k++){
                    if(tailX[k] == j && tailY[k] == i){
                        cout << "o";
                        istail = true;
                    }
                }
                if(!istail){
                    cout << " ";
                }
            }
         
            if(j == width - 1){
                cout << "#";
            }
            
        }//end line after one width
        cout << endl;
    }
    
    //print bottom wall
    for(int i = 0; i < width + 2; i++){
        cout << "#";
    } 
    cout << endl;
    cout << "YOUR SCORE: " << score <<endl;
    cout << "Press 'x' to exit" << endl;
}

void keys(){
    if(_kbhit()){
        switch(_getch()) {
            case KEY_UP:    // key up
                dir = UP;
                break;
            case KEY_DOWN:    // key down
                dir = DOWN;
                break;
            case KEY_RIGHT:    // key right
                dir = RIGHT;
                break;
            case KEY_LEFT:    // key left
                dir = LEFT;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void logic(){
   
    for(int i = tail - 1; i > 0; i--){
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }
    tailX[0] = x;
    tailY[0] = y;
    switch(dir){
        case UP:
            y--;
            Sleep(20);
            break;
        case DOWN:
            y++;
            Sleep(20);
            break;
        case RIGHT:
            x++;
            Sleep(20);
            break;
        case LEFT:
            x--;
            Sleep(20);
            break;
    }

    if(x == fx && y == fy){
        score += 10;
        fx = rand() % width;
        fy = rand() % height;
        tail++;
    }

    if(x >= width)
        x = 0;
    else if(x < 0)
        x = width - 1;
    if(y >= height)
        y = 0;
    else if(y < 0)
        y = height - 1;

    for(int i = 0; i < tail; i++){
        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }
    
}

int main(){
    init();
    while(!gameOver){
        print();
        keys();
        logic();
        Sleep(10);
        //system("pause"); 
    }    
    cout << "YOUR FINAL SCORE IS: " << score;
    return 0;
}



