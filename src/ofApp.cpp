#include "ofApp.h"
using namespace std;



//--------------------------------------------------------------
void ofApp::setup(){
	background.load("Background.jpg");
	instructionScreen = true;
	spread = false;
	gameOver = false;
	moveLeft = false;
	moveRight = false;
	newGame = false;
	ofSetFrameRate(120);
	level = 1;
	movement = 0;
	timer = 0;
	power = false;
	score = 0;
	sc = "0";
	ofSetRectMode(OF_RECTMODE_CENTER);
	enemyLeft = 20;
	for (int i{}; i < enemyLeft/2; i++)
	{
		enemies.add(Enemy1{ ofGetWidth() / enemyLeft *2*(int)(i) + ofGetWidth()/enemyLeft,ofGetHeight() / 4,3,3 }); //lower
		enemies.add(Enemy1{ ofGetWidth() / enemyLeft *2*(int)(i) + ofGetWidth() / enemyLeft,ofGetHeight() / 3,3,3 }); //higher
	}

}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255); //background
	background.draw(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(), ofGetHeight());
	if (instructionScreen)
	{
		font.load("AGENCYB.ttf", 72);
		font.drawString("Galaga", ofGetWidth() / 2-120, ofGetHeight() / 4);
		font.load("AGENCYB.ttf", 20);
		font.drawString("Use left and right arrow keys to move, and spacebar to shoot", 225, ofGetHeight() / 3+80);
		font.drawString("Kill all enemies to beat each level, but don't get hit by their bombs", 200, ofGetHeight() / 3 + 180 );
		font.drawString("Shoot the red flashing powerup for a boost", 305, ofGetHeight() / 3 + 280);
		font.drawString("Press \"Enter\" to begin game", 375, ofGetHeight() / 3 + 380);
	}
	if (!instructionScreen && !gameOver) {
		sc = ofToString(score);
		font.drawString("Score: ", 20, 40);
		font.drawString(sc, 100, 40);
		font.drawString("Level: ", ofGetWidth() - 100, 40);
		sc = ofToString(level);
		font.drawString(sc, ofGetWidth() -30, 40);
		if (!pause)
			playLevel();
		else
			pauseScreen();
	}
	else if (!fighter.isAlive()) {
		sc = ofToString(score);
		font.load("AGENCYB.ttf", 100);
		font.drawString("Game Over", ofGetWidth() / 2 - 235, ofGetHeight() / 4);
		font.load("AGENCYB.ttf", 80);
		font.drawString("Your Score:", ofGetWidth() / 2 - 330, ofGetHeight() /2);
		font.drawString(sc, ofGetWidth() / 2 + 146, ofGetHeight() /2);
		font.drawString("High Score:", ofGetWidth() / 2 - 330, ofGetHeight() * 3/4);
		font.drawString(hScore, ofGetWidth() / 2 + 146, ofGetHeight() *3/4);
		font.load("AGENCYB.ttf", 40);
		font.drawString("Press \"n\" to start new game", ofGetWidth() / 2 - 250, ofGetHeight() - 70);
		if (newGame) {
			resetGame();
		}
	}

}


//--------------------------------------------------------------

void ofApp::playLevel()
{
		if (timer < 10) {
			font.load("AGENCYB.ttf", 100);
			sc = ofToString(level);
			font.drawString("Level", ofGetWidth() / 2 - 170, ofGetHeight() / 2);
			font.drawString(sc, ofGetWidth() / 2 +100, ofGetHeight() / 2);
			font.load("AGENCYB.ttf", 20);
		}
		else {
			if (fighter.isAlive()) { //until dead
				if (moveLeft && fighter.getX() > 30)  //movement 
					fighter.move(-fighter.getSpeed());
				else if (moveRight && fighter.getX() < ofGetWidth() - 30)
					fighter.move(fighter.getSpeed());
				fighter.draw();

				if (shotCycle == 1)  //shooting
				{
					shotX.add(fighter.getX());
					shotY.add(fighter.getY() - 25);
					shotCycle = 2;
					if (spread) {
						shotXLeft.add(fighter.getX());
						shotYLeft.add(fighter.getY() - 25);
					}
				}

				for (int i{}; i < bombX.size(); i++)
				{
					Shot s{ bombX.get(i), bombY.get(i), 2 };
					int temp = bombY.get(i); // moves enemy bombs
					bombY.remove(i);
					bombY.add(i, temp + s.getSpeed());
					
					int temp2 = bombX.get(i); // moves enemy bombs
					bombX.remove(i);
					bombX.add(i, temp2 + bombDir.get(i));

					s.draw();
					if (abs(bombY.get(i) - fighter.getY()) < 25 && abs(bombX.get(i) - fighter.getX()) < 33)  //sees if kills fighter
					{
						fighter.die();
						bombY.remove(i);
						bombX.remove(i);
						gameOver = true;
						ifstream file("HighScores.txt");
						string line;
						if (file.is_open())
						{
							getline(file, line);
							hScore = line;
							file.close();
						}
						int hScoreInt = ofToInt(hScore);
						ofstream file2("HighScores.txt");
						if (score > hScoreInt) {
							hScoreInt = score;
							hScore = ofToString(score);
						}

						if (file2.is_open()) {
							file2 << hScoreInt;
							file2.close();
						}
					}
				}
			}

			for (int i{}; i < shotX.size(); i++)  //draws bullets
			{
				Shot s{ shotX.get(i), shotY.get(i), 5 };
				s.draw();
			}
			for (int i{}; i < shotXLeft.size(); i++) {
				Shot l{ shotXLeft.get(i), shotYLeft.get(i),5 };
				//Shot r{ shotXRight.get(i), shotYRight.get(i),5 };
				l.draw();
				//r.draw();
			}

			for (int i{}; i < shotY.size(); i++)
			{
				int temp = shotY.get(i); // moves shot
				shotY.remove(i);
				shotY.add(i, temp - fighter.getShotSpeed());


				for (int j{}; j < enemyLeft; j++) {  //sees if shot hits enemy
					if (abs(shotY.get(i) - enemies.get(j).getY()) < 25 && abs(shotX.get(i) - enemies.get(j).getX()) < 33)
					{
						enemies.remove(j);
						shotY.remove(i);
						shotX.remove(i);
						enemyLeft--;
						score += 10;
					}
				}
				if (power) //powerup stuff
				{
					if (abs(shotY.get(i) - pow.getY()) < 20 && abs(shotX.get(i) - pow.getX()) < 20) {
						power = false;
						shotY.remove(i);
						shotX.remove(i);
						fighter.powerOn();
						timer = 11;
					}

				}
				if (shotY.get(i) < 0) {  //removes shots off the screen
					shotY.remove(i);
					shotX.remove(i);
				}
			}
			if(spread)
				spreadShot();

			for (int i{}; i < enemyLeft; i++) {
				//int shoot = ofRandom(0, 1000);  //makes enemies randomly shoot bombs
				//Enemy1 e{ enemyX.get(i), enemyY.get(i),2,2 };
				//e.draw(en1);
				//e.move();
				enemies.get(i).draw();
				if (abs(fighter.getY() - enemies.get(i).getY()) < 45 && abs(fighter.getX() - enemies.get(i).getX()) < 45)
				{
					fighter.die();
					gameOver = true;

					ifstream file("HighScores.txt");
					string line;
					if (file.is_open())
					{
						getline(file, line);
						hScore = line;
						file.close();
					}
					int hScoreInt = ofToInt(hScore);
					cout << hScoreInt << endl;
					ofstream file2("HighScores.txt");
					if (score > hScoreInt) {
						hScoreInt = score;
						hScore = ofToString(score);
					}

					if (file2.is_open()) {
						file2 << hScoreInt;
						file2.close();
					}

				}
				if (movement < 30) {
					enemies.get(i).move(1);
				}
				else if (movement < 60)
					enemies.get(i).move(-1);
				if (enemies.get(i).fire())
				{
					bombX.add(enemies.get(i).getX());
					bombY.add(enemies.get(i).getY());
					bombDir.add(ofRandom(-2, 2));
				}
			}

			if (power == false && !fighter.hasPowerUp()) {
				int s = ofRandom(0, 1500);
				if (s == 5) {
					power = true;
					pow = Powerup();
				}
			}
			if (power == true) {
				pow.move();
				pow.draw();
				if (pow.getX() < 0 || pow.getX() > ofGetWidth())
					power = false;
			}
			if (fighter.hasPowerUp() && timer > 700) {
				fighter.powerOff();
			}
		}
		if (movement < 60)
			movement++;
		else
			movement = 0;
		if (enemyLeft == 0)
		{
			power = false;
			level++;
			levelSetUp();
			bombX.clear();
			bombY.clear();
			bombDir.clear();
			if(fighter.hasPowerUp())
				fighter.powerOff();
			
		}
		timer++;
		//cout << level << endl;
}

//--------------------------------------------------------------

void ofApp::spreadShot() {
	for (int i{}; i < shotYLeft.size(); i++)
	{
		int temp = shotYLeft.get(i); // moves shot
		shotYLeft.remove(i);
		shotYLeft.add(i, temp - fighter.getShotSpeed());
		int tempX = shotXLeft.get(i);
		shotXLeft.remove(i);
		shotXLeft.add(i, tempX -1);


		for (int j{}; j < enemyLeft; j++) {  //sees if shot hits enemy
			if (abs(shotYLeft.get(i) - enemies.get(j).getY()) < 25 && abs(shotXLeft.get(i) - enemies.get(j).getX()) < 33)
			{
				enemies.remove(j);
				shotYLeft.remove(i);
				shotXLeft.remove(i);
				enemyLeft--;
				score += 10;
			}
		}
		if (power) //powerup stuff
		{
			if (abs(shotYLeft.get(i) - pow.getY()) < 20 && abs(shotXLeft.get(i) - pow.getX()) < 20) {
				power = false;
				shotYLeft.remove(i);
				shotXLeft.remove(i);
				fighter.powerOn();
				timer = 11;
			}

		}
		if (shotYLeft.get(i) < 0) {  //removes shots off the screen
			shotYLeft.remove(i);
			shotXLeft.remove(i);
		}
	}



}

//--------------------------------------------------------------

void ofApp::levelSetUp() {
	shotX.clear();
	shotY.clear();
	bombX.clear();
	bombY.clear();
	score += 50;
	movement = 0;
	timer = 0;
	if (level == 2)
		enemyLeft = 10 + 10 * level;
	else if (level < 5)
		enemyLeft = 9 + 9 * level;
	else
		enemyLeft = 8 + 8 * level;
	if (level < 3) {
		for (int i{}; i < enemyLeft / 2; i++)
		{
			enemies.add(Enemy1{ ofGetWidth() / enemyLeft * 2 * (int)(i)+ofGetWidth() / enemyLeft,ofGetHeight() / 4,3,3 }); //lower
			enemies.add(Enemy1{ ofGetWidth() / enemyLeft * 2 * (int)(i)+ofGetWidth() / enemyLeft,ofGetHeight() / 3,3,3 }); //higher
		}
	}
	else if(level <5){
		for (int i{}; i < enemyLeft / 3; i++)
		{
			enemies.add(Enemy1{ ofGetWidth() / enemyLeft * 3 * (int)(i)+ofGetWidth() / enemyLeft,ofGetHeight() / 6,3,3 }); //lower
			enemies.add(Enemy1{ ofGetWidth() / enemyLeft * 3 * (int)(i)+ofGetWidth() / enemyLeft,ofGetHeight() / 4,3,3 });
			enemies.add(Enemy1{ ofGetWidth() / enemyLeft * 3 * (int)(i)+ofGetWidth() / enemyLeft,ofGetHeight() / 3,3,3 }); //higher
		}
	}

	else{
		for (int i{}; i < enemyLeft / 4; i++)
		{
			enemies.add(Enemy1{ ofGetWidth() / enemyLeft * 4 * (int)(i)+ofGetWidth() / enemyLeft,ofGetHeight() / 6,3,3 }); //lower
			enemies.add(Enemy1{ ofGetWidth() / enemyLeft * 4 * (int)(i)+ofGetWidth() / enemyLeft,ofGetHeight() / 4,3,3 });
			enemies.add(Enemy1{ ofGetWidth() / enemyLeft * 4 * (int)(i)+ofGetWidth() / enemyLeft,ofGetHeight() / 3,3,3 });
			enemies.add(Enemy1{ ofGetWidth() / enemyLeft * 4 * (int)(i)+ofGetWidth() / enemyLeft,ofGetHeight() *5/12,3,3 }); //higher
		}
	}

}

//--------------------------------------------------------------

void ofApp::pauseScreen() {
	font.load("AGENCYB.ttf", 100);
	font.drawString("Paused", ofGetWidth() / 2 - 165, ofGetHeight() / 3);
	font.load("AGENCYB.ttf", 70);
	font.drawString("Press \"r\" to resume", ofGetWidth() / 2 - 325, ofGetHeight() *3/5);
	font.load("AGENCYB.ttf", 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 356){
		moveLeft = true;
		moveRight = false;
	}
	if (key == 358) {
		moveLeft = false;
		moveRight = true;
	}
	if (key == 32 && shotCycle == 0)
		shotCycle = 1;
	if (key == 13)//enter
		instructionScreen = false;
	if (key == 112)
		pause = true;
	if (key == 114)
		pause = false;
	if (key == 110)
		newGame = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 356)
		moveLeft = false;
	if (key == 358)
		moveRight = false;
	if (key == 32 && shotCycle == 2)
		shotCycle = 0;

}


void ofApp::resetGame() {
	background.load("Background.jpg");
	instructionScreen = true;
	gameOver = false;
	moveLeft = false;
	moveRight = false;
	newGame = false;
	ofSetFrameRate(120);
	level = 1;
	movement = 0;
	timer = 0;
	power = false;
	score = 0;
	sc = "0";
	enemies.clear();
	fighter.revive();
	shotX.clear();
	shotY.clear();
	bombX.clear();
	bombY.clear();
	enemyLeft = 20;
	for (int i{}; i < enemyLeft / 2; i++)
	{
		enemies.add(Enemy1{ ofGetWidth() / enemyLeft * 2 * (int)(i)+ofGetWidth() / enemyLeft,ofGetHeight() / 4,3,3 }); //lower
		enemies.add(Enemy1{ ofGetWidth() / enemyLeft * 2 * (int)(i)+ofGetWidth() / enemyLeft,ofGetHeight() / 3,3,3 }); //higher
	}


}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
