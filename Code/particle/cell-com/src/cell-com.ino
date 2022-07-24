/*
 * Project cell-com
 * Description: Cellular communication with onboard micro controller via serial interface
 * Author: Ethan Vosburg
 * Date: July 21, 2022
 */

// setup() runs once, when the device is first turned on.

#include <JsonParserGeneratorRK.h>

int led = D7;  // The on-board LED


void setup() {
  pinMode(led, OUTPUT);
  Particle.subscribe("waypoint_payload", myHandler);
}

// void loop() {
//   digitalWrite(led, HIGH);   // Turn ON the LED

//   String temp = String(random(60, 80));
//   Particle.publish("DATA", temp, PRIVATE);
//   delay(10000);               // Wait for 30 seconds

//   digitalWrite(led, LOW);    // Turn OFF the LED
//   delay(10000);               // Wait for 30 seconds
// }

void myHandler(const char *eventName, const char *data){
  JsonParser parser;
  Serial.print(parser.addString(data));
  parser.parse();
  Serial.print(data);

  String temp;
  int waypoint_count = parser.getReference().key("waypoint_count").valueInt();

  for(int i = 0; i <= waypoint_count; i++){
    temp = parser.getReference().key("waypoints").key("long"+ String(i)).valueString();
    // parser.getOuterValueByKey("waypoint_count", temp);
    Serial.print(temp);
    delay(100);
    Particle.publish("DATA", temp, PRIVATE);
  }
}

