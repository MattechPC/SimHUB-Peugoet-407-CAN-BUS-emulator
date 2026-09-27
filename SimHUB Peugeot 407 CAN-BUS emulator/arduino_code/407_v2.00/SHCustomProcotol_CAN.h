struct can_frame canMsg1; //0x0F6
struct can_frame canMsg2; //0x036
struct can_frame canMsg3; //0x0B6
struct can_frame canMsg4; //0x128
struct can_frame canMsg5; //0x168
struct can_frame canMsg6; //0x161
struct can_frame canMsg7;
struct can_frame canMsg8;
struct can_frame canMsg9;
struct can_frame canMsg10;

void carregaCAN () {
 
  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x8E; //ignition
  canMsg1.data[1] = 0x00; //coolant temp 100 <-> 160
  canMsg1.data[2] = 0x00; //odo 1
  canMsg1.data[3] = 0x00; //odo 2
  canMsg1.data[4] = 0x00; //odo 3
  canMsg1.data[5] = 0x08;
  canMsg1.data[6] = 0x63;
  canMsg1.data[7] = 0x20;

// can code 2 liga painel
  canMsg2.can_id  = 0x036;
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0x00;
  canMsg2.data[1] = 0x00;
  canMsg2.data[2] = 0x06;
  canMsg2.data[3] = 0x2F; //backlight
  canMsg2.data[4] = 0x01; 
  canMsg2.data[5] = 0x80;
  canMsg2.data[6] = 0x00;
  canMsg2.data[7] = 0x00;

// can code 3 envia rpm velocidade 
  canMsg3.can_id  = 0x0B6;
  canMsg3.can_dlc = 8;
  canMsg3.data[0] = 0x00; //rpm 0x20 -> 1k
  canMsg3.data[1] = 0x00; 
  canMsg3.data[2] = 0x00; //speedo
  canMsg3.data[3] = 0x00;
  canMsg3.data[4] = 0x00;
  canMsg3.data[5] = 0xFF;
  canMsg3.data[6] = 0x00;
  canMsg3.data[7] = 0xA0;


  canMsg4.can_id  = 0x128;
  canMsg4.can_dlc = 8;
  canMsg4.data[0] = 0x00; //rezerwa, ręczny, pasy, dezaktywacja poduszki, swiece
  canMsg4.data[1] = 0x00; 
  canMsg4.data[2] = 0x00; 
  canMsg4.data[3] = 0x00;
  canMsg4.data[4] = 0x00; //swiatla 
  canMsg4.data[5] = 0xA0; 
  canMsg4.data[6] = 0x00; //wyświetlacz skrzyni
  canMsg4.data[7] = 0x00; //C0 manual
  
   // can code 5 luzes painel 2
  canMsg5.can_id  = 0x168;
  canMsg5.can_dlc = 8;
  canMsg5.data[0] = 0x00;
  canMsg5.data[1] = 0x00;
  canMsg5.data[2] = 0x00; 
  canMsg5.data[3] = 0x00; //abs, check
  canMsg5.data[4] = 0x00; 
  canMsg5.data[5] = 0x00;
  canMsg5.data[6] = 0x00; 
  canMsg5.data[7] = 0x00; 
   
    // Combustivel
  canMsg6.can_id  = 0x161;
  canMsg6.can_dlc = 7;
  canMsg6.data[0] = 0x00;
  canMsg6.data[1] = 0x00;
  canMsg6.data[2] = 0x00; //oil temp 105 <-> 200
  canMsg6.data[3] = 0x00; //fuel
  canMsg6.data[4] = 0x00;
  canMsg6.data[5] = 0x00;
  canMsg6.data[6] = 0x00;

  
  //tempomat
  canMsg7.can_id  = 0x228;
  canMsg7.can_dlc = 8;
  canMsg7.data[0] = 0x80;
  canMsg7.data[1] = 0x00;
  canMsg7.data[2] = 0x80;
  canMsg7.data[3] = 0x80; 


  canMsg8.can_id  = 0x1A8;
  canMsg8.can_dlc = 8;
  canMsg8.data[0] = 0x00; //wybór tempomat limiter 40-50-60 tempomat | 80-90-100 limiter
  canMsg8.data[1] = 0; //prędkość
  canMsg8.data[2] = 0; //prędkość
  canMsg8.data[3] = 0x00; 
  canMsg8.data[4] = 0x00;
  canMsg8.data[5] = 0x00; //dzienne
  canMsg8.data[6] = 0xA0; //dzienne
  canMsg8.data[7] = 0x00; //dzienne

  canMsg9.can_id  = 0x1A1;
  canMsg9.can_dlc = 8;
  canMsg9.data[0] = 0x00; //wyswietl
  canMsg9.data[1] = 0x8B; //kod bledu
  canMsg9.data[2] = 0xC6; 
  canMsg9.data[3] = 0x00; //otwieranie drzwi
  canMsg9.data[4] = 0x00;
  canMsg9.data[5] = 0x00;
  canMsg9.data[6] = 0x00;
  canMsg9.data[7] = 0x00;

  canMsg10.can_id  = 0x3F6;
  canMsg10.can_dlc = 7;
  //canMsg9.data[0] = 0x00; 
  //canMsg9.data[1] = 0x00; 
  //canMsg9.data[2] = 0x00; 
  //canMsg9.data[3] = 0x00; 
  //canMsg9.data[4] = 0x00;
  canMsg10.data[5] = 0xC0; //KMH / MPH
  //canMsg9.data[6] = 0x00; 



}
