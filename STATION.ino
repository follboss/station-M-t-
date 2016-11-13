# include <math.h>
# include <LiquidCrystal.h>
#include <EEPROM.h>
#include "DHT.h"
#define SERIESRESISTOR 10000
#define THERMISTORPIN A0
#define DHTPIN 8     //pour connecté les pins digitales de la dht
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define DHTTYPE DHT11   // DHT 11


DHT dht(DHTPIN, DHTTYPE);

int led = 13; // LED connectée à la broche numérique 13
int resetPin = 1;
int led1 = 1;
int tempMin = 22;
int tempMax = 25;
int tempPin = A1;
int ventillo = 7;

double Thermistance( int val){ // formule de SteinhartHart 

 double tempExt;
 tempExt = log(10000.0*((1024.0/val-1))); 
 tempExt = 1 / (0.001113 + (0.000237 + (0.00000006957 * tempExt * tempExt ))* tempExt );
 tempExt = tempExt - 273.15;          
 return tempExt;
  
}



void setup() {
  // s'execute une fois lorsque l'on appuie sur le reset  pinMode(ventillo, OUTPUT);  // initialise la broche numérique en sortie 
  pinMode(led1,OUTPUT);
  pinMode(tempPin, INPUT); // en entré
  lcd.begin(16,2);
  dht.begin();
  digitalWrite(resetPin,HIGH);//(allume
  delay(200);
  pinMode(led,OUTPUT);
  pinMode(resetPin,OUTPUT);
  Serial.begin(9600);
  Serial.println("reset");
  delay(200);
  
}


  
void loop() {
  
float Valrecup;
 int nbr;                
  double temp;
  int vaLum = analogRead(A1); // Mesure la tension sur la broche A1 pour la photoresistance.
 /* double max = -300.0; cette partie en commentaire est destinée à recupérer les température minimale et maximale après un reset.
  double min = 300.0;
  double maxEx= -300;
  double minEx= 300;*/
 /* Serial.println(EEPROM.read(0));
    Serial.println(EEPROM.read(10));*/
  //   lcd.clear();
   /*   Serial.println(EEPROM.read(20));
    Serial.println(EEPROM.read(30));
    delay(5000);
*/
  // temps d'attente entre deux mesures
  delay(2000);

//lecture de l' humidité 
  float h = dht.readHumidity();
  //lecture de la temperature en celsuis
 float t = dht.readTemperature();
  /*if (t>max){ // récuperation des min et max pour l'intérieur
    max=t; 
    EEPROM.write(0,max);
       
  }
  if(t<min){
    min=t;
     EEPROM.write(10,min);
     
  }*/
 
  Valrecup = analogRead(THERMISTORPIN);
  Serial.print("valeur analogique ");
  Serial.print(Valrecup);
  nbr=analogRead(0);      
  temp=Thermistance(nbr);
  /*if (temp>maxEx){ // min et max pour la température de l'extérieur
    maxEx=temp; 
    EEPROM.write(20,maxEx);
       
  }
  if(temp<minEx){
    minEx=temp;
     EEPROM.write(30,minEx);
     
  }   
  
    */
  if(t>tempMin && t<tempMax) 
  { // actionnement du ventillo entre 22 et 25 °
     digitalWrite(7, LOW); 
     analogWrite(7,51);
     lcd.print("ventillo ON   ");
     delay(100);
  } 
  else 
  {                    
     digitalWrite(7, HIGH); 
  }
   
 
 lcd.begin(16,2);

 delay(200);

 //defilement lcd;
  for (int positionlcd = 0; positionlcd < 16; positionlcd++) {
    // deflie vers la gauche
     lcd.setCursor(0,0);
     lcd.print("Tempext en C = ");
     lcd.print(temp);
     //lcd.print(" C");
     lcd.print(" tempdht: " );
     lcd.print(t);
     lcd.setCursor(0,1);
     lcd.print("humidite: " );
     lcd.print(h);
     lcd.print("%");
     lcd.scrollDisplayLeft();
   
    delay(200);
  }
   
 

  Serial.print("  Humidité: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("TemperatureEXT: ");
  Serial.print(temp);
  Serial.print(" C");

/* digitalWrite(led,HIGH); permet d'actionner le reset
 Serial.println("on");
 delay(1000);
 digitalWrite(led,LOW);
 Serial.println("off");
 delay(1000);
 Serial.println("resetting");*/
  // Envoi la mesure au PC pour affichage et attends 250ms
 
  Serial.print(" Luminosité ambiante: ");
 Serial.println(vaLum);
 delay(250);
 
 
}
