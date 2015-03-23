long pulseCount = 0;  //a pulse counter variable

unsigned long pulseTime,lastTime, duration, totalDuration;

int samplingPeriod=1; // the number of seconds to measure 555 oscillations

int avenum=1; // number of samples to average
//int fivefivefive = 13; // the pin that powers the 555 subcircuit

void setup()
{
  Serial.begin(9600);
  
     // pinMode(fivefivefive, OUTPUT);   
           
}

void loop()
{
  //delay(1000); // imagine riffle is doing other stuff (like sleeping)
  
  // now make a conductivity measurement
  
  //turn on the 555 system
  //digitalWrite(fivefivefive,HIGH); //turns on the 555 timer subcircuit
  float pulseAve=0.;
  int pulseStats=0;
  
  for (int i=0;i<avenum;i++) {
    
  //delay(1000);
  
  pulseCount=0; //reset the pulse counter
  totalDuration=0;  //reset the totalDuration of all pulses measured
  
  attachInterrupt(0,onPulse,RISING); //attach an interrupt counter to interrupt pin 0 (digital pin #2) -- the only other possible pin on the 328p is interrupt pin #1 (digital pin #3)
  
  pulseTime=micros(); // start the stopwatch
  
  delay(samplingPeriod*1000); //give ourselves samplingPeriod seconds to make this measurement, during which the "onPulse" function will count up all the pulses, and sum the total time they took as 'totalDuration' 
 
  detachInterrupt(1); //we've finished sampling, so detach the interrupt function -- don't count any more pulses
  
  //turn off the 555 system
  //digitalWrite(fivefivefive,LOW);
  
  if (pulseCount>0) { //use this logic in case something went wrong
  
  double durationS=totalDuration/double(pulseCount)/1000000.; //the total duration, in seconds, per pulse (note that totalDuration was in microseconds)
  pulseAve+=pulseCount;
  pulseStats++;
  
}
  } 
  
  if (pulseAve>0) {
    pulseAve=pulseAve/pulseStats;

int pulseAveInt = (int) pulseAve;

  Serial.println(pulseAveInt);
  Serial.println("x");
  // print out stats
  //Serial.print("sampling period=");
  //Serial.print(samplingPeriod);
    //Serial.print(" sec; #pulses=");
  //Serial.print(pulseCount);
 // Serial.print("; duration per pulse (sec)=");
 // Serial.println(durationS,8);
  }
  
  
  }
  

void onPulse()
{
  pulseCount++;
  //Serial.print("pulsecount=");
  //Serial.println(pulseCount);
  lastTime = pulseTime;
  pulseTime = micros();
  duration=pulseTime-lastTime;
  totalDuration+=duration;
  //Serial.println(totalDuration);
}