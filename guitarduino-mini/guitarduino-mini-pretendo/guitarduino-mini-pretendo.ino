/*   Guitarduino software for the PR3T3ND-0 pedal - runs on ATTiny85
 *   Square Wave of input signal + 1 and 2 octaves down, separate volume controls for each
 */

const int inputPin = A3; //pin 3 (pin 2 of the DIP) analog input
const int outputPin = 1; //pin 1 (pin 6 of the DIP) output
const int octavePin = 0;//pin 0 (pin 5 of the DIP) output for the octave down
const int subPin = 2;//pin 2 (pin 7 of the DIP) output for the 2 octaves down
const int highpoint = 520; // point at which the wave is considered "high"
const int lowpoint = 504; //point at which the wave is considered "low"
unsigned int sampleIn = 0; //Stores the sample from the ADC
boolean octaveState = false;
boolean subState = false;
boolean flipReady = true;
boolean subReady = true;

void setup() {
  pinMode (inputPin, INPUT);
  pinMode (outputPin, OUTPUT);
  pinMode (octavePin, OUTPUT);
  pinMode (subPin, OUTPUT);
}

void loop() {
  sampleIn = analogRead(inputPin); //sample the input
  
  //Below outputs a square wave 1 octave down on DIP pin 5
  if (flipReady && (sampleIn >= highpoint))//if it's ready to flip because the input has gone low and is now high enough...
    {
      octaveState = !octaveState; //change the output for each top half of the input wave. Two full input cycles generate one full output cycle.
      if (octaveState)
        {
          digitalWrite(octavePin, HIGH);
        }
      else
        {
          digitalWrite(octavePin, LOW);
        }
      flipReady = false; //won't be ready to flip again until the input goes low
    }

  //Below outputs a square wave 2 octaves down on DIP pin 7
  if (subReady && octaveState)
    {
      subState = !subState;
      if (subState)
        {
          digitalWrite(subPin, HIGH);
        }
      else
        {
          digitalWrite(subPin, LOW);
        }
      subReady = false;
    }
    
  //Below outputs the straight square wave of the input on DIP pin 6
  if (sampleIn >= highpoint)
    {
      digitalWrite(outputPin, HIGH);
    }
  if (sampleIn <= lowpoint)
    {
      digitalWrite(outputPin, LOW);
    }
  
  //Below sets readiness bits for frequency divider flip flop
  if (sampleIn < lowpoint)//if the input goes low, we're ready to flip again once it gets high enough
    {
      flipReady = true;
    }
  if (!octaveState)
    {
      subReady = true;
    }
  
}

