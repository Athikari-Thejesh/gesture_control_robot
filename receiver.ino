#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[] = "robot";
int command = 0;

// Motor Driver Connections
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

void setup() {
    Serial.begin(9600);

    // Initialize NRF24L01
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();

    // Set motor driver pins as output
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Stop motors at start
    stopMotors();
}

// Function to stop the motors
void stopMotors() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

// Function to move forward
void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

// Function to move backward
void moveBackward() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

// Function to turn right
void turnRight() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

// Function to turn left
void turnLeft() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void loop() {
    if (radio.available()) {
        radio.read(&command, sizeof(command));
        Serial.print("Received Command: ");
        Serial.println(command);

        // Control motors based on received command
        switch (command) {
            case 1:
                Serial.println("Moving Forward");
                moveBackward();
                break;
            case 2:
                Serial.println("Moving Backward");
                moveForward();
                break;
            case 3:
                Serial.println("Turning Right");
                turnLeft();
                break;
            case 4:
                Serial.println("Turning Left");
                turnRight();
                break;
            default:
                Serial.println("Stopping");
                stopMotors();
                break;
        }
    }
}