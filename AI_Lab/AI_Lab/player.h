#pragma once


#ifndef Player_H
#define Player_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
//Class used for our Player

class Player
{
public:
	Player();
	~Player();

	void initialise(int i);


	void update(sf::RenderWindow& window, sf::Event e, sf::Time t);


	sf::Vector2f getPosition();
	bool getAlive();
	float getHealth();
	sf::Vector2f getVelocity();
	float getRadius();
	void setPosition(sf::Vector2f position);
	void setAlive(bool alive);
	void setHealth(float healthChange);
	void setVelocity(sf::Vector2f velocity);

private:
	float m_radius;
	sf::Vector2f maxVelo;
	sf::Vector2f minVelo;
	int minSpeed;
	int maxSpeed;
	float angle;
	sf::Sprite m_image; //Player sprite
	sf::Texture m_texture;  //Player texture
	int m_size;
	sf::Vector2f m_position; //position of Player
	const float m_maxHealth = 1; //max Player health
	float m_health = m_maxHealth; //Player health
	bool m_isAlive = false; //is Player alive
	std::vector<sf::Vector2f> m_waypoint; //vector of vector2s that hold the waypoints set for the Player
	int currentWaypoint; //the current waypoint in a vector
	const int maxWaypoint = 5; //the maximum number of waypoints in a vector
	int rPath; //random path
	sf::Vector2f m_velocity; //Player velocity
	int PlayerType; //fed a random distrubution to see if Player is type 1, 2 or 3
	float speed;
};

#endif
