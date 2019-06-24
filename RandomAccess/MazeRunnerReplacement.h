/*
  MazeRunner.h - Library for the Maze Runner Competition.
  Created by Manav Gupta, Jun 3, 2019.
  Released into the public domain.
*/
#ifndef MazeRunner_h
#define MazeRunner_h


#include "../Pololu3pi/Pololu3pi.h"
#include "../PololuQTRSensors/PololuQTRSensors.h"
#include "../OrangutanMotors/OrangutanMotors.h"
#include "../OrangutanAnalog/OrangutanAnalog.h"
#include "../OrangutanLCD/OrangutanLCD.h"
#include "../OrangutanPushbuttons/OrangutanPushbuttons.h"
#include "../OrangutanBuzzer/OrangutanBuzzer.h"

class MazeRunner
{
  public:
    MazeRunner();
    MazeRunner(int straight, int turning, int delay, double unit, int white, int grey, int black);
    void setupRobot();
    void turn(char dir);
	void roundedTurn(char dir);
    unsigned int straightUntilIntersection();
	unsigned int straightForDistance(unsigned int distanceUnits);
   	void directionsAvailable(unsigned int *direction_array);
	void directionsAvailableNew(unsigned int *direction_array);
    unsigned int isEndOfMaze();
    void stop();
	void setSpeedsFor(int leftMotor, int rightMotor, int delay_ms);
  private:
  	void load_custom_characters();
  	void display_readings(const unsigned int *calibrated_values);
    
     int straight_max_speed = 60;
     int turning_max_speed = 80;
     int delay_ms = 175;
     double unit_time = 260.0;

     int white_threshold = 100;
     int grey_threshold = 200;
     int black_threshold = 600;
};

#endif
