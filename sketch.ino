#include <Servo.h>

// Define pins for Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;

// Define Servos for Arduino's choices
Servo servo1;  // Rock
Servo servo2;  // Paper
Servo servo3;  // Scissors

// Define Buzzer
const int buzzerPin = 8;

// Variables for ultrasonic sensor
long duration;
int distance;
int userChoice = -1;  // User's choice (0 = Rock, 1 = Paper, 2 = Scissors)
int arduinoChoice;    // Arduino's choice (random)

// Setup function
void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Initialize servos
  servo1.attach(5);  // Servo for Rock
  servo2.attach(3);  // Servo for Paper
  servo3.attach(6);  // Servo for Scissors

  // Initialize the buzzer
  pinMode(buzzerPin, OUTPUT);

  // Set all servos to the default position
  servo1.write(0);  // Rock position
  servo2.write(0);  // Paper position
  servo3.write(0);  // Scissors position
  
  // Seed the random function for randomness
  randomSeed(analogRead(0));
}

// Function to measure distance using the ultrasonic sensor
int getDistance() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send a pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo time
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in cm
  return duration * 0.034 / 2;
}

// Function to determine the user's choice based on distance
void getUserChoice() {
  distance = getDistance();
  
  if (distance > 0 && distance < 10) {
    userChoice = 0; // Rock
    Serial.println("User choice: Rock");
  } else if (distance >= 10 && distance < 20) {
    userChoice = 1; // Paper
    Serial.println("User choice: Paper");
  } else if (distance >= 20) {
    userChoice = 2; // Scissors
    Serial.println("User choice: Scissors");
  } else {
    userChoice = -1; // No valid choice
  }
}

// Function to play the game and get Arduino's random choice
void playGame() {
  // Generate a random choice for Arduino (0 = Rock, 1 = Paper, 2 = Scissors)
  arduinoChoice = random(0, 3);
  
  // Reset all servos first
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  
  // Move the servo corresponding to Arduino's choice
  if (arduinoChoice == 0) {
    servo1.write(90);  // Rock
    Serial.println("Arduino choice: Rock");
  } else if (arduinoChoice == 1) {
    servo2.write(90);  // Paper
    Serial.println("Arduino choice: Paper");
  } else if (arduinoChoice == 2) {
    servo3.write(90);  // Scissors
    Serial.println("Arduino choice: Scissors");
  }

  // Compare user's choice with Arduino's choice and output the result
  if (userChoice != -1) {
    if (userChoice == arduinoChoice) {
      Serial.println("Result: It's a Tie!");
      tone(buzzerPin, 500, 500);  // Beep for 500ms (tie)
    } else if ((userChoice == 0 && arduinoChoice == 2) || 
               (userChoice == 1 && arduinoChoice == 0) ||
               (userChoice == 2 && arduinoChoice == 1)) {
      Serial.println("Result: User Wins!");
      tone(buzzerPin, 1000, 500);  // Higher beep for 500ms (user wins)
    } else {
      Serial.println("Result: Arduino Wins!");
      tone(buzzerPin, 200, 500);  // Lower beep for 500ms (arduino wins)
    }
  } else {
    Serial.println("Invalid user input.");
  }
}

// Main loop
void loop() {
  // Get the user's choice based on hand distance
  getUserChoice();
  
  // If the user made a valid choice, play the game
  if (userChoice != -1) {
    delay(1000);  // Wait a bit before starting the game
    playGame();
    
    // Wait for a while before allowing the next game
    delay(3000);  // 3 seconds delay between rounds
  }
}
