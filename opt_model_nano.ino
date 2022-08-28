#include "ModelPro.h"
#include "EEPROM.h"

#define startReffAddress 0 // 0 - 5 
#define startServoSetAddress  10 // 10-11-12-13-14
#define startCanAddress 20 // 20 - 33
#define startColorAddress 40 // 40 - 43

///////////////////////////////////////////////////
int T1 = 80; //เดินหน้าขึ้นไป เส้นมุมฉาก
int T2 = 390; //เดินหน้าขึ้นไป เส้นมุมแหลม
int T3 = 340; //เดินหน้าขึ้นไป เส้นมุมแหลมแบบคู่
int T4 = 10; //เดินหน้าขึ้นไป เส้นมุมฉาก ธรรมดา

int FT1 = 0; //เดินหน้าผ่าน เส้นมุมฉาก
int FT2 = 430; //เดินหน้าผ่าน เส้นมุมแหลม
int FT3 = 380; //เดินหน้าผ่าน เส้นมุมแหลมแบบคู่
int FT4 = 0; //เดินหน้าผ่าน เส้นมุมสี่แยก

int Ref_LLL = EEPROM.read(startReffAddress + 1); //ค่าแสงตเซ็นเซอร์นับแยกซ้าย
int Ref_LL = EEPROM.read(startReffAddress + 2); //ค่าแสงตเซ็นเซอร์ทางซ้ายสุด
int Ref_L = EEPROM.read(startReffAddress + 3); //ค่าแสงตเซ็นเซอร์ด้านในซ้าย
int Ref_C = EEPROM.read(startReffAddress + 4); //ค่าแสงตเซ็นเซอร์ด้านในซ้าย
int Ref_R = EEPROM.read(startReffAddress + 5); //ค่าแสงตเซ็นเซอร์ด้านในขวา
int Ref_RR = EEPROM.read(startReffAddress + 6); //ค่าแสงตเซ็นเซอร์ทางขวาสุด
int Ref_RRR = EEPROM.read(startReffAddress + 7); //ค่าแสงตเซ็นเซอร์นับแยกขวา

int Ref_CR = EEPROM.read(startColorAddress + 1); // ค่าเซนเซอร์มือสีแดงจับกระป๋องขาวดำ

////////// 1 = ดำ ---- 2 = ขาว ------- 0 = ไม่มีกระป๋อง ////////////
int can1 = EEPROM.read(startCanAddress + 1);
int can2 = EEPROM.read(startCanAddress + 2);
int can3 = EEPROM.read(startCanAddress + 3);
int can4 = EEPROM.read(startCanAddress + 4);
int can5 = EEPROM.read(startCanAddress + 5);
int can6 = EEPROM.read(startCanAddress + 6);
int can7 = EEPROM.read(startCanAddress + 7);
int can8 = EEPROM.read(startCanAddress + 8);
int can9 = EEPROM.read(startCanAddress + 9);
int can10 = EEPROM.read(startCanAddress + 10);
int can11 = EEPROM.read(startCanAddress + 11);
int can12 = EEPROM.read(startCanAddress + 12);
int can13 = EEPROM.read(startCanAddress + 13);

int can_check[16] = {
     0 // 0
    ,0 // 1
    ,0 // 2
    ,0 // 3
    ,0 // 4
    ,0// 5
    ,0 // 6
    ,0 // 7
    ,0 // 8
    ,0 // 9
    ,0 // 10
    ,0 // 11
    ,0 // 12
    ,0 // 13
    ,0 // 14
    ,0 // 15
};
int CanPosition[2] = {
  0,
  1
};
///////////////////////////////////////////////////
int logTime = 100; //เวลาในการหยุดหุ่นยนต์
int timeOutLineT1 = 150; //เวลาในการวิ่งออกจากแยก เส้นมุมฉาก
int timeOutLineT2 = 80; //เวลาในการวิ่งออกจากแยก เส้นมุมแหลม
int timeOutLineT3 = 80; //เวลาในการวิ่งออกจากแยก เส้นมุมแหลมแบบคู่
int timeOutLineT4 = 150; //เวลาในการวิ่งออกจากแยก เส้นมุมฉาก ธรรมดา
int timeOutLineT5 = 120; //เวลาในการวิ่งออกจากแยก เส้นมุมฉาก สามแยก

int timeOutLineFT1 = 70; //เวลาในการวิ่งออกจากแยก FF เส้นมุมฉาก
int timeOutLineFT2 = 80; //เวลาในการวิ่งออกจากแยก FF เส้นมุมแหลม
int timeOutLineFT3 = 80; //เวลาในการวิ่งออกจากแยก FF เส้นมุมแหลมแบบคู่
int timeOutLineFT4 = 40; //เวลาในการวิ่งออกจากแยก FF เส้นมุมสี่แยก

int SS_Can = 5; //ระยะเข้าหนีบกระป๋อง cm
int SS_Can_Slow = 12; //ระยะเข้าหนีบกระป๋๋องก่อนวิ่งช้า

int Clasp_Keep = EEPROM.read(startServoSetAddress + 1) == 255 ? 160 : EEPROM.read(startServoSetAddress + 1) ; //ค่าหนีบกระป๋อง
int Clasp_Place = EEPROM.read(startServoSetAddress + 2) == 255 ? 54 : EEPROM.read(startServoSetAddress + 2) ; //ค่าวางกระป๋อง
int Clasp_Set = EEPROM.read(startServoSetAddress + 3) == 255 ? 24 : EEPROM.read(startServoSetAddress + 3) ; //ค่าเซ็ทมือ หลบกระป๋อง

int Raise_Up = EEPROM.read(startServoSetAddress + 4) == 255 ? 45 : EEPROM.read(startServoSetAddress + 4) ; //ค่ายกมือ
int Raise_Down = EEPROM.read(startServoSetAddress + 5) == 255 ? 19 : EEPROM.read(startServoSetAddress + 5) ; //ค่าเอามือลง
///////////////////////////////////////////////////
#define S_LLL map(analog(0),0,1023,0,100) //พอร์ตเซ็นเซอร์นับแยกซ้าย
#define S_LL map(analog(1),0,1023,0,100)  //พอร์ตเซ็นเซอร์ทางซ้ายสุด
#define S_L map(analog(2),0,1023,0,100) //พอร์ตเซ็นเซอร์ด้านในซ้าย
#define S_C map(analog(3),0,1023,0,100) //พอร์ตเซ็นเซอร์ด้านในซ้าย
#define S_R map(analog(4),0,1023,0,100) //พอร์ตเซ็นเซอร์ด้านในขวา
#define S_RR map(analog(5),0,1023,0,100) //พอร์ตเซ็นเซอร์ทางขวาสุด
#define S_RRR map(analog(6),0,1023,0,100) //พอร์ตเซ็นเซอร์นับแยกขวา

#define S_CR map(analog(7),0,1023,0,69) //พอร์ตเซ็นเซอร์สีแดง
#define S_Can 8 //พอร์ตเซ็นเซอร์เซ็คกระป๋อง

#define Clasp 2 //พอร์ต servo หนีบ
#define Raise 1 //พอร์ต servo ยก

int function = 0;

void setup() {
  ok();
}
void loop() {
  if (function == 0) {
    code();
  }
  if (function == 1) {
    setSensor();
  }
  if (function == 2) {
    setServo();
  }
  if (function == 3) {
    setSensorHand();
    Stop(100000);
  }
  if (function == 4) {
    // oledClear();
    // oled(0,10,"LLL: %d ",S_LLL);
    // oled(50,10,"RR: %d ",S_RR);
    // oled(0,20,"LL: %d ",S_LL);
    // oled(50,20,"RRR: %d ",S_RRR);
    // oled(0,30,"L: %d ",S_L);
    // oled(0,40,"C: %d ",S_C);
    // oled(0,50,"R: %d ",S_R);
    // delay(20);
    
    
    // Stop(100000);
  }
  else{
    
    CanPosition[0] = 1; // L = White
    CanPosition[1] = 0; // R = Black

    code();
  }
}
//////////start//////////
void start() {
  Start();
  FF(4);
}
//// CAN PART
void Can1(){
  LL(1, 2);

  InCan(4, 1);

  if(can_check[1] == 0){
    RR(3,2);
    GoTarget(readCan());
  }
}
void Can2(){
  if(can_check[1] == 0){
    RR(1, 2);
  }

  InCan(4, 2);

  if(can_check[2] == 0){
    LL(3,2);
    GoTarget(readCan());
  }
}
void Can3(){
  if(can_check[2] == 0){
    FF(1);
    LL(4, 1);
  }

  InCan(2, 3);

  if(can_check[3] == 0){
    RR(4,1);
    FF(1);
    GoTarget(readCan());
  }
}
void Can4(){
  if(can_check[3] == 0){
    FF(1);
    RR(4, 1);
  }

  InCan(2, 4);

  if(can_check[4] == 0){
    LL(4,1);
    FF(1);
    GoTarget(readCan());
  }
}
void Can5(){
  if(can_check[4] == 0){
    FF(1);
    FF(4);
    LL(1, 2);
  }

  InCan(4, 5);

  if(can_check[5] == 0){
    RR(3,2);
    FF(4);
    FF(1);
    GoTarget(readCan());
  }
}
void Can6(){
  if(can_check[5] == 0){
    FF(1);
    FF(4);
    RR(1, 2);
  }

  InCan(4, 6);

  if(can_check[6] == 0){
    LL(3,2);
    FF(4);
    FF(1);
    GoTarget(readCan());
  }
}
void Can7(){
  if(can_check[6] == 0){
    FF(1);
    FF(4);
    FF(1);
    LL(4, 1);
  }

  InCan(2, 7);

  if(can_check[7] == 0){
    RR(4,1);
    FF(1);
    FF(4);
    FF(1);
    GoTarget(readCan());
  }
}
void Can8(){
  if(can_check[7] == 0){
    FF(1);
    FF(4);
    FF(1);
    RR(4, 1);
  }

  InCan(2, 8);

  if(can_check[8] == 0){
    LL(4,1);
    FF(1);
    FF(4);
    FF(1);
    GoTarget(readCan());
  }
}
void Can9(){
  if(can_check[8] == 0){
    FF(1);
    FF(4);
    FF(1);
    FF(4);
    LL(1, 2);
  }

  InCan(4, 9);

  if(can_check[9] == 0){
    RR(3,2);
    FF(1);
    FF(4);
    FF(1);
    FF(4);
    GoTarget(readCan());
  }
}
void Can10(){
  if(can_check[9] == 0){
    FF(1);
    FF(4);
    FF(1);
    FF(4);
    RR(1, 2);
  }

  InCan(4, 10);

  if(can_check[10] == 0){
    LL(3,2);
    FF(1);
    FF(4);
    FF(1);
    FF(4);
    GoTarget(readCan());
  }
}
void Can11(){
  if(can_check[10] == 0){
    FF(1);
    FF(4);
    FF(1);
    FF(4);
    LL(1, 1);
  }

  InCan(4, 11);

  if(can_check[11] == 0){
    RR(2,1);
    FF(1);
    FF(4);
    FF(1);
    FF(4);
    GoTarget(readCan());
  }
}
void Can12(){
  if(can_check[11] == 0){
    FF(1);
    FF(4);
    FF(1);
    FF(4);
    RR(1, 1);
  }

  InCan(4, 12);

  if(can_check[12] == 0){
    LL(2,1);
    FF(1);
    FF(4);
    FF(1);
    FF(4);
    GoTarget(readCan());
  }
}
void Can13(){
  if(can_check[12] == 0){
    FF(1);
    FF(4);
    FF(1);
    FF(4);
    FF(1);
  }

  InCan(4, 13);

  if(can_check[13] == 0){
    FF(1);
    FF(4);
    FF(1);
    FF(4);
    FF(1);
    GoTarget_Finish(readCan());
  }
}

//// GoTarget
void GoTarget(int cancolor){
  if(cancolor == 0){
    bb();
  }
  else{
    ww();
  }
}
void GoTarget_Finish(int cancolor){
  if(cancolor == 0){
    bb_finish();
  }
  else{
    ww_finish();
  }
}
void bb(){
  RR(4,1);
  LL(6,1);
  PlaceCan("R");
  RR(5,2);
  LL(4,1);
}
void ww(){
  LL(4,1);
  RR(6,1);
  PlaceCan("L");
  LL(5,2);
  RR(4,1);
}

void bb_finish(){
  RR(4,1);
  LL(6,1);
  PlaceCan("R");
  RR(5,2);
  RR(4,1);
  Finish();
}
void ww_finish(){
  LL(4,1);
  RR(6,1);
  PlaceCan("L");
  LL(5,2);
  LL(4,1);
  Finish();
}
//// NO CAN PART
void no_can1_to_can2(){
  TL90();
  FF(3);
}
void no_can2_to_can3(){
  TR90();
  RR(3,2);
  LL(4,1);
}
void no_can3_to_can4(){
  U90();
  FF(4);
}
void no_can4_to_can5(){
  U90();
  RR(4,1);
  LL(1,2);
}
void no_can5_to_can6(){
  TL90();
  FF(3);
}
void no_can6_to_can7(){
  TR90();
  RR(3,2);
  LL(4,1);
}
void no_can7_to_can8(){
  U90();
  FF(3);
}
void no_can8_to_can9(){
  U90();
  RR(4,1);
  LL(1,2);
}
void no_can9_to_can10(){
  TL90();
  FF(3);
}
void no_can10_to_can11(){
  TR90();
  RR(3,1);
}
void no_can11_to_can12(){
  TL90();
  LL(2,2);
}
void no_can12_to_can13(){
  TR90();
  RR(2,3);
}
void no_can13_to_finish(){
  TR90();
  FF(1);
  FF(4);
  FF(1);
  FF(4);
  FF(1);
  FF(4);
  Finish();
}
