#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <queue>
#include <future>
#include <thread>
#include <vector>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"
#include <chrono>
#include <stdlib.h>
#include <time.h>

// forward declarations to avoid include cycle
class Vehicle;


// FP.3 Define a class „MessageQueue“ which has the public methods send and receive. 
// Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// Also, the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
// Also, there should be an std::condition_variable as well as an std::mutex as private members. 

template <class T>
class MessageQueue
{
public:
	void send(T &&msg);
    T receive();
private:
    std::deque <T> _queue;
    std::condition_variable _cond;
    std::mutex _mute;
};

// FP.1 : Define a class „TrafficLight“ which is a child class of TrafficObject. 
// The class shall have the public methods „void waitForGreen()“ and „void simulate()“ 
// as well as „TrafficLightPhase getCurrentPhase()“, where TrafficLightPhase is an enum that 
// can be either „red“ or „green“. Also, add the private method „void cycleThroughPhases()“. 
// Furthermore, there shall be the private member _currentPhase which can take „red“ or „green“ as its value. 

class TrafficLight: public TrafficObject{
public:
    // constructor / desctructor
	TrafficLight();
  	~TrafficLight();
  
    // getters / setters
  	enum TrafficLightPhase {red, green};
    TrafficLightPhase getCurrentPhase();
    void setCurrentPhase(TrafficLightPhase);

    // typical behaviour methods
  	void waitForGreen();
  	void simulate();

private:
    // typical behaviour methods
  	void cycleThroughPhases();
  	TrafficLightPhase _currentPhase;
  
  	// clock varibales
  	std::chrono::high_resolution_clock::time_point mLastTime;
    std::chrono::high_resolution_clock::time_point mCurrentTime;
  	std::chrono::duration<float, std::milli> diff;
  	float lightPhaseTime;
  

    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.

    std::condition_variable _condition;
    std::mutex _mutex;
  	MessageQueue<TrafficLightPhase> _msgque;
};

#endif