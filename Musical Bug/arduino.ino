#define BUZZER_PIN 8

#define Sa 2
#define Re 3
#define Ga 4
#define Ma 5
#define Pa 6
#define Dha 7

#define P1_L1 A0
#define P1_L2 A1
#define P1_L3 A2
#define P2_L1 A3
#define P2_L2 A4 
#define P2_L3 A5

#define computer_mode 10

int melody[] = {262, 294, 330, 349, 392, 440};
int noteDuration = 1000;

void setup() {

  randomSeed(analogRead(0));
  // pinMode(IR_SENSOR_PIN_1, INPUT);
  // pinMode(IR_SENSOR_PIN_2, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(Sa, INPUT);
  pinMode(Re, INPUT);
  pinMode(Ga, INPUT);
  pinMode(Ma, INPUT);
  pinMode(Pa, INPUT);
  pinMode(Dha, INPUT);

  digitalWrite(Sa, LOW);
  digitalWrite(Re, LOW);
  digitalWrite(Ga, LOW);
  digitalWrite(Ma, LOW);
  digitalWrite(Pa, LOW);
  digitalWrite(Dha, LOW);

  pinMode(P1_L1, OUTPUT);
  pinMode(P1_L2, OUTPUT);
  pinMode(P1_L3, OUTPUT);
  pinMode(P2_L1, OUTPUT);
  pinMode(P2_L2, OUTPUT);
  pinMode(P2_L3, OUTPUT);  

  analogWrite(P1_L1, 255);
  analogWrite(P1_L2, 255);
  analogWrite(P1_L3, 255);
  analogWrite(P2_L1, 255);
  analogWrite(P2_L2, 255);
  analogWrite(P2_L3, 255); 
  pinMode(computer_mode, INPUT);  

  Serial.begin(9600);
}

void loop() {

  // int sensorValue_1 = analogRead(IR_SENSOR_PIN_1);
  
  // if(sensorValue_1 < 500)
  // {
  //   //blinking of led
  //   digitalWrite(P1_L1, 255);
  //   digitalWrite(P1_L2, 255);
  //   digitalWrite(P1_L3, 255);
  //   delay(500);
  //   digitalWrite(P1_L1, 0);
  //   digitalWrite(P1_L2, 0);
  //   digitalWrite(P1_L3, 0);
  //   delay(500);
  //   digitalWrite(P1_L1, 255);
  //   digitalWrite(P1_L2, 255);
  //   digitalWrite(P1_L3, 255);
  //   delay(500);
    
  //   //forward playing
  //   for (int j = 0; j <= 7; j++) {
  //     tone(8, melody[j]);
  //     delay(noteDuration);
  //   }

  //   noTone(8); // no tone for the duration specified by noteDuration
  //   delay(noteDuration);

  //   //revert playing
  //   for (int j = 7; j >= 0; j--) {
  //     tone(8, melody[j]);
  //     delay(noteDuration);
  
  //   }

  //   noTone(8); // no tone for the duration specified by noteDuration
  //   delay(noteDuration);

  //   digitalWrite(P1_L1, 255);
  //   digitalWrite(P1_L2, 255);
  //   digitalWrite(P1_L3, 255);
  //   delay(500);
  //   digitalWrite(P1_L1, 0);
  //   digitalWrite(P1_L2, 0);
  //   digitalWrite(P1_L3, 0);
  //   delay(500);
  //   digitalWrite(P1_L1, 255);
  //   digitalWrite(P1_L2, 255);
  //   digitalWrite(P1_L3, 255);
  //   delay(500);
  // }

  // int sensorValue_2 = analogRead(IR_SENSOR_PIN_2);

  // if(sensorValue_2 < 500)
  // {
  //   analogWrite(P2_L1, 255);
  //   analogWrite(P2_L2, 255);
  //   analogWrite(P2_L3, 255);
  //   delay(500);
  //   analogWrite(P2_L1, 0);
  //   analogWrite(P2_L2, 0);
  //   analogWrite(P2_L3, 0);
  //   delay(500);
  //   analogWrite(P2_L1, 255);
  //   analogWrite(P2_L2, 255);
  //   analogWrite(P2_L3, 255);
  //   delay(500);
  //   //forward playing
  //   for (int j = 0; j <= 7; j++) {
  //     tone(8, melody[j]);
  //     delay(noteDuration);
  
  //   }

  //   noTone(8); // no tone for the duration specified by noteDuration
  //   delay(noteDuration);

  //   //revert playing
  //   for (int j = 7; j >= 0; j--) {
  //     tone(8, melody[j]);
  //     delay(noteDuration);
  
  //   }

  //   noTone(8); // no tone for the duration specified by noteDuration
  //   delay(noteDuration);

  //   analogWrite(P2_L1, 255);
  //   analogWrite(P2_L2, 255);
  //   analogWrite(P2_L3, 255);
  //   delay(500);
  //   analogWrite(P2_L1, 0);
  //   analogWrite(P2_L2, 0);
  //   analogWrite(P2_L3, 0);
  //   delay(500);
  //   analogWrite(P2_L1, 255);
  //   analogWrite(P2_L2, 255);
  //   analogWrite(P2_L3, 255);
  //   delay(500);
  // }

  int computer = digitalRead(computer_mode);

  //player mode
  if(computer == 0)
  {
    //chance of player 1
    play_P1();
    delay(1000);

    //chance of player 2
    play_P2();
    delay(1000);
  }

  //computer mode
  else
  {    
    play_online();
    delay(1000);
  }
  
}

void play_P2()
{
  //p2 chance
  int tone_1 = 0;
  int i=3;
  int count_1 = 0;
  for(; tone_1 != 1; i++)
  {    
    count_1++;
    int reading = digitalRead(i);
    if(reading)
    {
      tone_1 = 1;
      break;
    }
    
  }

  i--;
  Serial.println("p2 challenge is ");  
  Serial.println(i);

  // int p_ch = 0;
  // for(int q = A0; q <= A5; q++)
  // {
  //   if(analogRead(q) > 500)
  //   {
  //     break;
  //   }
  //   p_ch++;
  //   Serial.println(analogRead(q));
  // }
  //playing song
  for (int j = i; j <i + 6; j++) {
    tone(8, melody[j%6]);
    delay(noteDuration);

  }    
  
  noTone(8); // no tone for the duration specified by noteDuration
  delay(noteDuration);

  //p1 response
  int tone_2 = 0;
  int k=2;
  int count_2 = 0;
  for(; tone_2 != 1; k++)
  {    
    count_2++;
    int reading = digitalRead(k);
    if(reading)
    {
      tone_2 = 1;
      break;
    }
    
  }

  Serial.println("p1 response is ");  
  Serial.println(k);
  
  if(k != i)
  {
    if(digitalRead(P1_L1))
    digitalWrite(P1_L1, 0);

    else if(digitalRead(P1_L2))
    digitalWrite(P1_L2, 0);



    else
    {
      digitalWrite(P1_L1, 255);
      delay(500);
      digitalWrite(P1_L1, 0);
      delay(500);
      digitalWrite(P1_L2, 255);
      delay(500);
      digitalWrite(P1_L2, 0);
      delay(500);
      digitalWrite(P1_L3, 255);
      delay(500);
      digitalWrite(P1_L3, 0);
      delay(500);
      digitalWrite(P2_L1, 255);
      delay(500);
      digitalWrite(P2_L1, 0);
      delay(500);
      digitalWrite(P2_L2, 255);
      delay(500);
      digitalWrite(P2_L2, 0);
      delay(500);
      digitalWrite(P2_L3, 255);
      delay(500);
      digitalWrite(P2_L3, 0);
      delay(500);

      //restart the game
      digitalWrite(P1_L1, 255);
      digitalWrite(P1_L2, 255);
      digitalWrite(P1_L3, 255);
      digitalWrite(P2_L1, 255);
      digitalWrite(P2_L2, 255);
      digitalWrite(P2_L3, 255);

    }
  }
}

void play_P1()
{
  //p2 chance
  int tone_1 = 0;
  int i=3;
  int count_1 = 0;
  for(; tone_1 != 1; i++)
  {    
    count_1++;
    int reading = digitalRead(i);
    if(reading)
    {
      tone_1 = 1;
      break;
    }
    
  }

  i--;
  Serial.println("p1 challenge is ");  
  Serial.println(i);

  // int p_ch = 0;
  // for(int q = A0; q <= A5; q++)
  // {
  //   if(analogRead(q) > 500)
  //   {
  //     break;
  //   }
  //   p_ch++;
  //   Serial.println(analogRead(q));
  // }
  //playing song
  for (int j = i; j <i + 6; j++) {
    tone(8, melody[j%6]);
    delay(noteDuration);

  }    
  
  noTone(8); // no tone for the duration specified by noteDuration
  delay(noteDuration);

  //p1 response
  int tone_2 = 0;
  int k=2;
  int count_2 = 0;
  for(; tone_2 != 1; k++)
  {    
    count_2++;
    int reading = digitalRead(k);
    if(reading)
    {
      tone_2 = 1;
      break;
    }
    
  }

  Serial.println("p2 response is ");  
  Serial.println(k);
  
  if(k != i)
  {
    if(digitalRead(P2_L1))
    digitalWrite(P2_L1, 0);

    else if(digitalRead(P2_L2))
    digitalWrite(P2_L2, 0);   

    else
        {
      digitalWrite(P1_L1, 255);
      delay(500);
      digitalWrite(P1_L1, 0);
      delay(500);
      digitalWrite(P1_L2, 255);
      delay(500);
      digitalWrite(P1_L2, 0);
      delay(500);
      digitalWrite(P1_L3, 255);
      delay(500);
      digitalWrite(P1_L3, 0);
      delay(500);
      digitalWrite(P2_L1, 255);
      delay(500);
      digitalWrite(P2_L1, 0);
      delay(500);
      digitalWrite(P2_L2, 255);
      delay(500);
      digitalWrite(P2_L2, 0);
      delay(500);
      digitalWrite(P2_L3, 255);
      delay(500);
      digitalWrite(P2_L3, 0);
      delay(500);

      //restart the game
      digitalWrite(P1_L1, 255);
      digitalWrite(P1_L2, 255);
      digitalWrite(P1_L3, 255);
      digitalWrite(P2_L1, 255);
      digitalWrite(P2_L2, 255);
      digitalWrite(P2_L3, 255);

    }
  }
}

void play_online()
{
  int p_ch = rand() % 6;
  Serial.println("computer challenge is ");
  Serial.println(p_ch);
  
  for (int j = p_ch; j <p_ch + 6; j++) {
    tone(8, melody[j%6]);
    delay(noteDuration);

  }    
  
  noTone(8); // no tone for the duration specified by noteDuration
  delay(noteDuration);

  //p1 response
  int tone_2 = 0;
  int k=2;
  int count_2 = 0;
  for(; tone_2 != 1; k++)
  {    
    count_2++;
    int reading = digitalRead(k);
    if(reading)
    {
      tone_2 = 1;
      break;
    }
    
  }

  Serial.println("player response is "); 
  Serial.println(k); 
  int p_re = k;

  if(p_ch != p_re)
  {
    if(digitalRead(P1_L1))
    digitalWrite(P1_L1, 0);

    else if(digitalRead(P1_L2))
    digitalWrite(P1_L2, 0);   

    else
        {
      digitalWrite(P1_L1, 255);
      delay(500);
      digitalWrite(P1_L1, 0);
      delay(500);
      digitalWrite(P1_L2, 255);
      delay(500);
      digitalWrite(P1_L2, 0);
      delay(500);
      digitalWrite(P1_L3, 255);
      delay(500);
      digitalWrite(P1_L3, 0);
      delay(500);
      digitalWrite(P2_L1, 255);
      delay(500);
      digitalWrite(P2_L1, 0);
      delay(500);
      digitalWrite(P2_L2, 255);
      delay(500);
      digitalWrite(P2_L2, 0);
      delay(500);
      digitalWrite(P2_L3, 255);
      delay(500);
      digitalWrite(P2_L3, 0);
      delay(500);

      //restart the game
      digitalWrite(P1_L1, 255);
      digitalWrite(P1_L2, 255);
      digitalWrite(P1_L3, 255);
      digitalWrite(P2_L1, 255);
      digitalWrite(P2_L2, 255);
      digitalWrite(P2_L3, 255);

    }
  }
}