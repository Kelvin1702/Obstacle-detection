#include <AFMotor.h>      
#include <Servo.h>              
#include <NewPing.h>      

#define TRIG_PIN A0 // có thể đổi pin theo ý muốn cho cả hai
#define ECHO_PIN A1
#define MAX_DISTANCE 300 // đơn vị cm, khoảng cách tối đa sensor có thể đo được dựa trên thông số nsx.
#define MAX_SPEED 255 // đơn vị theo sensor' s output voltage 10 bit 0-255 pwm (ko có đơn vị thực tế) nếu integrate lên xe thì lấy theo xe còn này là set speed để test case.
#define MAX_SPEED_OFFSET 250 // speed thực tế propotion theo max speed 
#define COLL_DIST 30 // dơn vị cm ( khoảng cách detect có thể chỉnh tùy ý)

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
 
AF_DCMotor leftMotor(2, MOTOR12_8KHZ); // define bit cho motor 2,1 tương ứng trên motor driver là m1,m2 có thể đổi nếu không cắm pin đó. Còn m3 và m4.
AF_DCMotor rightMotor(1, MOTOR12_8KHZ); 
Servo myservo;  

int leftDistance, rightDistance; 
int curDist = 0;
String motorSet = "";
int speedSet = 0;


void setup() {
  myservo.attach(10);   
  myservo.write(90); 
  delay(1000); 
 }
// condition khi gặp vật cản
void loop() {
  myservo.write(90);      // look straight ahead
  delay(90);              // give the servo time to move

  curDist = readPing();   // distance in cm

  /* --- COLLISION-AVOIDANCE LOGIC -------------------- */
  if (curDist < COLL_DIST) {          // too close → stop
      moveStop();                 // hard brake

      /* keep checking until the obstacle is gone       *
       * use a little “hysteresis” so we don’t bounce   */
      do {
         delay(100);                  // short idle
         curDist = readPing();
      } while (curDist < COLL_DIST + 5);
      // falls through when distance ≥ COLL_DIST + 5 cm
  }

  /* --- PATH IS CLEAR -------------------------------- */
  moveForward();          // drive straight ahead
  delay(20);              // brief pause before next check
}

// khúc này trở xuống là define vs formula cho stop vs đi thẳng

int readPing() { 
  delay(70);   
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

void moveStop() {leftMotor.run(RELEASE); rightMotor.run(RELEASE);}  
void moveStop(bool hard = false)   // <-- new parameter
{
  if (hard) {
    // active brake: short the motor terminals together
    leftMotor.run(BRAKE);
    rightMotor.run(BRAKE);
  } else {
    // coast to a halt
    leftMotor.run(RELEASE);
    rightMotor.run(RELEASE);
  }
}

void moveForward() {
    motorSet = "FORWARD";
    leftMotor.run(FORWARD);      
    rightMotor.run(FORWARD); 
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2)    
    
  {
    leftMotor.setSpeed(250);
    rightMotor.setSpeed(250); 
    delay(5);
  }
}




