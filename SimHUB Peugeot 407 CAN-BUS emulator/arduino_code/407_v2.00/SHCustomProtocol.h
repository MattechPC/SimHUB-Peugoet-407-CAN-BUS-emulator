#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

#include <Arduino.h>
#include <SPI.h>



class SHCustomProtocol {
private:

public:
  //**** POCZĄTEK NCALC ****

  //Wskazówki
  float rpm;
  int rpm_P;
  float speed;
  int fuel = 0;
  int coolant = 0;
  int oil_temp = 0;

  int bieg;
  long przebieg;
  int tempo_act;
  int tempo_speed;
  int limit_speed;

  String game_type;
  String limit_act;

  //Konfiguracja NCalc
  String engine_type;
  String rpm_type;
  String auto_backlight;
  String auto_ignition;
  String simulate_MPH;
  String copyrights_1;

  //**** KONIEC NCALC ****

  //Debug LEDs
  bool MCP_OK = false;

  bool cluster_ok = false;
  unsigned long cluster_last_time = 0;

  String SimHUB_OK;
  bool SimHUB_status = false;
  unsigned long SimHUB_last_time = 0;

  //Wewnętrzne zmienne
  unsigned long poprzedniCzas = 0;
  unsigned long poprzedniCzas1 = 0;
  unsigned long poprzedniCzas2 = 0;

  int send_coolant;

  //Wygładzenie prędkościomierza
  int smooth_speedo_c;
  int smooth_c;
  float smooth;
  float smooth_speedo;

  //Wygładzenie obrotomierza
  int rpm_sc;
  float rpm_s;

  //Definiowanie warunków dla specyficznych gier
  int game = 0;

  //Licznik przebiegu
  double m1;
  long m2;
  double m3;
  long checksum;
  int m3c;
  int m2c;

  //Kontrolki
  int l_kier;
  int p_kier;
  int pozycyjne;
  int mijania;
  int drogowe;
  int p_przod;
  int p_tyl;
  int rezerwa;
  int check;
  int ABS;
  int retarder;
  int podniesiona;
  int reczny;
  int przebita_opona;
  int pauza = 100;
  int niskie_cisnienie;
  int akumulator;
  int redline;
  int oil;
  int check_indicator;
  int check_indicator_status;
  int ignition;
  int komunikacja;
  int swiatla_on;

  //Wewnętrzne kontrolki
  int overspeed;
  int stop;
  int pauza_time;

  //Tempomat/limiter
  int cc_status;
  int digital_speed;
  int speed_dig;
  int speed_lim_1;
  int speed_lim_2;

  //Zmienne używane do sterowania sekcją błędów wyświetlacza

  int screen = 0;
  int screen_hex = 222;

  bool screen_change = true;
  int errors_count = 0;

  unsigned long obecnyCzas;

  void setup() {
    //Debbuging LEDs
    pinMode(A0, OUTPUT);  //Cluster OK
    pinMode(A1, OUTPUT);  //SimHUB OK
    pinMode(A2, OUTPUT);  //STATUS MCP2515

    SPI.begin();
    mcp2515.reset();
    MCP2515::ERROR status = mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ);

    if (status == MCP2515::ERROR_OK) {
      MCP_OK = true;
      mcp2515.setNormalMode();
      carregaCAN();
    } else {
      MCP_OK = false;
    }
  }

  void debug_LEDs() {
    //MCP2515 status
    if (MCP_OK == true) {
      digitalWrite(A2, HIGH);
    } else {
      digitalWrite(A2, LOW);
    }
    //SimHUB_status status
    if (SimHUB_status == true) {
      digitalWrite(A1, HIGH);
    } else {
      digitalWrite(A1, LOW);
    }
    //Cluster status
    if (cluster_ok == true) {
      digitalWrite(A0, HIGH);
    } else {
      digitalWrite(A0, LOW);
    }
  }


  void SimHUB_status_OK() {
    if (SimHUB_OK == "SimHUB_communication_OK") {
      SimHUB_status = true;
      SimHUB_last_time = millis();
    }
    if (SimHUB_OK && millis() - SimHUB_last_time >= 5000) {
      SimHUB_status = false;
    }
  }

  void cluster_OK() {
    struct can_frame canMsg;

    if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
      if (canMsg.can_id == 0x217 || canMsg.can_id == 0x51F || canMsg.can_id == 0x317) {
        cluster_ok = true;
        cluster_last_time = millis();
      }
    }

    if (cluster_ok && (millis() - cluster_last_time >= 5000)) {
      cluster_ok = false;
    }
  }

  // Sekcja odczytu danych z SimHUB
  void read() {
    game = (FlowSerialReadStringUntil(';').toInt());
    rpm = (FlowSerialReadStringUntil(';').toFloat());
    rpm_P = (FlowSerialReadStringUntil(';').toInt());
    speed = (FlowSerialReadStringUntil(';').toFloat());
    fuel = (FlowSerialReadStringUntil(';').toInt());
    coolant = (FlowSerialReadStringUntil(';').toInt());
    oil_temp = (FlowSerialReadStringUntil(';').toInt());
    bieg = (FlowSerialReadStringUntil(';').toInt());
    l_kier = (FlowSerialReadStringUntil(';').toInt());
    p_kier = (FlowSerialReadStringUntil(';').toInt());
    mijania = (FlowSerialReadStringUntil(';').toInt());
    drogowe = (FlowSerialReadStringUntil(';').toInt());
    p_tyl = (FlowSerialReadStringUntil(';').toInt());
    p_przod = (FlowSerialReadStringUntil(';').toInt());
    check = (FlowSerialReadStringUntil(';').toInt());
    ABS = (FlowSerialReadStringUntil(';').toInt());
    retarder = (FlowSerialReadStringUntil(';').toInt());
    podniesiona = (FlowSerialReadStringUntil(';').toInt());
    reczny = (FlowSerialReadStringUntil(';').toInt());
    przebita_opona = (FlowSerialReadStringUntil(';').toInt());
    pauza = (FlowSerialReadStringUntil(';').toInt());
    niskie_cisnienie = (FlowSerialReadStringUntil(';').toInt());
    akumulator = (FlowSerialReadStringUntil(';').toInt());
    redline = (FlowSerialReadStringUntil(';').toInt());
    ignition = (FlowSerialReadStringUntil(';').toInt());
    komunikacja = (FlowSerialReadStringUntil(';').toInt());
    swiatla_on = (FlowSerialReadStringUntil(';').toInt());
    oil = (FlowSerialReadStringUntil(';').toInt());
    przebieg = (FlowSerialReadStringUntil(';').toInt());
    tempo_act = (FlowSerialReadStringUntil(';').toInt());
    tempo_speed = (FlowSerialReadStringUntil(';').toInt());
    limit_speed = (FlowSerialReadStringUntil(';').toInt());
    game_type = (FlowSerialReadStringUntil(';'));
    engine_type = (FlowSerialReadStringUntil(';'));
    rpm_type = (FlowSerialReadStringUntil(';'));
    auto_backlight = (FlowSerialReadStringUntil(';'));
    auto_ignition = (FlowSerialReadStringUntil(';'));
    simulate_MPH = (FlowSerialReadStringUntil(';'));
    limit_act = (FlowSerialReadStringUntil(';'));
    SimHUB_OK = (FlowSerialReadStringUntil(';'));
    copyrights_1 = (FlowSerialReadStringUntil('\n'));
  }

  void loop() {
    obecnyCzas = millis();
    if (obecnyCzas - poprzedniCzas >= 3000) {
      poprzedniCzas = obecnyCzas;
    }
    if (obecnyCzas <= 1000) {
      canMsg1.data[0] = 0x86;
      canMsg2.data[4] = 0x00;
      CAN_send();
    } else if (obecnyCzas > 1000 && obecnyCzas <= 3000) {
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);

      canMsg1.data[0] = 0x8E;
      canMsg2.data[4] = 0x01;
      rpm = 1000;
      speed = 260;
      coolant = 130;
      oil_temp = 150;
      fuel = 100;
      set_RPM();
      set_speedo();
      set_fuel();
      set_coolant();
      set_oil_temp();
      CAN_send();
    } else if (obecnyCzas > 3000 && obecnyCzas <= 4000) {
      digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      canMsg1.data[0] = 0x86;
      canMsg2.data[4] = 0x00;
      rpm = 0;
      speed = 0;
      coolant = 0;
      oil_temp = 0;
      fuel = 0;
      set_RPM();
      set_speedo();
      set_fuel();
      set_coolant();
      set_oil_temp();
      CAN_send();
    } else if (obecnyCzas > 4000 && obecnyCzas <= 4200) {
      canMsg1.data[0] = 0x8E;
      canMsg2.data[4] = 0x01;
      CAN_send();
    } else if (obecnyCzas > 4200) {
      CAN_send();
      set_RPM();
      CAN_send();
      set_speedo();
      CAN_send();
      set_indicators();
      CAN_send();
      set_fuel();
      CAN_send();
      set_coolant();
      set_indicators();
      CAN_send();
      set_screen();
      CAN_send();
      set_oil_temp();
      CAN_send();
      set_odometer();
      CAN_send();
      set_cruise_control();
      set_indicators();
      CAN_send();
      set_RPM();
      CAN_send();
      set_indicators();
      CAN_send();
      game_detection();
      CAN_send();
      speed_calculations();
      CAN_send();
      set_screen();
      CAN_send();
      set_indicators();
      set_RPM();
      CAN_send();
      set_biegi();
      custom_ncalc();
      CAN_send();
      set_screen();
      CAN_send();
      debug_LEDs();
      cluster_OK();
      SimHUB_status_OK();
    }
  }


  void set_biegi() {

    //Przeliczanie biegów
    if (game_type == "ETS2" || game_type == "ATS") {
      switch (bieg) {
        case -3:  //** R **
          canMsg4.data[6] = 0x10;
          canMsg4.data[7] = 0x00;
          break;
        case -2:  //** R **
          canMsg4.data[6] = 0x10;
          canMsg4.data[7] = 0x00;
          break;
        case -1:  //** R **
          canMsg4.data[6] = 0x10;
          canMsg4.data[7] = 0x00;
          break;
        case 0:  //** N **
          canMsg4.data[6] = 0x20;
          canMsg4.data[7] = 0x00;
          break;
        case 1:  //** 1 **
          canMsg4.data[6] = 0x90;
          canMsg4.data[7] = 0xC0;
          break;
        case 2:  //** 2 **
          canMsg4.data[6] = 0x80;
          canMsg4.data[7] = 0xC0;
          break;
        case 3:  //** 3 **
          canMsg4.data[6] = 0x70;
          canMsg4.data[7] = 0xC0;
          break;
        case 4:  //** 4 **
          canMsg4.data[6] = 0x60;
          canMsg4.data[7] = 0xC0;
          break;
        case 5:  //** 5 **
          canMsg4.data[6] = 0x50;
          canMsg4.data[7] = 0xC0;
          break;
        case 6:  //** 6 **
          canMsg4.data[6] = 0x40;
          canMsg4.data[7] = 0xC0;
          break;
        case 7:  //** 7 **
          canMsg4.data[6] = 0x30;
          canMsg4.data[7] = 0x00;
          break;
        default:
          break;
      }
      if (bieg >= 8) {
        canMsg4.data[6] = 0x30;
        canMsg4.data[7] = 0x00;
      }
    }
    if (game_type == "FH5") {

      switch (bieg) {
        case 0:  //** R **
          canMsg4.data[6] = 0x10;
          canMsg4.data[7] = 0x00;
          break;
        case 1:  //** 1 **
          canMsg4.data[6] = 0x90;
          canMsg4.data[7] = 0xC0;
          break;
        case 2:  //** 2 **
          canMsg4.data[6] = 0x80;
          canMsg4.data[7] = 0xC0;
          break;
        case 3:  //** 3 **
          canMsg4.data[6] = 0x70;
          canMsg4.data[7] = 0xC0;
          break;
        case 4:  //** 4 **
          canMsg4.data[6] = 0x60;
          canMsg4.data[7] = 0xC0;
          break;
        case 5:  //** 5 **
          canMsg4.data[6] = 0x50;
          canMsg4.data[7] = 0xC0;
          break;
        case 6:  //** 6 **
          canMsg4.data[6] = 0x40;
          canMsg4.data[7] = 0xC0;
          break;
        case 7:  //** D **
          canMsg4.data[6] = 0x30;
          canMsg4.data[7] = 0x00;
          break;
        case 11:  //** N **
          canMsg4.data[6] = 0x20;
          canMsg4.data[7] = 0x00;
          break;
        /*case 8:  //** D **
          canMsg4.data[6] = 0x30;
          canMsg4.data[7] = 0xC0;
          break;
          */
        default:
          break;
          if (bieg > 7 && bieg != 11) {
            canMsg4.data[6] = 0x30;
            canMsg4.data[7] = 0x00;
          }
      }
    }

    if (game_type == "CodemastersGrid2") {
      switch (bieg) {
        case 10:  //** R **
          canMsg4.data[6] = 0x10;
          canMsg4.data[7] = 0x00;
          break;
        case 0:  //** N **
          canMsg4.data[6] = 0x20;
          canMsg4.data[7] = 0x00;
          break;
        case 1:  //** 1 **
          canMsg4.data[6] = 0x90;
          canMsg4.data[7] = 0xC0;
          break;
        case 2:  //** 2 **
          canMsg4.data[6] = 0x80;
          canMsg4.data[7] = 0xC0;
          break;
        case 3:  //** 3 **
          canMsg4.data[6] = 0x70;
          canMsg4.data[7] = 0xC0;
          break;
        case 4:  //** 4 **
          canMsg4.data[6] = 0x60;
          canMsg4.data[7] = 0xC0;
          break;
        case 5:  //** 5 **
          canMsg4.data[6] = 0x50;
          canMsg4.data[7] = 0xC0;
          break;
        case 6:  //** 6 **
          canMsg4.data[6] = 0x40;
          canMsg4.data[7] = 0xC0;
          break;
        case 7:  //** D **
          canMsg4.data[6] = 0x30;
          canMsg4.data[7] = 0xC0;
          break;
        default:
          break;
      }
    }
    if (game_type == "CodemastersDirt4") {
      switch (bieg) {
        case -1:  //** R **
          canMsg4.data[6] = 0x10;
          canMsg4.data[7] = 0x00;
          break;
        case 0:  //** N **
          canMsg4.data[6] = 0x20;
          canMsg4.data[7] = 0x00;
          break;
        case 1:  //** 1 **
          canMsg4.data[6] = 0x90;
          canMsg4.data[7] = 0xC0;
          break;
        case 2:  //** 2 **
          canMsg4.data[6] = 0x80;
          canMsg4.data[7] = 0xC0;
          break;
        case 3:  //** 3 **
          canMsg4.data[6] = 0x70;
          canMsg4.data[7] = 0xC0;
          break;
        case 4:  //** 4 **
          canMsg4.data[6] = 0x60;
          canMsg4.data[7] = 0xC0;
          break;
        case 5:  //** 5 **
          canMsg4.data[6] = 0x50;
          canMsg4.data[7] = 0xC0;
          break;
        case 6:  //** 6 **
          canMsg4.data[6] = 0x40;
          canMsg4.data[7] = 0xC0;
          break;
        case 7:  //** D **
          canMsg4.data[6] = 0x30;
          canMsg4.data[7] = 0xC0;
          break;
        default:
          break;
      }
    }

    if (game == 99 || game_type == "LFS" || game_type == "BeamNgDrive") {
      switch (bieg) {
        case 0:  //** R **
          canMsg4.data[6] = 0x10;
          canMsg4.data[7] = 0x00;
          break;
        case 1:  //** N **
          canMsg4.data[6] = 0x20;
          canMsg4.data[7] = 0x00;
          break;
        case 2:  //** 1 **
          canMsg4.data[6] = 0x90;
          canMsg4.data[7] = 0xC0;
          break;
        case 3:  //** 2 **
          canMsg4.data[6] = 0x80;
          canMsg4.data[7] = 0xC0;
          break;
        case 4:  //** 3 **
          canMsg4.data[6] = 0x70;
          canMsg4.data[7] = 0xC0;
          break;
        case 5:  //** 4 **
          canMsg4.data[6] = 0x60;
          canMsg4.data[7] = 0xC0;
          break;
        case 6:  //** 5 **
          canMsg4.data[6] = 0x50;
          canMsg4.data[7] = 0xC0;
          break;
        case 7:  //** 6 **
          canMsg4.data[6] = 0x40;
          canMsg4.data[7] = 0xC0;
          break;
        case 8:  //** D **
          canMsg4.data[6] = 0x30;
          canMsg4.data[7] = 0xC0;
          break;
        default:
          break;
      }
    }
  }

  void set_RPM() {

    if (engine_type == "DIESEL" && rpm_type == "Uzywaj pelnej skali obrotomierza: ON") {
      rpm_sc = (int)(rpm);
      canMsg3.data[0] = (map(rpm_sc, 0, 1000, 0, 186));
      canMsg3.data[1] = map(((rpm - rpm_sc) * 1000), 0, 99, 0, 508);
    } else if (engine_type == "DIESEL" && rpm_type == "Uzywaj pelnej skali obrotomierza: OFF") {
      canMsg3.data[0] = rpm_P >> 5;
      canMsg3.data[1] = (rpm_P & 0x1f) << 3;
    } else if (engine_type == "BENZYNA" && rpm_type == "Uzywaj pelnej skali obrotomierza: ON") {
      rpm_sc = (int)(rpm);
      canMsg3.data[0] = (map(rpm_sc, 0, 1000, 0, 217));
      canMsg3.data[1] = map(((rpm - rpm_sc) * 1000), 0, 99, 0, 508);
    } else if (engine_type == "BENZYNA" && rpm_type == "Uzywaj pelnej skali obrotomierza: OFF") {
      canMsg3.data[0] = rpm_P >> 5;
      canMsg3.data[1] = (rpm_P & 0x1f) << 3;
    }


    else {
      canMsg3.data[0] = (map(rpm, 0, 1000, 0, 217));
    }
  }

  void set_speedo() {

    if (speed >= 1) {
      if (simulate_MPH == "Wyswietlaj predkosc na skali MPH: ON" && game == 1) {
        smooth = speed / 1.63;  // Dzielenie prędkości przez 1.59 (symulacja MPH)
      } else {
        smooth = speed / 2.56;  // Dzielenie prędkości przez 2.56
      }

      smooth_c = (int)(smooth);                   // Ucięcie części ułamkowej
      smooth_speedo = (smooth - smooth_c) * 100;  // Odejmowanie pomnożonej zmiennej od prędkości
      smooth_speedo_c = map(smooth_speedo, 0, 99, 0, 254);
      canMsg3.data[2] = (smooth_c & 0xFF);
      canMsg3.data[3] = (smooth_speedo_c & 0xFF);
    } else {
      smooth_c = 0;
      smooth_speedo_c = 0;
      canMsg3.data[2] = (smooth_c & 0xFF);
      canMsg3.data[3] = (smooth_speedo_c & 0xFF);
    }
  }

  // Wskaźnik paliwa
  void set_fuel() {

    if (fuel <= 15) {
      rezerwa = 1;
    } else {
      rezerwa = 0;
    }
    if (game_type != "FH5" || game_type != "FH4") {
      if (game == 2 || game == 3 || game_type == "CodemastersGrid2") {
        fuel = 100;
        rezerwa = 0;
      }
    }
    canMsg6.data[3] = (fuel & 0xff);
  }

  // Wskaźnik temp. cieczy
  void set_coolant() {

    if (coolant < 50) {
      coolant = 50;
    } else if (coolant > 130) {
      coolant = 130;
    }
    if (game == 2 || game == 3 || game == 5) {
      canMsg1.data[1] = (136 & 0xff);
    } else {
      if (coolant <= 90) {
        canMsg1.data[1] = (map(coolant, 50, 90, 100, 136) & 0xff);
      } else {
        canMsg1.data[1] = (map(coolant, 90, 130, 136, 160) & 0xff);
      }
    }
    //Zapalenie STOP - przegrzanie cieczy.
    if (coolant >= 120) {
      stop = 1;
    } else {
      stop = 0;
    }
  }

  // Wskaźnik temp. oleju
  void set_oil_temp() {
    if (game_type == "FH5" || game_type == "FH4" || game_type == "LFS") {
      if (oil_temp == 0) {
        oil_temp = 120;
      }
    }

    if (game == 2 || game == 3) {
      canMsg6.data[2] = (153 & 0xff);
    } else if (game != 2 || game != 3) {
      if (oil_temp <= 120) {
        canMsg6.data[2] = (map(oil_temp, 78, 120, 98, 155) & 0xff);
      }
      if (oil_temp > 120) {
        canMsg6.data[2] = (map(oil_temp, 120, 150, 155, 215) & 0xff);
      }
      if (oil_temp < 78) {
        canMsg6.data[2] = (98 & 0xff);
      }
      if (oil_temp > 150) {
        canMsg6.data[2] = (215 & 0xff);
      }
    }
    //Zapalenie STOP - przegrzanie oleju.
    if (oil_temp >= 140) {
      stop = 1;
    } else {
      stop = 0;
    }
  }

  //Przebieg
  void set_odometer() {
    if (przebieg == 0) {
      m1 = 0;
      m2c = 0;
      m3c = 0;
    }
    if (przebieg <= 255) {
      m1 = przebieg;
      m2c = 0;
      m3c = 0;
    }
    if (przebieg > 255) {
      m2c = 0;
      m3c = 0;
      m2 = round(przebieg / 256);
      m1 = przebieg - (256 * m2);
      if (m1 < 0) {
        m2 += -1;
        m1 += 256;
      }
      if (m2 > 255) {
        m3 = m2 / 256;  //255
        checksum = 256 * m3c;
        if (checksum >= 0) {
          m2c = m2 - (256 * m3c);
        }
        if (checksum < 0) {
          m2c = m2 + (256 * m3c);
        }
      }
      if (m2 < 256) {
        m2c = m2;
      }
      if (m2c < 0) {
        m2c += +256;
        m3c += -1;
      }
    }
    if (przebieg > 65530) {
      m3c = round(m3);
    } else {
      m3c = 0;
    }

    canMsg1.data[2] = m3c;  //odo 2
    canMsg1.data[3] = m2c;  //odo 2
    canMsg1.data[4] = m1;   //odo 3
  }

  //Ustawienie tempomatu/limitera
  void set_cruise_control() {
    //DIGITAL SPEEDO | CC | SPEED LIMIT
    if (game == 1) {
      if (tempo_act == 0 && limit_act == "Speed limit: OFF") {
        cc_status = 128;
        digital_speed = speed_dig;
        if (limit_speed <= speed_dig - 500 && limit_speed > 0) {
          cc_status += 32;
        }
      }
      if (tempo_act == 1 && limit_act == "Speed limit: OFF") {
        cc_status = 80;
        digital_speed = tempo_speed;
      }
      if (tempo_act == 0 && limit_act == "Speed limit: ON") {
        cc_status = 144;
        digital_speed = limit_speed;
      }
      if (tempo_act == 1 && limit_act == "Speed limit: ON") {
        cc_status = 80;
        digital_speed = tempo_speed;
      }
    } else {
      cc_status = 128;
      digital_speed = speed_dig;
    }

    if (speed_dig <= 100) {
      speed_lim_1 = 0;
      speed_lim_2 = 0;
    } else {
      if (digital_speed <= 255) {
        speed_lim_1 = speed_dig;
      }
      if (digital_speed > 255) {
        speed_lim_2 = round(digital_speed / 256);
        speed_lim_1 = digital_speed - (256 * speed_lim_2);

        if (speed_lim_1 < 0) {
          speed_lim_2 += -1;
          speed_lim_1 += 256;
        }
      }
    }
    if (limit_speed <= speed_dig - 500 && limit_speed >= 1) {
      overspeed = 1;
    } else {
      overspeed = 0;
    }


    canMsg8.data[0] = ((cc_status)&0xFF);
    canMsg8.data[1] = speed_lim_2;
    canMsg8.data[2] = speed_lim_1;
  }

  void speed_calculations() {
    speed_dig = (int)(speed * 100);
  }

  //Detekcja gry
  void game_detection() {
    if (game_type == "ETS2" || game_type == "ATS") {
      game = 1;
    } else if (game_type == "FH4" || game_type == "CodemastersGrid2" || game_type == "CodemastersDirt4") {
      game = 2;
    } else if (game_type == "FH5") {
      game = 3;
    } else if (game_type == "BeamNgDrive") {
      game = 4;
    } else if (game_type == "LFS") {
      game = 5;
    } else {
      game = 99;
    }
  }

  void custom_ncalc() {
    //Automatyczne podświetlenie licznika
    if (auto_backlight == "Stale podswietlenie licznika: OFF") {
      if (game == 1 || game == 4) {
        if (swiatla_on == 1) {
          canMsg2.data[3] = 0x2F;
        }
        if (swiatla_on == 0) {
          canMsg2.data[3] = 0x4F;
        }
      }
    } else {
      canMsg2.data[3] = 0x2F;
    }

    //Automatyczny zapłon
    if (auto_ignition == "Staly zaplon licznika: OFF") {
      if (game == 1 || game == 4) {
        if (ignition == 1) {
          canMsg1.data[0] = 0x8E;
          canMsg2.data[4] = 0x01;
        }
        if (ignition == 0) {
          canMsg1.data[0] = 0x86;
          canMsg2.data[4] = 0x00;
        }
      }
    } else {
      canMsg1.data[0] = 0x8E;
    }

    //Copyrights
    if (komunikacja == 1) {
      if (copyrights_1 == "Created by MattechPC") {
        canMsg4.data[5] = 0xA0;
        CAN_send();
      } else {
        //canMsg4.data[5] = 0x00;
        //CAN_send();
      }
    }
  }

  // Kontrola ekranu LCD licznika
  void set_screen() {
    // RESETOWANIE EKRANU
    canMsg9.data[0] = 0x80;
    if (!screen_change) {
      canMsg9.data[0] = 0x00;
      screen_change = true;
    }
    unsigned long obecnyCzas2 = millis();
    if (obecnyCzas2 - poprzedniCzas2 >= 10) {
      poprzedniCzas2 = obecnyCzas2;
      screen_change = false;
    }
    unsigned long obecnyCzas1 = millis();
    if (obecnyCzas1 - poprzedniCzas1 >= 1500) {
      poprzedniCzas1 = obecnyCzas1;
      screen++;
    }
    if (screen > 11) { screen = 0; }

    if (game == 1 || game == 4) {
      switch (screen) {

        case 0:
          if (fuel <= 15) {
            screen_hex = 224;
            errors_count++;
          } else {
            screen++;
          }
          break;

        case 1:
          if (coolant >= 110) {
            screen_hex = 1;
            errors_count++;
          } else {
            screen++;
          }
          break;

        case 2:
          if (oil_temp >= 130) {
            if (oil_temp >= 130 && oil_temp <= 139) {
              screen_hex = 4;
            }
            if (oil_temp >= 140) {
              screen_hex = 5;
            }
            errors_count++;
          } else {
            screen++;
          }
          break;

        case 3:
          if (przebita_opona == 1) {
            screen_hex = 13;
            errors_count++;
          } else {
            screen++;
          }
          break;

        case 4:
          if (pauza <= 120) {
            if (pauza <= 120) {
              screen_hex = 109;
            }
            if (pauza <= 45) {
              screen_hex = 101;
            }
            errors_count++;
          } else {
            screen++;
          }
          break;

        case 5:
          if (niskie_cisnienie == 1) {
            screen_hex = 125;
            errors_count++;
          } else {
            screen++;
          }
          break;

        case 6:
          if (akumulator == 1) {
            screen_hex = 138;
            errors_count++;
          } else {
            screen++;
          }
          break;

        case 7:
          if (overspeed == 1) {
            screen_hex = 111;
            errors_count++;
          } else {
            screen++;
          }
          break;

        case 8:
          if (check == 1) {
            screen_hex = 240;
            errors_count++;
          } else {
            screen++;
          }
          break;

        case 9:
          if (stop == 1) {
            screen_hex = 101;
            errors_count++;
          } else {
            screen++;
          }
          break;

        case 10:
          if (oil == 1) {
            screen_hex = 5;
            errors_count++;
          } else {
            screen++;
          }
          break;

        case 11:
          if (errors_count == 0) {
            screen_hex = 64;
            errors_count = 0;
            screen = 0;
          } else {
            errors_count = 0;
            screen = 0;
          }
          break;
      }
    }
    if (game == 2 || game == 3 || game == 5) {
      if (redline == 1) {
        screen_hex = 126;
      } else {
        screen_hex = 64;
      }
    }

    canMsg9.data[1] = (screen_hex & 0xff);
  }

  // Sekcja aktywacji kontrolek
  void set_indicators() {
    //kontrolki
    if (coolant >= 110 || oil_temp >= 135) {
      check_indicator_status = 1;
    } else {
      check_indicator_status = 0;
    }
    if (check == 1 || check_indicator_status == 1) {
      check_indicator = 1;
    }
    if (check == 0 && check_indicator_status == 0) {
      check_indicator = 0;
    }
    if (pauza <= 90) {
      pauza_time = 1;
    } else {
      pauza_time = 0;
    }

    canMsg4.data[4] = ((l_kier * 2) + (p_kier * 4) + (p_tyl * 8) + (p_przod * 16) + (drogowe * 32) + (mijania * 64) & 0xFF);
    canMsg4.data[0] = ((reczny * 32) + (podniesiona * 128) + (rezerwa * 16) + (retarder * 4) + (pauza_time * 3) & 0xFF);
    canMsg5.data[4] = ((check_indicator * 2) & 0xFF);
    canMsg5.data[3] = ((ABS * 32) & 0xff);
  }

  //Wysyłanie ramek CAN
  void CAN_send() {
    mcp2515.sendMessage(&canMsg1);
    mcp2515.sendMessage(&canMsg2);
    mcp2515.sendMessage(&canMsg3);
    mcp2515.sendMessage(&canMsg4);
    mcp2515.sendMessage(&canMsg5);
    mcp2515.sendMessage(&canMsg6);
    mcp2515.sendMessage(&canMsg7);
    mcp2515.sendMessage(&canMsg8);
    mcp2515.sendMessage(&canMsg9);
    mcp2515.sendMessage(&canMsg10);
  }

  void idle() {
    set_indicators();
    CAN_send();
    if (obecnyCzas >= 5000) {
      set_RPM();
      CAN_send();
    }
  }
};
#endif