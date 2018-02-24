#include <NewPing.h>

#define SONAR_NUM     2   // Number of sensors.
#define MAX_DISTANCE  70 // Maximum distance in cm.
#define LOOP_INTERVAL 50  // Milliseconds between each loop.
#define START_INTERVAL 33 // Milliseconds between each sensor ping.

unsigned long pingTimer[SONAR_NUM]; // Array containing the time when the next ping to a certain sensor should happen.
int cm[SONAR_NUM];        // Where the distance in cm is stored, referred to each sensor.
int currentSensor = 0;

NewPing sonar[SONAR_NUM] = {     // Sensor object array.
  NewPing(6, 3, MAX_DISTANCE),   // NewPing (trigger pin, echo pin, max distance)
  NewPing(7, 5, MAX_DISTANCE)
  };

void setup() {

  Serial.begin(4800);
  Serial.println("Piano_Stairs v1.0~"); // print as first line in serial the code on the arduino
  Serial.end();
  
  Serial.begin(115200);
  pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) // Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + START_INTERVAL;

  
}
  

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
    if (millis() >= pingTimer[i]) {         // Is this sensor's time to ping?
      pingTimer[i] += LOOP_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == SONAR_NUM - 1) oneSensorCycle(); // Sensor ping cycle complete, do something with the results.
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = -1;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    }
  }
  // Other code that *DOESN'T* analyze ping results can go here.
}

void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
  // The following code would be replaced with your code that does something with the ping results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    //Serial.print(i);
    //Serial.print("=");
    Serial.print(cm[i]);
    Serial.print(",");
  }
  Serial.print("\n");
  //Serial.println();
}
