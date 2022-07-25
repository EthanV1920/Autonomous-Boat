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
  Serial.print("\n");

  int waypoint_count = parser.getReference().key("waypoint_status").key("waypoint_count").valueInt();

  // print_waypoint(waypoint_count, data, parser);
  for(int i = 0; i <= waypoint_count; i++){
    String temp = parser.getReference().key("waypoints").key("long"+ String(i)).valueString();
    // parser.getOuterValueByKey("waypoint_count", temp);
    Serial.print(temp);
    Serial.print("\n");
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    Particle.publish("DATA", temp, PRIVATE);
  }
}

// void print_waypoint(int waypoint_count, const char *data, JsonParser parser){
//   for(int i = 0; i <= waypoint_count; i++){
//     String temp;
//     temp = parser.getReference().key("waypoints").key("long"+ String(i)).valueString();
//     // parser.getOuterValueByKey("waypoint_count", temp);
//     Serial.print(temp + "\n");
//     // delay(100);
//     Particle.publish("DATA", temp, PRIVATE);
//   }
// }