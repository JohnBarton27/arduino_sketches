#define A 2
#define B 3
#define C 4
#define D 5
 
#define NUMBER_OF_STEPS_PER_REV 512
#define DELAY 5

void setup() {
  Serial.begin(9600);
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
}

void write(int a, int b, int c, int d) {
  digitalWrite(A,a);
  digitalWrite(B,b);
  digitalWrite(C,c);
  digitalWrite(D,d);
}

void step_backwards() {
  write(1,0,0,0);
  delay(DELAY);
  write(1,1,0,0);
  delay(DELAY);
  write(0,1,0,0);
  delay(DELAY);
  write(0,1,1,0);
  delay(DELAY);
  write(0,0,1,0);
  delay(DELAY);
  write(0,0,1,1);
  delay(DELAY);
  write(0,0,0,1);
  delay(DELAY);
  write(1,0,0,1);
  delay(DELAY);
}

void step_forwards() {
  write(1,0,0,1);
  delay(DELAY);
  write(0,0,0,1);
  delay(DELAY);
  write(0,0,1,1);
  delay(DELAY);
  write(0,0,1,0);
  delay(DELAY);
  write(0,1,1,0);
  delay(DELAY);
  write(0,1,0,0);
  delay(DELAY);
  write(1,1,0,0);
  delay(DELAY);
  write(1,0,0,0);
  delay(DELAY);
}

void rotate_degrees(int degrees) {
  bool forwards = true;
  if (degrees < 0) {
    forwards = false;
    degrees = abs(degrees);
  }
  float degrees_per_step = 360.00 / NUMBER_OF_STEPS_PER_REV;
  int num_steps_needed = degrees / degrees_per_step;

  int curr_step = 0;
  while (curr_step < num_steps_needed) {
    if (forwards) {
      step_forwards();
    } else {
      step_backwards();
    }
    curr_step++;
  }

}

void loop(){
  rotate_degrees(90);

  delay(2500);
  
  rotate_degrees(-45);
  delay(2500);
  rotate_degrees(-45);

  delay(10000);
}
