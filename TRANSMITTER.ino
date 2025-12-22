#include <MPU6050.h>
#include <nRF24L01.h>

RF24 radio(9, 10); // CE, CSN
const byte address[] = "robot";
MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    mpu.initialize();
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
}

void loop() {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    int command = 0; // Default STOP (0)
    
    if (ay > 10000) command = 1; // FORWARD
    if (ay < -10000) command = 2; // BACKWARD
    if (ax > 10000) command = 3; // RIGHT
    if (ax < -10000) command = 4; // LEFT

    radio.write(&command, sizeof(command));
    Serial.println(command);
    
    delay(200);
}