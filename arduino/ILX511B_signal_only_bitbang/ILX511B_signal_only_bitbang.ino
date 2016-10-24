/*
ILX511 LINEAR CCD CONTROL : SIGNAL ONLY, BIT BANG

THIS CODE INTERFACES WITH A SONY ILX511 LINEAR CCD
AND GENERATES THE NECESSARY SIGNALS TO MEASURE LIGHT.
IN ORDER TO READ THE OUTPUT OF THE CCD THE CIRCUIT MUST
BE CONNECTED TO A OSCILLISCOPE AS IT DOES NOT SEND DATA TO A PC

THIS SCRIPT BIT BANGS TO GENERATE THE CLOCK SIGNAL
FOR MORE PRECISE CONTROL OVER THE INTEGRATION TIME USE THE
PWM CCD CODE (FORTHCOMING)
*/

//half pulse length of the clock signal in milliseconds
//a minimum of 2088 clock pulses are needed per read cycle
//therefore integration time ~ 2*half_pulse*2088  us
//integrations time is aproximate and effected by 
//delayMicroseconds() accuracy and other delays
int half_pulse =1;

void setup() 
{
  // set the clock (CLK) and read out gate (PINS) as output
  // in this case CLK = pin 6 and ROG = pin 5
  DDRD = DDRD | B11111100; 
}

void loop() 
{
 
  collectPhotons();
 
}

// generate CLK and ROG signals
// description of the timing periods
// can be found in the ILX511 datasheet
void collectPhotons() 
{  
  
  // CLK: low 
  // ROG: high
  PORTD = B00100000;
  
  // T5 clock pulse timing 1
  delayMicroseconds(1);
  
  // CLK: high
  // ROG: low
  PORTD = B01000000;
  
  // T7 ROG pulse period
  delayMicroseconds(3);
  
  // CLK: high
  // ROG: high
  PORTD = B01100000;
  
  //  T9 clock pulse timing 2
  delayMicroseconds(1);
  
  //  commence photon collection 
  for (int i = 0; i < 2088; i++)
  {
    //  CLK: low 
    //  ROG: high
    PORTD = B00100000;
    delayMicroseconds(half_pulse);
    
    // CLK: high 
    // ROG: high
    PORTD = B01100000;
    delayMicroseconds(half_pulse);
  }  
}


