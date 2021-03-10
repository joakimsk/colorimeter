# Colorimeter

A project to develop an open source colorimeter / spectrophotometer that is "good enough". End goal is to analyze sample colors for water quality measurements, using off-the-shelf test kits for aquarium water quality. In the process, maybe we can do a sample with less reagents, as well.

## What you need
### Hardware needed
- An LDR, light sensitive resistor as light detector
- A single-wavelength or multi-wavelength LED as light source
- A couvette, preferably of quartz due to its optical qualities (Mine is 12.5x12.5x45mm from Purshee.com wavelength 200-2500nm, 3.5ml volume)
- An Arduino to make the measurements
- A PC to run software and analysis

### Tools needed
- A 3D-printer is nice but not necessary, print in black filament if possible, reduce light noise. Or spray paint with black. Or run in dark room.
- A PC for software
- Basic electronics tools are recommended

### Other things needed
- Food coloring for initial tests (optional)
- Water quality test kit (ammonia suggested, can be of any chemistry, but I am using salicylate method, JBL Seawater Ammonia test kit)
- Household ammonia (to calibrate software)

## Theory
Send light through a liquid, our sample. Detect how much light is received. With light at a certain color, the light received tells us how much light was absorbed, and how much was passed through the sample. If we use three different colors, maybe we can say which color the liquid is.

By taking samples through time, we can explore the kinematics of the liquid, to make sure we make a reading we can trust, when reagents are done reacting.

Putting this all together, we can also calibrate the readings of the kits to a known solution, for example using an ammonia kit and dosing ammonia at certain concentrations.

![Light path](img/colorimeter_3d_exploded_analysis.png?raw=true "Light path")
![Overview of couvette holder](img/colorimeter_3d_exploded.png?raw=true "Overview of couvette holder")

Something like that.

## Remaining work
- ~~Design 3D models, then print for couvette-assembly~~
- Assemble electronics
- Make Arduino software
- Make PC software
- Test and calibrate
- Final casing