


//  ELLITONE MULTI-SYNTH is powered using the Mozzi Sonification Library for Arduino.

// I have spent the last 2.5 years exploring this library, finding the atmega328s strong and weak points when processing realtime audio

// In the following program, I attempted to squeeze as much Mozzi functionality into a single device, paired with a simple "patch and play" interface.

// Currently, this program uses 99.99% of the atmega328 program storage space. This includes the 6 WaveTable files that represent the WaveForm Shapes  <tables/AKWF_.....h>

//You might be asking "can I use my own waveforms?". Creating custom waveforms for use in mozzi is not a simple or straightforward process. Still, you can look more into this process
//by reading through the Mozzi Forum Google Group.

//However, replacing the initial 6 Waveforms with other waveforms from the AKWF library is simple and straightforward! This library contains hundreds of waveshapes that
//can all be viewed here:   https://www.adventurekid.se/AKRTfiles/AKWF/view/waveforms_index.html

//to replace the waveforms, First download and install the Arduino IDE:  https://www.arduino.cc/en/Main/Software

//Next, download and unzip the Mozzi file. Take the unzipped Mozzi folder and place it inside the "libraries" folder located within the Arduino Folder, (usually found in My Documents).

//Now, make sure you have successfully installed the CH340 Driver. This driver allows your computer to communicate with the Ellitones atmega328.
//If installed correctly, your computer should recognize the Arduino when plugged into USB and it will show up as a COM in Tools-Port menu in Arduino IDE

//Now, Navigate to Documents > Arduino > libraries > Mozzi-1.0.3rc6 > tables
//Scroll down until you start seeing the files that start with "AKWF" these are all the possible waveforms you can choose from!

//Next, in the #include section below, copy in the waveshape files you want to use instead of the 6 that are currently there.

//Next, Around Code Line ~93 (current line code # is in bottom left hand corner of Arduino IDE window) make sure that one of your new wavetables is used here instead of old waveform!
//Code Line ~246, make sure that one of your new wavetables is used here aswell!

//Lastly, Code Line ~869 through ~946 is where the actual switching between waveforms happen when you connect different outputs to the WaveForm input.
//This is where you will put in all your new selected waveform files!

//If you wish to try adding new features and modes, one way to quickly free up a bunch of space (to work with) is to #include and use LESS than 6 WaveForms.
//You can just use 1 waveform file in all the places listed above and free up ~40% more space for added logic functions!

//I am more than happy to further explain the following code and its workings if people are interested in taking this device even further!
//Feel free to email me at ellistronics.usa@gmail.com



#include <MozziGuts.h>        //loads all the essential mozzi engine stuff 
#include <Oscil.h>           //loads behind the scenes oscillator magic
#include <EventDelay.h>   //used throughout this program as "timers" in place of the usual arduino "delay" functions which are disabled by mozzi workings
#include <Ead.h>              // stands for Exponential Attack Decay (Envelope). This loads the behind the scenes envelope magic
#include <WavePacket.h>          //loads "chirp" type synthesis engine 
#include <Smooth.h>          //loads basic smoothing filter (not for audio). used to smooth the jumpy analog data readings from the 4 knobs 

#include <tables/cos2048_int8.h>      // loads cosine wavetable used in the FM mode (FreqModz)

#include "tables/AKWF_oscchip_0100_512.h"    //loads the 6 wavetables for use in modes: 1(wavetables),2(patterns),5(infinite bounce),6(panic voice)
#include "tables/AKWF_vgsaw_0005_512.h"
#include "tables/AKWF_nes_square_512.h"
#include "tables/AKWF_hvoice_0010_512.h"
#include "tables/AKWF_hvoice_0020_512.h"
#include "tables/AKWF_vgame_0126_512.h"


// INPUT PINS
#define POT1_PIN A0
#define POT2_PIN A1
#define POT3_PIN A2
#define POT4_PIN A3

#define BUTTON1_PIN 4
#define BUTTON2_PIN 5
#define BUTTON3_PIN 6
#define BUTTON4_PIN 7

#define OPT_WAVEFORM_PIN  A4
#define OPT_VOICING_PIN   A5
#define OPT_PLAYSTYLE_PIN 10
#define OPT_SPEED_PIN     11
#define OPT_RHYTHM_PIN    12

// OUTPUT PINS
#define OPT_OUT1_PIN 0
#define OPT_OUT2_PIN 1
#define OPT_OUT3_PIN 2
#define OPT_OUT4_PIN 3
#define OPT_OUT5_PIN 8
#define OPT_OUT6_PIN 13

EventDelay pulse1, pulse2, pulse3, pulse4, pulse5, pulse6; //option outpus 1-6

EventDelay offTimer1, offTimer2, offTimer3, offTimer4, offTimer5;              //this stuff will be explained further on down. Just initializing variables here
byte counter1, counter2, counter3, counter4, counter5, counter6 = 1;

int pulseCounter1 = 1;
int pulseCounter2 = 1;
int pulseCounter3 = 1;
int pulseCounter4 = 1;
int pulseCounter5 = 1;

bool reset1 = true;
byte outPut1;

bool reset2 = true;
byte outPut2;

bool reset3 = true;
byte outPut3;

bool reset4 = true;
byte outPut4;

bool reset5 = true;
byte outPut5;

bool reset6 = true;
byte outPut6;


Oscil <AKWF_oscchip_0100_512_NUM_CELLS, AUDIO_RATE> aSin1;     //initializes the wavetable type oscillators
Oscil <AKWF_oscchip_0100_512_NUM_CELLS, AUDIO_RATE> aSin2;
Oscil <AKWF_oscchip_0100_512_NUM_CELLS, AUDIO_RATE> aSin3;    //if you are using different waveforms, you must use one of your new waveform files here instead of this old one.
Oscil <AKWF_oscchip_0100_512_NUM_CELLS, AUDIO_RATE> aSin4;
Oscil <AKWF_oscchip_0100_512_NUM_CELLS, AUDIO_RATE> aSin5;
Oscil <AKWF_oscchip_0100_512_NUM_CELLS, AUDIO_RATE> aSin6;
Oscil <AKWF_oscchip_0100_512_NUM_CELLS, AUDIO_RATE> aSin7;
Oscil <AKWF_oscchip_0100_512_NUM_CELLS, AUDIO_RATE> aSin8;


Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aCarrier(COS2048_DATA);    //initialzies the FM mode oscillators
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aModulator(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, CONTROL_RATE> kModIndex(COS2048_DATA);



byte gain1, gain2, gain3, gain4, gain5, gain6, gain7, gain8 = 1;

byte envGain1, envGain2, envGain3, envGain4, envGain5, envGain6, envGain7, envGain8 = 255; //just initializing more stuff for later on

byte key = 1;     //the most current key button that was last pressed (1-4)
byte mode = 1;

int p1 = 100;    //4 pitches
int p2 = 100;
int p3 = 100;
int p4 = 100;

int pitchAlter = 0; //used for sequence transposing

EventDelay seqTimer;
byte seqPos = 1;

Ead envelope1(CONTROL_RATE), envelope2(CONTROL_RATE), envelope3(CONTROL_RATE), envelope4(CONTROL_RATE); //initializes envelopes with the same resolution as our run time (CONTROL_RATE)

int tempGain;

EventDelay speedsTimer;    //speeds

EventDelay newRandrh;
EventDelay newRandvoicing;

int step1rh = 200;          //seriously, dont worry about all these weird variables till later.
int step2rh = 200;
int step3rh = 200;
int step4rh = 200;


byte stepNum = 1;

int attack = 100; //envelope stuff
int decay = 100;

int fmLevel;

int fmGain;

WavePacket <DOUBLE> wavey;       //initializes "chirp" sound engine (referred to as a WavePacket in Mozzi terms)

float keySpread;
float waveyFund;


EventDelay bounceTimer1, bounceTimer2, bounceTimer3, bounceTimer4; //timers used in the infinite bounce matter mode to trigger the envelopes

EventDelay randomPulse;



int bounceTime1, bounceTime2, bounceTime3, bounceTime4 = 10; //actual bounce times for infinite bounce mode



float enhance;       //panic voice engine variables being simply initialized here
float finalFreq;
float alter;
int freq = 500;

byte modGain = 255;

int pulse6Time;
byte rando;

int speeds;

byte rhtime1 = 1;
byte rhtime2 = 1;
byte rhtime3 = 1;
byte rhtime4 = 1;

byte voicing1 = 1;    //these are the chord divisions for the voicing control
byte voicing2 = 1;
byte voicing3 = 1;
byte voicing4 = 1;

int randoPulseTime;


int modFreq = 100;

Smooth <int> smoothKnob1(0.92f);     //sets up smoothing filters that we will run our raw potentiometer (knob) readings through to get steady pitch settings
Smooth <int> smoothKnob2(0.92f);
Smooth <int> smoothKnob3(0.92f);
Smooth <int> smoothKnob4(0.92f);

int baseSpeed;
int speed1;
int speed2;
int speed3;
int speed4;
int speed5;

float sin2Freq;

int rawA7 = 100;       //raw potentiometer (knob) readings
int rawA6 = 100;
int rawA0 = 100;
int rawA1 = 100;

int phold1 = 100;
int phold2 = 100;
int phold3 = 100;
int phold4 = 100;


int freakFreq = 0;
int waveyFreak = 0;

int riggy;

#define CONTROL_RATE 64       //this entire mozzi engine program operates at a click rate determined here. this is how fast the programs updateControl() section will loop 




void setup() {

  startMozzi(CONTROL_RATE);   //starts the entire mozzi engine at the control rate

  randomSeed(mozziAnalogRead(POT1_PIN));     //takes a quick reading of potentiometer (knob) A7 and bases its psuedo random # generator on it to calculate the following random values

  baseSpeed = random(200, 400);
  speed1 = random(50, 100);
  speed2 = random(100, 250);
  speed3 = random(300, 500);
  speed4 = random(500, 1000);
  speed5 = random(500, 2000);

  randoPulseTime = random(200, 800);

  riggy = random(10, 1000);


  aSin1.setTable(AKWF_vgsaw_0005_512_DATA);   //not too important. still just setting up the oscillators with initial wavetable shape data
  aSin2.setTable(AKWF_vgsaw_0005_512_DATA);
  aSin3.setTable(AKWF_vgsaw_0005_512_DATA);
  aSin4.setTable(AKWF_vgsaw_0005_512_DATA);    //if you are using different waveform files, you MUST use one of your new waveform files here instead.
  aSin5.setTable(AKWF_vgsaw_0005_512_DATA);
  aSin6.setTable(AKWF_vgsaw_0005_512_DATA);
  aSin7.setTable(AKWF_vgsaw_0005_512_DATA);
  aSin8.setTable(AKWF_vgsaw_0005_512_DATA);


  // Serial.begin(9600);   //for debugging


  pinMode(BUTTON1_PIN, INPUT_PULLUP); //button 1     //4 key buttons are "pulled-up" to HIGH +5V signal. When pressed, they connect the input pin to GROUND which will now
  pinMode(BUTTON2_PIN, INPUT_PULLUP); //button 2      read as LOW in the code. this may seem confusing at first but HIGH means that button IS NOT pressed and
  pinMode(BUTTON3_PIN, INPUT_PULLUP);  //button 3      LOW means that the button IS pressed
  pinMode(BUTTON4_PIN, INPUT_PULLUP); //button 4


  pinMode(OPT_WAVEFORM_PIN, INPUT_PULLUP);   //waveform        //
  pinMode(OPT_VOICING_PIN, INPUT_PULLUP);   //voicing
  pinMode(OPT_PLAYSTYLE_PIN, INPUT_PULLUP);   //play style
  pinMode(OPT_SPEED_PIN, INPUT_PULLUP);   //speed
  pinMode(OPT_RHYTHM_PIN, INPUT_PULLUP);   //rhythm



  pinMode(OPT_OUT6_PIN, OUTPUT);   //6
  pinMode(OPT_OUT5_PIN, OUTPUT);   //5       //Option Outputs 1-6
  pinMode(OPT_OUT4_PIN, OUTPUT);   //4
  pinMode(OPT_OUT3_PIN, OUTPUT);   //3
  pinMode(OPT_OUT2_PIN, OUTPUT);   //2
  pinMode(OPT_OUT1_PIN, OUTPUT);    //1

  pulse1.start(100);        //This sections simply "starts" all the little timers that will be used throughout the program
  pulse2.start(100);
  pulse3.start(100);
  pulse4.start(100);
  pulse5.start(100);

  seqTimer.start(100);
  speedsTimer.start(100);

  bounceTimer1.start(100);
  bounceTimer2.start(100);
  bounceTimer3.start(100);
  bounceTimer4.start(100);

  randomPulse.start(200);

  newRandrh.start(5000);
  newRandvoicing.start(500);

}


void updateControl() {


  phold1 = smoothKnob1.next(mozziAnalogRead(POT1_PIN));  // from right to left:  takes raw analog knob reading (mozziAnalogRead()) ,smooths them (smoothKnob), then sets
  phold2 = smoothKnob2.next(mozziAnalogRead(POT2_PIN));  // phold variable (final pitch) with the final smoothed output
  phold3 = smoothKnob3.next(mozziAnalogRead(POT3_PIN));
  phold4 = smoothKnob4.next(mozziAnalogRead(POT4_PIN));


  if (phold1 > rawA7 + 2 || phold1 < rawA7 - 2) {      // this section here performs a "pitch hold" where the new incoming pitch values must be either +3 or -3 compared
    rawA7 = phold1;                                      //   to the held value in order to update the final pitch
  }
  if (phold2 > rawA6 + 2 || phold2 < rawA6 - 2) {
    rawA6 = phold2;
  }
  if (phold3 > rawA0 + 2 || phold3 < rawA0 - 2) {
    rawA0 = phold3;
  }
  if (phold4 > rawA1 + 2 || phold4 < rawA1 - 2) {
    rawA1 = phold4;
  }





  if (mode == 6) {                             /////////////////////////////PANIC VOICE (mode 6) WORKINGS

    if (outPut1 == 0 && outPut2 == 0) {

      if (outPut4 != 0) {
        freakFreq = riggy * outPut4;
      }
      if (outPut5 != 0) {
        freakFreq = riggy / outPut5;
      }
    } else {
      freakFreq = 0;
    }


    enhance = map(rawA6, 0, 1023, 10, 255); //Push/Strength Control here was called "enhance" during dev.
    enhance = enhance * 0.007;

    if (outPut1 == 0) {
      modGain = map(rawA1, 0, 1023, 0, 255);
    } else {
      if (envelope1.next() != 0) {
        modGain = (envelope1.next() * rawA1);
      } else {
        modGain = map(rawA1, 0, 1023, 0, 255);
      }
    }

    if (outPut2 == 0) {
      sin2Freq = p3 * 10;
    } else {
      if (envelope1.next() != 0) {
        sin2Freq = (envelope1.next() * (rawA0 >> 4));
      } else {
        sin2Freq = p3 * 10;
      }
    }


    alter = map(rawA7, 0, 1023, 400, 200);

    finalFreq = freq * alter;

    aSin2.setFreq(sin2Freq + freakFreq);
    aSin1.setFreq(finalFreq);

  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////// WAVETABLE (mode 1) WORKINGS


  if (digitalRead(BUTTON1_PIN) == LOW) {
    key = 1;
    freq = 100;
  }
  if (digitalRead(BUTTON2_PIN) == LOW) {
    key = 2;
    freq = 500;
  }
  if (digitalRead(BUTTON3_PIN) == LOW) {
    key = 3;
    freq = 900;
  }
  if (digitalRead(BUTTON4_PIN) == LOW) {
    key = 4;
    freq = 1500;
  }


  p1 = rawA7;
  p2 = rawA6;
  p3 = rawA0;
  p4 = rawA1;





  /////////////////////////////////////////////////////////////////////////////////////////////////  "CHIRP" (mode 4) - WAVEPACKET WORKINGS

  if (mode == 4) {


    if (outPut1 == 0 && outPut2 == 0) { //basically, if there is no attachment but a speed or rhythm is in fact selected then

      if (outPut4 != 0) {
        waveyFreak = outPut4 * 250;
      }
      if (outPut5 != 0) {
        waveyFreak = outPut5 * 250;
      }
    } else {
      waveyFreak = 0;
    }



    if (outPut1 == 0) {                                     //if waveform is 0 then set by knob. otherwise, set bandwidth control by envelope
      wavey.setBandwidth((rawA7 * 2) + waveyFreak);
    } else {
      wavey.setBandwidth((envelope1.next() * (rawA7 >> 5)) + (outPut1 * 100));
    }

    if (outPut2 == 0) {
      wavey.setCentreFreq((rawA6 * 2) + waveyFreak);               //if voicing is 0 then set by knob. otherwise, set centrefreq by envelope
    } else {
      wavey.setCentreFreq((envelope1.next() * (rawA6 >> 5)) + (outPut2 * 200));
    }

    waveyFund = rawA0 >> 4;

    keySpread = rawA1 / 1023.0; //converts 10-bit analog reading (0-1023) to float range between (0.00-1.00)


    float finekey = keySpread * waveyFund;


    if (key == 1) {
      wavey.setFundamental(waveyFund + (finekey * 0.50)); //Sets coarse frequency based on the "base frequency" control plus the "key note spread" control times 0.5,1.0,1.5,2.0
    }
    if (key == 2) {
      wavey.setFundamental(waveyFund + (finekey * 1.0));
    }
    if (key == 3) {
      wavey.setFundamental(waveyFund + (finekey * 1.5));
    }
    if (key == 4) {
      wavey.setFundamental(waveyFund + (finekey * 2.0));
    }

  }





  ///////////////////////////////////////////////////////////////////////////////////////FM (mode 3) WORKINGS



  if (mode == 3 && outPut4 == 0 && outPut5 == 0) { //if mode is fm and speed is 0 (base) and rhthym is 0 (base), then set main pitches by 4 Keys

    if (key == 1) {
      aCarrier.setFreq(p1);
    }
    if (key == 2) {
      aCarrier.setFreq(p2);
    }
    if (key == 3) {
      aCarrier.setFreq(p3);
    }
    if (key == 4) {
      aCarrier.setFreq(p4);
    }

  }







  ///////////////////////// RANDOM VOICING RATIO CREATOR

  if (outPut2 != 0) {
    newRandvoicing.start(300);
  }

  if (newRandvoicing.ready()) {

    voicing1 = random(1, 8);
    voicing2 = random(1, 8);
    voicing3 = random(1, 8);
    voicing4 = random(1, 8);

    newRandvoicing.start();
  }





  if (mode == 1) {                                      //////WAVETABLE (mode 1)


    if (key == 1) {
      aSin1.setFreq(p1);
      aSin2.setFreq(p1 + (p1 / voicing1));
      aSin3.setFreq(p1 + (p1 / voicing2));
      aSin4.setFreq(p1 + (p1 / voicing3));
      aSin5.setFreq(p1 + (p1 / voicing4));
      aSin6.setFreq((p1 * 2) + (p1 / voicing1));
      aSin7.setFreq((p1 * 2) + (p1 / voicing2));
      aSin8.setFreq((p1 * 2) + (p1 / voicing3));
    }
    if (key == 2) {
      aSin1.setFreq(p2);
      aSin2.setFreq(p2 + (p2 / voicing1));
      aSin3.setFreq(p2 + (p2 / voicing2));
      aSin4.setFreq(p2 + (p2 / voicing3));
      aSin5.setFreq(p2 + (p2 / voicing4));
      aSin6.setFreq((p2 * 2) + (p2 / voicing1));
      aSin7.setFreq((p2 * 2) + (p2 / voicing2));
      aSin8.setFreq((p2 * 2) + (p2 / voicing3));
    }
    if (key == 3) {
      aSin1.setFreq(p3);
      aSin2.setFreq(p3 + (p3 / voicing1));
      aSin3.setFreq(p3 + (p3 / voicing2));
      aSin4.setFreq(p3 + (p3 / voicing3));
      aSin5.setFreq(p3 + (p3 / voicing4));
      aSin6.setFreq((p3 * 2) + (p3 / voicing1));
      aSin7.setFreq((p3 * 2) + (p3 / voicing2));
      aSin8.setFreq((p3 * 2) + (p3 / voicing3));
    }
    if (key == 4) {
      aSin1.setFreq(p4);
      aSin2.setFreq(p4 + (p4 / voicing1));
      aSin3.setFreq(p4 + (p4 / voicing2));
      aSin4.setFreq(p4 + (p4 / voicing3));
      aSin5.setFreq(p4 + (p4 / voicing4));
      aSin6.setFreq((p4 * 2) + (p4 / voicing1));
      aSin7.setFreq((p4 * 2) + (p4 / voicing2));
      aSin8.setFreq((p4 * 2) + (p4 / voicing3));
    }

    tempGain = (int) envelope1.next();
    envGain1 = tempGain;
    envGain2 = tempGain;
    envGain3 = tempGain;
    envGain4 = tempGain;
    envGain5 = tempGain;
    envGain6 = tempGain;
    envGain7 = tempGain;
    envGain8 = tempGain;

  }

  //////////////////////////////////////////////////////////////////INFINITE BOUNCE MATTER (mode5)


  if (mode == 5) {

    if (bounceTimer1.ready()) {           //if timer has reached the end,
      envelope1.start(attack, decay);         //do action
      bounceTimer1.start(bounceTime1);       //then reset the timer
    }

    if (bounceTimer2.ready()) {
      envelope2.start(attack, decay);
      bounceTimer2.start(bounceTime2);
    }

    if (bounceTimer3.ready()) {
      envelope3.start(attack, decay);
      bounceTimer3.start(bounceTime3);
    }

    if (bounceTimer4.ready()) {
      envelope4.start(attack, decay);
      bounceTimer4.start(bounceTime4);
    }


    envGain1 = (int) envelope1.next();      //translates envelope data into gain data for individual voice volumes
    envGain2 = (int) envelope2.next();
    envGain3 = (int) envelope3.next();
    envGain4 = (int) envelope4.next();




    if (outPut2 == 0) {
      aSin1.setFreq(p1);
      aSin2.setFreq(p2);
      aSin3.setFreq(p3);
      aSin4.setFreq(p4);
      gain1 = 1;
      gain2 = 1;
      gain3 = 1;
      gain4 = 1;
      gain5 = 0;
      gain6 = 0;
      gain7 = 0;
      gain8 = 0;
    }




    if (outPut2 == 2) {
      aSin1.setFreq(p1);
      aSin2.setFreq(p2);
      aSin3.setFreq(p3);
      aSin4.setFreq(p4);
      aSin5.setFreq(p1 + 2);
      aSin6.setFreq(p2 - 2);
      aSin7.setFreq(p3 + 2);
      aSin8.setFreq(p4 - 2);
    }

    if (outPut2 == 3) {
      aSin1.setFreq(p1);
      aSin2.setFreq(p2);
      aSin3.setFreq(p3);
      aSin4.setFreq(p4);
      aSin5.setFreq((p1 * 2) + 2);
      aSin6.setFreq((p2 * 2) - 2);
      aSin7.setFreq((p3 * 2) + 2);
      aSin8.setFreq((p4 * 2) - 2);
    }

    if (outPut2 == 5) {
      aSin1.setFreq(p1);
      aSin2.setFreq(p2);
      aSin3.setFreq(p3);
      aSin4.setFreq(p4);
      aSin5.setFreq(p1 * voicing1);
      aSin6.setFreq(p2 * voicing1);
      aSin7.setFreq(p3 * voicing1);
      aSin8.setFreq(p4 * voicing1);
    }

    if (outPut2 == 6) {
      aSin1.setFreq(p1);
      aSin2.setFreq(p2);
      aSin3.setFreq(p3);
      aSin4.setFreq(p4);
      aSin5.setFreq(p1 * voicing2);
      aSin6.setFreq(p2 * voicing2);
      aSin7.setFreq(p3 * voicing2);
      aSin8.setFreq(p4 * voicing2);
    }

    if (outPut2 == 7) {
      aSin1.setFreq(p1);
      aSin2.setFreq(p2);
      aSin3.setFreq(p3);
      aSin4.setFreq(p4);
      aSin5.setFreq(p1 * voicing1);
      aSin6.setFreq(p2 * voicing2);
      aSin7.setFreq(p3 * voicing3);
      aSin8.setFreq(p4 * voicing4);
    }

    if (outPut2 != 0) {                                              //if voicing is zero than all gains are on / gains 1-8 are either 1 (on) or 0 (off)
      gain1 = 1;
      gain2 = 1;
      gain3 = 1;
      gain4 = 1;
      gain5 = 1;
      gain6 = 1;
      gain7 = 1;
      gain8 = 1;
    }



    if (digitalRead(BUTTON1_PIN) == LOW) {        ///INCREASE BOUNCE TIMES WITH KEYS
      bounceTime1 = bounceTime1 + 3;
    }
    if (digitalRead(BUTTON2_PIN) == LOW) {
      bounceTime2 = bounceTime2 + 3;
    }
    if (digitalRead(BUTTON3_PIN) == LOW) {
      bounceTime3 = bounceTime3 + 3;
    }
    if (digitalRead(BUTTON4_PIN) == LOW) {
      bounceTime4 = bounceTime4 + 3;
    }

  }

  if (mode != 5) {             //once mode is changed, all bounce times reset to 100 millis
    bounceTime1 = 100;
    bounceTime2 = 100;
    bounceTime3 = 100;
    bounceTime4 = 100;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////END OF BOUNCE MODE






  ////////////////////////////////////////////////  CENTER PATCH BAY AREA WORKINGS

  //each of the 6 option output jacks output a pulse (on/off) signal at a unique rate. The 5 input jack holes
  //are listening and timing these incoming pulses to determine which of the output jacks is connected to it.



  if (pulse1.ready()) {        //here you can see a basic timer/reset function constantly running. whenever the timer has reached the end point,
    counter1 = counter1 + 1;      //the counter variable (counter1) is increased by one
    pulse1.start(10);              //then the timer starts over again with its unique time.
  }

  if (pulse2.ready()) {
    counter2 = counter2 + 1;
    pulse2.start(30);
  }

  if (pulse3.ready()) {
    counter3 = counter3 + 1;
    pulse3.start(50);
  }

  if (pulse4.ready()) {
    counter4 = counter4 + 1;
    pulse4.start(70);
  }

  if (pulse5.ready()) {
    counter5 = counter5 + 1;
    pulse5.start(90);
  }



  if (randomPulse.ready()) {
    rando = random(0, 6);
    randomPulse.start(randoPulseTime);      //just picks a new random number between 1-5, assigns it to the rando variable and then restarts the timer
  }


  if (rando == 1) {
    pulse6Time = 10;          //sets output option jack 6 to different pulse output rates determined by value of rando.
  }
  if (rando == 2) {
    pulse6Time = 30;
  }
  if (rando == 3) {
    pulse6Time = 50;
  }
  if (rando == 4) {
    pulse6Time = 70;
  }
  if (rando == 5) {
    pulse6Time = 90;
  }


  if (pulse6.ready()) {
    counter6 = counter6 + 1;
    pulse6.start(pulse6Time);
  }


  if (counter1 > 2) {                  // basic resetting of counter variables allowing them to only equal 1 or 2.
    counter1 = 1;
  }
  if (counter2 > 2) {
    counter2 = 1;
  }
  if (counter3 > 2) {
    counter3 = 1;
  }

  if (counter4 > 2) {
    counter4 = 1;
  }
  if (counter5 > 2) {
    counter5 = 1;
  }
  if (counter6 > 2) {
    counter6 = 1;
  }



  if (counter1 == 1) {                //This is where the actual output option jacks are getting turned on and off (1 or 2) at their unique rates.
    digitalWrite(OPT_OUT1_PIN, LOW);
  } else {
    digitalWrite(OPT_OUT1_PIN, HIGH);
  }

  if (counter2 == 1) {
    digitalWrite(OPT_OUT2_PIN, LOW);
  } else {
    digitalWrite(OPT_OUT2_PIN, HIGH);
  }

  if (counter3 == 1) {
    digitalWrite(OPT_OUT3_PIN, LOW);
  } else {
    digitalWrite(OPT_OUT3_PIN, HIGH);
  }

  if (counter4 == 1) {
    digitalWrite(OPT_OUT4_PIN, LOW);
  } else {
    digitalWrite(OPT_OUT4_PIN, HIGH);
  }

  if (counter5 == 1) {
    digitalWrite(OPT_OUT5_PIN, LOW);
  } else {
    digitalWrite(OPT_OUT5_PIN, HIGH);
  }

  if (counter6 == 1) {
    digitalWrite(OPT_OUT6_PIN, LOW);
  } else {
    digitalWrite(OPT_OUT6_PIN, HIGH);
  }






  ///////////////////////////////////////////////////////////////  INPUT JACKS



  if (digitalRead(OPT_WAVEFORM_PIN) == HIGH && reset1) {         // here is input jack 1. whenever it reads HIGH, it resets itself and waits to read LOW
    reset1 = false;
    outPut1 = pulseCounter1;
    pulseCounter1 = 1;
    offTimer1.start(250);
  }

  if (digitalRead(OPT_WAVEFORM_PIN) == LOW) {             //here the input jack reads LOW and continually increments its pulseCounter variable until it reads HIGH again.
    reset1 = true;                           //This is the timing of the pulse functionality that determines what output jack is connected (if any)
    pulseCounter1 = pulseCounter1 + 1;
  }
  if (offTimer1.ready()) {
    outPut1 = 0;
  }




  //WAVEFORM INPUT JACK
  if (outPut1 == 7) {                                      //the outPut1 variable represents the "output" from the pulse counter explained above.
    // Here is where settings are changed based on what output jack is connected.
    fmLevel = 900;

    aSin1.setTable(AKWF_hvoice_0020_512_DATA);
    aSin2.setTable(AKWF_hvoice_0020_512_DATA);
    aSin3.setTable(AKWF_hvoice_0020_512_DATA);
    aSin4.setTable(AKWF_hvoice_0020_512_DATA);
    aSin5.setTable(AKWF_hvoice_0020_512_DATA);
    aSin6.setTable(AKWF_hvoice_0020_512_DATA);
    aSin7.setTable(AKWF_hvoice_0020_512_DATA);
    aSin8.setTable(AKWF_hvoice_0020_512_DATA);

  }
  if (outPut1 == 6) {

    fmLevel = 700;
    aSin1.setTable(AKWF_vgame_0126_512_DATA);
    aSin2.setTable(AKWF_vgame_0126_512_DATA);
    aSin3.setTable(AKWF_vgame_0126_512_DATA);
    aSin4.setTable(AKWF_vgame_0126_512_DATA);
    aSin5.setTable(AKWF_vgame_0126_512_DATA);
    aSin6.setTable(AKWF_vgame_0126_512_DATA);
    aSin7.setTable(AKWF_vgame_0126_512_DATA);
    aSin8.setTable(AKWF_vgame_0126_512_DATA);

  }
  if (outPut1 == 5) {

    fmLevel = 500;

    aSin1.setTable(AKWF_hvoice_0010_512_DATA);
    aSin2.setTable(AKWF_hvoice_0010_512_DATA);
    aSin3.setTable(AKWF_hvoice_0010_512_DATA);
    aSin4.setTable(AKWF_hvoice_0010_512_DATA);
    aSin5.setTable(AKWF_hvoice_0010_512_DATA);
    aSin6.setTable(AKWF_hvoice_0010_512_DATA);
    aSin7.setTable(AKWF_hvoice_0010_512_DATA);
    aSin8.setTable(AKWF_hvoice_0010_512_DATA);
  }
  if (outPut1 == 3) {

    fmLevel = 400;

    aSin1.setTable(AKWF_nes_square_512_DATA);
    aSin2.setTable(AKWF_nes_square_512_DATA);
    aSin3.setTable(AKWF_nes_square_512_DATA);
    aSin4.setTable(AKWF_nes_square_512_DATA);
    aSin5.setTable(AKWF_nes_square_512_DATA);
    aSin6.setTable(AKWF_nes_square_512_DATA);
    aSin7.setTable(AKWF_nes_square_512_DATA);
    aSin8.setTable(AKWF_nes_square_512_DATA);

  }
  if (outPut1 == 2) {

    fmLevel = 255;

    aSin1.setTable(AKWF_oscchip_0100_512_DATA);
    aSin2.setTable(AKWF_oscchip_0100_512_DATA);
    aSin3.setTable(AKWF_oscchip_0100_512_DATA);
    aSin4.setTable(AKWF_oscchip_0100_512_DATA);
    aSin5.setTable(AKWF_oscchip_0100_512_DATA);
    aSin6.setTable(AKWF_oscchip_0100_512_DATA);
    aSin7.setTable(AKWF_oscchip_0100_512_DATA);
    aSin8.setTable(AKWF_oscchip_0100_512_DATA);

  }


  if (outPut1 == 0) {

    fmLevel = 150;

    aSin1.setTable(AKWF_vgsaw_0005_512_DATA);
    aSin2.setTable(AKWF_vgsaw_0005_512_DATA);
    aSin3.setTable(AKWF_vgsaw_0005_512_DATA);
    aSin4.setTable(AKWF_vgsaw_0005_512_DATA);
    aSin5.setTable(AKWF_vgsaw_0005_512_DATA);
    aSin6.setTable(AKWF_vgsaw_0005_512_DATA);
    aSin7.setTable(AKWF_vgsaw_0005_512_DATA);
    aSin8.setTable(AKWF_vgsaw_0005_512_DATA);

  }


  ///////////////////////////////////////////////////////////////////////////////


  if (digitalRead(OPT_VOICING_PIN) == HIGH && reset2) {         //VOICING INPUT JACK. Each input jack functions the same here.  Incrementing its pulseCounter variable as long as
    reset2 = false;                               //the input signal is HIGH. This in effect, times the incoming pulses to determine which is connected.
    outPut2 = pulseCounter2;                      //the longer the pulse length is, the higher "pulseCounter" becomes.
    pulseCounter2 = 1;
    offTimer2.start(250);
  }

  if (digitalRead(OPT_VOICING_PIN) == LOW) {
    reset2 = true;
    pulseCounter2 = pulseCounter2 + 1;
  }
  if (offTimer2.ready()) {
    outPut2 = 0;
  }






  if (outPut2 == 0 && mode != 5) {                       //if nothing is connected to Voicing input, AND we are NOT in Infinite Bounce Mode, set gain gates and fm mod freqs.
    // the gain gates simply turn audio coming from each oscillator on or off.

    if (outPut4 != 0 || outPut5 != 0) {
      aModulator.setFreq(100 + pitchAlter);
    } else {
      aModulator.setFreq(100);
    }

    gain1 = 1;
    gain2 = 0;
    gain3 = 0;
    gain4 = 0;
    gain5 = 0;
    gain6 = 0;
    gain7 = 0;
    gain8 = 0;
  }

  if (outPut2 == 2 && mode != 5) {        //the outPut variables that time the incoming pulses can be:  0(not connected to anything), 2,3,5,6,7. these values
    //represent the 6 different output option jacks
    if (outPut4 != 0 || outPut5 != 0) {
      aModulator.setFreq(200 + pitchAlter);
    } else {
      aModulator.setFreq(200);
    }


    gain1 = 1;
    gain2 = 1;

    gain3 = 0;
    gain4 = 0;
    gain5 = 0;
    gain6 = 0;
    gain7 = 0;
    gain8 = 0;

  }

  if (outPut2 == 3 && mode != 5) {

    if (outPut4 != 0 || outPut5 != 0) {
      aModulator.setFreq(300 + pitchAlter);
    } else {
      aModulator.setFreq(300);
    }


    gain1 = 1;
    gain2 = 1;

    gain3 = 1;
    gain4 = 0;
    gain5 = 0;
    gain6 = 0;
    gain7 = 0;
    gain8 = 0;

  }

  if (outPut2 == 5 && mode != 5) {

    if (outPut4 != 0 || outPut5 != 0) {
      aModulator.setFreq(400 + pitchAlter);
    } else {
      aModulator.setFreq(400);
    }

    gain1 = 1;
    gain2 = 1;

    gain3 = 1;
    gain4 = 1;
    gain5 = 0;
    gain6 = 0;
    gain7 = 0;
    gain8 = 0;

  }

  if (outPut2 == 6 && mode != 5) {

    if (outPut4 != 0 || outPut5 != 0) {
      aModulator.setFreq(500 + pitchAlter);
    } else {
      aModulator.setFreq(500);
    }

    gain1 = 1;
    gain2 = 1;
    gain3 = 1;
    gain4 = 1;
    gain5 = 1;
    gain6 = 0;
    gain7 = 0;
    gain8 = 0;
  }

  if (outPut2 == 7 && mode != 5) {

    if (outPut4 != 0 || outPut5 != 0) {
      aModulator.setFreq(600 + pitchAlter);
    } else {
      aModulator.setFreq(600);
    }


    gain1 = 1;
    gain2 = 1;
    gain3 = 1;
    gain4 = 1;
    gain5 = 1;
    gain6 = 1;
    gain7 = 1;
    gain8 = 1;
  }





  ///////////////////////////////////////////////////////////////////////////////////


  if (digitalRead(OPT_PLAYSTYLE_PIN) == HIGH && reset3) {         //outPut3     MODE SELECT
    reset3 = false;
    outPut3 = pulseCounter3;
    pulseCounter3 = 1;
    offTimer3.start(250);
  }

  if (digitalRead(OPT_PLAYSTYLE_PIN) == LOW) {
    reset3 = true;
    pulseCounter3 = pulseCounter3 + 1;
  }
  if (offTimer3.ready()) {
    outPut3 = 0;
  }


  if (outPut3 == 0) {
    mode = 1;
  }

  if (outPut3 == 2) {
    mode = 2;
  }

  if (outPut3 == 3) {
    mode = 3;
  }

  if (outPut3 == 5) {
    mode = 4;
  }

  if (outPut3 == 6) {
    mode = 5;
  }

  if (outPut3 == 7) {
    mode = 6;
  }

  ///////////////////////////////////////////////////////////////////////////////////


  if (digitalRead(OPT_SPEED_PIN) == HIGH && reset4) {         //outPut4     SPEED
    reset4 = false;
    outPut4 = pulseCounter4;
    pulseCounter4 = 1;
    offTimer4.start(250);
  }

  if (digitalRead(OPT_SPEED_PIN) == LOW) {
    reset4 = true;
    pulseCounter4 = pulseCounter4 + 1;
  }
  if (offTimer4.ready()) {
    outPut4 = 0;
  }



  if (outPut4 == 0) { //if speeds is zero than speeds equals baseSpeeds which is 200 millis
    speeds = baseSpeed;
  }

  if (outPut4 == 2) {
    bounceTime1 = 200;        //these are the preset poly-rhythms that can be chosen while in infinte bounce mode.
    bounceTime2 = 400;
    bounceTime3 = 600;
    bounceTime4 = 800;
    speeds = speed1;
  }
  if (outPut4 == 3) {
    bounceTime1 = 300;
    bounceTime2 = 600;
    bounceTime3 = 1000;
    bounceTime4 = 1200;
    speeds = speed2;
  }
  if (outPut4 == 5) {
    bounceTime1 = 500;
    bounceTime2 = 1000;
    bounceTime3 = 1500;
    bounceTime4 = 2500;
    speeds = speed3;
  }
  if (outPut4 == 6) {
    bounceTime1 = 100;
    bounceTime2 = 150;
    bounceTime3 = 300;
    bounceTime4 = 700;
    speeds = speed4;
  }
  if (outPut4 == 7) {
    bounceTime1 = 700;
    bounceTime2 = 900;
    bounceTime3 = 1150;
    bounceTime4 = 2200;
    speeds = speed5;
  }


  /////////////////////////////////////////////////////////////////////////////////////END OF SPEEDS



  if (seqPos > 3) {                      /////SEQ MODE   ////////////////////////////////////////////////////////////////////////////
    seqPos = 0;
  }                  //simply resets the sequencer back to 0 after getting to the end

  if (stepNum > 3) {
    stepNum = 0;
  }

  if (mode == 2 || mode == 3) {       //If in Seq mode (patterns) or in FM mode (freqmodz)


    if (digitalRead(BUTTON1_PIN) == LOW) {                    //Keys changing values of the pitchAlter variable which is added to the final pitch output
      pitchAlter = pitchAlter - 2;
    }

    if (digitalRead(10) == LOW) {
      pitchAlter = pitchAlter + 2;
    }



    if (mode == 2) {                                 //if we are in mode 2 (patterns) then we are only using a single envelope instead of all 8.
      //here we grab the output from the first envelope and assign it to all 8 oscillator volumes
      tempGain = (int) envelope1.next();
      envGain1 = tempGain;
      envGain2 = tempGain;
      envGain3 = tempGain;
      envGain4 = tempGain;
      envGain5 = tempGain;
      envGain6 = tempGain;
      envGain7 = tempGain;
      envGain8 = tempGain;


    }



    if (speedsTimer.ready()) {           //in mozzi, things like delay() and delayMillis() do not work. You must learn to use the EventDelays instead to perform this
      //simple timer functionality. first, you start() the EventDelay variable with some millis time. Then, once the millis time
      //time period has passed, the EventDelay variable will be TRUE or "ready".
      stepNum = stepNum + 1;

      if (mode == 2 || mode == 3) {  //if we are in either patterns mode or freqmodz mode
        if (digitalRead(BUTTON2_PIN) == HIGH) { //if the HOLD SEQUENCE key button is NOT pressed (HIGH)
          if (digitalRead(BUTTON3_PIN) == LOW) { //if the random step button is pressed then choose the next seq step randomly between 1-4
            seqPos = random(0, 5);
          } else {
            seqPos = seqPos + 1;    //if the random step button is not pressed, then just move onto the next step
          }
        }
      } else {
        seqPos = seqPos + 1;
      }



      if (stepNum == 1) {
        speedsTimer.start(step1rh);
        envelope1.start(attack, decay);     //here the single envelope used is triggered at each new step. also, the step timer (speedsTimer) is start() again with new
      }                                   //rhythm step time (step1rh). this variable is a combination of the basic speed time and a unique rhythm variable seen later.
      if (stepNum == 2) {
        speedsTimer.start(step2rh);
        envelope1.start(attack, decay);
      }
      if (stepNum == 3) {
        speedsTimer.start(step3rh);
        envelope1.start(attack, decay);
      }
      if (stepNum == 4) {
        speedsTimer.start(step4rh);
        envelope1.start(attack, decay);
      }


      if (seqPos == 1) {
        if (outPut4 != 0 || outPut5 != 0) { //  if speeds input is connected to an output or rhythms input connected to an output
          aCarrier.setFreq(p1);         //sets fm mode (freqmodz) main carrier pitch
        }
        aSin1.setFreq(p1 + pitchAlter);                       // sets final pitch based on p1 (plus) p1/whatever voicing option we are in (plus) the pitchAlter variable
        aSin2.setFreq(p1 + (p1 / voicing1) + pitchAlter);
        aSin3.setFreq(p1 + (p1 / voicing2) + pitchAlter);
        aSin4.setFreq(p1 + (p1 / voicing3) + pitchAlter);
        aSin5.setFreq(p1 + (p1 / voicing4) + pitchAlter);
        aSin6.setFreq((p1 * 2) + (p1 / voicing1) + pitchAlter);
        aSin7.setFreq((p1 * 2) + (p1 / voicing2) + pitchAlter);
        aSin8.setFreq((p1 * 2) + (p1 / voicing3) + pitchAlter);
      }
      if (seqPos == 2) {
        if (outPut4 != 0 || outPut5 != 0) {
          aCarrier.setFreq(p2);
        }
        aSin1.setFreq(p2 + pitchAlter);
        aSin2.setFreq(p2 + (p2 / voicing1) + pitchAlter);
        aSin3.setFreq(p2 + (p2 / voicing2) + pitchAlter);
        aSin4.setFreq(p2 + (p2 / voicing3) + pitchAlter);
        aSin5.setFreq(p2 + (p2 / voicing4) + pitchAlter);
        aSin6.setFreq((p2 * 2) + (p2 / voicing1) + pitchAlter);
        aSin7.setFreq((p2 * 2) + (p2 / voicing2) + pitchAlter);
        aSin8.setFreq((p2 * 2) + (p2 / voicing3) + pitchAlter);
      }
      if (seqPos == 3) {
        if (outPut4 != 0 || outPut5 != 0) {
          aCarrier.setFreq(p3);
        }
        aSin1.setFreq(p3 + pitchAlter);
        aSin2.setFreq(p3 + (p3 / voicing1) + pitchAlter);
        aSin3.setFreq(p3 + (p3 / voicing2) + pitchAlter);
        aSin4.setFreq(p3 + (p3 / voicing3) + pitchAlter);
        aSin5.setFreq(p3 + (p3 / voicing4) + pitchAlter);
        aSin6.setFreq((p3 * 2) + (p3 / voicing1) + pitchAlter);
        aSin7.setFreq((p3 * 2) + (p3 / voicing2) + pitchAlter);
        aSin8.setFreq((p3 * 2) + (p3 / voicing3) + pitchAlter);
      }
      if (seqPos == 4) {
        if (outPut4 != 0 || outPut5 != 0) {
          aCarrier.setFreq(p4);
        }
        aSin1.setFreq(p4 + pitchAlter);
        aSin2.setFreq(p4 + (p4 / voicing1) + pitchAlter);
        aSin3.setFreq(p4 + (p4 / voicing2) + pitchAlter);
        aSin4.setFreq(p4 + (p4 / voicing3) + pitchAlter);
        aSin5.setFreq(p4 + (p4 / voicing4) + pitchAlter);
        aSin6.setFreq((p4 * 2) + (p4 / voicing1) + pitchAlter);
        aSin7.setFreq((p4 * 2) + (p4 / voicing2) + pitchAlter);
        aSin8.setFreq((p4 * 2) + (p4 / voicing3) + pitchAlter);
      }

    }

  }




  /////////////////////////////////////////////////////////////////////////////////////////

  if (outPut4 != 0 && outPut5 == 0) {  //  speed input is connected to an output AND rhythms input is not connected to an output.

    if (mode != 2 && mode != 5) {         // if we are NOT in mode 2 (patterns) or mode 5 (infinte bounce)

      if (speedsTimer.ready()) {
        envelope1.start(attack, decay);
        speedsTimer.start(speeds);
        stepNum = stepNum + 1;
      }
    }
  }


  if (outPut4 == 0 && outPut5 != 0) {  // speed input is NOT connected to an output (==0) AND rhythm input is connected to an output jack.

    if (mode != 2 && mode != 5) {

      if (speedsTimer.ready()) {

        stepNum = stepNum + 1;

        if (stepNum == 1) {
          speedsTimer.start(step1rh);
          envelope1.start(attack, decay);

        }
        if (stepNum == 2) {
          speedsTimer.start(step2rh);
          envelope1.start(attack, decay);
        }
        if (stepNum == 3) {
          speedsTimer.start(step3rh);
          envelope1.start(attack, decay);
        }
        if (stepNum == 4) {
          speedsTimer.start(step4rh);
          envelope1.start(attack, decay);
        }

      }
    }
  }

  if (outPut4 != 0 && outPut5 != 0) {  //  if speed input is connected to output AND rhythm input is also connected to output

    if (mode != 2 && mode != 5) {

      if (speedsTimer.ready()) {


        stepNum = stepNum + 1;

        if (stepNum == 1) {
          speedsTimer.start(step1rh);
          envelope1.start(attack, decay);
        }
        if (stepNum == 2) {
          speedsTimer.start(step2rh);
          envelope1.start(attack, decay);
        }
        if (stepNum == 3) {
          speedsTimer.start(step3rh);
          envelope1.start(attack, decay);
        }
        if (stepNum == 4) {
          speedsTimer.start(step4rh);
          envelope1.start(attack, decay);
        }

      }
    }
  }

  if (outPut4 == 0 && outPut5 == 0) {             // if speed input is not connected to an output and rhythm input is not connected to an output.


    if (mode != 2 && mode != 5) {


      fmGain = 255;

      envGain1 = 255;
      envGain2 = 255;
      envGain3 = 255;
      envGain4 = 255;
      envGain5 = 255;
      envGain6 = 255;
      envGain7 = 255;
      envGain8 = 255;

    }
  } else {
    fmGain = envelope1.next();
  }







  ///////////////////////////////////////////////////////////////////////////////////


  if (digitalRead(OPT_RHYTHM_PIN) == HIGH && reset5) {         //outPut5     RHYTHMS
    reset5 = false;
    outPut5 = pulseCounter5;
    pulseCounter5 = 1;
    offTimer5.start(250);
  }

  if (digitalRead(OPT_RHYTHM_PIN) == LOW) {
    reset5 = true;
    pulseCounter5 = pulseCounter5 + 1;
  }
  if (offTimer5.ready()) {
    outPut5 = 0;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////


  if (outPut5 != 0) {                         // RANDOM RHYTHMS CREATOR
    newRandrh.start(500);
  }

  if (newRandrh.ready()) {
    rhtime1 = random(1, 10);
    rhtime2 = random(1, 10);
    rhtime3 = random(1, 10);
    rhtime4 = random(1, 10);
    newRandrh.start();
  }





  if (outPut5 == 0) {                                  //if rhythm input is not connected to an output, all rhythm speeds default to the original speeds variable
    step1rh = speeds;
    step2rh = speeds;
    step3rh = speeds;
    step4rh = speeds;

    attack = 50;                         //the rhythm input also sets the envelope attack and decay times here.
    decay = 1200;

  }

  if (outPut5 == 2) {                  // else if rhythm input is connected to an output, speeds variable is modified to create the unique rhythm times
    step1rh = 1 * (speeds / rhtime1);
    step2rh = 1 * (speeds / rhtime2);
    step3rh = 1 * (speeds / rhtime3);
    step4rh = 1 * (speeds / rhtime4);

    attack = 50;
    decay = 250;

  }
  if (outPut5 == 3) {
    step1rh = 2 * (speeds / rhtime1);
    step2rh = 2 * (speeds / rhtime2);
    step3rh = 2 * (speeds / rhtime3);
    step4rh = 2 * (speeds / rhtime4);

    attack = 50;
    decay = 1000;
  }
  if (outPut5 == 5) {
    step1rh = 3 * (speeds / rhtime1);
    step2rh = 3 * (speeds / rhtime2);
    step3rh = 3 * (speeds / rhtime3);
    step4rh = 3 * (speeds / rhtime4);

    attack = 150;
    decay = 2000;
  }
  if (outPut5 == 6) {
    step1rh = 4 * (speeds / rhtime1);
    step2rh = 4 * (speeds / rhtime2);
    step3rh = 4 * (speeds / rhtime3);
    step4rh = 4 * (speeds / rhtime4);

    attack = 500;
    decay = 3000;

  }
  if (outPut5 == 7) {
    step1rh = 5 * (speeds / 400);
    step2rh = 5 * (speeds / rhtime2);
    step3rh = 5 * (speeds / rhtime3);
    step4rh = 5 * (speeds / rhtime4);

    attack = 1000;
    decay = 3000;

  }






}


int updateAudio() {                  ////// THE FINAL SECTION:  updateAudio() which takes all the audio data from each of the modes and mixes them into the final audio
  //output stream




  if (mode == 1 || mode == 2) {                   ////Wavetables and Patterns Modes
    long asig = (long)
                (aSin1.next() * envGain1) * gain1 +
                (aSin2.next() * envGain2) * gain2 +
                (aSin3.next() * envGain3) * gain3 +
                (aSin4.next() * envGain4) * gain4 +
                (aSin5.next() * envGain5) * gain5 +           //here the 8 oscillators (aSin1-8) are amplified by the envelope variables. then all of that is controlled by the
                (aSin6.next() * envGain6) * gain6 +           //individual gain variables. These gain gates are either ON (1) or OFF (0)
                (aSin7.next() * envGain7) * gain7 +
                (aSin8.next() * envGain8) * gain8;
    asig >>= 10;                          //this line is crucial! here we take this large audio sum and squish it down into a range that does not distort.
    return (int) asig;                  //variable asig is the final audio output variable
  }

  if (mode == 3) {                                                                  // FM
    return (int)(aCarrier.phMod(aModulator.next() * fmLevel)) * fmGain >> 8; //carrier phase modulation is controlled by the (modulator freq * the fm level)

  }

  if (mode == 4) {
    // CHIRP
    return wavey.next() >> 7;

  }

  if (mode == 5) {                               //BOUNCE
    long asig = (long)
                (aSin1.next() * envGain1) * gain1 +
                (aSin2.next() * envGain2) * gain2 +
                (aSin3.next() * envGain3) * gain3 +
                (aSin4.next() * envGain4) * gain4 +   //infinite bounce mode uses 4 individual envelopes and various groupings of oscillators
                (aSin5.next() * envGain1) * gain5 +
                (aSin6.next() * envGain2) * gain6 +
                (aSin7.next() * envGain3) * gain7 +
                (aSin8.next() * envGain4) * gain8;
    asig >>= 10;
    return (int) asig;
  }

  if (mode == 6) {                                      // PANIC

    long asig = (long)

                ((255 * aSin1.next()) + (modGain * aSin2.next())) * enhance; // the secret to data distortion synthesis (panic mode) is over-inflating the audio stream as seen here.


    return (int) asig >> 6;
  }
}
void loop() {
  audioHook();    //actual loop section which crunches all the audio date in updateAudio() above
}
