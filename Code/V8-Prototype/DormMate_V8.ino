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
// TIME MODE VARIABLES
bool is24hours = true;
int timeModeRow = 0;
// -------- ALARM VARIABLES --------
int alarmHour = 7;
int alarmMinute = 30;

bool alarmEnabled = false;
bool alarmRinging = false;

bool alarmTriggered = false;

int alarmEditMode = 0; // 0 = hour, 1 = minute
// ---------- Alarm --------------------
# define NOTE_C 262// HZ
# define NOTE_E 330// HZ
# define NOTE_G 392// HZ
# define NOTE_A 440 // HZ

const int speaker = 6; //SPEAKER on pin 12
//--------------Reminders--------------
// ---------- REMINDERS ----------
int reminderHour0 = 0;
int reminderMinute0 = 0;
int reminderHour1 = 0;
int reminderMinute1 = 0;
int reminderHour2 = 0;
int reminderMinute2 = 0;
int reminderHour3 = 0;
int reminderMinute3 = 0;
int reminderHour4 = 0;
int reminderMinute4 = 0;

int currentReminderMinute =0;// the minute if the current reminder
int currentReminder = 0;// select one of the reminders in the array


bool reminderEnabled = false;
bool reminderTriggered = false;
bool reminderRinging = false;

// reminder menu navigation
int r = 0;
int c = 1;

String Reminderd[] =
{
  "MATH HW",
  "HUM PAPER",
  "SPORT",
  "MEETING",
  "PRACTICE"
};

// open reminder screens
bool rem0Open = false;
bool rem1Open = false;
bool rem2Open = false;
bool rem3Open = false;
bool rem4Open = false;

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
  "Time",//0
  "Sensor value",//1
  "motivation message",//2
  "Set time",//3
  "Time mode",//4
  "Alarm"     ,//5
  "REMINDER",//6
};
int x=0 ;
int y=1;
//control arrow
int selectedRow = 0;
/*Screen 0 = menu
  screen 1 = clock
  screen 2 = sensor value
  screen3 = motivation
  screen 4 = set time
  screen 5 = time mode
  screen 6 = alarm
  screen 7 = alarm screen 
  screen 8 = Reminder
  screen 9 = ----
  screen 10 = rem0
  screen 11 = reminder screen
  screen 12 = rem1
  screen 13 = rem2
  screen 14 = rem3
  screen 15 = rem4  
  screen 16 = schedule my classes

*/

void setup()
{
  lcd.begin(16, 2);

  Serial.begin(9600);

  pinMode(YLED, OUTPUT);
  pinMode(speaker, OUTPUT);// speaker

  irReceiver.begin();

  randomSeed(analogRead(A1));
}

void loop()
{

  //------ LIGHT------------
  autoLight();

  // -------- CLOCK --------
  VirtualTimeCount();
  //-------- ALARM CHECK ------
  alarmCheck();

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
    //-------- SCREEN 5 -----------
    timeMode() ;
    //--------- SCREEN 6 ------------ 
    alarm();
    //-------- SCREEN 7 -------------
    alarmScreen();
    Remindercheck();
    //----SCREEN 8-------
    Reminder();
    //------SCREEN 10 ------
    reminder0();
    reminder1();
    reminder2();
    reminder3();
    reminder4();
    ReminderScreen();

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
      //screen = 1;
    }

    // BUTTON 2
    if (irReceiver.data == 0xFF18E7)
    {
      //screen = 2;
    }

    // BUTTON 3
    if (irReceiver.data == 0xFF7A85)
    {
      //screen = 3;
    }
    
    // BUTTON 4
    if (irReceiver.data == 0xFF10EF)
    {
     // screen = 4;
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
                if(y < 6)
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

        // ---------- PLAY / OK BUTTON ----------
        if(irReceiver.data == 0xFF02FD)
        {
            int selectedItem;

            // Determine selected item
            if(selectedRow == 0)
            {
                selectedItem = x;
            }
            else
            {
                selectedItem = y;
            }

            // Open screen
            switch(selectedItem)
            {
                case 0:
                    screen = 1;
                    break;

                case 1:
                    screen = 2;
                    break;

                case 2:
                    screen = 3;
                    break;

                case 3:
                    screen = 4;
                    break;

                case 4:
                    screen = 5;
                    break;
                case 5:
                    screen = 6;
                    break;  
                case 6:
                    screen = 8;
                    break;      
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

    if(is24hours)
    {
        // -------- 24H --------
        if(H < 10) lcd.print("0");
        lcd.print(H);

        lcd.print(":");

        if(M < 10) lcd.print("0");
        lcd.print(M);
    }
    else
    {
        // -------- 12H --------
        int displayHour = H;
        String period = "AM";

        if(H == 0)
        {
            displayHour = 12;
        }
        else if(H == 12)
        {
            period = "PM";
        }
        else if(H > 12)
        {
            displayHour = H - 12;
            period = "PM";
        }

        if(displayHour < 10) lcd.print("0");
        lcd.print(displayHour);

        lcd.print(":");

        if(M < 10) lcd.print("0");
        lcd.print(M);

        lcd.print(period);
    }

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

   // screen = 1;
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

void timeMode(){
  if(screen == 5){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Time mode");

        // ---------- Draw Arrow ----------
        lcd.setCursor(0,1);
        if(timeModeRow == 0)
        {
            lcd.print(" >12h  24h");
        }
        else
        {
            lcd.print(" 12h  >24h");
        }

       // left button
       if(irReceiver.data == 0xFF22DD){
        timeModeRow = 0;
        irReceiver.data = 0;
       }

       // right button
       if(irReceiver.data == 0xFFC23D){
          
          timeModeRow = 1;
          irReceiver.data = 0;

       }
       
       //play button
       if(irReceiver.data == 0xFF02FD){
        if(timeModeRow == 0){
          is24hours = false;
        }
        else{
          is24hours = true;
        }
        screen = 1;
        irReceiver.data = 0;
       }

  }
}

void alarm()
{
    if(screen == 6)
    {
        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Alarm");

        // display alarm time
        lcd.setCursor(0,1);

        if(alarmHour < 10) lcd.print("0");
        lcd.print(alarmHour);

        lcd.print(":");

        if(alarmMinute < 10) lcd.print("0");
        lcd.print(alarmMinute);

        lcd.print(" ");

        if(alarmEnabled)
        {
            lcd.print("ON");
        }
        else
        {
            lcd.print("OFF");
        }

        // -------- HOUR UP --------
        if(irReceiver.data == 0xFF906F)
        {
            alarmHour++;

            if(alarmHour == 24)
            {
                alarmHour = 0;
            }

            irReceiver.data = 0;
        }

        // -------- HOUR DOWN --------
        if(irReceiver.data == 0xFFE01F)
        {
            alarmHour--;

            if(alarmHour < 0)
            {
                alarmHour = 23;
            }

            irReceiver.data = 0;
        }

        // -------- MINUTE UP --------
        if(irReceiver.data == 0xFFC23D)
        {
            alarmMinute++;

            if(alarmMinute == 60)
            {
                alarmMinute = 0;
            }

            irReceiver.data = 0;
        }

        // -------- MINUTE DOWN --------
        if(irReceiver.data == 0xFF22DD)
        {
            alarmMinute--;

            if(alarmMinute < 0)
            {
                alarmMinute = 59;
            }

            irReceiver.data = 0;
        }

        // -------- OK BUTTON --------
        if(irReceiver.data == 0xFF02FD)
        {
            alarmEnabled = !alarmEnabled;
            irReceiver.data = 0;
        }
    }
}
void alarmCheck()
{
    // -------- Trigger alarm ONCE --------
    if(alarmEnabled &&
       !alarmTriggered)
    {
        if(H == alarmHour &&
           M == alarmMinute)
        {
            alarmRinging = true;
            alarmTriggered = true;
            screen = 7;
        }
    }

    // -------- Ringing --------
    if(alarmRinging)
    {
        playTone(262,200);
        playTone(330,200);
        playTone(440,200);

        // BUTTON 1 stops alarm
        if(irReceiver.data == 0xFF30CF)
        {
            alarmRinging = false;

            screen = 1;

            irReceiver.data = 0;
        }
    }

    // -------- Reset trigger next minute --------
    if(M != alarmMinute)
    {
        alarmTriggered = false;
    }
}

void playTone(int frequency, int duration)
{
    long delayValue = 1000000 / frequency / 2;
    long cycles = frequency * duration / 1000;

    for(long i = 0; i < cycles; i++)
    {
        digitalWrite(speaker, HIGH);
        delayMicroseconds(delayValue);

        digitalWrite(speaker, LOW);
        delayMicroseconds(delayValue);
    }
}

void alarmScreen(){
  if(screen == 7){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PRESS 1(STOP)");
  }

  // JUST TRYING TO SEE IF IT WILL STOP AND RETURN TO SCREEN 1
          if(irReceiver.data ==   0xFF30CF)
        {
            alarmRinging = false;
            irReceiver.data = 0;
            screen = 1;// back to time
        }
}
void Reminder()
{
    if(screen == 8)
    {
        lcd.clear();

        // -------- Draw Arrow --------
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

        // -------- Display Menu --------
        lcd.setCursor(2,0);
        lcd.print(Reminderd[r]);

        lcd.setCursor(2,1);
        lcd.print(Reminderd[c]);

        // -------- DOWN BUTTON --------
        if(irReceiver.data == 0xFFE01F)
        {
            if(selectedRow == 0)
            {
                selectedRow = 1;
            }
            else
            {
                if(c < 4)
                {
                    r++;
                    c++;
                }
            }

            irReceiver.data = 0;
        }

        // -------- UP BUTTON --------
        if(irReceiver.data == 0xFF906F)
        {
            if(selectedRow == 1)
            {
                selectedRow = 0;
            }
            else
            {
                if(r > 0)
                {
                    r--;
                    c--;
                }
            }

            irReceiver.data = 0;
        }

        // -------- OK BUTTON --------
        if(irReceiver.data == 0xFF02FD)
        {
            int selectedItem;

            if(selectedRow == 0)
            {
                selectedItem = r;
            }
            else
            {
                selectedItem = c;
            }

            switch(selectedItem)
            {
                case 0:
                    rem0Open = true;
                    screen = 10;
                    break;
                case 1: 
                    rem1Open = true;
                    screen   = 12;
                    break;    
                case 2: 
                    rem2Open = true;
                    screen   = 13;
                    break; 
                case 3: 
                    rem3Open = true;
                    screen   = 14;
                    break;  
                case 4: 
                    rem4Open = true;
                    screen   = 15;
                    break;                                                            
            }

            irReceiver.data = 0;
        }
    }
}
void reminder0()
{
    if(rem0Open && screen == 10)
    {
        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Reminder at");

        lcd.setCursor(0,1);

        if(reminderHour0 < 10)
            lcd.print("0");

        lcd.print(reminderHour0);

        lcd.print(":");

        if(reminderMinute0 < 10)
            lcd.print("0");

        lcd.print(reminderMinute0);

        lcd.print(" ");

        if(reminderEnabled)
        {
            lcd.print("ON");
        }
        else
        {
            lcd.print("OFF");
        }

        // HOUR UP
        if(irReceiver.data == 0xFF906F)
        {
            reminderHour0++;

            if(reminderHour0 == 24)
            {
                reminderHour0 = 0;
            }

            irReceiver.data = 0;
        }

        // HOUR DOWN
        if(irReceiver.data == 0xFFE01F)
        {
            reminderHour0--;

            if(reminderHour0 < 0)
            {
                reminderHour0 = 23;
            }

            irReceiver.data = 0;
        }

        // MINUTE UP
        if(irReceiver.data == 0xFFC23D)
        {
            reminderMinute0++;

            if(reminderMinute0 == 60)
            {
                reminderMinute0 = 0;
            }

            irReceiver.data = 0;
        }

        // MINUTE DOWN
        if(irReceiver.data == 0xFF22DD)
        {
            reminderMinute0--;

            if(reminderMinute0 < 0)
            {
                reminderMinute0 = 59;
            }

            irReceiver.data = 0;
        }

        // OK BUTTON
        if(irReceiver.data == 0xFF02FD)
        {
            reminderEnabled = !reminderEnabled;
            irReceiver.data = 0;
        }

        // BUTTON 0 returns menu
        if(irReceiver.data == 0xFF6897)
        {
            rem0Open = false;
            screen = 8;

            irReceiver.data = 0;
        }
    }
}

void reminder1()
{
    if(rem1Open && screen == 12)
    {
        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Reminder at");

        lcd.setCursor(0,1);

        if(reminderHour1 < 10)
            lcd.print("0");

        lcd.print(reminderHour1);

        lcd.print(":");

        if(reminderMinute1 < 10)
            lcd.print("0");

        lcd.print(reminderMinute1);

        lcd.print(" ");

        if(reminderEnabled)
        {
            lcd.print("ON");
        }
        else
        {
            lcd.print("OFF");
        }

        // HOUR UP
        if(irReceiver.data == 0xFF906F)
        {
            reminderHour1++;

            if(reminderHour1 == 24)
            {
                reminderHour1 = 0;
            }

            irReceiver.data = 0;
        }

        // HOUR DOWN
        if(irReceiver.data == 0xFFE01F)
        {
            reminderHour1--;

            if(reminderHour1 < 0)
            {
                reminderHour1 = 23;
            }

            irReceiver.data = 0;
        }

        // MINUTE UP
        if(irReceiver.data == 0xFFC23D)
        {
            reminderMinute1++;

            if(reminderMinute1 == 60)
            {
                reminderMinute1 = 0;
            }

            irReceiver.data = 0;
        }

        // MINUTE DOWN
        if(irReceiver.data == 0xFF22DD)
        {
            reminderMinute1--;

            if(reminderMinute1 < 0)
            {
                reminderMinute1 = 59;
            }

            irReceiver.data = 0;
        }

        // OK BUTTON
        if(irReceiver.data == 0xFF02FD)
        {
            reminderEnabled = !reminderEnabled;
            irReceiver.data = 0;
        }

        // BUTTON 0 returns menu
        if(irReceiver.data == 0xFF6897)
        {
            rem1Open = false;
            screen = 8;

            irReceiver.data = 0;
        }
    }
}
void reminder2()
{
    if(rem2Open && screen == 13)
    {
        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Reminder at");

        lcd.setCursor(0,1);

        if(reminderHour2 < 10)
            lcd.print("0");

        lcd.print(reminderHour2);

        lcd.print(":");

        if(reminderMinute2 < 10)
            lcd.print("0");

        lcd.print(reminderMinute2);

        lcd.print(" ");

        if(reminderEnabled)
        {
            lcd.print("ON");
        }
        else
        {
            lcd.print("OFF");
        }

        // HOUR UP
        if(irReceiver.data == 0xFF906F)
        {
            reminderHour2++;

            if(reminderHour2 == 24)
            {
                reminderHour2 = 0;
            }

            irReceiver.data = 0;
        }

        // HOUR DOWN
        if(irReceiver.data == 0xFFE01F)
        {
            reminderHour2--;

            if(reminderHour2 < 0)
            {
                reminderHour2 = 23;
            }

            irReceiver.data = 0;
        }

        // MINUTE UP
        if(irReceiver.data == 0xFFC23D)
        {
            reminderMinute2++;

            if(reminderMinute2 == 60)
            {
                reminderMinute2 = 0;
            }

            irReceiver.data = 0;
        }

        // MINUTE DOWN
        if(irReceiver.data == 0xFF22DD)
        {
            reminderMinute2--;

            if(reminderMinute2 < 0)
            {
                reminderMinute2 = 59;
            }

            irReceiver.data = 0;
        }

        // OK BUTTON
        if(irReceiver.data == 0xFF02FD)
        {
            reminderEnabled = !reminderEnabled;
            irReceiver.data = 0;
        }

        // BUTTON 0 returns menu
        if(irReceiver.data == 0xFF6897)
        {
            rem2Open = false;
            screen = 8;

            irReceiver.data = 0;
        }
    }
}
void reminder3()
{
    if(rem3Open && screen == 14)
    {
        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Reminder at");

        lcd.setCursor(0,1);

        if(reminderHour3 < 10)
            lcd.print("0");

        lcd.print(reminderHour3);

        lcd.print(":");

        if(reminderMinute3 < 10)
            lcd.print("0");

        lcd.print(reminderMinute3);

        lcd.print(" ");

        if(reminderEnabled)
        {
            lcd.print("ON");
        }
        else
        {
            lcd.print("OFF");
        }

        // HOUR UP
        if(irReceiver.data == 0xFF906F)
        {
            reminderHour3++;

            if(reminderHour3 == 24)
            {
                reminderHour3 = 0;
            }

            irReceiver.data = 0;
        }

        // HOUR DOWN
        if(irReceiver.data == 0xFFE01F)
        {
            reminderHour3--;

            if(reminderHour3 < 0)
            {
                reminderHour3 = 23;
            }

            irReceiver.data = 0;
        }

        // MINUTE UP
        if(irReceiver.data == 0xFFC23D)
        {
            reminderMinute3++;

            if(reminderMinute3 == 60)
            {
                reminderMinute3 = 0;
            }

            irReceiver.data = 0;
        }

        // MINUTE DOWN
        if(irReceiver.data == 0xFF22DD)
        {
            reminderMinute3--;

            if(reminderMinute3 < 0)
            {
                reminderMinute3 = 59;
            }

            irReceiver.data = 0;
        }

        // OK BUTTON
        if(irReceiver.data == 0xFF02FD)
        {
            reminderEnabled = !reminderEnabled;
            irReceiver.data = 0;
        }

        // BUTTON 0 returns menu
        if(irReceiver.data == 0xFF6897)
        {
            rem3Open = false;
            screen = 8;

            irReceiver.data = 0;
        }
    }
}

void reminder4()
{
    if(rem4Open && screen == 15)
    {
        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Reminder at");

        lcd.setCursor(0,1);

        if(reminderHour4 < 10)
            lcd.print("0");

        lcd.print(reminderHour4);

        lcd.print(":");

        if(reminderMinute4 < 10)
            lcd.print("0");

        lcd.print(reminderMinute4);

        lcd.print(" ");

        if(reminderEnabled)
        {
            lcd.print("ON");
        }
        else
        {
            lcd.print("OFF");
        }

        // HOUR UP
        if(irReceiver.data == 0xFF906F)
        {
            reminderHour4++;

            if(reminderHour4 == 24)
            {
                reminderHour4 = 0;
            }

            irReceiver.data = 0;
        }

        // HOUR DOWN
        if(irReceiver.data == 0xFFE01F)
        {
            reminderHour4--;

            if(reminderHour4 < 0)
            {
                reminderHour4 = 23;
            }

            irReceiver.data = 0;
        }

        // MINUTE UP
        if(irReceiver.data == 0xFFC23D)
        {
            reminderMinute4++;

            if(reminderMinute4 == 60)
            {
                reminderMinute4 = 0;
            }

            irReceiver.data = 0;
        }

        // MINUTE DOWN
        if(irReceiver.data == 0xFF22DD)
        {
            reminderMinute4--;

            if(reminderMinute4 < 0)
            {
                reminderMinute4 = 59;
            }

            irReceiver.data = 0;
        }

        // OK BUTTON
        if(irReceiver.data == 0xFF02FD)
        {
            reminderEnabled = !reminderEnabled;
            irReceiver.data = 0;
        }

        // BUTTON 0 returns menu
        if(irReceiver.data == 0xFF6897)
        {
            rem4Open = false;
            screen = 8;

            irReceiver.data = 0;
        }
    }
}


void Remindercheck()
{
    if(reminderEnabled &&
       !reminderTriggered)
    {
        if(H == reminderHour0 &&
           M == reminderMinute0)
        {
            reminderRinging = true;
            reminderTriggered = true;
            currentReminder =0;

            screen = 11;
             currentReminderMinute = reminderMinute0;
        }

        if(H == reminderHour1 &&
           M == reminderMinute1)
        {
            reminderRinging = true;
            reminderTriggered = true;
            currentReminder=1;

            screen = 11;
             currentReminderMinute = reminderMinute1;
        }

        if(H == reminderHour2 &&
           M == reminderMinute2)
        {
            reminderRinging = true;
            reminderTriggered = true;
            currentReminder=2;

            screen = 11;
             currentReminderMinute = reminderMinute2;
        }

        if(H == reminderHour3 &&
           M == reminderMinute3)
        {
            reminderRinging = true;
            reminderTriggered = true;
            currentReminder=3;

            screen = 11;
             currentReminderMinute = reminderMinute3;
        } 
        if(H == reminderHour4 &&
           M == reminderMinute4)
        {
            reminderRinging = true;
            reminderTriggered = true;
            currentReminder=4;

            screen = 11;
             currentReminderMinute = reminderMinute4;
        }                               
        
    }

    // reset next minute
     if(M != currentReminderMinute)
    {
        reminderTriggered = false;
    }
    
}

void ReminderScreen()
{
    if(screen == 11)
    {
        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("REMINDER");

        lcd.setCursor(0,1);
        lcd.print(Reminderd[currentReminder]);

        playTone(880,200);
        playTone(466,200);
        playTone(494,200);

        // BUTTON 1 stop reminder
        if(irReceiver.data == 0xFF30CF)
        {
            reminderRinging = false;
           // r = 0;
           // c = 1;
           // selectedRow = 0;

            lcd.clear();
            screen = 1;

            irReceiver.data = 0;
        }
    }
}
