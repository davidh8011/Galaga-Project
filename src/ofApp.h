#pragma once

#include "ofMain.h"
#include "Ship.h"
#include "Shot.h"
#include "ArrayList2.h"
#include "Fighter.h"
#include "Enemy1.h"
#include "ArrayListEnemy.h"
#include "ArrayListShot.h"
#include "Powerup.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ofApp : public ofBaseApp {
	Fighter fighter{ ofGetWidth() / 2 - 25, ofGetHeight() - 50, 5, 5 };
	bool instructionScreen;
	bool gameOver;
	bool pause;
	bool moveLeft;
	bool moveRight;
	bool spread;
	bool newGame;
	int moveKey;
	int level;
	int timer;
	bool power;
	Powerup pow;
	string sc;
	int score;
	string hScore;
	int highScore;
	int movement;
	ofImage en1;
	ArrayList shotX;
	ArrayList shotY;
	ArrayList shotXLeft;
	ArrayList shotYLeft;
	//ArrayList shotXRight;
	//ArrayList shotYRight;
	ArrayList bombX;
	ArrayList bombY;
	ArrayList bombDir;
	//ArrayList enemyX;
	//ArrayList enemyY;
	ArrayListEnemy enemies;
	//ArrayListShot shotList;
	//ArrayListShot bombs;
	int shotCycle{ 0 };
	ofImage background;
	ofTrueTypeFont font;
	//Enemy1* enemy1;
	//int numEnemy1;
	int enemyLeft;


	public:
		void setup();
		void update();
		void draw();
		void spreadShot();
		void levelSetUp();
		void playLevel();
		void pauseScreen();
		void resetGame();
		//~ofApp();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
