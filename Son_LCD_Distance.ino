#include<LiquidCrystal.h>                                   // Charger la library de Liquid Crysttal
LiquidCrystal LCD(10,9,5,4,3,2);                            // Nous créons le LiquidCrystal comme objet nommé LCD

int objectDistance;                                         // Nous créons une variable nommée objectDistance

int trigPin = 13;                                           // trigPin ( émeteur de son) est relié au pin 13 de l'Aduino
int echoPin = 11;                                           // echoPin ( récepteur ultrasonic) est relié au pin 11 de l'Arduino

float pingTime;                                             // C'est le temps que met le son pour toucher l'objet et revenir dans le récepteur
float targetDistance;                                       // la variable est atribuée pour imprimer la distance de l'objet
float speedOfSound = 1234.8;                                // Nous indiquons la vitesse du son en m/s

int redLED = 7;                                             // Nous indiquons à l'Arduino que la LED rouge est branché sur le Pin 7
int onTimeLED = 1000;                                       // Temps ou la LED rouge reste allumée
int offTimeLED = 500;                                       // Temps ou la LED rouge est éteinte

void setup() {

  Serial.begin(115200);                                     // On ouvre le Serial Port de l'Arduino et indiquons la vitesse de communication                                 
  pinMode(trigPin,OUTPUT);                                  // Nous indiquons que trigPin est un OUTPUT
  pinMode(echoPin,INPUT);                                   // Nous indiquons que echoPin est un INPUT

  LCD.begin(16,2);                                          // On indique à l'Arduino que notre écran LCD à 16 colonnes et 2 rangées
  LCD.setCursor(0,0);                                       // On indique au curseur du LCD de commencer en haut à gauche de l'écran
  LCD.print("  Distant de : ");

}

void loop() {

  digitalWrite(trigPin,LOW);                               // On stop l'envoit à trigPin
  delayMicroseconds(1000);                                 // On laisse un delay de 1s
  digitalWrite(trigPin,HIGH);                              // On envoit à trigPin
  delayMicroseconds(10);                                   // On laisse un delay de 10ms
  digitalWrite(trigPin,LOW);                               // On stop l'envoit à trigPin

  pingTime = pulseIn(echoPin,HIGH);                        // On envoit à echoMin pour calculer la distance de l'objet 
  pingTime = pingTime / 1000000;                           // On convertit le signal en s
  pingTime = pingTime / 3600;                              // On convertit le signal en h

  targetDistance = speedOfSound * pingTime;                // Calcule pour trouver en combient de temps l'onde revient dans le capteur en Km/h
  targetDistance = targetDistance / 2;                     // On divise par 2 pour avoir la distance réel de l'objet en metre
  targetDistance = targetDistance * 100000;                // On convertit la distance en CM


  LCD.setCursor(0,1);                                      // On indique la position initaile du curseur de l'écran LCD
  LCD.print("                ");                           // On suprime toute éventuelle ecriture sur l'écran en imprimant des espace

  LCD.setCursor(0,1);                                      // On indique la position initaile du curseur de l'écran LCD
  LCD.print(targetDistance);                               // On imprime la distance de la cible sur le LCD
  LCD.print(" CM");                                        // On imprime l'unité de mesure sur l'écran LCD
  delay(1000);                                             // On laisse un delay de 1s

  
  if (targetDistance <= 20.){                                                   // If statement, La LED rouge s'allume si la distance est inferieur ou égale à 20cm
    digitalWrite (redLED,HIGH);                                                 // On envoit sur la LED rouge
    delay(onTimeLED);                                                           // Delay ou la LED rouge reste allumée
    digitalWrite (redLED,LOW);                                                  // On stop la LED rouge
    delay(offTimeLED);                                                          // Delay ou la LED rouge est stoppée
    Serial.println("Attention la distance de la cible est trop proche");        // On imprime sur le Serial Moniter de l'ordinateur
    Serial.print("Vous etes à  : ");                                            // On imprime sur le Serial Moniteur de l'ordinateur
    Serial.print(targetDistance);                                               // On imprime sur le Serial Moniteur de l'ordinateur la distance de la cible
    Serial.println(" cm");
    Serial.println("-------------------------------------------------");
  }
  else{                                                                         // Sinon la boucle peut continuer et la LED rouge séteint si la distance est suppérieur à 20cm
Serial.print("La distance de la cible est de : ");                              // On imprime sur le Serial Moniteur de l'ordinateur
Serial.print(targetDistance);                                                   // On imprime sur le Serial Moniteur de l'ordinateur la distance de la cible
Serial.println(" cm");
Serial.println("------------------------------------------");
  }

}
