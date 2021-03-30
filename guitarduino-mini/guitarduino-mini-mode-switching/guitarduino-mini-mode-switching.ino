/*   Guitarduino software for the mini version - runs on ATTiny85
 *   Use a switch connected from DIP pin 5 to ground
 *   
 *   When switch is closed:
 *   Octave down mode - works like a flip-flop - think Blue Box or Arcadiator.
 *   Each time the input goes high, it toggles the state of the output.
 *   One high/low cycle of the output takes two high/low cycles of the input.
 *   
 *   When switch is open:
 *   Square wave mode - exactly what you expect
 */

const int inputPin = A3; //establish pin 3 (pin 2 of the DIP) as the analog input
const int outputPin = 1; //establish pin 1 (pin 6 of the DIP) as the output
const int switchPin = 2; //establish pin 2 (pin 7 of the DIP) as the switch input
const int highpoint = 520; // establishes the point at which the wave is considered "high"
const int lowpoint = 504; //establishes the point at which the wave is considered "low"
unsigned int sampleIn = 0; //Stores the sample from the ADC
int switchMode;//Stores the position of the switch
boolean outputState = false;
boolean flipReady = true;

void setup() {
  pinMode (inputPin, INPUT);
  pinMode (switchPin, INPUT_PULLUP);
  pinMode (outputPin, OUTPUT);
  switchMode = digitalRead(switchPin);//check the switch mode
}

void loop() {
if (switchMode == 0)//
  {
    sampleIn = analogRead(inputPin); //sample the input
    if (flipReady && sampleIn >= highpoint)//if it's ready to flip because the input has gone low and is now high enough...
      {
        outputState = !outputState; //change the output for each top half of the input wave. Two full input cycles generate one full output cycle.
        if (outputState)
          {
            digitalWrite(outputPin, HIGH);
          }
        else
          {
            digitalWrite(outputPin, LOW);
          }
        flipReady = false; //won't be ready to flip again until the input goes low
      }
    if (sampleIn < lowpoint)//if the input goes low, we're ready to flip again once it gets high enough
      {
        flipReady = true;
      }
  }
if (switchMode == 1)
  {
    sampleIn = analogRead(inputPin); //sample the input
    if (sampleIn > 520)
      {
        digitalWrite(outputPin, HIGH);
      }
    if (sampleIn < 504)
      {
        digitalWrite(outputPin, LOW);
      }
  }
switchMode = digitalRead(switchPin);//check the switch mode
}

