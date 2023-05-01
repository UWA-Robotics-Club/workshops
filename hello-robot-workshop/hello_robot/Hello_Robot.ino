// Include Libraries
#include "Servo.h"
#include "String.h"

// Pin Definitions
#define SERVO_PIN       2
#define ECHO_PIN        6
#define TRIG_PIN        7

// Define servo object and declare variables
Servo servo;
long duration, cm;     
int limit = 15;         // this variable sets the limit of our sensor - robot only waves if something is within 15 cm

/**
 * This function is run once before the loop function
 * Put initialising code in here
 */
void setup() 
{   
    // Connect sensors and servo
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    servo.attach(SERVO_PIN);

    // wait for serial port to connect
    Serial.begin(9600);
    while (!Serial); 
    Serial.println("Starting");
    
}

/**
 * This is the main part of the code, and this function is run over and over again
 * 1. Get the pulse travel time
 * 2. Calculate the distance travelled
 * 3. Print the distance to the Serial Monitor
 * 4. If an object is close enough, make the robot wave
 */
void loop() 
{
    duration = get_pulse_duration();
    cm = ms_to_cm(duration);
    Serial.println("Distance is: " + String(cm));
    if (cm < limit) {wave(0, 40);}
}

/**
 * Send a pulse to the ultrasonic sensor, then count how long it takes for the pulse to return
 */
long get_pulse_duration() { 
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    return pulseIn(ECHO_PIN, HIGH);
}

/**
 * Convert between ultrasonic signal time (in microseconds) and distance travelled (centimetres)
 * Using formula d = v * t
 */
long ms_to_cm(long microseconds) {          
    double speed_sound = 0.0343;            // in centimetres per microseconds
    return microseconds * speed_sound / 2;  // divide by 2 since the signal travels forwards and backwards
}

/**
 * Slowly move the servo between angle1 and angle2
 * Angle2 must be greater than Angle1
 */
void wave(int angle1, int angle2) {   
    // Starting at angle1, increment the servo angle until it is angle2             
    for (int pos = angle1; pos < angle2; pos++) {  
        servo.write(pos);
        delay(10);
    }
    delay(400);

    // Starting at angle2, decrement the servo angle until it is angle1 
    for (int pos = angle2; pos > angle1; pos--) {
        servo.write(pos);
        delay(10);
    }
    delay(400);
}
