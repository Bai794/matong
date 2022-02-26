
#include <Arduino.h>

#define sw1 2
#define sw2 3
#define sw3 4
#define sw4 5

uint8_t temp = 0;
int wait_time = 0;
uint8_t key_scan()
{
  int a[4] = {sw1, sw2, sw3, sw4};
  for (int i = 0; i < 4; i++)
  {
    if (digitalRead(a[i]) == 0)
    {
      delay(100);
      if (digitalRead(a[i]) == 0)
        return i + 1;
      else
        continue;
    }
    else
      continue;
  }
  return 0;
}
void set_moterSpeed(int s, int dir)
{
  if (dir == 0)
  {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  else
  {
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
  }
  if (s == 1)
  {
    set_moterSpeed(4, 0); 
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
    delay(500);
    wait_time = 1000;
    analogWrite(8, 250);
    delay(1000);
    analogWrite(8, 0);
  }
  if (s == 2)
  {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    wait_time -= 100;
    analogWrite(8, 250);
    delay(100);
    analogWrite(8, 0);
  }
  if (s == 3)
  {
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
    wait_time += 100;
    analogWrite(8, 250);
    delay(100);
    analogWrite(8, 0);
  }
  if (s == 4)
  {
    if (wait_time > 0)
    {
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      analogWrite(8, 250);
      delay(wait_time);
      wait_time = 0;
      analogWrite(8, 0);
    }
    else
    {
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      analogWrite(8, 250);
      delay(-wait_time);
      wait_time = 0;
      analogWrite(8, 0);
    }
  }
}
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  uint8_t key_num = key_scan();
  if (digitalRead(9))
  {
    set_moterSpeed(2, 0);
  }
  if (key_num < 4 && key_num > 0)
  {
    set_moterSpeed(key_num, 1); // 1代表正转
    Serial.println(key_num);
    Serial.println("  ");
    Serial.println(temp);
  }
  else if (key_num == 4)
  {
    set_moterSpeed(4, 0); 
    // if (temp > 0)
    //   set_moterSpeed(temp, 0); // 1代表正转
    // Serial.println(temp);
  }
  if (key_num)
    temp = key_num;
}
