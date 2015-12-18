# guitarduino
Software for running Arduino based guitar effects. Free software licensed under GPL.

guitarduino-mode-switching is the main release intended to run on the matching hardware to take advantage of the mode switches and provide 16 different effect modes.

Supports ATMega 168/328 based Arduinos using onboard ADC and resistor ladder DAC on PORTB. 
The schematic is included for the board used to develop these sketches and can be viewed / edited in Eagle 6 or higher.
This instructable offers a good explanation of the resistor ladder DAC used: http://www.instructables.com/id/Arduino-Audio-Output/
  NOTE: In the instructable PORTD is used for an 8 bit DAC.
        Even with 1% resistors it's impossible to achieve 
        an accurate 8 bit resistor ladder DAC. In this project
        PORTB is used, which offers 6 pins (the 2 highest bits
        are used for the clock crystal on the ATMega chip. It
        is possible to achieve good accuracy for a 6 bit R/2R
        resistor ladder DAC using common 5% resistors, and this
        project is going for simplicity wherever possible.
        

