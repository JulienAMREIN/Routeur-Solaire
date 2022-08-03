/*
Routeur solaire
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

  const int buttonPinPlus = 2;     // the number of the pushbutton pin
  const int buttonPinMoins = 4;     // the number of the pushbutton pin
  const int ledPin =  13;      // the number of the LED pin
  int varSeuilWatt = 0; // Variable de valeur de seuil activation desactivation relais
  byte pasVarIncrementation = 100; // valeur d'incrementation lors de l'appui sur un bouton de 0 à 255
  boolean etatBoutonPlus = 0;
  boolean etatBoutonMoins = 0;
  boolean menuDejaVu = 0;
  
void setup() {
  
  lcd.init(); // initialisation de l'afficheur
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinPlus, INPUT);
  pinMode(buttonPinMoins, INPUT);
  

  
  Serial.begin(9600);

  
}


void loop() {
  
//--------------------------------------------Initialisation LCD avec message de base----------------------------------------------------------------------------

if (menuDejaVu == 0)
  {
  lcd.backlight();
// Envoi du message
lcd.setCursor(0, 0);
lcd.print("Routeur solaire");
lcd.setCursor(0,1);
lcd.print(" Version 0.1");
delay(3000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Seuil de bascule");
lcd.setCursor(0,1);
lcd.print("           Watts");
lcd.print(varSeuilWatt);
menuDejaVu = 1;
delay(3000);
  }
  
 // --------------------------------------------------------------------------------------------------------------------------------------------------On vérifie si il y a un appui sur le bouton plus et moins puis on donne la valeur à la variable watt
etatBoutonPlus = digitalRead(buttonPinPlus);         // lecture de la valeur du bouton poussoir
etatBoutonMoins = digitalRead(buttonPinMoins);         // lecture de la valeur du bouton poussoir

    if (etatBoutonPlus == LOW)                    // controle si le bouton est pressé
      {                            
      digitalWrite(ledPin, HIGH);                  // turn LED on:
      varSeuilWatt += pasVarIncrementation;        // augmenter la valeur des watts pour la bascule au pas de la variable pas incrementation
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Seuil de bascule");
      lcd.setCursor(0,1);
      lcd.print("           Watts");
      lcd.setCursor(0,1);
      lcd.print(varSeuilWatt);
      etatBoutonPlus = !etatBoutonPlus;            // temporisation anti rebond logicielle
      delay(300);
      } 
    else 
      { 
      digitalWrite(ledPin, LOW);                         // turn LED off:       

      if (etatBoutonMoins == LOW)                     // controle si le bouton est pressé. If it is, the buttonState is HIGH:
        {                  
        digitalWrite(ledPin, HIGH);                   // turn LED on:
        varSeuilWatt -= pasVarIncrementation;         // diminuer la valeur des watts pour la bascule au pas de la variable pas incrementation
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Seuil de bascule");
        lcd.setCursor(0,1);
        lcd.print("           Watts");
        lcd.setCursor(0,1);
        lcd.print(varSeuilWatt);
        etatBoutonMoins = !etatBoutonMoins;           // temporisation anti rebond logicielle
        delay(300);
        } 
      else 
        {
        digitalWrite(ledPin, LOW);                      // turn LED off:
        }            
                    
      }
      
// -------------------------------------------------------------------------------------------------------------------------------------------------- Lecture moniteur série de la variable watt

 Serial.println(varSeuilWatt);


  
}
