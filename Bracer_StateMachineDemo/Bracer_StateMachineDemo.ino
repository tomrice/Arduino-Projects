#define c1 6
#define c2 7
#define c3 8
#define r1 9
#define r2 10
#define r3 11
#define r4 12

//display pixels

boolean c1r1 = 0;
boolean c2r1 = 0;
boolean c3r1 = 0;
boolean c1r2 = 0;
boolean c2r2 = 0;
boolean c3r2 = 0;
boolean c1r3 = 0;
boolean c2r3 = 0;
boolean c3r3 = 0;
boolean c1r4 = 0;
boolean c2r4 = 0;
boolean c3r4 = 0;

int tiltpos = 0;

int dcycl1 = 0;
boolean blinkstate = 0;
int dspclock = 9;

boolean WpnSelect;
int shieldLvl = 0;

int gpcyc = 0;

boolean shieldtoggle = 0;
boolean firetoggle = 0;
int firecycl=0;


int shieldtimer = 0;

int serialmsg=0;
int prevmsg=0;

void setup() {

 for(int i = 6; i<9; i++){
  pinMode(i, OUTPUT);
 digitalWrite(i, LOW);
 }

 for(int i = 9; i<13; i++){
  pinMode(i,INPUT);
 }

 Serial.begin(9600);

}

void loop() {

 if(gpcyc>0){gpcyc--;}
 if(gpcyc==0){
 grabposition();}

 shieldmain();

 firemain();

 display();
 
 serialdisplay();

 shieldLvl=0;
}

void display(){

 //blink timer
 dcycl1++;
 if(dcycl1==250){blinkstate=!blinkstate; dcycl1=0;}


 if(WpnSelect==0){c1r4=blinkstate;}
 else{c2r4=blinkstate;};

 if(shieldLvl==0){}
 else if(shieldLvl==1){c3r4=1;}
 else if(shieldLvl==2){c3r4=1;c3r3=1;}
 else if(shieldLvl==3){c3r4=1;c3r3=1;c3r2=1;}
 else if(shieldLvl==4){c3r4=1;c3r3=1;c3r2=1;c3r1=1;}
 else if(shieldLvl==5){c3r4=blinkstate;c3r3=blinkstate;c3r2=blinkstate;c3r1=blinkstate;}

 //display routine
 dspclock++;
 if(dspclock==13){dspclock=9;}
 switch(dspclock){
  case 9:
 pinMode(9,OUTPUT);digitalWrite(9, LOW);
 digitalWrite(c1, c1r1);
 digitalWrite(c2, c2r1);
 digitalWrite(c3, c3r1);
 break;
  case 10:
 pinMode(10,OUTPUT);digitalWrite(10, LOW);
 digitalWrite(c1, c1r2);
 digitalWrite(c2, c2r2);
 digitalWrite(c3, c3r2);
 break;
  case 11:
 pinMode(11,OUTPUT);digitalWrite(11, LOW);
 digitalWrite(c1, c1r3);
 digitalWrite(c2, c2r3);
 digitalWrite(c3, c3r3);
 break;
  case 12:
 pinMode(12,OUTPUT);digitalWrite(12, LOW);
 digitalWrite(c1, c1r4);
 digitalWrite(c2, c2r4);
 digitalWrite(c3, c3r4);  
 break;
 }

 for(int i = 6; i<9; i++){
  pinMode(i, OUTPUT);
 digitalWrite(i, LOW);
 }

 for(int i = 9; i<13; i++){
  pinMode(i,INPUT);
 }

c1r1 = 0; c2r1 = 0; c3r1 = 0; c1r2 = 0;
c2r2 = 0; c3r2 = 0; c1r3 = 0; c2r3 = 0;
c3r3 = 0; c1r4 = 0; c2r4 = 0; c3r4 = 0;

 }


void grabposition(){

 if(map(analogRead(A0),380,620,0,10)>7){

 };
 if(map(analogRead(A0),380,620,0,10)<3){
 shieldtoggle=1;
 }else{shieldtoggle=0;};
 if(map(analogRead(A1),380,620,0,10)>7){
 firetoggle=1;
 }else{firetoggle=0;};
 if(map(analogRead(A1),380,620,0,10)<2){
 WpnSelect=!WpnSelect; if(WpnSelect==0){serialmsg=6;}else{serialmsg=7;};
 gpcyc = 1500;
 };


}

void shieldmain(){

 if(shieldtoggle==0){shieldtimer=0; return;}
 if(shieldtimer==5000){shieldtimer=5001;serialmsg=8;}
 if(shieldtimer<5001){shieldtimer++;}


 switch(map(shieldtimer,0,5000,0,5)){
  case 0:
  shieldLvl=4; serialmsg = 1;
  break;
  case 1:
  shieldLvl=3; serialmsg = 2;
  break;
  case 2:
  shieldLvl=2; serialmsg = 3;
  break;
  case 3:
  shieldLvl=1; serialmsg = 4;
  break;
  case 4:
  shieldLvl=5; serialmsg = 5;
  break;

 }
}

void firemain(){

 firecycl++;
 if(firecycl==300){firecycl=0;}

if(firetoggle==1){
 if(WpnSelect==0){

  switch(map(firecycl,0,300,0,4)){
    case 0:
    c1r4=1;
  break;
    case 1:
    c1r3=1;
  break;
    case 2:
    c1r2=1;
  break;
    case 3:
    c1r1=1;
  break;
  
  }}
  else{

  switch(map(firecycl,0,25,0,1)){
    case 0:
  break;
    case 1:
    c2r3=1;
    c2r2=1;
    c2r1=1;
  break;
  
  }
  }
 }

}

void serialdisplay() 
                    
{
  
  if(serialmsg!=0 && serialmsg!=prevmsg){ //If not same as previous or none

    //wipe whatever's already on screen
  Serial.write(27); 
  Serial.print("[2J"); 
  Serial.write(27); 
  Serial.print("[H");
    
    switch(serialmsg){
     case 1: 
    Serial.println("SHIELD ENGAGED");
    Serial.println("0|##########|100"); 
      break;
     case 2: 
    Serial.println("SHIELD ENGAGED");
    Serial.println("0|########  |100"); 
      break;
     case 3: 
    Serial.println("SHIELD ENGAGED");
    Serial.println("0|######    |100"); 
      break;
     case 4: 
    Serial.println("SHIELD ENGAGED");
    Serial.println("0|####      |100"); 
      break;
     case 5: 
    Serial.println("SHIELD DEPLETED!!");
    Serial.println("0|##        |100"); 
      break;
     case 6: 
    Serial.println("RAPIDFIRE ACTIVE");
      break;
     case 7: 
    Serial.println("CHARGE WEAPON ACTIVE");
      break;
     case 8: 
    Serial.println("SHIELD DISENGAGED!!");
      break;
      
      
    }
  prevmsg=serialmsg;  
  serialmsg=0;
  }

}
