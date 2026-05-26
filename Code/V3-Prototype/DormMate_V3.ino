#include <LiquidCrystal.h>
#include <AlashIRControlRX.h>

// ---------------- LCD ----------------
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// ---------------- NIGHT LIGHT ----------------
const int YLED = 7;
const int LIGHT = A0;

int val = 0;

// ---------------- TIMER ----------------
const unsigned long SECONDS = 60000;
unsigned long previousTime = 0;

int H = 10;
int M = 15;

// ---------------- IR REMOTE ----------------
AlashIRControlRX irReceiver(8);

// ---------------- SCREEN CONTROL ----------------
int screen = 0;

// ---------------- ENCOURAGEMENTS ----------------
String messages[] = {
  "Keep Going!",
  "You Got This!",
  "Stay Focused!",
  "Future Engineer!",
  "Never Give Up!"
};
String menud[]={
  "Time",
  "Sensor value",
  "motivation message",
  "Set time",
  "Auto mode",
};
int x=0 ;
int y=1;
//control arrow
int selectedRow = 0;

void setup()
{
  lcd.begin(16, 2);

  Serial.begin(9600);

  pinMode(YLED, OUTPUT);

  irReceiver.begin();

  randomSeed(analogRead(A1));
}

void loop()
{

  //------ LIGHT------------
  autoLight();

  // -------- CLOCK --------
  VirtualTimeCount();

  // -------- IR REMOTE --------
  RemoteControl();
  // -------- SCREEN 0 -------
  menu();
  // -------- SCREEN 1 --------
  clock();

  // -------- SCREEN 2 --------
  sensorvalue();

  // -------- SCREEN 3 --------
  motivation();
 // -------- SCREEN 4 --------
  setTime();

  delay(200);
}
void autoLight(){
    // -------- LIGHT SENSOR --------
  val = analogRead(LIGHT);

  // -------- AUTO NIGHT LIGHT --------
  if (val < 300)
  {
    digitalWrite(YLED, HIGH);
  }
  else
  {
    digitalWrite(YLED, LOW);
  }
}
void VirtualTimeCount(){
    // -------- CLOCK --------
    unsigned long currentTime = millis();
  if (currentTime - previousTime >= SECONDS)
  {
    M = M + 1;

    previousTime = currentTime;
  }

  if (M == 60)
  {
    H = H + 1;
    M = 0;
  }

  if (H == 24)
  {
    H = 0;
  }
}

void RemoteControl(){
  // -------- IR REMOTE --------
  if (irReceiver.check())
  {
    Serial.println(irReceiver.data, HEX);

    // BUTTON 0
    if(irReceiver.data == 0xFF6897)
    {
      screen = 0;
    }
    // BUTTON 1
    if (irReceiver.data == 0xFF30CF)
    {
      screen = 1;
    }

    // BUTTON 2
    if (irReceiver.data == 0xFF18E7)
    {
      screen = 2;
    }

    // BUTTON 3
    if (irReceiver.data == 0xFF7A85)
    {
      screen = 3;
    }
    
    // BUTTON 4
    if (irReceiver.data == 0xFF10EF)
    {
      screen = 4;
    }
  }
}
void menu()
{
    if(screen == 0)
    {
        lcd.clear();

        // ---------- Draw Arrow ----------
        if(selectedRow == 0)
        {
            lcd.setCursor(0,0);
            lcd.print(">");

            lcd.setCursor(0,1);
            lcd.print(" ");
        }
        else
        {
            lcd.setCursor(0,0);
            lcd.print(" ");

            lcd.setCursor(0,1);
            lcd.print(">");
        }

        // ---------- Display Menu ----------
        lcd.setCursor(2,0);
        lcd.print(menud[x]);

        lcd.setCursor(2,1);
        lcd.print(menud[y]);

        // ---------- DOWN BUTTON ----------
        if(irReceiver.data == 0xFFE01F)
        {
            // Move arrow down first
            if(selectedRow == 0)
            {
                selectedRow = 1;
            }
            else
            {
                // Scroll menu
                if(y < 4)
                {
                    x++;
                    y++;
                }
            }

            irReceiver.data = 0;
        }

        // ---------- UP BUTTON ----------
        if(irReceiver.data == 0xFF906F)
        {
            // Move arrow up first
            if(selectedRow == 1)
            {
                selectedRow = 0;
            }
            else
            {
                // Scroll upward
                if(x > 0)
                {
                    x--;
                    y--;
                }
            }

            irReceiver.data = 0;
        }
    }
}

void clock(){
    if (screen == 1)
  {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("TIME ");

    if (H < 10) lcd.print("0");
    lcd.print(H);

    lcd.print(":");

    if (M < 10) lcd.print("0");
    lcd.print(M);

    lcd.setCursor(0, 1);

    if (val < 350)
    {
      lcd.print("Room dark");
    }
    else
    {
      lcd.print("Room bright");
    }
  }
}
void sensorvalue(){
    if (screen == 2)
  {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Sensor Value");

    lcd.setCursor(0, 1);
    lcd.print(val);
  }
}

void motivation(){
    if (screen == 3)
  {
    lcd.clear();

    int msg = random(0, 5);

    lcd.setCursor(0, 0);
    lcd.print("Message:");

    lcd.setCursor(0, 1);
    lcd.print(messages[msg]);

    delay(2000);

    screen = 1;
  }
}

void setTime(){
  if(screen == 4)
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set Time      ");

    lcd.setCursor(0,1);

    if(H < 10) lcd.print("0");
    lcd.print(H);
    lcd.print(":");

    if(M < 10) lcd.print("0");
    lcd.print(M);

    // UP BUTTON -> increase hour
    if(irReceiver.data == 0xFF906F)
    {
        H=H+1;

        if(H == 24)
        {
            H = 0;
        }

        irReceiver.data = 0; // reset button
    }

    // DOWN BUTTON -> decrease hour
    if(irReceiver.data == 0xFFE01F)
    {
        H--;

        if(H < 0)
        {
            H = 23;
        }
        irReceiver.data = 0; // reset button
    }

    // RIGHT BUTTON -> increase minutes
    if(irReceiver.data == 0xFFC23D)
    {
        M++;

        if(M == 60)
        {
            M = 0;
        }
        irReceiver.data = 0; // reset button
    }

    // LEFT BUTTON -> decrease minutes
    if(irReceiver.data == 0xFF22DD)
    {
        M--;

        if(M < 0)
        {
            M = 59;
        }
        irReceiver.data = 0; // reset button
    }

    // PLAY/OK -> exit
    if(irReceiver.data == 0xFF02FD)
    {
        screen = 1;
    }
}
}
