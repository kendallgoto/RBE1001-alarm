//define the states in easy-to-read terms
#include <Arduino.h>
#include <iostream>
#include <ESP32Servo.h>
enum {ALARM_OFF, ALARM_ARMED, ALARM_INTRUDER};
int currentState = ALARM_OFF; //start off with the alarm deactivated

void HandleArmingButton();
void HandleLaserBroken();
void HandleDisarmingButton();
bool CheckArmingButton();
bool CheckIfLaserBroken();
bool CheckDisarmingButton();

//Some pin definitions:
const int buttonArmingPin       = 33;
const int buttonDisarmingPin    = 32;
const int photoPin	            = 27;
const int piezoPin	            = 26;
const int ledPin	            = 14;
const int servoPin	            = 12;

Servo myservo;  // create servo object to control a servo

void setup()
{
	Serial.begin(115200);
	Serial.println("Hello!");

	pinMode(buttonArmingPin, INPUT_PULLUP); //if we use INPUT_PULLUP, we don't have to have an external pullup resistor
	pinMode(buttonDisarmingPin, INPUT_PULLUP); //if we use INPUT_PULLUP, we don't have to have an external pullup resistor
	pinMode(photoPin, INPUT);
	pinMode(piezoPin, OUTPUT);
	pinMode(ledPin, OUTPUT);
	pinMode(servoPin, OUTPUT);
    myservo.attach(servoPin, 750, 2250);
	delay(500);

	Serial.println("setup() complete");
}

void loop()
{
    Serial.println("Loop");
	if(CheckArmingButton()) HandleArmingButton();
	if(CheckIfLaserBroken()) HandleLaserBroken();
	if(CheckDisarmingButton()) HandleDisarmingButton();
}

void HandleArmingButton()
{
	if(currentState == ALARM_OFF)
	{
		Serial.println("Arming!");

		//take action: light the LED
		digitalWrite(ledPin, HIGH);

		//TODO: spin motor
		myservo.write(135);
		currentState = ALARM_ARMED;
	}
}

void HandleLaserBroken()
{
	//YOUR CODE HERE!
	if(currentState == ALARM_ARMED) {
        Serial.println("Laser Broken!");
        currentState = ALARM_INTRUDER;
        tone(piezoPin, 4186);
    }

}

void HandleDisarmingButton()
{
	//YOUR CODE HERE!
	if(currentState == ALARM_ARMED || currentState == ALARM_INTRUDER) {
        Serial.println("Disarmed!");
        currentState = ALARM_OFF;
        digitalWrite(ledPin, LOW);
        myservo.write(1);
        noTone(piezoPin);
    }
}

/*
 * Code for checking the button -- you don't need to edit this one
 */
bool CheckArmingButton()
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

enum {DARK, LIGHT};
bool CheckIfLaserBroken()
{
	static int prevLaserSensorState = DARK; //the program starts with the laser off
	bool retVal = false;

	//add code here to detect the EVENT of the laser being broken. See the button checker above for hints
	Serial.println(analogRead(photoPin));
    int currentLaserState = (analogRead(photoPin) < 1730) ? LIGHT : DARK;
    if(currentLaserState != prevLaserSensorState) {
        if(currentLaserState == DARK)
            retVal = true;
    }
    prevLaserSensorState = currentLaserState;
	return retVal;
}

/*
 * You'll have to make your own disarming checker!
 */

bool CheckDisarmingButton()
{
    static int prevDisarmState = HIGH; //button up => pin reads HIGH

    bool retVal = false;

    int currButtonState = digitalRead(buttonDisarmingPin);
    if(prevDisarmState != currButtonState)
    {
        delay(10); //debounce
        if(currButtonState == LOW) retVal = true;	//button is down => pin reads LOW
    }
    prevDisarmState = currButtonState;

    return retVal;
}
