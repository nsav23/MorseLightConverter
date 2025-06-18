const int shortPulse = 300;                                       // This is the duration in ms of the ".". Based on 25 wpm standard (sort of... not really)
const int longPulse = 500;                                        // Same as above but for "-"
const int letterInterval = 600;                                   // ms duration between different letters
const int wordInterval = 800;                                     // ms interval between words
const int noiseThreshold = 20;                                    // Ignore very tiny blips (noise)

int sensorValue;                                                  // Holds the analogue value from the phototransistor
int sensorHigh = 200;                                             // Upper threshold sensor value (use Serial readings for tweaking)
int sensorLow = 100;                                              // See above comment

String morseStorage = "";                                         // Stores the currently input morse character sequence

bool lightOn = false;                                             // Returns whether light is on or off according to the thresholds set for the sensor

unsigned long stateChangeTime = 0;                                // Indicates starting time of last state change (lightOn == true/false)

void setup() 
{
  Serial.begin(9600);                                             // Start serial communication
}

void loop() 
{
  sensorValue = analogRead(A0);                                   // Sensor value equals the analogue value that the phototransistor receives

  bool currentLight = isHitByLight(sensorValue);                  // Stores whether the light is on
  unsigned long presentTime = millis();                           // Time in ms since the Arduino booted

  // Detect change in state
  if (currentLight != lightOn)
  {

    unsigned long duration = presentTime - stateChangeTime;       // Duration of the last state
    stateChangeTime = presentTime;                                // Update duration of the last state

    if (currentLight)                                             // Start of current light
    {

      if (duration > wordInterval)                                // Dark period was long enough to start new word
      {

        decodeMorseBuffer();                                      
        Serial.print(" ");                                        // Print space between words

      } 
      else if (duration > letterInterval)                         // Dark period was long enough to start new letter
      {

        decodeMorseBuffer();

      } 

    } 
    else                                                          // End of current light
    {

      if (duration >= noiseThreshold && duration < shortPulse)    // Dot
      {

        morseStorage += ".";

      } 
      else if (duration < longPulse)                              // Dash
      {

        morseStorage += "-";

      }

      // Else: Ignore noise or undefined long pulses
    }

    lightOn = currentLight;                                       // Update the state

  }
}

char decodeMorse(String codeSequence)
{

  struct MorseSymbol
  {

    const char* code;
    char letter;

  };

  MorseSymbol morseMap[] = 
  {

    {".-", 'A'},   {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'},  {".", 'E'},
    {"..-.", 'F'}, {"--.", 'G'},  {"....", 'H'}, {"..", 'I'},   {".---", 'J'},
    {"-.-", 'K'},  {".-..", 'L'}, {"--", 'M'},   {"-.", 'N'},   {"---", 'O'},
    {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'},  {"...", 'S'},  {"-", 'T'},
    {"..-", 'U'},  {"...-", 'V'}, {".--", 'W'},  {"-..-", 'X'}, {"-.--", 'Y'},
    {"--..", 'Z'}

  };

  for (int i = 0; i < sizeof(morseMap) / sizeof(MorseSymbol); i++)
  {

    if (codeSequence == morseMap[i].code)
    {

      return morseMap[i].letter;

    }

  }

  return '?';                                                     // Return ? if no match found

}

void decodeMorseBuffer()
{

  if (morseStorage.length() == 0)
  {

    return;

  }

  char decodedMorse = decodeMorse(morseStorage);
  Serial.print(decodedMorse);
  morseStorage = "";

}

bool isHitByLight(int sensorValue)
{

  if (sensorValue > sensorHigh) 
  {

    return true;

  } 
  else if (sensorValue < sensorLow) 
  {

    return false;

  }

  return lightOn;

}
