// import libraries
// define pin constants
// define objects and variables

void setup() {
  // TODO - Attach pins and servo
}

void loop() {
  duration = get_pulse_duration();
  cm = ms_to_cm(duration);
  if (cm < limit) {wave()};
}

long get_pulse_duration() {
  // TODO - used to interact with sensor
}

long ms_to_cm(long ms) {
  // TODO - conversion function using speed of sound
}

void wave() {
  // TODO - control of servos, rotate to set angles
}
