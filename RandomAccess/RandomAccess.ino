#include <MazeRunner.h>
#include "Arduino.h"
#include <OrangutanMotors.h>
#include <OrangutanLCD.h>
#include <OrangutanBuzzer.h>
#include <OrangutanPushbuttons.h>
#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanAnalog.h>
#include <OrangutanBuzzer.h>

/*
  __  __                 ____                              
 |  \/  | __ _ _______  |  _ \ _   _ _ __  _ __   ___ _ __ 
 | |\/| |/ _` |_  / _ \ | |_) | | | | '_ \| '_ \ / _ \ '__|
 | |  | | (_| |/ /  __/ |  _ <| |_| | | | | | | |  __/ |   
 |_|  |_|\__,_/___\___| |_| \_\\__,_|_| |_|_| |_|\___|_|   

 Event created by Aisha Animashaun, Andrew Gillard, Georgia Isaac, Jamie Tizzard and Manav Gupta

*/
 straight_max_speed = 60;
  turning_max_speed = 80;
  delay_ms = 175;
  unit_time = 260.0;

  white_threshold = 100;
  grey_threshold = 200;
  black_threshold = 600;
     
MazeRunner bot = MazeRunner(straight_max_speed, turning_max_speed, delay_ms, unit_time, white_threshold, grey_threshold, black_threshold);

char path[100] = "";
unsigned char path_length = 0; // How many turns has the robot done?
unsigned int availableDirs[3] ;

/* Initializes the 3pi, displays a welcome message, calibrates, 
   and plays the initial music. */
void setup() {
    bot.setupRobot();
}

/*This function decides which way to turn during the learning phase of
  maze solving.  It uses the variables found_left, found_straight, and
  found_right, which indicate whether there is an exit in each of the
  three directions, applying the "left hand on the wall" strategy. */
char select_turn(unsigned char found_left, unsigned char found_straight, unsigned char found_right)
{
    // Make a decision about how to turn.  The following code
    // implements a left-hand-on-the-wall strategy, where we always
    // default to left turns first if found.
    
    if (found_left)
        return 'L';
    else if (found_straight)
        return 'S';
    else if (found_right)
        return 'R';
    else
        return 'B';
}

/* This is the brain of the robot. Everything done within here is
   what the robot will do after setting up. */
void loop()
{
    // Loop until we have solved the maze.
    
    // FIRST MAIN LOOP BODY
    bot.straightUntilIntersection();
    
    bot.directionsAvailable(availableDirs);

    while (bot.isEndOfMaze()) {
        bot.stop();
    }
    
    delay(1000);

    bot.turn(select_turn(availableDirs[0], availableDirs[1], availableDirs[2]));

    delay(1000);
    
    // Solved the maze!

    
}
