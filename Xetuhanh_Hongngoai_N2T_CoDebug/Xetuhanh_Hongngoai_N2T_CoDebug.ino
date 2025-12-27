/*====================================
  XE TỰ HÀNH - DEBUG SERIAL MONITOR
  Driver: L9110
  Board : Arduino Nano
====================================*/

// --------- CHÂN CẢM BIẾN ----------
#define SENSOR_LEFT   A2
#define SENSOR_MID    A1
#define SENSOR_RIGHT  A0

// --------- CHÂN ĐỘNG CƠ ----------
#define A1B 6
#define A1A 9
#define B1B 10
#define B1A 11

int speedMotor = 180;

// Lưu trạng thái cảm biến
int leftSensor, midSensor, rightSensor;

void setup() {
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_MID, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);

  Serial.begin(9600);
  Serial.println("=== XE TU HANH BAT DAU ===");

  stopMotor();
}

void loop() {

  readSensors();
  printSensorStatus();

  // ----- THUẬT TOÁN ĐIỀU KHIỂN -----

  if (leftSensor == 0 && midSensor == 0 && rightSensor == 0) {
    Serial.println(">> Chay thang");
    forward();
  }
  else if ((rightSensor == 1 && midSensor == 0 && leftSensor == 0) ||
           (rightSensor == 1 && midSensor == 1 && leftSensor == 0)) {
    Serial.println(">> Re trai");
    turnLeft();
  }
  else if ((leftSensor == 1 && midSensor == 0 && rightSensor == 0) ||
           (leftSensor == 1 && midSensor == 1 && rightSensor == 0)) {
    Serial.println(">> Re phai");
    turnRight();
  }
  else if (leftSensor == 1 && midSensor == 1 && rightSensor == 1) {
    Serial.println(">> Vat can truoc mat - Lui xe");
    backward();
    delay(2000);
    stopMotor();
  }

  Serial.println("-------------------------");
  delay(200);
}

// --------- HÀM ĐỌC CẢM BIẾN ---------
void readSensors() {
  leftSensor  = digitalRead(SENSOR_LEFT);
  midSensor   = digitalRead(SENSOR_MID);
  rightSensor = digitalRead(SENSOR_RIGHT);
}

// --------- HÀM IN TRẠNG THÁI --------
void printSensorStatus() {
  Serial.print("Cam bien [T-G-P]: ");
  Serial.print(leftSensor);
  Serial.print(" - ");
  Serial.print(midSensor);
  Serial.print(" - ");
  Serial.println(rightSensor);
}

// --------- HÀM ĐIỀU KHIỂN ĐỘNG CƠ ----
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
