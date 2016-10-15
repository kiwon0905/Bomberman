#pragma once
#include "State.h"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML/Window.hpp>

template<class T>
class StateMachine
{
private:
	T* owner; //owner of this state machine
	State<T>* currentState; //currentState
public:
	void tick(float dt);
	void handleEvent(const sf::Event & event, T * owner);
	void draw(sf::RenderWindow & w);
	void changeState(State<T> * newState);

	StateMachine(T * owner_, State<T> * initialState);
	~StateMachine();
};

template<class T>
StateMachine<T>::StateMachine(T* owner_, State<T>* initialState):owner(owner_), currentState(initialState)
{
	initialState->enter(owner);
}

template<class T>
StateMachine<T>::~StateMachine()
{
	currentState->exit(owner);
	delete currentState;
}

template<class T>
void StateMachine<T>::changeState(State<T> * newState)
{
	currentState->exit(owner);
	delete currentState;
	currentState=newState;
	currentState->enter(owner);
}

template<class T>
void StateMachine<T>::handleEvent(const sf::Event & event, T * owner)
{
	currentState->handleEvent(event, owner);
}

template<class T>
void StateMachine<T>::tick(float dt)
{
	currentState->tick(owner, dt);
}

template<class T>
void StateMachine<T>::draw(sf::RenderWindow & window)
{
	currentState->draw(window);
}