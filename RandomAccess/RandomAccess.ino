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
double modifier = 1;
int straightMaxSpeed = 60 * modifier;
int turningMaxSpeed = 80 * modifier;
int delayMs = 175 / modifier;
double unitTime = 260.0;

int whiteThreshold = 100;
int greyThreshold = 200;
int blackThreshold = 600;

MazeRunner bot = MazeRunner(straightMaxSpeed, turningMaxSpeed, delayMs, unitTime, whiteThreshold, greyThreshold, blackThreshold);

char path[100] = "";
unsigned char path_length = 0; // How many turns has the robot done?
unsigned int availableDirs[3] ;

/*  Initializes the 3pi, displays a welcome message, calibrates,
    and plays the initial music. */
void setup() {
    bot.setupRobot();
}

/*  This function decides which way to turn during the learning phase of
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

int degreesFromTurn(char c) {
    if (c == 'S') {
        return 0;
    } else if (c == 'R') {
        return 90;
    } else if (c == 'B') {
        return 180;
    } else if (c == 'L') {
        return 270;
    }
}

char degreesToTurn(int t) {
    if (t == 0) {
        return 'S';
    } else if (t == 90) {
        return 'R';
    } else if (t == 180) {
        return 'B';
    } else if (t == 270) {
        return 'L';
    }
}
void simplifyPath() {
    while ( path_length > 2 && path[path_length - 2] == 'B') {
        int total = degreesFromTurn(path[path_length-1]) + degreesFromTurn(path[path_length - 2]) + degreesFromTurn(path[path_length - 3]) % 360;

        path[path_length - 3] = degreesToTurn(total);
    }
}

void printPath() {
    OrangutanLCD::clear();
   // OrangutanLCD::gotoXY(0, 0);
  OrangutanLCD::print(path);
  delay(1000);
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
    
    delay(200);

    path[path_length] = select_turn(availableDirs[0], availableDirs[1], availableDirs[2]);
    bot.turn(path[path_length]);
    path_length++;
    
    //simplifyPath();

    printPath();
    
    

    delay(200);
    
    // Solved the maze!

    
}
