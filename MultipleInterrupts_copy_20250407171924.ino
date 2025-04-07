#define BUTTON_PIN 2            // Push button connected to digital pin 2
#define TRIG_PIN 3              // Trig pin of ultrasonic sensor connected to digital pin 3
#define ECHO_PIN 4              // Echo pin of ultrasonic sensor connected to digital pin 4
#define LED1_PIN 5              // LED1 connected to digital pin 5
#define LED2_PIN 6              // LED2 connected to digital pin 6

volatile bool isButtonPressed = false;  // Flag for button press
long pulseDuration, measuredDistance;   // To store sensor data

// Interrupt service routine for button press
void onButtonPress() {
  isButtonPressed = true;   // Set the flag when the button is pressed
}

void setup() {
  Serial.begin(9600);

  // Set pin modes for input and output pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  // Set up interrupt to monitor the button press
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonPress, FALLING);

  // Initialize LEDs to off state
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
}

void loop() {
  // Check if button was pressed and toggle LED1
  if (isButtonPressed) {
    isButtonPressed = false;  // Reset the flag
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));  // Toggle the state of LED1
    Serial.println("Button pressed! LED1 state changed.");
  }

  // Trigger the ultrasonic sensor to measure distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the duration of the pulse from the Echo pin
  pulseDuration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  measuredDistance = pulseDuration * 0.0344 / 2;

  // Output the distance to the serial monitor
  Serial.print("Measured Distance: ");
  Serial.print(measuredDistance);
  Serial.println(" cm");

  // Toggle LED2 based on the measured distance
  if (measuredDistance < 20) {
    digitalWrite(LED2_PIN, HIGH);  // Turn on LED2 if distance is less than 20 cm
    Serial.println("LED2 ON: Object detected within 20 cm.");
  } else {
    digitalWrite(LED2_PIN, LOW);  // Turn off LED2 if distance is greater than or equal to 20 cm
    Serial.println("LED2 OFF: Object not detected within 20 cm.");
  }

  delay(500);  // Delay to avoid overwhelming the serial output
}
 //code for muliple interrupts