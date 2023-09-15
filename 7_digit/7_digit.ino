#include <Servo.h>

Servo servos[7]; // Array to hold servo objects

const int servoPins[] = {2, 3, 4, 5, 6, 7, 8}; // Pins connected to servos

void setup() {
  for (int i = 0; i < 7; i++) {
    servos[i].attach(servoPins[i]); // Attach servos to pins
  }
}

void displayDigit(int digit) {
  int patterns[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
  };

  for (int i = 0; i < 7; i++) {
    if (patterns[digit][i] == 1) {
      servos[i].write(90); // Set servo position for 'on' state
    } else {
      servos[i].write(0); // Set servo position for 'off' state
    }
  }
}

void loop() {
  for (int digit = 0; digit < 10; digit++) {
    displayDigit(digit);
    delay(1000); // Delay between digits
  }
}
