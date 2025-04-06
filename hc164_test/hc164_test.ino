/*
  74HC164 test code

  by Mark J. Koch ( @maehem on GitHub )

  This code was written on an Arduino Leonardo. Should work on others.

  2 x 4 Digital Display Module 74HC164 Driver
  Amazon Link:  https://www.amazon.com/dp/B0BG2G95CT

  This test draws the numbers 1 through 8 on the LED segments
  of the module.

  First byte clocked in is the segment data.
  Second byte clocked in is the position data.
  Usually only one bit is set, but setting multiple position 
  bits will copy the current segment data to each of those positions.

*/

#define DATA_PIN 6
#define CLK_PIN 7

// Segment layout
// Seg: MSB-LSB:
//     7: top,
//     6: r-upper
//     5: r-lower
//     4: bot
//     3: l-lower
//     2: l-upper
//     1: mid
//     0: point
//
// Another way to look at it: Clockwise: top..mid..point
//

uint8_t seg[8] = {
  0b00000001,  // 8
  0b00011111,  // 7
  0b01000001,  // 6
  0b01001001,  // 5
  0b10011001,  // 4
  0b00001101,  // 3
  0b00100101,  // 2
  0b10011111   // 1

};

int channel;

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);

  digitalWrite(DATA_PIN, LOW);
  digitalWrite(CLK_PIN, LOW);
}

void loop() {

  for (int i = 0; i < 8; i++) {

    for (int j = 0; j < 8; j++) {  // Write the segment data bits.
      digitalWrite(DATA_PIN, (seg[i] >> j) & 0x01);
      clkPulse();
    }

    channel = 1 << i;  // Select which LED to display on.

    for (int j = 0; j < 8; j++) {  // Write bits for channel.
      digitalWrite(DATA_PIN, (channel >> j) & 0x01);
      clkPulse();
    }

    // Use a much higher number to watch the numbers strobe across.
    // Lower numbers lower contrast, not pretty.
    delayMicroseconds(3000);  // Persistance of Vision delay.
  }
}

/*
 * Bit-banged clock pulse.  Using a PWM/timer might yeild better results?
 */
void clkPulse() {
  digitalWrite(CLK_PIN, HIGH);
  digitalWrite(CLK_PIN, LOW);
  delayMicroseconds(1);
}
