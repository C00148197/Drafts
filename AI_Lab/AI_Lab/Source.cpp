

#include "include.h"
using namespace std;


sf::Sprite playerSprite; //sprite used
sf::Texture playerTexture; //texture used

sf::Sprite aiSprite; //sprite used
sf::Texture aiTexture; //texture used


sf::Time inputTime; //timer for controller input repeat to be implemented.
sf::Int32 msec = 0; //holds time for cont input

const float maxVelo = 3.5f;



const int noOfEnemies = 4; //the max number of enemies in the game
Enemy enemy[noOfEnemies]; //enemy object array
Enemy *pEnemy = &enemy[0];  //pointer to enemy

//
Player player; //player object
Player *pPlayer = &player; //pointer to player

							//std::shared_ptr<Player> player(new Player(0, true, 5000)); //addy for player, problem using atm, using raw pointer for the moment until solved
//Player player(0, true, 1000); //player object
//Player *pPlayer = &player; //pointer to player


int main()
{

	for (size_t i = 0; i < noOfEnemies; i++) //intialise all enemies
	{
		enemy[i].initialise(i); //enemies get passed which enemy they are in the array
	}
	player.initialise(0);

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "zippy zoo" /*, sf::Style::Fullscreen*/);
	window.setVerticalSyncEnabled(true);
	//Screens Setup
	
	sf::Clock clock;
	const float FPS = 1.0f / 60;
	sf::Time elapsedTime;

	//Loops
	while (window.isOpen())
	{
		//INPUT LOOP
		sf::Event e;






		while (window.pollEvent(e))
		{
			//If the X button on the window is press, close the window
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
			//Send input to the current screen
			
		}
	
			inputTime += clock.getElapsedTime(); //########
			msec = inputTime.asSeconds();

		//GAME LOOP
		elapsedTime += clock.restart();	//Add time since last update
		if (elapsedTime.asSeconds() > FPS)	//If it's been long enough...
		{
			//window 
			window.clear();




			for (size_t i = 0; i < noOfEnemies; i++)
			{
				enemy[i].update(window, i, player, elapsedTime); //update enemy objects
			}

			player.update(window, e, inputTime);

			//UPDATE CALL###
			//call methods
			//aiSprite.setScale(sf::Vector2f(0.3f, 0.3f));
			//aiTexture.loadFromFile("ai.png"); //load the help screen
			//aiSprite.setTexture(aiTexture);
			//aiSprite.setPosition(400, 700);
			//window.draw(aiSprite); //draw help screen

			//
			//playerTexture.loadFromFile("player.png"); //load the help screen
			//playerSprite.setTexture(playerTexture);
			//playerSprite.setPosition(200, 700);
			//window.draw(playerSprite); //draw help screen
		
			elapsedTime = sf::Time::Zero;
			//Display current frame
			window.display();
			elapsedTime = elapsedTime.Zero;
		}
	}
	return 0;
}


//
//
//void checkGameStates(sf::RenderWindow& window)
//{
//
//
//	if (gameState == GameState::Upgrade)
//	{
//		if (tiles.getTowerManager()->getTowers()->size() > 0) //if there are towers to upgrade, and there are towers at all, upgrade the tower
//		{
//			tiles.getTowerManager()->upgrade(player);
//		}
//		gameState = GameState::Play; //back to play once upgrade is complete.
//	}
//
//	if (gameState == GameState::Help)
//	{
//		playerTexture.loadFromFile("help.png"); //load the help screen
//		playerSprite.setTexture(playerTexture);
//		window.draw(playerSprite); //draw help screen
//	}
//
//	if (gameState == GameState::GameOver)
//	{
//		playerTexture.loadFromFile("gameover.png"); //load and draw gameover screen
//		playerSprite.setTexture(playerTexture);
//		window.draw(playerSprite);
//		retry.initialize(0, true, player, gameState); //update retry button
//		retry.update(0, 0, 0, gameState, window, player, 0);
//
//		if (sf::Joystick::isButtonPressed(0, 0)) //if retry is pressed.
//		{
//			runOnce = false;
//			gameState = retry.pressed(0, gameState);
//
//			for (size_t i = 0; i < noOfEnemies; i++)  //reinitialise game objects.
//			{
//				enemy[i].initialise(i);
//			}
//
//			hudHealth.Initialise();
//
//			for (size_t i = 0; i < noOfHudButtons; i++)
//			{
//				hudButton[i].initialize(0, false, player, gameState);
//			}
//			player.setScore(0);
//			player.setMoney(100);
//			tiles.getTowerManager()->getTowers()->clear(); ///clear towers for restart
//		}
//	}
//

//}