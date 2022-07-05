#include <Servo.h>
#include <LiquidCrystal.h>
Servo myServo_entry,myServo_exit;
char inbyte;
int car_count=0;
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int Contrast=90;
//LiquidCrystal lcd(12,11,5,4,3,2);
LiquidCrystal lcd(12,13,8,4,7,2);

//int num_array[10][7] = {  { 1,1,1,1,1,1,0 },    // 0
  //                        { 0,1,1,0,0,0,0 },    // 1
    //                      { 1,1,0,1,1,0,1 },    // 2
      //                    {1,1,1,1,0,0,1 },    // 3
        //                  {  0,1,1,0,0,1,1 },    // 4
          //                { 1,0,1,1,0,1,1 },    // 5
            //              { 1,0,1,1,1,1,1 },    // 6
              //            { 1,1,1,0,0,0,0 },    // 7
                //          { 1,1,1,1,1,1,1 },    // 8
                  //        { 1,1,1,0,0,1,1 }};   // 9
                                       
//function header
//void Num_Write(int);
const int trigPin = 3;
const int echoPin = 11;
// defines variables
long duration;
int distance;
void setup()
{
     analogWrite(6,Contrast);
     /*pinMode(4);
     pinMode(2);
     pinMode(7);
     pinMode(8)
     pinMode(9);
     pinMode(12);
     pinMode(13);
     pinMode(4);*/
   myServo_entry.attach(5);
   myServo_exit.attach(10);
   //Num_Write(car_count); 
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input
   lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(1,0);
  lcd.print("Welcome to Car");
  lcd.setCursor(0,1);

  lcd.print("    Parking");
  Serial.begin(9600); // Starts the serial communication
}
void loop()
{
    if(Serial.available()>0)
    {
    inbyte = Serial.read();
    if(inbyte=='C') // input comes from a python script which performs object detection using YOLO v2 and returns 'C' is a car is detected in the camera feed
    {
      if(car_count>=3)
      {
        lcd.setCursor(0,1);
        lcd.print("Parking Full!");
      }
      else{
      car_count++;
      lcd.setCursor(1,0);
      lcd.print("Total Cars: ");
      lcd.print(car_count);
      for(int pos = 0; pos <=90; pos += 10) 
      {                                 
        myServo_entry.write(pos);              
        delay(200);                             
      } 
      delay(3500);
      for(int pos = 90; pos >=0; pos -= 10) 
      {                                 
        myServo_entry.write(pos);              
        delay(200);                             
      } 
      }
    
      
      }
      //Num_Write(car_count);      
    
   
     // Num_Write(car_count);
        
   
    }
     //digitalWrite(trigPin, LOW);
   // delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    //Serial.print("Distance: ");
    //Serial.println(distance);
    if(distance<=6.0)
    {
      car_count--;
      if(car_count<=0)
          car_count=0;
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Total cars: ");
      lcd.print(car_count);
      for(int pos = 0; pos <=90; pos += 10) 
      {                                 
        myServo_exit.write(pos);              
        delay(100);                             
      } 
      delay(3500);
      for(int pos = 90; pos >=0; pos -= 10) 
      {                                 
        myServo_exit.write(pos);              
        delay(100);                             
      } 
    }
     
}
    
        
    

/*void Num_Write(int number) 
{
  int pin= 2;
  for (int j=0; j < 7; j++) 
  {
   digitalWrite(pin, num_array[number][j]);
   pin++;
  }
}*/


