#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

// Define pins for sensors and actuators
#define IR_SENSOR_1 2 // Parking Spot 1
#define IR_SENSOR_2 3 // Parking Spot 2
#define TRIG_PIN 4    // Ultrasonic Trigger
#define ECHO_PIN 5    // Ultrasonic Echo
#define SERVO_PIN 17   // Servo Control Pin

// Create an OLED display object
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Initialize components
Servo servo;

void setup() {
  // Set pin modes for IR sensors and ultrasonic sensor
  pinMode(IR_SENSOR_1, INPUT);
  pinMode(IR_SENSOR_2, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Attach the servo motor to the specified pin
  servo.attach(SERVO_PIN);
  
  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Use the correct I2C address
  display.clearDisplay();
  display.setTextSize(1.5); // Increased font size
  display.setTextColor(SSD1306_WHITE);
  
  // Set the initial position of the servo motor (barrier up)
  servo.write(0); // Start with the flap closed
}

void loop() {
  // Read the state of the IR sensors
  int ir1 = digitalRead(IR_SENSOR_1);
  int ir2 = digitalRead(IR_SENSOR_2);
  
  // Variables to store the duration measured by the ultrasonic sensor
  long duration;

  // Trigger the ultrasonic sensor to send a pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Measure the duration of the pulse returned by the ultrasonic sensor
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance based on the duration
  long distance = (duration / 2) / 29.1;

  // Clear the OLED display
  display.clearDisplay();
  
  // Draw a border around the display
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  
  // Initialize available spots count
  int availableSpots = 0;

  // Check parking availability based on IR sensors
  if (ir1 == HIGH) availableSpots++; // Spot 1 available
  if (ir2 == HIGH) availableSpots++; // Spot 2 available

  // Display parking availability
  display.setCursor(10, 10);
  if (availableSpots > 0) {
    display.print("Parking Available");
  } else {
    display.print("No Parking Spots");
  }

  // Display the number of available parking spots
  display.setCursor(10, 40);
  display.print("Available: ");
  display.print(availableSpots);

  // If a vehicle is detected within range
  if (distance < 10) {
    if (availableSpots > 0) {
      servo.write(90); // Move the servo to open the flap
      delay(3000); // Keep the flap open for 2 seconds
      servo.write(0); // Close the flap after opening
    }
  }
  
  // Display everything on the OLED
  display.display();
  
  // Short delay to avoid rapid updates
  delay(500); // Adjust this delay for desired refresh rate
}
