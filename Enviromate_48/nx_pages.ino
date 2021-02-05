// commando's van nextion display zodra de pagina actief word
void NextionPage(String nxInput) {

  if (nxInput.indexOf("Home") != -1 ) {
    nxHome();
    nextionvenster = 0;
  }
 
  else if (nxInput.indexOf("Light") != -1 ) {
    nx_Light();
    nextionvenster = 1;
  }

  else if (nxInput.indexOf("Mister") != -1 ) { // sproeier
    nx_Mister();
    nextionvenster = 2;
  }

  else if (nxInput.indexOf("Fogger") != -1 ) {
    nx_Fogger();
    nextionvenster = 3;
  }

  else if (nxInput.indexOf("Fan") != -1 ) {
    nx_Fan();
    nextionvenster = 4;
  }

  else if (nxInput.indexOf("Led") != -1 ) {
    nx_LED();
    nextionvenster = 5;
  }


  else if (nxInput.indexOf("System") != -1 ) {
    nxSystem();
    nextionvenster = 6;
  }
}


/* bij openen nextionpagina worden de actuele waarden op het display verzonden */ 


/* verstuur waarden bij activeren page */

void nxHome(){      // print naar nextion scherm "Home"
  String tmpstr;

  Serial1.print(F("t_date.txt=\""));
  Serial1.print(DatumStr()+"\"");
  endString();
  Serial1.print(F("t_time.txt=\""));
  Serial1.print(TijdStr()+"\"");
  endString();

  Serial1.print(F("Hum.txt=\""));
  Serial1.print(String(humidity,1)+"\"");
  endString();

  Serial1.print(F("Temp.txt=\""));
  Serial1.print(String(temperature,1)+"\"");
  endString();

  tmpstr = (DHTalarm == 0) ? wit : rood;
  Serial1.print(F("Temp.bco="));
  Serial1.print(tmpstr);
  endString();

  tmpstr = (DHTalarm == 0) ? zwart : wit;
  Serial1.print(F("Temp.pco="));
  Serial1.print(tmpstr);
  endString();
  
  Serial1.print(F("UVI.txt=\""));
  Serial1.print(String(uvIndex)+"\"");
  endString();

  tmpstr = (UVIalarm == 0) ? wit : rood;
  Serial1.print(F("UVI.bco="));
  Serial1.print(tmpstr);
  endString();
 
  tmpstr = (UVIalarm == 0) ? zwart : wit;
  Serial1.print(F("UVI.pco="));
  Serial1.print(tmpstr);
  endString();

  Serial1.print(F("Dawn.txt=\""));
  Serial1.print(zonOp+"\"");
  endString();

  Serial1.print(F("Dusk.txt=\""));
  Serial1.print(zonOnder+"\"");
  endString();

// status LED, UVlamp en Warmtelamp
  tmpstr = (timers[0][0] == 1) ? geel : wit;
  Serial1.print(F("LED.bco="));
  Serial1.print(tmpstr);
  endString();

  tmpstr = (UVlamp == 1) ? geel : wit;
  Serial1.print(F("UV.bco="));
  Serial1.print(tmpstr);
  endString();

  tmpstr = (infrarood == 1) ? geel : wit;
  Serial1.print(F("Heat.bco="));
  Serial1.print(tmpstr);
  endString();
}


void knopLight(String knop, byte waarde){
  String tekst = (waarde == 1) ? "\"Auto\"" : "\"Time\"";
  Serial1.print(knop+".txt=");
  Serial1.print(tekst);
  endString();
  Serial1.print(knop+".val=");
  Serial1.print(String(waarde));
  endString();
}

void nx_Light(){ // print naar nextion scherm "Light"
  String nxtmp;
  nxtmp = MinutesToStr(timers[1][1]);    // tijd aan UV lamp
  Serial1.print("t0.txt=\""+nxtmp+"\""); // print naar nextion scherm "Light" veld "t0.txt"
  endString();                           // einde regel
  nxtmp = MinutesToStr(timers[1][2]);    // tijd uit relais_a
  Serial1.print("t1.txt=\""+nxtmp+"\""); // print naar nextion scherm "Light" veld "t1.txt"
  endString();
  knopLight("bt0",OnOff[1]);

  nxtmp = MinutesToStr(timers[2][1]);
  Serial1.print("t2.txt=\""+nxtmp+"\"");
  endString();
  nxtmp = MinutesToStr(timers[2][2]);
  Serial1.print("t3.txt=\""+nxtmp+"\"");
  endString();
  knopLight("bt1",OnOff[2]);

}

void knop(String knop, byte waarde){
  String tekst = (waarde == 1) ? "\"On\"" : "\"Off\"";
  Serial1.print(knop+".txt=");
  Serial1.print(tekst);
  endString();
  Serial1.print(knop+".val=");
  Serial1.print(String(waarde));
  endString();
}

void nx_Mister(){ // print naar nextion scherm "Mister"
//word spray[3] = {450,750,1020}; 
//byte sprayduration[3] = {10,20,30};
//byte sprayOnOff[3]

  String nxtmp;
  nxtmp = MinutesToStr(spray[0]);            // tijd aan
  Serial1.print("t0.txt=\""+nxtmp+"\""); 
  endString();                                // einde regel
  nxtmp = String(sprayduration[0]);
  Serial1.print("n0.val=");
  Serial1.print(nxtmp); 
  endString();
  knop("bt1",sprayOnOff[0]);

  nxtmp = MinutesToStr(spray[1]);
  Serial1.print("t1.txt=\""+nxtmp+"\""); 
  endString();
  nxtmp = String(sprayduration[1]);
  Serial1.print("n1.val=");
  Serial1.print(nxtmp); 
  endString();
  knop("bt2",sprayOnOff[1]);

  nxtmp = MinutesToStr(spray[2]);
  Serial1.print("t2.txt=\""+nxtmp+"\""); 
  endString();
  nxtmp = String(sprayduration[2]);
  Serial1.print("n2.val=");
  Serial1.print(nxtmp); 
  endString();
  knop("bt3",sprayOnOff[2]);
}


void nx_Fogger(){
  String nxtmp;
  nxtmp = MinutesToStr(timers[3][1]);
  Serial1.print("t0.txt=\""+nxtmp+"\"");
  endString();
  nxtmp = MinutesToStr(timers[3][2]);
  Serial1.print("t1.txt=\""+nxtmp+"\"");
  endString();
  knop("bt0",OnOff[3]);
  
  nxtmp = MinutesToStr(timers[4][1]);
  Serial1.print("t2.txt=\""+nxtmp+"\"");
  endString();
  nxtmp = MinutesToStr(timers[4][2]);
  Serial1.print("t3.txt=\""+nxtmp+"\"");
  endString();
  knop("bt1",OnOff[4]);

  nxtmp = MinutesToStr(timers[5][1]);
  Serial1.print("t4.txt=\""+nxtmp+"\"");
  endString();
  nxtmp = MinutesToStr(timers[5][2]);
  Serial1.print("t5.txt=\""+nxtmp+"\"");
  endString();
  knop("bt2",OnOff[5]);
  // check op overlap
  String kleur;
  kleur = (timers[4][1] <= timers[3][2]) ? geel : wit;
  Serial1.print("t1.bco="+kleur);
  endString();
  Serial1.print("t2.bco="+kleur);
  endString();
  
  kleur = (timers[5][1] <= timers[4][2]) ? geel : wit;
  Serial1.print("t3.bco="+kleur);
  endString();
  Serial1.print("t4.bco="+kleur);
  endString(); 

}


void nx_Fan(){ // print naar nextion scherm "Fan"
/*
byte FanPWM[3]  = {110,120,130}; // variabele PWM waarden voor fan
byte FanOnOff[3] = {1,1,1}; // fan aan/uit
*/
  String nxtemp;
  nxtemp = String(FanPWM[0]);
  Serial1.print("h1.val="+nxtemp); 
  endString();
  nxtemp = "t1.txt=\""+nxtemp+"\"";
  Serial1.print(nxtemp); 
  endString();
  knop("bt0",FanOnOff[0]);
 
  nxtemp = String(FanPWM[1]);
  Serial1.print("h2.val="+nxtemp); 
  endString();
  Serial1.print("t2.txt=\""+nxtemp+"\""); 
  endString();
  knop("bt1",FanOnOff[1]);

  nxtemp = String(FanPWM[2]);
  Serial1.print("h3.val="+nxtemp); 
  endString();
  Serial1.print("t3.txt=\""+nxtemp+"\""); 
  endString();
  knop("bt2",FanOnOff[2]);
}



void nx_LED(){ // print naar nextion scherm "LED"
/*
byte PWMval[0] 1 2
byte on_off[3]
*/
  String nxtemp;
  nxtemp = String(maxPWMval[0]);
  Serial1.print("h0.val=");
  Serial1.print(nxtemp);
  endString();
  nxtemp = "\""+nxtemp+"\"";
  Serial1.print("t0.txt=");
  Serial1.print(nxtemp);
  endString();
  knop("bt0",LedOnOff[0]);
  
  nxtemp = String(maxPWMval[1]);
  Serial1.print("h1.val=");
  Serial1.print(nxtemp);
  endString();
  nxtemp = "\""+nxtemp+"\"";
  Serial1.print("t1.txt=");
  Serial1.print(nxtemp);
  endString();
  knop("bt1",LedOnOff[1]);

  nxtemp = String(maxPWMval[2]);
  Serial1.print("h2.val=");
  Serial1.print(nxtemp);
  endString();
  nxtemp = "\""+nxtemp+"\"";
  Serial1.print("t2.txt=");
  Serial1.print(nxtemp);
  endString();
  knop("bt2",LedOnOff[2]);
}

void nxLEDval(){
  String nxtemp;
  nxtemp = String(PWMval[0]);
  Serial1.print("n0.val=");
  Serial1.print(nxtemp);
  endString();

  nxtemp = String(PWMval[1]);
  Serial1.print("n1.val=");
  Serial1.print(nxtemp);
  endString();

  nxtemp = String(PWMval[2]);
  Serial1.print("n2.val=");
  Serial1.print(nxtemp);
  endString();
  
  
}

void nxSystem(){
    Serial1.print("page System");
    endString();
    Serial1.print("c0.val="+String(autozomertijd));
    endString();
    Serial1.print("t1.txt=\"" + DatumStr() + "\"");
    endString();
    Serial1.print("t0.txt=\"" + TijdStr() + "\"");
    endString();
    Serial1.print("maxtemp.val=" + String((maxtemp*10),0));
    endString();
    Serial1.print("mintemp.val=" + String((mintemp*10),0));
    endString();

    Serial1.print("maxuv.val=" + String((maxUVindx*100),0));
    endString();
    Serial1.print("minuv.val=" + String((minUVindx*100),0));
    endString();

    Serial1.print("latitude.txt=\"" + latitude +"\"");
    endString();
    Serial1.print("longitude.txt=\"" + longitude +"\"");
    endString();  

    Serial1.print("UVIcal.val=" + String((UVIcal*1000),0));
    endString();


}


void endString(){
  // einde regel printopdracht naar nextion
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
  unsigned long wacht = millis()+10;
  while (millis() < wacht){}
}
