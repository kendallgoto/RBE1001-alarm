//define the states in easy-to-read terms
#include <Arduino.h>
#include <iostream>
using namespace std;
enum {ALARM_OFF, ALARM_ARMED, ALARM_INTRUDER};
int currentState = ALARM_OFF; //start off with the alarm deactivated

void HandleArmingButton();
void handleLaserBroken();
void handleDisarmingButton();
bool CheckArmingButton();
bool CheckIfLaserBroken();
bool CheckDisarmingButton();

//Some pin definitions:
const int buttonArmingPin       = 32;
const int buttonDisarmingPin    = 33;
const int photoPin	            = 27;
const int piezoPin	            = 26;
const int ledPin	            = 14;
const int servoPin	            = 25;

void setup(void)
{
	Serial.begin(115200);
	Serial.println("Hello!");

	pinMode(buttonArmingPin, INPUT_PULLUP); //if we use INPUT_PULLUP, we don't have to have an external pullup resistor
	pinMode(buttonDisarmingPin, INPUT_PULLUP); //if we use INPUT_PULLUP, we don't have to have an external pullup resistor
	pinMode(photoPin, INPUT);
	pinMode(piezoPin, OUTPUT);
	pinMode(ledPin, OUTPUT);
	pinMode(servoPin, OUTPUT);

	delay(500);

	Serial.println("setup() complete");
}

void loop(void)
/*
 * Our loop() is just a set of checker-handler pairs.
 */
{
		//output ADC value
	if(CheckArmingButton()) HandleArmingButton();
	if(CheckIfLaserBroken()) HandleLaserBroken();
	if(CheckDisarmingButton()) HandleDisarmingButton();
}

void HandleArmingButton(void)
{
	if(currentState == ALARM_OFF)
	{
		Serial.println("Arming!");

		//take action: light the LED
		digitalWrite(ledPin, HIGH);

		//take action: you get to ADD CODE HERE to move the servo!
		
		currentState = ALARM_ARMED; //Don't forget to change the state!
	}
}

void HandleLaserBroken(void)
{
	//YOUR CODE HERE!
	
}

void HandleDisarmingButton(void)
{
	//YOUR CODE HERE!
}

/*
 * Code for checking the button -- you don't need to edit this one
 */
bool CheckArmingButton(void)
{
	static int prevButtonState = HIGH; //button up => pin reads HIGH

	bool retVal = false;

	int currButtonState = digitalRead(buttonArmingPin);
	if(prevButtonState != currButtonState)
	{
		delay(10); //this is a cheat for debouncing -- the only place delay is allowed!
		if(currButtonState == LOW) retVal = true;	//button is down => pin reads LOW
	}
	prevButtonState = currButtonState;

	return retVal;
}

/*
 * Code for checking the laser. YOU WILL NEED TO EDIT THIS ONE
 */
enum {DARK, LIGHT};

bool CheckIfLaserBroken(void)
{
	static int prevLaserSensorState = DARK; //the program starts with the laser off
	bool retVal = false;

	//add code here to detect the EVENT of the laser being broken. See the button checker above for hints

	return retVal;
}

/*
 * You'll have to make your own disarming checker!
 */

bool CheckDisarmingButton(void)
{
	bool retVal = false;

	return retVal;
}
