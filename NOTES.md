# Colorimeter Notes


## PWM vs LDR resistance

Measurement of LDR resistance against PWM output value, Arduino ADC range is {0-255}. Shining through the colorimeter, but without couvette (i forgot it...).
Colorimeter is kept in the dark (with a Norwegian dark grey lue), so light pollution should be minimal.

|       	| 20     	| 45    	| 50    	| 100  	| 150  	| 200  	| 250  	| 255  	|
|-------	|--------	|-------	|-------	|------	|------	|------	|------	|------	|
| Red   	| ~1975k 	| ~835k 	| ~760k 	| 366k 	| 241k 	| 180k 	| 144k 	| 142k 	|
| Green 	| 526k   	| 232k  	| 208k  	| 102k 	| 67k  	| 49k  	| 38k  	| 38k  	|
| Blue  	| ~760k  	| 333k  	| 299k  	| 141k 	| 88k  	| 63k  	| 49k  	| 48k  	|
| All   	| 249k   	| 112k  	| 101k  	| 50k  	| 32k  	| 23k  	| 18k  	| 18k  	|

All means all three colors are turned on at the same time. Driving voltage is 5v, and resistors I forgot to write down...

We do this to consider which resistor value to use for the voltage divider on the LDR side.

We also get an impression of where the LDR is most sensitive, and least sensitive.

Here is a chart of the data.

![Light path](img/notes_ldr_pwm_chart.png?raw=true "LDR vs PWM duty chart")

Average of the table is 256.9 kohm
Median of the table is 126.5 kohm

I cannot remember how to select optimal value, so I will just use the average value as the second resistor in the voltage divider. This should give us a 2.5 volt to ADC when the LDR is at the average value.

I select 220 kohm + 38.6 kohm, measured to 258 kohm, near enough to 256.9 kohm.

We set RGB to <100,100,100>
LDR resistance with clear path: 53 kohm
LDR resistance with quartz couvette: 58.3 kohm and inserted wrongly: 191 kohm
LDR resistance with plastic couvette: 61 kohm and inserted wrongly: 66 kohm

## Thoughts about Arduino ADC
The Analog to Digital conversion in the Arduino Uno, using the ATmega328 8-bit MCU, has 10 bits resolution.

ADC Resolution = Vref / ((2^n) - 1) = 5 / ((2^10)-1) = 5/1023 = 0.00488758553 volt bins

Digital output = Vin / Resolution
Digital output = 5 / 0.00488758553 = 1023 (when Vin is 5v)
Digital output = 2.5 / 0.00488758553 = 512 (when Vin is 2.5v)

A voltage divider:
Vout = ( R2 / (R1 + R2)) * Vin
Vout = ( R2 / (R1 + R2)) * Vin

![Light path](img/notes_res_div.png?raw=true "Resistive divider")

Setting R2 = 258 kohm
We have R1 being the LDR, varying from 18 kohm to up to 2000 kohm (guestimates finger in the air values from the table).

We set R1 to be LDR because when LDR gets light on it, it will "pull up" Vout to Vin voltage. This is because LDR resistance goes down when light amount goes up.

This gives us two extremes, for high light and low light conditions, remembering that the LDR lowers resistance under higher light:

Vout = ( 258000 / (18000 + 258000)) * 5 = 4.67391304348 volts

Digital output = 4.67391304348 / 0.00488758553 = 956 (when Vin is 5v)


Vout = (258000 / (2000000 + 258000)) * 5 = 0.5713020372 volts

Digital output = 0.5713020372 / 0.00488758553 = 117 (when Vin is 5v)


## Color sample solutions
Food coloring was used to make "standard" solutions for red, green and blue. The primary colors we are interested in, for the Salicylate method for total ammonia nitrogen, is green/yellow to dark blue, but it is nice to check the colorimeter for more colors.

"1 cm long" string of blue food coloring and 5 ml freshwater was mixed.
Aproximately the same amount of red and green was added to their own 5 ml freshwater, and was mixed.

Two "1ml syringes" of colored liquid was added to the quartz couvettes, totalling 2 ml in each couvette, hopefully enough to not allow light to pass in air above the liquid.

![Blue & Green](img/notes_blue_green_standards.jpeg?raw=true "Blue & Green Standard")
![Blue & Red](img/notes_blue_red_standards.jpeg?raw=true "Blue & Red Standard")

## Actual LED colors
It seems that R + G + B != White with an RGB led, to my eyes it looks more azure blue than anything else.
Ideally I would do all this with a white LED as well one day.

![Red](img/notes_red_led.jpeg?raw=true "Red led")
![Green](img/notes_green_led.jpeg?raw=true "Green led")
![Blue](img/notes_blue_led.jpeg?raw=true "Blue led")
![All](img/notes_all_leds.jpeg?raw=true "All leds")

## First trials
We receive the voltage coming from the voltage bridge, using an ADC in the Ardunio, translating this voltage into a value between 0-1023.

We use the "Lue" to make sure its dark around the colorimeter, as the black spray paint was not enough to make it opaque to outside light.

This is just to get to know the thing. Lids of couvettes were marked A and B, to keep them seperate. A couvette stand was used after the first spill of saltwater across the desk.

![Colorimeter, couvette inserted](img/notes_colorimeter_couvette_inserted_nolid.jpeg?raw=true "Colorimeter, couvette inserted")

### Comparing freshwater and saltwater without and with lue
Temperature on both water was roughly 10 degree Celsius in this case.

Unit: 10-bit ADC values, higher means more light passed liquid
|                  | R       | G       | B       | All |
|------------------|---------|---------|---------|-----|
| Freshwater       | 706-710 | 909-910 | 885-886 | NA  |
| Saltwater        | 703-704 | 906-907 | 882-883 | NA  |
| Freshwater (Lue) | 705-708 | 907-909 | 882-883 | NA  |
| Saltwater (Lue)  | 705-707 | 906-907 | 881-882 | NA  |

Here I wanted to see if Lue had much to say on the readings. It has 1-4 values to say, it seems, so we continue using Lue.
I also think freshwater and saltwater has different colors, but the readings fluctuate a bit so not so easy to say.

### Comparing "standard" freshwater solutions
The "standards" were compared.

Unit: 10-bit ADC values, higher means more light passed liquid
|                    | R       | G       | B       | ALL     |
|--------------------|---------|---------|---------|---------|
| "Standard green"   | 408-412 | 869-870 | 550-553 | 900-902 |
| "Standard blue"    | 290-294 | 891-892 | 879-880 | 950     |
| "Standard red"     | 384-389 | 0-1     | 0-1     | 373-376 |
| "50% standard red" | 566-568 | 48-51   | 141-145 | 612-614 |

It seems that the "standard red" is too dense, it does not allow any green nor blue through it. After diluting 50%, it was better, but still very strong. I believe the standard was mixed too strong.

Here is blue, red and 50% red standards, notice transparency and lack thereof.

![Blue standard](img/notes_blue_standard.jpeg?raw=true "Blue standard")
![Red standard](img/notes_full_red.jpeg?raw=true "Red standard")
![50% red standard](img/notes_50p_red.jpeg?raw=true "50% red standard")

### Some observations, possible issues and improvements
There is a big difference in viscosity between red, green and blue food coloring. The blue was very viscous, and it was difficult to portion out the amount of coloring by volume

When sampling, I would say I used "n=5-10" by making several reads after a few seconds, when LDR should be stable, not so scientific.

Saltwater vial also had small bubbles in it, which may reduce light. I forgot to make readings with all LEDs on.
![Bubbles in saltwater](img/notes_swbubbles.jpeg?raw=true "Bubbles in saltwater")

Pharmacy syringes seem to loose their markings after some mechanical action. Get a proper one.

The LDR likely does not behave linearly, either.

The voltage divider would probably be nicer with a potentiometer, so we can adjust the voltage range.

### Conclusion from first trials
Red is more opaque to green and blue, than red light.
Green is more opaque to blue and red, than green light.
Blue is more opaque to green and red, than blue light.

Could we use ALL leds without a couvette as 100% Transmittance, and then do a simple divison to find transmittance in %? Plausible way forward.
We could also do transmittance at different wavelengths.