#pragma once 

class GameObject {
public :
	virtual void update() = 0 ; 
	virtual void render() = 0 ; 
protected :
	int health ; 
	int x ,y ;
	int time_since_last_damage ;
}; 
