/**Author:Rishi Anand
 simple tic tac toe game**/
#include<iostream>
#include<conio.h>
using namespace std;
struct Move{
    int row,col;
};
//to initialize the board
/**function1**/void initialize(char board[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            board[i][j]='_';
        }
    }
}
//to display the board
/**function2**/void draw(char b[3][3])
{
    clrscr();
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
}
//to check if there are any moves left
/**function3**/bool isMoveleft(char board[3][3])
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]=='_')
                return true;
    return false;
}
//to check if any player is winning or not
/**function4**/int evaluate(char b[3][3])
{
    //to check all the rows
    for(int i=0;i<3;i++)
    {
        if(b[i][0]==b[i][1]&&b[i][1]==b[i][2])
        {
            if(b[i][0]=='X')
            return +10;
            if(b[i][0]=='O')
            return -10;
        }

    }
    //to check all the columns
    for(int j=0;j<3;j++)
    {
         if(b[0][j]==b[1][j]&&b[1][j]==b[2][j])
        {
            if(b[0][j]=='X')
            return +10;
            if(b[0][j]=='O')
            return -10;
        }
    }
    //to check diagonals
    if(b[0][0]==b[1][1]&&b[1][1]==b[2][2])
        {
            if(b[0][0]=='X')
            return +10;
            if(b[0][0]=='O')
            return -10;
        }
        if(b[0][2]==b[1][1]&&b[1][1]==b[2][0])
        {
            if(b[0][2]=='X')
            return +10;
            if(b[0][2]=='O')
            return -10;
        }
        return 0;
}
//to input value from human player
/**function5**/
void input(char board[3][3],int a)
{
int r,c;
r=a/10;
c=a%10;
board[r][c]='O';
}
//Minimax algorithm
/**function5**/
int minimax(char b[3][3],int depth,bool isMax)
{
int score=evaluate(b);
if(score==10)
return score;
if(score==-10)
return score;
if(isMoveleft(b)==false)
return 0;
if(isMax)
{
    int best=-1000;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
          if(b[i][j]=='_')
          {
              b[i][j]='X';
              best=max(best,minimax(b,depth+1,false));
              //Undo move
              b[i][j]='_';
          }
        }
    }
    return best;
}
else
{
    int best=1000;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
          if(b[i][j]=='_')
          {
              b[i][j]='O';
              best=min(best,minimax(b,depth+1,true));
              //Undo move
              b[i][j]='_';
          }
        }
    }
    return best;
}
}
//to return the location of best move
/**function6**/
Move bestmove(char b[3][3])
{
    Move bestval;
    bestval.row=-1;
    bestval.col=-1;
    int best=-1000,val;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(b[i][j]=='_')
            {
                b[i][j]='X';
                val=minimax(b,0,false);
                if(val>best)
                {
                    bestval.row=i;
                    bestval.col=j;
                    best=val;
                }
                b[i][j]='_';
            }
        }
    }
    return bestval;
}
//main function
int main()
{
    char bo[3][3];
    initialize(bo);
    int i,r;
    Move bestMove;
    bool gameover=true;
    while(gameover==true)
    {
        bestMove=bestmove(bo);
        bo[bestMove.row][bestMove.col]='X';
        gameover=isMoveleft(bo);
        r=evaluate(bo);
        if(gameover==false||r==10||r==-10)
        break;
        draw(bo);
        cin>>i;
        input(bo,i);
    }
    r=evaluate(bo);
    draw(bo);
    if(r==10)
    cout<<"The computer has won"<<endl;
    if(r==-10)
    cout<<"You Win!!"<<endl;
    if(r==0)
    cout<<"Its a tie!"<<endl;
    return 0;
}
