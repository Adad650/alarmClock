#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int buttonMinute = 5;
const int buttonHour = 3;
const int buttonConfirm = 6;
const int buzzerPin = 4;

int buttonStateMinute = 0;
int lastButtonStateMinute = 0;

int buttonStateHour = 0;
int lastButtonStateHour = 0;

int buttonStateConfirm = 0;
int lastButtonStateConfirm = 0;

int hours = 0;
int minutes = 0;
bool alarmSet = false;


void setup() {
  lcd.begin(16, 2);
  Serial.begin(115200);
  pinMode(buttonMinute, INPUT_PULLUP);
  pinMode(buttonHour, INPUT_PULLUP);
  pinMode(buttonConfirm, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("h: 0");
  lcd.setCursor(0, 1);
  lcd.print("m: 0");
}

void loop() {
  if (!alarmSet) {

    // read the xxxx
    buttonStateHour = digitalRead(buttonHour);
    if (buttonStateHour == LOW && lastButtonStateHour == HIGH) { //xxx
      hours++;
      if (hours > 23) hours = 0;
      lcd.setCursor(0, 0);
      lcd.print("h:");
      lcd.print(hours);
      lcd.print("      ");
      delay(300);
    }
    lastButtonStateHour = buttonStateHour;

    // read the state of the minute button
    buttonStateMinute = digitalRead(buttonMinute);
    if (buttonStateMinute == LOW && lastButtonStateMinute == HIGH) { // if the minute button is pressed
      minutes++;
      if (minutes > 59) minutes = 0;
      lcd.setCursor(0, 1);
      lcd.print("m:");
      lcd.print(minutes);
      lcd.print("      ");
      delay(300);
    }
    lastButtonStateMinute = buttonStateMinute;

    // find out if the confirm button is pressed
    buttonStateConfirm = digitalRead(buttonConfirm);
    if (buttonStateConfirm == LOW && lastButtonStateConfirm == HIGH) { // yes, the confirm button is pressed
      lcd.clear();
      lcd.print("Alarm Set!");
      alarmSet = true;
      delay(500);
    } 
    lastButtonStateConfirm = buttonStateConfirm;
  } // end of if(!alarmset)

  else { // if alarmset
    int totalMinutes = hours * 60 + minutes;

    while (totalMinutes >= 0) {
      int remainingHours = totalMinutes / 60;
      int remainingMinutes = totalMinutes % 60;

      // make a function to show time left
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Time Left:");
      lcd.setCursor(0, 1);
      lcd.print(remainingHours);
      lcd.print("h ");
      lcd.print(remainingMinutes);
      lcd.print("m");

      delay(60000); // sleep until it is time to refresh the screen. 
      totalMinutes--;
    }

    // beep 3 times // todo: make a function
    for (int i = 0; i < 20; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(50);
    }
    hours = 0;
    minutes = 0;
    alarmSet = false;

    lcd.clear();
    lcd.print("Alarm Reset");
    delay(2000);
    // todo: make a function to init the screen to home screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("h:0");
    lcd.setCursor(0, 1);
    lcd.print("m:0");
  }
}