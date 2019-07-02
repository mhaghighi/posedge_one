# Posedge-One Hardware self-test Project
Hardware verification project for Posedge-One board.

# How-to
- Programm the board with project .bit file
- Put the LED-PB wing on one of the 6 possible wing locations on posedge-one board.
  All the LEDs must blink by default. By pressing each of 4 push-buttons on the wing
  the corresponding LED turns-off.
- Run Putty and connect to serial port of the board. Press the USER_PB button on the
  board to see the result of SRAM test on the terminal. All tests should be PASSED.
  
# Note:
In case you are going to build the project from the source (Not the .zip archive)
after openning the project in ISE, you need to remove microblaze instante from 
ISE project-nav and re-add it using "add source" option.