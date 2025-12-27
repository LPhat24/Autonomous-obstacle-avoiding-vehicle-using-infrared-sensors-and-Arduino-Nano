/*====================================
  XE TỰ HÀNH - 3 CẢM BIẾN HỒNG NGOẠI
  Driver: L9110
  Board : Arduino Nano
  LE THANH PHAT
====================================*/

// --------- CHÂN CẢM BIẾN ----------
#define SENSOR_LEFT   A2
#define SENSOR_MID    A1
#define SENSOR_RIGHT  A0

// --------- CHÂN ĐỘNG CƠ (L9110) ----
#define A1B 6    // Motor A
#define A1A 9
#define B1B 10   // Motor B
#define B1A 11

int speedMotor = 180;   // tốc độ động cơ (0–255)

void setup() {
  // Cảm biến
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_MID, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);

  // Động cơ
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);

  stopMotor();
}

void loop() {

  int left  = digitalRead(SENSOR_LEFT);
  int mid   = digitalRead(SENSOR_MID);
  int right = digitalRead(SENSOR_RIGHT);

  // ----- THUẬT TOÁN ĐIỀU KHIỂN -----

  if (left == 0 && mid == 0 && right == 0) {
    forward();
  }
  else if ((right == 1 && mid == 0 && left == 0) ||
           (right == 1 && mid == 1 && left == 0)) {
    turnLeft();
  }
  else if ((left == 1 && mid == 0 && right == 0) ||
           (left == 1 && mid == 1 && right == 0)) {
    turnRight();
  }
  else if (left == 1 && mid == 1 && right == 1) {
    backward();
    delay(2000);
    stopMotor();
  }
}

// --------- HÀM ĐIỀU KHIỂN ----------

void forward() {
  analogWrite(A1A, speedMotor);
  analogWrite(A1B, 0);
  analogWrite(B1A, speedMotor);
  analogWrite(B1B, 0);
}

void backward() {
  analogWrite(A1A, 0);
  analogWrite(A1B, speedMotor);
  analogWrite(B1A, 0);
  analogWrite(B1B, speedMotor);
}

void turnLeft() {
  analogWrite(A1A, 0);
  analogWrite(A1B, speedMotor);
  analogWrite(B1A, speedMotor);
  analogWrite(B1B, 0);
}

void turnRight() {
  analogWrite(A1A, speedMotor);
  analogWrite(A1B, 0);
  analogWrite(B1A, 0);
  analogWrite(B1B, speedMotor);
}

void stopMotor() {
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(B1B, LOW);
}
