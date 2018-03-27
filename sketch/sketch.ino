int pumpPin1 = 8; // номер пина 
int pumpState1 = LOW; // состояние
// последний момент времени, когда состояние изменялось
unsigned long previousMillis1 = 0;
long OnTime1 = 20000; // длительность работы (в миллисекундах)
long OffTime1 = 1800000;// не работает  (в миллисекундах)
// контроль воды
int wtrlvlled1 = 10; 
int wtrlvlState1 = LOW;
int lvlbtn1 = 3;
int lvlvar1 = 1 ;
// свет 
int lightled1 = 9;
int lightState1 = LOW;
unsigned long previousMillis2 = 0;
long day = 54000000;
long holeDay = 86400000;
int lightbtn1 = 2;
//fix датчик света
int lightvar1 = 1;
long previousMillislight = 0;
long measurepause = 300000; 


void setup() {
 pinMode(pumpPin1, OUTPUT);
 pinMode(wtrlvlled1, OUTPUT);
 pinMode(lvlbtn1, INPUT);
 pinMode(lightled1, OUTPUT);
 pinMode(lightbtn1, INPUT);
 Serial.begin(9600);
}
//объявляем функцию reset с адресом 0
void(* resetFunc) (void) = 0;

void loop() {
 // выясняем не настал ли момент сменить состояние 
 
 unsigned long currentMillis = millis(); // текущее время в миллисекундах
 lvlvar1 = digitalRead(lvlbtn1);
 //fix датчик света
 if(currentMillis - previousMillislight >= measurepause)
 {
 lightvar1 = digitalRead(lightbtn1);
 previousMillislight = currentMillis;
 }
 // конечный автомат для воды
 if((pumpState1 == LOW) && (currentMillis - previousMillis1 >= OnTime1))
 {
   pumpState1 = HIGH; // выключаем
   previousMillis1 = currentMillis; // запоминаем момент времени
   digitalWrite(pumpPin1, pumpState1); // реализуем новое состояние
 }
 else if ((pumpState1 == HIGH) && (currentMillis - previousMillis1 >= OffTime1))
 {
   if (lvlvar1 == HIGH)
   {
    Serial.println(currentMillis);
   pumpState1 = LOW; // включаем
   wtrlvlState1 = LOW;
   previousMillis1 = currentMillis ; // запоминаем момент времени
   digitalWrite(pumpPin1, pumpState1); // реализуем новое состояние
   digitalWrite(wtrlvlled1, wtrlvlState1);
   } 
   else { 
     wtrlvlState1 = HIGH;
      digitalWrite(wtrlvlled1, wtrlvlState1);
   }
     
 }
 
 // конечный автомат для света
 if(currentMillis <= day)
 { 
   if (lightvar1 == HIGH)
   {
   lightState1 = LOW; 
   digitalWrite(lightled1, lightState1); 
   }
   else 
     {
   lightState1 = HIGH; 
   digitalWrite(lightled1, lightState1); 
   }
 }
 else
 {
    lightState1 = HIGH; 
   digitalWrite(lightled1, lightState1);  
   Serial.println("day end");
 }
  // сброс дня 
  if (currentMillis > holeDay)
  { 
    Serial.println("reset");
    resetFunc(); //вызываем reset
    delay(100);
    Serial.println("hello");
  }
}
