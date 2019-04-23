#include <SoftwareSerial.h>//시리얼통신 라이브러리 호출
int txd_pin = 2; //Tx (보내는핀 설정)at
int rxd_pin = 3; //Rx (받는핀 설정)
SoftwareSerial BTSerial(txd_pin, rxd_pin); //시리얼 통신을 위한 객체선언

int signal_pin_1 = 8;
int signal_pin_2 = 9;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //시리얼모니터
  photoSensorSetup();
  BTSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  photoSensorLoop();
//  BTLoop();
}




void photoSensorSetup() {
    pinMode(signal_pin_1, INPUT);
    pinMode(signal_pin_2, INPUT);
}

void photoSensorLoop() {
  int value_1 = digitalRead(signal_pin_1);
  int value_2 = digitalRead(signal_pin_2);

  if (value_1 == 0) {
    BTSerial.write("a"); // 이것은 버퍼에 저장해서 보내는 것 까지만하고 샘플앱에 프린트되지 않는다.
//    BTSerial.println("a"); // 이건 샘플앱에 바로 프린트된다.
  } else {
    BTSerial.write("A");
  }
  
  if (value_2 == 0) {
    BTSerial.write("b");
  } else {
    BTSerial.write("B");
  }

//  delay(20);
}


//https://www.devicemart.co.kr/goods/view?no=1376882
//아두이노 전원 3.3V에 연결해야 한다. 
//시리얼 모니터의 전송 옵션을 Both NL & CR으로 설정해야 한다.
void BTSetup() {
  BTSerial.begin(9600); //블루투스 시리얼
}

void BTLoop() {
  if (BTSerial.available()) {
    Serial.write(BTSerial.read()); //블루투스측 내용을 시리얼모니터에 출력
  }
  if (Serial.available()) {
    BTSerial.write(Serial.read()); //시리얼 모니터 내용을 블루추스 측에 WRITE
  }
}
