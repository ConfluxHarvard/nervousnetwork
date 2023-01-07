# Nervous Network

// Peggy Yin '25, Alice Cai '25, AnhPhu Nguyen '25

Nervous Network is a social experiment using wearable technology to illustrate the collective experience of fright.

Specifically, we will be making individual jellyfish costumes. We will all be connected to each other, like the nodes in a neural network, through the jellyfish legs. Our legs will light up in accordance with our pulse, such that as we get more scared and our hearts beat faster, the network begins to light up more in certain spots depending on who is scared, thereby giving "weight" to certain connections in the network. As captured by photography, these "Nervous Network" visualizations will be unique to every collective experience of fear.

## Gather materials
1. 3x long programmable LED strips
2. 2x short programmable LED strips
3. Heartbeat sensor with ear clip
4. Neopixel ring
5. Arduino Uno
6. Battery pack
7. Decorative ribbon
8. Shower cap
9. Velcro
10. Zip ties

## Making the Jellyfish
For this step of the tutorial, we will be wiring each LED to the power side of the power rail, the ground side of the power rail, and the input pins of the Arduino board. We have already velcroed the battery pack to the Arduino, connected the 5V power pin to the left power rail, and the ground pin to the right power rail. 

### LED strips
For each LED strip, notice how there are three wires extending from the end of the strip: a power wire, an input wire, and a ground wire. Start by wiring your long LED power wires to the power rail, ground wires to the ground rail, and input pins to pins 12, 11, and 10. Then do the same with your short LED power and ground wires, but connect your input wires to pins 9 and 8.

### Neopixel ring
The Neopixel ring also has a power wire, ground wire, and input wire. Wire the power wire to the power rail, the ground wire to the ground rail, and the input wire to pin 6.

### Pulse sensor
The pulse sensor has a power wire, ground wire and input wire. Wire the power wire to the power rail, the ground wire to the ground rail, and the input wire to pin A0 (on the analog pin side of the board).

### Upload the code
Plug your Arduino into your computer, and run nervous_networks_blue.ino. Clip the pulse sensor onto your ear. The ring should light up blue, and the legs should light up blue to your heartbeats. Then unplug the wire, and plug the red wire of the battery pack into the Vin pin of the Arduino. Plug the ground wire of the battery pack into the Arduino ground. Turn on the battery pack. Your jellyfish module should work!

### Decorate your jellyfish
Decorate your legs with ribbon!
