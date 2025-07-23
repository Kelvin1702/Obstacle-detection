
#include <AFMotor.h>
//Khúc này khai báo biến thôi trên motor driver á, nếu trên motor driver của mình khác thì bây thay lại.
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);


void setup(){
  int speed = 200;// speed này không phải speed đơn vị vật lý như mình biết nha mà nó là digital bit dựa trên output voltage thôi 0-255max
  // nên là bây muốn set công suất cho nó chạy nhiu thì tùy nha 255 là 100%, còn xe mình có speed thì ko tính do này test demo nên t để const vậy luôn còn nếu muốn 
  // feed về số liệu vật lý thì có công thức convert dưới này nha (áp dụng cho khoảng cách)
// const float   A = 27.86; Volts·cm  (sensor constant)
// const float   B = 0.42; 
// if (adc == 0) return 999.0;(avoid divide-by-zero)
//     float volts = (adc * 5.0) / 1023.0;( assuming 5 V AREF)
//     float dist  = (A / volts) - B;
//     return dist;   
  motor1.setSpeed(speed);
  motor1.run(RELEASE);
  motor2.setSpeed(speed);
  motor2.run(RELEASE);
  motor3.setSpeed(speed);
  motor3.run(RELEASE);
  motor4.setSpeed(speed);
  motor4.run(RELEASE);

 
}

void loop(){
  //Từ khúc này là set condition khi gặp vật cản nè, read data thôi

  int sensor1 = analogRead(A0);
  int sensor2 = analogRead(A1);
  int sensor3 = analogRead(A2);
  int threshold = 300;// khúc này ban đầu t ko biết tưởng là set dc khoảng cách nên t để 300 ( đơn vị 10-bit digital nha search trên mạng thì tương đương 35cm ) 
  // thật ra lấy nguyên cái speed trên làm luôn vẫn dc tại nó chỉ là công suất thôi mà t ko biết nên bên trên set int 200 xuống đây thêm cái 300 nữa chứ nó cũng không 
  // thay đổi khoảng cách gì mấy, mãi gần đây mới biết là chỉnh khoảng cách bằng núm xoay trên cảm biến vl:((

  if (sensor1 < threshold || sensor2 < threshold || sensor3 < threshold) {
    moveStop();           
    delay(500);          
  } else {
    moveForward();       
  }

  delay(50);              // Khúc này tránh bị lag data thôi có cũng ko sao optional
}

//Công thức set bth thôi.
void moveStop(){
  
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward(){

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}


}




