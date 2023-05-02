# crashy-car

## Requirements:
- Qt 5.15.2
- qmake toolchain for your target
- BeagleBone Black
- 4.3” LCD touchscreen and cape for BeagleBone by element14
- Adafruit I2C LSM9DS0 breakout board

## File Organization
- /crashy-car
  - crashy_car.pro (project file)
  - /source
    - contains all the source files the project
    - /unimplemented
      - The WIP source files that we didn't implement yet.
  - /resources
    - contains all the images used in the project
    - /unused
      - placeholder and other images that did not make it into the final game
  

## How to Build and Install
- Connect cape to BeagleBone
- On the accelerometer breakout board, connect the pins to the GPIO headers on the cape as follows: `SDA` to header `pin 20`, `SCL` to header `pin 19`, `VIN` to header `pin 4` and `GND` to header `pin 2`.
- Download the repo to a directory of your choosing. 
- Run qmake in the same directory as `crashy_car.pro` to generate a `Makefile`.
- Run `make`
- Move the resulting executable `crashy-car` to the BeagleBone
- Make sure the executable has execution privileges and use `./crashy-car` to run the game.

## How to play
- Hold the accelerometer by the two holes in the top like a game pad. This means the writing will be upside down, but this is the most comfortable way to hold it while getting the best performance and avoiding the wiring.
- Touch the `start` button near the bottom of the screen.
- Steer the accelerometer left or right like a steering wheel to move the car left or right.
- If you crash, touch the `restart` button to start again.
