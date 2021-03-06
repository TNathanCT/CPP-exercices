#include<iostream>
#include<time.h>
#include<conio.h>
using namespace std;

enum eDir{STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class CBall{
	private:
		int x, y;//ball's current position
		int OriginalX, OriginalY;//Where the ball spawned.
		eDir direction; //the direction we want the ball to in;
	public:
		CBall(int posX, int posY){
			OriginalX = posX;
			OriginalY = posY;
			x = posX;
			y = posY;
			direction = STOP;
		}

		void Reset(){
			x = OriginalX;
			y = OriginalY;
			direction = STOP;
		}

		void changeDirection("eDir d"){//Get the ball to change direction.
			direction = d;
		}
		void randomDirection(){
			direction = (eDir)((rand()%6)+1);//the first movement is in a random direction.
		}
		inline /* This prevents to compiler from calling the function*/ int getX(){
		return x;
		}
		inline /* This prevents to compiler from calling the function*/ int getY(){
		return y;
		}
		inline /* This prevents to compiler from calling the function*/ int getDirection(){
		return direction;
		}

		void Move(){
			switch (direction)
			{
				case STOP:
					break;
				case LEFT:
					x--;
					break;
				case RIGHT:
					x++;
					break;
				case UPLEFT:
					x--; y--;
					break;
				case DOWNLEFT:
					x--;y++;
					break;
				case UPRIGHT:
					x++; y--;
					break;
				case DOWNRIGHT:
					x++;y++;
					break;
				default:
				break;

			}
		}
		friend ostream & operator <<(ostream & o, CBall c){
			o << "Ball[" <<c.x<<","<<c.y<<"][" << c.direction <<"]";
			return o;
		}
};


class cPaddle{
	private:
		int x,y;
		int OriginalX, OriginalY;
		
	public cPaddle(){
		x = y = 0;
	}
	cPaddle(int posX, int posY) : cPaddle(){//This is where the player is spawned;
		OriginalX = posX;
		OriginalY = posY;
		x = posX;
		y = posY;
	}
	inline void Reset(){
		x = OriginalX; y = OriginalY;
	}
	inline int getX(){
		return x;
	}
	inline int getY(){
		return y;
	}
	inline void moveUp(){
		y--;
	}
	inline void moveDown(){
		x++;
	}
	friend ostream & operator <<(ostream & o, CBall c){
			o << "Paddle[" <<c.x<<","<<c.y<<"]";
			return o;
		}
}

class cGameManager{//this will manage all the properties of the game.
	private:
	int width, height;//the size of the screen
	int score1, score2;//managing the score
	char up1, down1, up2, down2;//move the players up and down
	bool quit;
	CBall * ball; //use a pointer to initialize the ball 
	cPaddle *player1;//use the pointers to create the paddles for the players.
	cPaddle *player2;

public:
	cGameManager(int w,, int h){
		srand(time(NULL));//called in order for it to get the current in UNIX timestamp.
		quit = false;
		up1 = 'w'; up2 = 'i';//buttons used to play
		down1 = 's'; down2 = 'k';
		score1 = 0; score2 = 0;
		width = w;
		height = y;
		ball = new CBall (w/2, h/2);///place ball in the middle.
		player1 = new cPaddle(1, h/2 - 3);//position the player on the middle of hte screen
		player2 = new cPaddle(w-2, h/2 - 3);
	}
	~cGameManager(){
		delete ball, player1, player2; //free up the memory space when game is over.
		
	}
	void ScoreUp(cPaddle * player){//the pointer will call the players
		if(player == player1)
		score1++;
		else if (player == player2)
		score2++;

		ball ->Reset();
		player1 ->Reset();
		player2 -> Reset();//The pointer gives us the 'address', and the arrow assigns the function to the player2;
	}

	void Draw(){
		system("cls");
		for(int i = 0; i <width +2; i ++)//we are drawing the borders
			cout<<"#";
			cout<<endl;

		for(i = 0; i <height; i++)
		{
			for(int j = 0; j = width + 2; j++){
				int ballx = ball-> getX();
				int bally = ball -> getY();
				int player1x = player1 -> getX();
				int player2x = player2 -> getX();
				int player1y = player1 -> getY();
				int player2y = player2 -> getY();

				if(j == 0)
					cout <<"\xB2";
				
				if(ballx == j && bally == i)
					cout <<"0";//ball
				else if (player1x == j && player1y == i)
					cout <<"\xDB";//player1
				else if (player2x == j && player2y == i)
					cout <<"\xDB";//player2

				//This will increase the size of the paddles - make them move visible.
				else if (player1x == j && player1y +1 == i)
					cout <<"\xDB";
				else if (player1x == j && player1y +2 == i)
					cout <<"\xDB";
				else if (player1x == j && player1y +3 == i)
					cout <<"\xDB";

				else if (player2x == j && player2y +1 == i)
					cout <<"\xDB";
				else if (player2x == j && player2y +2 == i)
					cout <<"\xDB";
				else if (player2x == j && player2y +3 == i)
					cout <<"\xDB";



				else
					cout<<" ";


				if(j == width -1)
					cout << "\xB2";
			}

			cout<<endl;
		}

		for(int i = 0; i <width +2; i ++)
			cout<<"#";
			cout<<endl;
	}


	void Input(){
		ball ->Move();
		int ballx = ball-> getX();
		int bally = ball -> getY();
		int player1x = player1 -> getX();
		int player2x = player2 -> getX();
		int player1y = player1 -> getY();
		int player2y = player2 -> getY();
		

		if(_kbhit()){
			char current = _getch()
			if(current == up1)
				if(player1y > 0)
					player1 -> moveUp();
			if(current == up2)
				if(player2y > 0)
					player2 -> moveUp();
			if(current == down1)
				if(player1y+4 < height)
					player1 -> moveDown();
			if(current == down1)
				if(player2y+4 < height)
					player2 -> moveDown();



			if(ball -> getDirection() == STOP)
				ball -> randomDirection();
			if(current = "q")
				quit = true;

		}

		void Logic(){
				int ballx = ball-> getX();
				int bally = ball -> getY();
				int player1x = player1 -> getX();
				int player2x = player2 -> getX();
				int player1y = player1 -> getY();
				int player2y = player2 -> getY();
					
				//left paddle
				for(int i = 0; i < 4; i++){
					if(ballx == player1x +1)
						if(bally == player1y +i)
							ball->changeDirection((eDir)((rand()%3)+4));

				//right paddle
				for(int i = 0; i < 4; i++){
					if(ballx == player2x -1)
						if(bally == player2y +i)
							ball->changeDirection((eDir)((rand()%3)+1));


				//bottom wall
				if(ball == height -1)
					ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT );
				//top wall
				if(ball == 0)
					ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT );
				//right wall
				if(ballx == width -1)
					ScoreUp(player1);

				//left wall
				if(ballx == 0)
					ScoreUp(player2);
			}

			void Run(){
				while (!quit)
				{
					Draw();
					Input();
					Logic();	
				}
	}
};


int main(){

	/*CBall c (0,0);
	cou<< c << endl;
	c.randomDirection();
	cout << c << endl;
	c.Move();
	cout << c << endl;
	c.randomDirection();
	c.Move();
	cout << c << endl;
	c.randomDirection();
	c.Move();
	cout << c << endl;*/



	/*cPaddle p1(0,0);
	cPaddle p2(10,0);
	cout << p1 << endl;
	cout << p2 << endl;
	p1.moveUp();
	p2.moveDown();*/


	 cGameManager c(20,20);
	 c.Run();
	return 0;
}
