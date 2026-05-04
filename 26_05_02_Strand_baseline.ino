//  5/02/26 notes
//this appears to be the most recent version
//plan - install it and see if it works


// 5/13/24 notes
//ran outside, pretty good - maybe needs more turns
//intermittent - loses voice recorder control
//also, can write fuction to blink LED, simplify code - works!
// next function to close rearMouth


// 5/11/24 notes
//add new eye commands to segment 2
//eyes are good now; some segs don't have eye movement it's OK
//next -take out some delays and try outside - OK
// next - is the front mouth action OK? - action is not bad
///can use code to return to closed position
//added closeMouth - works great
//clean up wiring, adjust volumes, try outside

// 5/9/24 notes
//trying to add function for eyes
//need more eye movement
// function A or B seems to have reversed sweep?


//added motors to segment 4
//motors OK
//shorten blinks
//overall pretty good, need faster eye movement
//start with eyes C, D segment 1    
 
//mouths are installed, strand runs
//not enough movement - add motors to seg 1A
//comment out LED blinks - back in but faster 


// 4/29/24 notes
//ran outside - make changes
// swap segment 0 & 1 - will make start-up more consistent?-done
//too much delay, shorten them - done
//turn isn't good, make one motor reverse to aid - done
//make these changes and then to garage to install mouths, etc.
//in garage, still too much delay - take out flashing lights!


//plan - add segment 3 - done
//next, add some more eye action to segments 1 & 2
//segment 2 OK, next segment 1 - done
//next, segment 0 - two cows + rearMouth, no eyes, no motors

// 4/26/24 status
//segment 1 OK, segment 2 underway
//still can't figure out how to use a function for eyes!

// 4/24/24 status
//frontMouth working OK, except may want to close it after use 
//next - finalize segment 1, then on to segment 2
//eyes A & B are OK

//4/21/24 plan
//get mouths working - start with chicken & cow
//unplug servo for voice recorder mouth
//rear mouth (hen, coe) is OK
//next is front mouth  
  
// 4/17/ notes
//both mouths move now, need major improvement
//eye sweeps are slow 
//first shorthen program - comment out seg 2, other stuff-done
//next - speed up one eye and eval - looks good running first half of segment
// is there a way to make the eyes functions? Huge code savings possible
// set up a segment 0 for testing

// 4/13/24 notes
//fix sound module - doesn't work
//load 23_09_15 Strand base  into strand and verify works - it works OK
//next, finish segment 2 of this program and test in strand
   
// 4/8/24 notes
//next remove print commands
//remove unused code from giant heads - done,works OK
//then work on segment 2 - next!
//evaluate for unneeded code 


//for older notes, see prvious version of this program


int Sound = 0; 
int Cow = 1;   
                //pin 2 not used
int eyeA = 3;    //front and rear eye locations A
int eyeB = 4;    //front and rear eye locations B
int motorL = 5;  //left side motor output pin
int motorR = 6;  //right side motor output pin
int eyeC = 7;    //front and rear eye locations C 
int eyeD = 8;    //front and rear eye locations D
int MOUTH = 9;   // front mouth
int Rmouth = 10;  // rear mouth  
                  //pin 11 not used 
int LEDA = 12;    //yellow
int LEDB = 13;    //red, also controls Hen   

int pulseMotorL = 2200;    //initial servo pulse width for left side motor
int pulseMotorR = 2200;    //initial servo pulse width for right side motor

int pulseEyeA = 1500;     //initial pulse for eye A
int pulseEyeB = 1500;     //initial pulse for eye B
int pulseEyeC = 1500;     //initial pulse for eye C
int pulseEyeD = 1500;      //initial pulse for eye D

                           //assumes LEDA and LEDB are low at start-up
int i = 0;                 //needed because this uses "i" below in "for "    

//____________________________________________________________________________
//add mouth code from giant heads

int val1 = 0;   // from analog pin 1
int val0 = 0; // from analog pin 0
int value = 0; //value from analog pin 1

int k=0; 
int dur =0; //length of servo pulses

int pulseMax = 1350;  //from 2300 to 1350 11/11/23
int PulseMin =510;  //use if frontMouth 4/22/24
int pulseMin = 700;  //from 800 on 4/21/24
int pulseLength = 1000;
int PulseLength = 1200;   //used in rearMouth function

int pulseCen = 1200; 
int mult = 25;   //       was this 50???, or 20 or 5?
float expt = .50;

int fwd = 2200;
int rev = 700;
int G = 6;




//_______________________________________________ new function frontMouth
//based on servo drive from giant heads

void frontMouth(int val0) {
val0 = analogRead(0);  //calculate pulseLength and limit its range

//pulseLength = PulseMin;
pulseLength = PulseMin+mult*pow(val0, expt);

 
if (pulseLength< PulseMin) pulseLength = PulseMin;
if (pulseLength> pulseMax) pulseLength = pulseMax;

digitalWrite(MOUTH, HIGH); //start servo pulse
delayMicroseconds(pulseLength);
digitalWrite(MOUTH, LOW);
}

//_______________________________________________ new function rearMouth
//based on servo drive from giant heads

void rearMouth(int val1) {
val1 = analogRead(1);  //calculate pulseLength and limit its range
PulseLength = pulseMin+ mult*pow(val1, expt)*1.3; // 4/21/24 added *1.3
 
if (PulseLength< pulseMin) PulseLength = pulseMin;
if (PulseLength> pulseMax) PulseLength = pulseMax;

digitalWrite(Rmouth, HIGH); //start servo pulse
delayMicroseconds(PulseLength);
digitalWrite(Rmouth, LOW);
}


//______________________________________________________ new function closeMouth

void closeMouth(int PulseMin)  {
 for (i= 0; i < 10; i++) { 
digitalWrite(MOUTH, HIGH); //start servo pulse
delayMicroseconds(PulseMin);
digitalWrite(MOUTH, LOW);

digitalWrite(Rmouth, HIGH); //start servo pulse
delayMicroseconds(pulseMin);
digitalWrite(Rmouth, LOW);

delay(18);  
} 
}

//______________________________________________________ new function blinkA

void blinkA (int J) {
for (i = 0; i < J; i++) {
digitalWrite(LEDA, HIGH);  //yellow
delay(150);
digitalWrite(LEDA, LOW);
delay(150);
}
}


//________________________________________________ new function motorsFWD 

void motorsFwd(int fwd) {
digitalWrite(motorL, HIGH);       //pulse for left motor
delayMicroseconds(fwd);   
digitalWrite(motorL, LOW);        

digitalWrite(motorR, HIGH);       //pulse for right motor
delayMicroseconds(fwd);   
digitalWrite(motorR, LOW);        
}


//________________________________________________ new function motorsRT 

void motorsRT(int fwd) {
digitalWrite(motorL, HIGH);       //pulse for left motor
delayMicroseconds(fwd);   
digitalWrite(motorL, LOW);        

digitalWrite(motorR, HIGH);       //pulse for right motor
delayMicroseconds(rev);      // 700us = reverse
digitalWrite(motorR, LOW);        
}



//______________________________________________________________ eye function?
//rewrite this using actual names of pins, etc - done
//still doesn't work - why? - returns value to program - forbidden!!
/*
void sweepLeft (int pulseEyeA) {
 if (i < 125) {
digitalWrite(eyeA, HIGH);       
delayMicroseconds(pulseEyeA);   //pulse width
digitalWrite(eyeA, LOW);        //end of pulse
pulseEyeA = pulseEyeA - 4;    //returns value to program - forbidden!!
}
}
*/
 int Test = 1000;

//_______________________________________________________________________ eye functions

void A (int pulseEyeA)  {
digitalWrite(eyeA, HIGH);       
delayMicroseconds(pulseEyeA);   
digitalWrite(eyeA, LOW);          
}

void B (int pulseEyeB)  {
digitalWrite(eyeB, HIGH);       
delayMicroseconds(pulseEyeB);   
digitalWrite(eyeB, LOW);          
}

void C (int pulseEyeC)  {
digitalWrite(eyeC, HIGH);       
delayMicroseconds(pulseEyeC);   
digitalWrite(eyeC, LOW);          
}

void D (int pulseEyeD)  {
digitalWrite(eyeD, HIGH);       
delayMicroseconds(pulseEyeD);   
digitalWrite(eyeD, LOW);          
}






void setup() {  //________________________________________________________ setup

digitalWrite(Sound, LOW);

 pinMode(eyeA, OUTPUT);
 pinMode(eyeB, OUTPUT);
 pinMode(motorL, OUTPUT);
 pinMode(motorR, OUTPUT);
 pinMode(eyeC, OUTPUT);
 pinMode(eyeD, OUTPUT);
 pinMode(MOUTH, OUTPUT);
 pinMode(Rmouth, OUTPUT); 
 pinMode(Sound, OUTPUT);     
 pinMode(Cow, OUTPUT);    
 pinMode(LEDA, OUTPUT);
 pinMode(LEDB, OUTPUT);  
}




void loop() {   //_____________________________________________________ start program


//________________________________________________________________________segment 1

digitalWrite(Sound, HIGH);  // start sound

pulseEyeA = 1500;
pulseEyeB = 1500;
pulseEyeC = 1500;
pulseEyeD = 1500;

blinkA (3);  //______________________________________________ 2 blink yellow LED
 
for (i=0; i<=500; i++){  
//___________________________________________________ motors forward
fwd = 2200;
motorsFwd(fwd);

//__________________________________________________cow & hen
if (i<200)
{digitalWrite(Cow, HIGH);
}
else {
  digitalWrite(Cow, LOW); 
}

if (i>300)
{digitalWrite(LEDB, HIGH); //hen
}

delay(1);

//_____________________________________eyeA, B, C, D
if (i >0 && i < 62.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*2; 
}

if (i >62.5 && i < 187.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA + G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*2; 
}

if (i >187.5 && i < 250) {
A (pulseEyeA);
pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*4; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*4; 
}

if (i >250 && i < 312.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*4; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*4; 
}

if (i >312.5 && i < 437.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA + G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*2; 
}

if (i >437.5 && i < 500) {
A (pulseEyeA);
 pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*2; 
}


rearMouth(val1);  //______________________________________rear mouth
frontMouth(val0);   //________________________________front mouth
delay(5);                   

}   

closeMouth(PulseMin);  //___________________________________close mouth

digitalWrite(LEDB, LOW);
digitalWrite(Cow, LOW);
digitalWrite(Sound, LOW);  //sound module trigger off 

blinkA (2);  //_________________________________________ 2 blink yellow LED





//__________________________________________________________________________ segment 1A

digitalWrite(Sound, LOW);

for (i = 0; i<=300; i++) {   // was 400 5/11/24

//___________________________________________________ motors forward
fwd = 2200;
motorsFwd(fwd);

delay (11);
rearMouth(val1);  //______________________________________rear mouth

if (i <50) {
digitalWrite(Cow, HIGH);
}
else {
digitalWrite(Cow, LOW); 
}
if (i>150 && i < 200)
{digitalWrite(Cow, HIGH);
}
}  


//______________________________________________________segment 2 - forward, animals

digitalWrite(Sound, HIGH);  //activate sound module

pulseEyeA = 1500;
pulseEyeB = 1500;
pulseEyeC = 1500;
pulseEyeD = 1500;

for (i=0; i<500; i++) {

fwd = 2200;   //________________________________________ motors
motorsFwd(fwd);
// motorsRT(fwd);

//__________________________________________________________ mouths
rearMouth(val1); 
frontMouth(val0);  

delay(1);

//_____________________________________________________ hen & cow
if (i >0 && i < 50) {
digitalWrite(LEDB, HIGH);  // Hen start
}
else {
digitalWrite(LEDB, LOW);   
}
if (i >400 && i < 450) {
digitalWrite(LEDB, HIGH);  // Hen start
}
if (i>200 && i < 250) {
digitalWrite(Cow, HIGH);
}
else {
digitalWrite(Cow, LOW);
}


delay(1);
//_____________________________________eyeA, B, C, D
if (i >0 && i < 62.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*2; 
}

if (i >62.5 && i < 187.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA + G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*2; 
}

if (i >187.5 && i < 250) {
A (pulseEyeA);
pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*4; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*4; 
}

if (i >250 && i < 312.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*4; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*4; 
}

if (i >312.5 && i < 437.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA + G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*2; 
}

if (i >437.5 && i < 500) {
A (pulseEyeA);
 pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*2; 
}

}

closeMouth(PulseMin);  //___________________________________close mouth

digitalWrite(LEDB, LOW);  // Hen stop
digitalWrite(Sound, LOW);  //sound module stp

blinkA (3);   //___________________________________________ 3 blink yellow LED





//___________________________________________________________   segment 3 - forward, animals

digitalWrite(Sound, HIGH);  //activate sound module

pulseEyeA = 1500;
pulseEyeB = 1500;
pulseEyeC = 1500;
pulseEyeD = 1500;


for (i=0; i<500; i++) {

fwd = 2200;   //________________________________________ motors
motorsFwd(fwd);

//__________________________________________________________ mouths
rearMouth(val1); 
frontMouth(val0);  

delay(1);

//_____________________________________________________ hen & cow
if (i >0 && i < 50) {
digitalWrite(Cow, HIGH);  // cow start
}
else {
digitalWrite(Cow, LOW);   
}
if (i >400 && i < 450) {
digitalWrite(Cow, HIGH);  // cow start
}
if (i>200 && i < 250) {
digitalWrite(LEDB, HIGH);  //hen
}
else {
digitalWrite(LEDB, LOW);
}

delay(1);
//_____________________________________eyeA, B, C, D
if (i >0 && i < 62.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA + G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*2; 
}

if (i >62.5 && i < 187.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*2; 
}

if (i >187.5 && i < 250) {
A (pulseEyeA);
pulseEyeA = pulseEyeA + G*4;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*3.8;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*4; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*4; 
}

if (i >250 && i < 312.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA - G*4;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*3.8;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*4; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*4; 
}

if (i >312.5 && i < 437.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA + G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*2; 
}

if (i >437.5 && i < 500) {
A (pulseEyeA);
 pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*2; 
}

}
closeMouth(PulseMin);  //___________________________________close mouth

digitalWrite(LEDB, LOW);  // Hen stop
digitalWrite(Sound, LOW);  //sound module stp


blinkA (4);  //___________________________________________ 4 blink yellow LED




//__________________________________________________________________________ segment 4

digitalWrite(Sound, LOW);
 
for (i = 0; i<=400; i++) {

fwd = 2200;   //________________________________________ motors
motorsFwd(fwd);
  
delay (11);
rearMouth(val1);  //______________________________________rear mouth

if (i <100) {
digitalWrite(LEDB, HIGH);  //Hen
}
else {
digitalWrite(LEDB, LOW); 
}
if (i>200 && i < 250)
{digitalWrite(LEDB, HIGH);
}
}  



//___________________________________________________________   segment 5 - right turn, animals

digitalWrite(Sound, HIGH);  //activate sound module

pulseEyeA = 1500;
pulseEyeB = 1500;
pulseEyeC = 1500;
pulseEyeD = 1500;
 
for (i=0; i<500; i++) {

fwd = 2200;   //________________________________________ motors
motorsRT(fwd);

//__________________________________________________________ mouths
rearMouth(val1); 
frontMouth(val0);  

delay(1);

//_____________________________________________________ hen & cow
if (i >0 && i < 50) {
digitalWrite(Cow, HIGH);  // cow start
}
else {
digitalWrite(Cow, LOW);   
}
if (i >400 && i < 450) {
digitalWrite(Cow, HIGH);  // cow start
}
if (i>200 && i < 250) {
digitalWrite(LEDB, HIGH);  //hen
}
else {
digitalWrite(LEDB, LOW);
}


delay(1);
//_____________________________________eyeA, B, C, D
if (i >0 && i < 62.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA + G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*2; 
}

if (i >62.5 && i < 187.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*2; 
}

if (i >187.5 && i < 250) {
A (pulseEyeA);
pulseEyeA = pulseEyeA + G*4;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*3.8;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*4; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*4; 
}

if (i >250 && i < 312.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA - G*4;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*3.8;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*4; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*4; 
}

if (i >312.5 && i < 437.5) {
A (pulseEyeA);
pulseEyeA = pulseEyeA + G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB + G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC + G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD - G*2; 
}

if (i >437.5 && i < 500) {
A (pulseEyeA);
 pulseEyeA = pulseEyeA - G*2;
B (pulseEyeB);
pulseEyeB = pulseEyeB - G*1.9;
C (pulseEyeC);
pulseEyeC = pulseEyeC - G*2; 
D (pulseEyeD);
pulseEyeD = pulseEyeD + G*2; 
}

}

closeMouth(PulseMin);  //___________________________________close mouth

digitalWrite(LEDB, LOW);  // Hen stop
digitalWrite(Sound, LOW);  //sound module stp


blinkA (4);  //_____________________________________________ 4 blink yellow LED


delay(1000);


}
