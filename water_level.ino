const int trigPin = 12;  //D6
const int echoPin = 13;  //D7

// defines variables
long duration;
int distance;
int waterLevelInPercentage;

#define SENSOR_LEVEL 150
#define MAX_WATER_LEVEL 110

void setupDistanceSensor() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}
void readDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance == 0) {
    // Invalid value
    publish(MQTT_WATERLEVEL_TOPIC, NULL);
  } else {
    waterLevelInPercentage = round((SENSOR_LEVEL - distance) / (float)MAX_WATER_LEVEL * 100);
    publish(MQTT_WATERLEVEL_TOPIC, String(waterLevelInPercentage).c_str());
  }
}
