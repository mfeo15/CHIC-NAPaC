// ESP32 Touch Test
// Just test touch pin to activate corresponding LED

const int RED_LED = 21;
const int YEL_LED = 22;
const int GRN_LED = 23;

const int RED_TOUCH = T3; //IO15
const int YEL_TOUCH = T6; //IO14
const int GRN_TOUCH = T4; //IO13

const int THRESHOLD_RED = 25; //to compare first and current sensor input
const int THRESHOLD_YEL = 30; //to compare first and current sensor input
const int THRESHOLD_GRN = 25; //to compare first and current sensor input

const int MAX_DIFF = 3; //to compare previous and current sensor input

void setup()
{
    Serial.begin(115200);
    delay(1000); // give me time to bring up serial monitor
    
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(RED_LED, OUTPUT);
    pinMode(YEL_LED, OUTPUT);
    pinMode(GRN_LED, OUTPUT);

    Serial.println();
    Serial.println();
    Serial.println("ESP32 Sensors Touch Test");
    Serial.println();
    Serial.println();
}

void toggleLED(String color)
{
    //Serial.print("Color of LED to light on: "); Serial.println(color);
    
    if (color == "RED") 
    {
        Serial.println("Toggling RED_LED");
        if ( digitalRead(RED_LED) == LOW)
            digitalWrite (RED_LED, HIGH);  // turn on the LED
        else
            digitalWrite (RED_LED, LOW);  // turn off the LED
        return;
    }
  
    if (color == "GRN") 
    {
        Serial.println("Toggling GRN_LED");
        if ( digitalRead(GRN_LED) == LOW)
            digitalWrite (GRN_LED, HIGH);  // turn on the LED
        else
            digitalWrite (GRN_LED, LOW);  // turn off the LED
        return;
    }
  
    if (color == "YEL") 
    {
        Serial.println("Toggling YEL_LED");
         if ( digitalRead(YEL_LED) == LOW)
            digitalWrite (YEL_LED, HIGH);  // turn on the LED
        else
            digitalWrite (YEL_LED, LOW);  // turn off the LED
        return;
    }
}

void readTouchSensor()
{
    static bool first_measure = 1; 
    static unsigned int counter, debug_measurement;
    static int first_read_RED, first_read_YEL, first_read_GRN;
    static int prev_read_RED, prev_read_YEL, prev_read_GRN;
    
    int current_read_RED, current_read_YEL, current_read_GRN;

    if (first_measure == 1)
    {
        //Initialization
        first_read_RED = touchRead(RED_TOUCH);
        first_read_YEL = touchRead(YEL_TOUCH);
        first_read_GRN = touchRead(GRN_TOUCH);
            
        first_measure = 0;
        counter = 0;
        debug_measurement = 0;
        return;
    }

    else if (counter > 1000000/4)
    {
        //Serial.print("Comparing previous_read_RED and current_read_RED with THRESHOLD "); Serial.println(THRESHOLD);
        Serial.println(debug_measurement);
        displayMonitorTouchSensors();
        
        current_read_RED = touchRead(RED_TOUCH);
        current_read_YEL = touchRead(YEL_TOUCH);
        current_read_GRN = touchRead(GRN_TOUCH);
        
        if ( abs(first_read_RED - current_read_RED) >= THRESHOLD_RED and (first_read_RED > current_read_RED) )
        {
            if ( abs(prev_read_RED - current_read_RED) <= MAX_DIFF )
                toggleLED("RED");
        }
          

        else if ( abs(first_read_YEL - current_read_YEL) >= THRESHOLD_YEL and (first_read_YEL > current_read_YEL) )
        {
             if ( abs(prev_read_YEL - current_read_YEL) <= MAX_DIFF )
                toggleLED("YEL");
        }
       

        else if ( abs(first_read_GRN - current_read_GRN) >= THRESHOLD_GRN and (first_read_GRN > current_read_GRN))
        {
            if ( abs(prev_read_GRN - current_read_GRN) <= MAX_DIFF )
                toggleLED("GRN");  
        }

       prev_read_RED = current_read_RED;
       prev_read_YEL = current_read_YEL;
       prev_read_GRN = current_read_GRN;
       
       counter = 0;
       debug_measurement++;
    } 

    counter++;
}

void displayMonitorTouchSensors()
{
    Serial.print("RED : "); Serial.println(touchRead(RED_TOUCH));
    Serial.print("YEL : "); Serial.println(touchRead(YEL_TOUCH));
    Serial.print("GRN : "); Serial.println(touchRead(GRN_TOUCH));
    Serial.println("");
}

void loop()
{
    readTouchSensor();
   
    //delay(1000);
}
