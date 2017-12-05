
#include "Enemy.h"
using namespace std;

Enemy::Enemy() {}
Enemy::~Enemy() {} //deconstructor

void Enemy::initialise(int i)
{
	if (i == 0) {
		m_texture.loadFromFile("sq.png"); //reset relevant vars
		m_image.setTexture(m_texture); //apply texture to image
		m_position = sf::Vector2f(436 + (128), 700); //offset each enemy (formerly i* 86) CONST

		m_image.setScale(0.5f, 0.5f);
		offSetX = m_image.getGlobalBounds().width / 2.0f;
		offSetY = m_image.getGlobalBounds().height / 2.0f;
		speed = 1;
		//sf::Rect r = 
		m_image.setOrigin(sf::Vector2f(m_image.getGlobalBounds().width, (m_image.getGlobalBounds().height)));
		cout << m_image.getGlobalBounds().width << endl;
		cout << m_image.getGlobalBounds().height << endl;
	}

	else if (i == 1) {
		m_texture.loadFromFile("enemy2.png"); //reset relevant vars
		m_image.setTexture(m_texture); //apply texture to image
		m_position = sf::Vector2f(736 + (128), 700); //offset each enemy (formerly i* 86) CONST
		m_image.setScale(0.2f,0.2f);
		offSetX = m_image.getGlobalBounds().width / 2.0f;
		offSetY = m_image.getGlobalBounds().height / 2.0f;
		speed = 1;
		m_image.setOrigin(sf::Vector2f(m_image.getGlobalBounds().width, (m_image.getGlobalBounds().height)));
		clocker.restart();
		timer = sf::Time::Zero;
	}

	else if (i == 2) {
		m_texture.loadFromFile("enemy3.png"); //reset relevant vars
		m_image.setTexture(m_texture); //apply texture to image
		m_position = sf::Vector2f(1036 + (128), 700); //offset each enemy (formerly i* 86) CONST
		m_image.setScale(0.1f, 0.1f);
		offSetX = m_image.getGlobalBounds().width / 2.0f;
		offSetY = m_image.getGlobalBounds().height / 2.0f;
		speed = 1;
		m_image.setOrigin(sf::Vector2f(m_image.getGlobalBounds().width, (m_image.getGlobalBounds().height)));
	}

	else if (i == 3) {
		m_texture.loadFromFile("sq2.png"); //reset relevant vars
		m_image.setTexture(m_texture); //apply texture to image
		m_position = sf::Vector2f(836 + (128), 200); //offset each enemy (formerly i* 86) CONST
		m_image.setScale(0.5f, 0.5f);
		offSetX = m_image.getGlobalBounds().width / 2.0f;
		offSetY = m_image.getGlobalBounds().height / 2.0f;
		speed = 1;
		m_image.setOrigin(sf::Vector2f(m_image.getGlobalBounds().width, (m_image.getGlobalBounds().height)));
	}
	endDegrees = 0;
	lastDegrees = 0;
	m_isAlive = false; //for test only

	

	minSpeed = 0;
	maxSpeed = 4;
	
	//m_image.setScale(0.3f, 0.3f);
	//m_image.rotate(-90); //maybe set this before the game starts with the player's respective atan blah blah

	m_isAlive = true;
	
	m_radius = 50;
	m_timeToTarget = 1;

	orient = 0;

	currentWaypoint = 0; //head to first waypoint at first.
	int hund = 100;
	m_waypoint.reserve(5);
//	cout << std::to_string(m_waypoint.size()) << endl;


	random_device rando; //rng 
	mt19937 gen(rando());
	uniform_int_distribution<> dist(0, 1);
	uniform_int_distribution<> dist2(0, 2);
	rPath = dist(gen); //select 
	//m_image.setOrigin(16, 16);
	m_waypoint.clear(); //if game restarts we want a fresh vector




}

//if enemies are alive, they should be doing stuff
void Enemy::update(sf::RenderWindow& window, float i, Player target, sf::Time t)
{

	timer += clocker.getElapsedTime();


	lastUp = t;



 if (i == 1)
	{

	 m_velocity.x = sin((3.14 / 180)*orient) * speed;// * t.asSeconds();

	 m_velocity.y = cos((3.14 / 180)*orient)* speed; //* t.asSeconds();

		Wander(target);


		//orient = ((orient) + 360) ; //even it out.

		if (orient < 0)
		{
			orient = (360) - (-orient);
		}

		m_position += m_velocity;

		int tempOri = orient;

		tempOri += 360;

		tempOri = tempOri % 360;
		tempOri *= -1;

		if (i != 2)
		{
			m_image.setRotation((tempOri + 180));
		}
		else {
			m_image.setRotation(tempOri); //flee points away
		}




		m_image.setPosition(m_position); //set position of sprite
	}



	if (m_position.y > 1180)
	{
		m_position.y = 0;
	}
	else if (m_position.y < -100)
	{
		m_position.y = 1080;
	}
	if (m_position.x > 2020)
	{
		m_position.x = 0;
	}
	else if (m_position.x < -100)
	{
		m_position.x = 1920;
	}




	window.draw(m_image);




}

//flee Velocity = my.position - target.position

float Enemy::getOrient(float orientation, sf::Vector2f velocity, Player target)
{


	//CGPoint originPoint = CGPointMake(endingPoint.x - startingPoint.x, endingPoint.y - startingPoint.y); // get origin point to origin by subtracting end from start
	//float bearingRadians = atan2f(originPoint.y, originPoint.x); // get bearing in radians
	//float bearingDegrees = bearingRadians * (180.0 / M_PI); // convert to degrees
	//bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees)); // correct discontinuity
	//return bearingDegrees;


	///m_velocity = target.getPosition() - m_position; //getcentresmayb



	float bearingRad = atan2f(target.getPosition().x - m_position.x, target.getPosition().y - m_position.y);
	float bearingDegrees = bearingRad * (180 / 3.14);
	bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees));

	return bearingDegrees;




	//float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;

	//
	//mag = sqrt(mag); //length of vector

	//if (mag > 0) //if valid vector, calc new ori
	//{
	//	cout << mag << endl;
	//	return atan2(target.getPosition().y, target.getPosition().x);
	//}

	//return 0; //else return same ori
}


void Enemy::Flee(Player target)
{

	m_velocity = sf::Vector2f(m_position.x+offSetX, m_position.y+offSetY) - sf::Vector2f(target.getPosition().x +offSetX, target.getPosition().y+offSetY); //getcentresmayb

	//m_velocity =  m_position - target.getPosition();

	float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;
	mag = sqrt(mag); //length of vector
	m_velocity = m_velocity / mag;
	//orient = getOrient(orient, m_velocity, target);
	//m_velocity = normalize(velocity)
	m_velocity = m_velocity * speed;

	orient = getOrient(orient, m_velocity, target);
}


void Enemy::Wander(Player target)
{
	sf::Vector2f force;

	timer += clocker.getElapsedTime();




	if (timer.asSeconds() > 5)
	{
		//cout << "TIMERW: " << m_timer.asSeconds() << endl;;

		m_velocity = sf::Vector2f(target.getPosition().x + offSetX, target.getPosition().y + offSetY) - sf::Vector2f(m_position.x + offSetX, m_position.y + offSetY); //getcentresmayb



		float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;

		mag = sqrt(mag); //length of vector

		m_velocity = m_velocity / mag;



		random_device rando; //rng 
		mt19937 gen(rando());
		uniform_int_distribution<> dist(-1, 1);

		rPath = dist(gen); //select 

		orient = getOrient(orient, m_velocity, target);

		cout << "case TIMER" << endl;
		rPath = dist(gen); //select 
		clocker.restart();
		timer = sf::Time::Zero;


		orient = orient + 10 * rPath;

	}
	//	rPath -= 1;


	//cout << "rpath: " << rPath << endl;
	sf::Vector2f temp = sf::Vector2f(-sin(orient), cos(orient));
	temp *= speed;


}

float Enemy::Arrive(Player target)
{
	sf::Vector2f temp = sf::Vector2f(target.getPosition().x + offSetX, target.getPosition().y + offSetY) - sf::Vector2f(m_position.x + offSetX, m_position.y + offSetY); //getcentresmayb
	float mag = temp.x * temp.x + temp.y * temp.y;
	mag = sqrt(mag);


	if (mag < target.getRadius())
	{
		m_velocity = sf::Vector2f(0, 0);
		return 0; //mayb this should be dist inverse or w/e
	}
	else
	{
		m_velocity = temp; //
		m_velocity = m_velocity / m_timeToTarget;
		if (mag > speed)
		{
			m_velocity = m_velocity / mag;
			m_velocity *= speed;
		}
		orient = getOrient(orient, m_velocity, target);
	}

}

void Enemy::Seek(Player target)
{


	//m_velocity = target.getPosition() - m_position; //getcentresmayb
	m_velocity = sf::Vector2f(target.getPosition().x + offSetX, target.getPosition().y + offSetY) - sf::Vector2f(m_position.x + offSetX, m_position.y + offSetY) ; //getcentresmayb

	float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;

	mag = sqrt(mag); //length of vector

	m_velocity = m_velocity / mag;

	//m_velocity = normalize(velocity)
	m_velocity = m_velocity * speed;

	orient = getOrient(orient, m_velocity, target);



	Arrive(target);
}


//function getNewOrientation(currentOrientation, velocity)
//If(velocity.length() > 0) then
//// Note atan2 returns an rotation in radians which you 
//// may want to convert to degrees.
//return atan2(-currentXposition, currentZposition)
//Else
//return currentOrientation


//
//
//Velocity = target.position - my.position
//Velocity = normalize(velocity)
//Velocity = velocity * maxSpeed
//Orientation = getNewOrientation(orientation, velocity)


float Enemy::getHealth()
{
	return m_health;
}

bool Enemy::getAlive()
{
	return m_isAlive;
}

sf::Vector2f Enemy::getPosition()
{
	return m_position;
}

sf::Vector2f Enemy::getVelocity()
{
	return m_velocity;
}

void Enemy::setAlive(bool alive)
{
	m_isAlive = alive;
}

void Enemy::setHealth(float healthChange)
{
	m_health -= healthChange;
}

void Enemy::setPosition(sf::Vector2f position)
{
	m_position = position;
}

void Enemy::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

//
//int rPath;
//random_device rando; //rng 
//mt19937 gen(rando());
//uniform_int_distribution<> dist(0, 1);
//uniform_int_distribution<> dist2(0, 2);
//rPath = dist(gen); //select 


/*if (rotation > 360)
{
rotation -= 360;
}
if (rotation < -360)
{
rotation += 360;
}
*/


/*function rotateOverTime(vector, angle, timespan, elapsedTimeSinceStart) :
partialAngle = elapsedTimeSinceStart / timespan * angle;
rotateZ(vector, partialAngle);*/


//if (rotation == 0)
//{
//	if (degrees < 5)
//	{
//		if (degrees > -5)
//		{
//			m_image.rotate(degrees);
//			degrees += degrees;
//		}
//		else {
//			m_image.rotate(-5);
//			degrees -= 5;
//		}
//	}
//	else if (degrees > 5)
//	{
//		if (degrees < 5)
//		{
//			m_image.rotate(degrees);
//			degrees -= degrees;
//		}
//		else {
//			m_image.rotate(5);
//			degrees -= 5;
//		}
//	}
//}
//m_image.rotate(rotation);

//lastDegrees = degrees;





//if (rotation == 0)
//{
//	rotation = degrees;
//}
//

//rotation = degrees - lastDegrees;

//if (rotation > -0.01 && rotation < 0.01)
//{
//	rotation = 0;
//}

//if (degrees == lastDegrees)
//{
//	rotation = degrees;
//}




//if (degrees != lastDegrees)
//{
//	//degrees = (std::stoi(degrees *-1)) % 360;
//	if (rotation < degrees +1)
//	{
//		if (rotation > degrees -1) //within 2 deg
//		{ 

//			m_image.rotate(1); //somehow find goal angle and only do this if we aren't at it.
//			rotation += 1;
//		
//		}

//	}
//	lastDegrees = degrees;
//}

//if (orient < -1)
//{
//	m_image.rotate((orient +1));
//}
//else {
//	
//}


