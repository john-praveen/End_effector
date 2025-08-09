#include "fork.h"
#include "main.h"

void init_fork()
{
  DDRH |= 0b01111000; // Configure PH3-PH6 as output - stepper motor control
  DDRE |= 1 << 3;
  PORTH &= ~(1 << 4);
}

void drive_stepper(int distance_cm)
{
  const int steps_per_cm = 10000; // Adjust this value based on your stepper motor's configuration
  int steps = abs(distance_cm) * steps_per_cm;
  bool direction = (distance_cm > 0); // True for forward, false for backward

  // Set direction pin (PH3) D7
  if (direction)
    PORTH |= (1 << 3); // Forward
  else
    PORTH &= ~(1 << 3); // Backward

  PORTH &= ~(1 << 4);

  for (int i = 0; i < steps; i++)
  {
    // Generate pulse on PH5 D8
    PORTE |= (1 << 3);  // Pulse high
    _delay_us(10);      // Adjust delay for pulse width
    PORTE &= ~(1 << 3); // Pulse low
    _delay_us(10);      // Adjust delay for step interval
  }

  // Disable stepper motor (PH3)
  PORTH |= (1 << 4);
}