/*
 * CapaSens file containing functions for managing textile capacitive 
 * touch sensors in NAPaC project
 */

const int RED_TOUCH = T3; //IO15
const int YEL_TOUCH = T6; //IO14
const int GRN_TOUCH = T4; //IO13

const int THRESHOLD_RED = 10; //to compare first and current sensor input
const int THRESHOLD_YEL = 30; //to compare first and current sensor input
const int THRESHOLD_GRN = 25; //to compare first and current sensor input

const int MAX_DIFF = 3; //to compare previous and current sensor input

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
//        Serial.println(debug_measurement);
//        displayMonitorTouchSensors();
        
        current_read_RED = touchRead(RED_TOUCH);
        current_read_YEL = touchRead(YEL_TOUCH);
        current_read_GRN = touchRead(GRN_TOUCH);
        
        if ( current_read_RED < THRESHOLD_RED ){
                toggleLED("RED");
        }
          

        else if ( current_read_YEL < THRESHOLD_RED )
        {
                toggleLED("YEL");
        }
       

        else if (current_read_GRN < THRESHOLD_RED)
        {
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


