////////////////////////////////////////
// Ricky Gardiner
// Started: 11 September, 2013
// Pong
// Last Edited: 17 September, 2013
////////////////////////////////////////

#include "AIE.h"
#include "Vector.h"
#include <string>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>

using namespace std;

struct movableObject
{
	vector2D position;
	vector2D speed;
	int iSprite;
	int iWidth;
	int iHeight;
};

const int SPEED = 10;
const int SCREEN_X = 1280;
const int SCREEN_Y = 780;

// All of these will be determined later.
const int PLAYER1_X = 80;
const int PLAYER1_W = 30;
const int PLAYER1_H = 120;

const int PLAYER2_X = 1200;
const int PLAYER2_W = 30;
const int PLAYER2_H = 120;

const int BALL_W = 30;
const int BALL_H = 30;

// Global variables.
unsigned int bgImage = -1;
movableObject player1 = { PLAYER1_X, 390, 0, 0, -1, PLAYER1_W, PLAYER1_H };
movableObject player2 = { PLAYER2_X, 390, 0, 0, -1, PLAYER2_W, PLAYER2_H };
movableObject ball = { 640, 390, 5, 5, -1, BALL_W, BALL_H };

//int iHighScores[5] = { 0 };
bool bGameOver = false;
bool bBallPause = true;

// Array that determines the direction of the ball.
int aRandDirection[2] = { 5, -5 };
int iDirectLength = sizeof(aRandDirection) / sizeof(int);

int iPlayer1Score = 0;
int iPlayer2Score = 0;
int iFrameCounter = 0;

//// Sorting an array of integers in descending order. Used for high score. No need for it yet.
//void sort( int array[], int size )
//{
//	for( int i = 0; i < size; i++ )
//	{
//		for( int j = 0; j < size; j++ )
//		{
//			if( array[i] > array[j] )
//			{
//				int temp = array[i];
//				array[i] = array[j];
//				array[j] = temp;
//			}
//		}
//	}
//}

// Tests if an object is outside of the screen boundaries.
// If an object has gone outside of the boundaries, this will change the object's speed so that it will move back onto the screen.
bool testOnScreen( movableObject &obj )
{
	if( obj.position.x > SCREEN_X )
	{
		obj.speed.x *= -1;
		return true;
	}
	if( obj.position.x < 0 )
	{
		obj.speed.x *= -1;
		return true;
	}
	
	if( obj.position.y > SCREEN_Y )
	{
		obj.speed.y *= -1;
	}
	if( obj.position.y < 0 )
	{
		obj.speed.y *= -1;
	}
	return false;
}
 
// Updates the position of the ball.
void updateBallPosition( movableObject &obj )
{
	obj.position = vectorAdd( obj.position, obj.speed );
}

// Checks if the ball has collided with the paddle.
bool checkPaddleCollision( movableObject &ball, movableObject &player )
{
	float fSpeed = ball.speed.x;

	int iBallHalfW = ball.iWidth >> 1;
	
	int iPlayerHalfW = player.iWidth >> 1;
	int iPlayerHalfH = player.iHeight >> 1;

	if( fSpeed == 0 )
	{
		return false;
	}

	if( fSpeed < 0 )
	{
		//Creates the region where the ball detects collision with paddle.
		if( ball.position.x - iBallHalfW < player.position.x + iPlayerHalfW &&
			ball.position.y > player.position.y - iPlayerHalfH &&
			ball.position.y < player.position.y + player.iHeight )
		{
			return true;
		}
	}
	else
	{
		if( ball.position.x + iBallHalfW > player.position.x - iPlayerHalfW &&
			ball.position.y > player.position.y - iPlayerHalfH &&
			ball.position.y < player.position.y + player.iHeight )
		{
			return true;
		}
	}
	return false;
}

// Checks if an object has collided with another object.
bool checkCollision( movableObject &obj1, movableObject &obj2 )
{
	vector2D diff = vectorSubtract( obj1.position, obj2.position);
	float fMag = getMagnitude( diff );

	if( fMag > 0 && fMag < obj1.iHeight )
	{
		obj1.speed = multiplyScalar( getNormal(diff), 5 );
		obj2.speed = multiplyScalar( getNormal(diff), -5 );
		return true;
	}
	return false;
}

// Computer player movement.
void seek( movableObject &player, movableObject &ball )
{
	float fSpeed = sqrt( ball.speed.x * ball.speed.x + ball.speed.y * ball.speed.y );

	if( player.position.y < ball.position.y - fSpeed )
	{
		float fDiff = ball.position.y - player.position.y;

		if( fDiff > fSpeed )
		{
			player.position.y += fSpeed;
		}
		else
		{
			player.position.y += fDiff;
		}
	}
	else if( player.position.y > ball.position.y + fSpeed )
	{
		float fDiff = player.position.y - ball.position.y;
		
		if( fDiff > fSpeed )
		{
			player.position.y -= fSpeed;
		}
		else
		{
			player.position.y -= fDiff;
		}
	}
}


// Player 1 movement function.
void player1Movement( movableObject &obj )
{
	if( IsKeyDown( 'W' ) )
	{
		MoveSprite( obj.iSprite, obj.position.x, obj.position.y -= 5 );
		obj.speed.y = 5;
	}
	else if( IsKeyDown( 'S' ) )
	{
		MoveSprite( obj.iSprite, obj.position.x, obj.position.y += 5 );
		obj.speed.y = 5;
	}

}

// Player 2 movement function.
void player2Movement( movableObject &obj )
{
	if( IsKeyDown( KEY_UP ) )
	{
		MoveSprite( obj.iSprite, obj.position.x, obj.position.y -= 5 );
	}
	else if( IsKeyDown( KEY_DOWN ) )
	{
		MoveSprite( obj.iSprite, obj.position.x, obj.position.y += 5 );
	}

}

// When a the ENTER key pressed, the ball will begin moving.
int ballServe()
{
	if( bBallPause )
	{
		
		ball.speed.x = 0;
		ball.speed.y = 0;
		ball.position.x = 640;
		ball.position.y = 390;

		if( IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_SPACE) )
		{
			bBallPause = false;
			
			// The ball can either go up-right, up-left, down-right, or down-left. This is chosen randomly.
			ball.speed.x = aRandDirection[ rand() % iDirectLength ];
			ball.speed.y = aRandDirection[ rand() % iDirectLength ];
			
			return 0;
		}
	
	}


}

// Initializes variables in the game.
void initGame()
{
	srand( (unsigned int)time(NULL) );

	bgImage = CreateSprite( "./images/blissPony.png", SCREEN_X, SCREEN_Y, true );
	MoveSprite( bgImage, SCREEN_X >> 1, SCREEN_Y >> 1 );

	ball.iSprite = CreateSprite( "./images/greenBall.png", BALL_W, BALL_H, true );

	player1.iSprite = CreateSprite( "./images/redPaddle.png", PLAYER1_W, PLAYER1_H, true );
	player2.iSprite = CreateSprite( "./images/redPaddle.png", PLAYER2_W, PLAYER2_H, true );
}

// Destroys all sprites in the game to clean up memory.
void destroyGame()
{
	DestroySprite( bgImage );
	DestroySprite( ball.iSprite );
	DestroySprite( player1.iSprite );
	DestroySprite( player2.iSprite );
}

// Updates game logic.
void updateGame()
{
	updateBallPosition( ball );

	ballServe();

	player1Movement( player1 );
	player2Movement( player2 );
	
	//if( ball.speed.x > 0 )
	//{
	//	seek( player2, ball );
	//}

	// Increments the player's score depending on which side the ball is on.
	if( testOnScreen( ball ) )
	{
		if( ball.position.x < 80 )
		{
			iPlayer2Score++;
			bBallPause = true;

		}
		else if( ball.position.x > 1200 )
		{
			iPlayer1Score++;
			bBallPause = true;

		}
	}

	if( ball.speed.x < 0 )
	{
		if( checkPaddleCollision( ball, player1 ) == true )
		{
			ball.speed.x *= -1;
		}
	}
	else
	{
		if( checkPaddleCollision( ball, player2 ) == true )
		{
			ball.speed.x *= -1;
		}
	}

	RotateSprite(player1.iSprite, 0);
	MoveSprite(player1.iSprite, player1.position.x, player1.position.y);

	RotateSprite(player2.iSprite, 0 );
	MoveSprite(player2.iSprite, player2.position.x, player2.position.y);

	MoveSprite( ball.iSprite, (float)ball.position.x, (float)ball.position.y );

	
}

// Draws each frame of the game.
void drawGame()
{
	DrawSprite( bgImage );
	
	DrawSprite( ball.iSprite );
	DrawSprite( player1.iSprite );
	DrawSprite( player2.iSprite );

	static char cOutScore1[15] = { '\n' };
	static char cOutScore2[15] = { '\n' };

	sprintf_s( cOutScore1, "Player 1: %d", iPlayer1Score );
	sprintf_s( cOutScore2, "Player 2: %d", iPlayer2Score );

	DrawString( cOutScore1, 50, 50, SColour( 255, 0, 0, 255 ) );
	DrawString( cOutScore2, 1000, 50, SColour( 255, 0, 0, 255 ) );
}

int main( int argc, char* argv[] )
{
	Initialise( SCREEN_X, SCREEN_Y, false );

	initGame();

	do
	{
		iFrameCounter++;

		if( iFrameCounter > 5000 )
		{
			iFrameCounter = 0;
		}

		ClearScreen();

		updateGame();
		
		drawGame();

	} while( FrameworkUpdate() == false );

	destroyGame();

	Shutdown();

	return 0;
}