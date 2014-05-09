// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

NewPing sonar; // NewPing setup of pins and maximum distance.

void setup() {
  pinMode(20,OUTPUT);
  digitalWrite(20,LOW);
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}
