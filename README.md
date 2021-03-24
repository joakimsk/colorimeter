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
- A small syringe, I have 1 ml with a short tip from the local pharmacy

## Theory
Send light through a liquid, our sample. Detect how much light is received. With light at a certain color, the light received tells us how much light was absorbed, and how much was passed through the sample. If we use three different colors, maybe we can say which color the liquid is.

By taking samples through time, we can explore the kinematics of the liquid, to make sure we make a reading we can trust, when reagents are done reacting.

Putting this all together, we can also calibrate the readings of the kits to a known solution, for example using an ammonia kit and dosing ammonia at certain concentrations.

![Light path](img/colorimeter_3d_exploded_analysis.png?raw=true "Light path")
![Overview of couvette holder](img/colorimeter_3d_exploded.png?raw=true "Overview of couvette holder")

Something like that.

### Optical parameters
Reflectance: Amount of reflected light, referenced to a reference measurement. Expessed in % or dB, negative number.

Absorbance: Amount of light absorbed, referenced to a reference measurement, can be original light source. Expressed in dB, considered opposite of transmittance.

Transmittance: Amount of light transmitted through a liquid, referenced to a reference measurement, can be original light source. Expressed in % or dB.

![Optical parameters, copyright original owner](img/readme_optical_parameters.png?raw=true "Optical parameters, copyright original owner")

[pyroistech.com relative measurements ](https://www.pyroistech.com/relative-measurements/)

We should probably decide on what 100% transmittance is, then do a divison to find relative transmittance for various colors/wavelengths.

[sigmaaldrich.com transmittance/absorbance table](https://www.sigmaaldrich.com/technical-documents/articles/biology/transmittance-to-absorbance.html#:~:text=Absorbance%20(A)%20is%20the%20flip,be%20determined%20using%20this%20calculator.)

### Beer-Lambert law
[wikipedia.org Beer-Lambert law](https://en.wikipedia.org/wiki/Beer%E2%80%93Lambert_law)

Related to the attenuation of light, as it passes through a material. Absorbance = absorpitivity * optical path in cm * concentration of attenuating species.

Should only be applied to absorbance within 0.2 to 0.5, to maintain linearity.

## LDR details
The LDRs are commonly of CdS, Cadmium sulfide. They have also been mostly discontinued on Elfa Distrelec, but I found a datasheet.

![LDR spectral response](img/ldr_response.png?raw=true "LDR spectral response")
[pdf: ldr datasheet](pdf/ldr_datasheet.pdf)

## Quartz couvette details
The couvettes are often found in plastic, normal glass and quartz glass. There are various types of quartz, suitable for different wavelengths.

Here is a typical UV Quartz couvette transmittance plot

![Quartz couvette](img/quartz_couvette.png?raw=true "Quartz")

## Error sources
- If using a round couvette (glass vials that follow test kit), light can get bent along sides and avoid the liquid all-together. Thus we do not use the vials, for now.

- If using a small reagent dose, we may get imbalance in chemistry. Not sure how this will affect the reading. Read up on best practice with syringe usage.

- White PLA plastic, and 20% infill during print will allow more light to pass through the body. And, imperfect joints will too. Try black plastic spray paint for this. If not enough, use black PLA and set 100% infill. If still not enough, put it all inside another light-proof box.

- LDR and LED may not be accurate enough, so we may consider upgrading these components, maybe using a light sensor instead of a light resistor. LDR resistance is among other, temperature dependent. LDR has also a bit of latency, it takes time for the resistance to reach stable value, going from full dark to full light, often taking one second.

- Conversion roundoff errors and noise in Arduino may become a problem as well. Arduino Uno is 8 bit, the ADC has 8 bit resolution. The LDR is an analog device.

- Temporal issues due to sampling not being instant - if we make several readings at several colors, these will necessarily happen at a delta t larger than 0. Meaning that our readings will not happen in the same time, but spread over time, giving us small errors. By making sampling faster, we can mitigate but not eliminate this. Using a full spectrum light and read all wavelengths at the same time would be the best, but most expensive.

## Remaining work
- ~~Design 3D models, then print for couvette-assembly~~
- ~~Assemble electronics~~
- ~~Make Arduino software~~
- Make PC software (in progress)
- Test and calibrate (in progress)
- Final casing

## Theory & code references
[moleculardevices.com Absorbance](https://www.moleculardevices.com/technology/absorbance)
[electronics-tutorials.ws Light sensors](https://www.electronics-tutorials.ws/io/io_4.html)

## Similar work
[mit.edu Low Cost Colorimeter](http://www.mit.edu/~milesdai/projects/colorimeter/index.html)
[iorodeo.com Open Source Colorimeter Project](https://iorodeo.com/pages/colorimeter-project)
[instructables.com Inexpensive photometer & colorimeter](https://www.instructables.com/An-Inexpensive-Photometer-and-Colorimeter/)
[arduino.cc Open Source Colorimeter](https://create.arduino.cc/projecthub/MOST/open-source-colorimeter-cd0a76)
[arduino.cc Mini spectrophotometer](https://create.arduino.cc/projecthub/radsensors/minispec-0e3bc5)
[publicLab.org Desktop spectrometer with DVD diffraction grating](https://publiclab.org/notes/abdul/08-11-2016/constructing-a-desktop-spectrometer-with-no-wood-and-no-velcro)

[researchgate.net A Simple, Rapid Analysis, Portable, Low-cost, and Arduino-based Spectrophotometer with White LED as a Light Source for Analyzing Solution Concentration](https://www.researchgate.net/publication/324161531_A_Simple_Rapid_Analysis_Portable_Low-cost_and_Arduino-based_Spectrophotometer_with_White_LED_as_a_Light_Source_for_Analyzing_Solution_Concentration)
[researchgate.net Open-Source Colorimeter](https://www.researchgate.net/publication/236252679_Open-Source_Colorimeter/link/0c9605171839574c56000000/download)
[iop.org Development of color detector using colorimetry system with
photodiode sensor for food dye determination application](https://iopscience.iop.org/article/10.1088/1742-6596/1185/1/012031/pdf)

## Possible light sources and detectors
[sparkfun rgb light sensor ISL29125](https://www.sparkfun.com/products/12829)
[Digital 16bit Serial Output Type Ambient Light Sensor IC BH1750FVI](https://www.mouser.com/datasheet/2/348/bh1750fvi-e-186247.pdf)
[electronics-notes.com LDR: Light Dependent Resistor](https://www.electronics-notes.com/articles/electronic_components/resistors/light-dependent-resistor-ldr.php)