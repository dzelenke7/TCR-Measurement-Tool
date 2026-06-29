#include <LiquidCrystal.h>
                                                // initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

#define div2  1                           //the thermistor attach to 
#define div1 0
#define R_ref1 32000                           
#define R_ref2 32000
const int B = 3950;                               //the beta of the thermistor
const float R0 = 10000.0;

void setup()
{
  Serial.begin(9600);
  pinMode(0, INPUT);
  pinMode(1, INPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
}

void loop()
{
  //read thermistor value
  long a = analogRead(div2);

  float V_therm = a * (5.0 / 1023.0);

  float V_out = analogRead(div1) * (5.0 / 1023.0);
  
  float R_test = (V_out * R_ref1) / (5.0 - V_out);

  float R_therm = (R_ref2 * V_therm) / (5.0 - V_therm);

  float tempC = B / (log(R_therm / R0) + B / 298.0) - 273.0;
  float tempF = 1.8 * tempC + 32.0;



  lcd.setCursor(0, 0);                                // set the cursor to column 0, line 0
  lcd.print("Temp: ");                                // Print a message of "Temp: "to the LCD.
                                                      
  lcd.print(tempC);
                                                      // Print the unit of the centigrade temperature to the LCD.
  lcd.print(char(223));//print the unit" ℃ "
  lcd.print("C");
                                                      
  lcd.setCursor(0, 1);                                // set the cursor to column 0, line 1
  lcd.print("Resistance: ");                                
  lcd.print(R_test);                                   // Print a Fahrenheit temperature to the LCD.
  lcd.print(" Ω");                                    

  Serial.println(tempC);
  Serial.println(R_test);
  Serial.println(R_therm);

  delay(200);                                         
}

