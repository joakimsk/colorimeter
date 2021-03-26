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
Temperature on both water was roughly 10 degree Celsius in this case. I forgot to make readings with all LEDs on.

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

Saltwater vial also had small bubbles in it, which may reduce light. And, try to avoid touching the quartz with my fatty fingers.
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

## Transmittance implementation
I think we can do this naively, take a calibration reading with an empty couvette in the colorimeter.

Then, take another with the couvette filled with sample liquid, and do a division of ADC values. Output in % transmittance, according to the different LED colors.

Since we do a calibration reading, we should even be able to let the Lue be on the head, where it belongs, instead of on top of the colorimeter.

## LDR time stability and settling-time
It seems that one second is not enough for the LDR to settle after being illuminated. I should probably try an experiment for each LED, to see how long the LDR really takes.

![LDR time stability](img/notes_ldr_stability.png?raw=true "LDR time stability")

Notice that after the LDR has been kept in the dark for a while, the end-point does not seem to be reached, since the red-transmittance reading is lower.

Since my LDR is a generic no-name without a datasheet, I have no clue about its spectral response nor its response time, but response time could be deduced experimentally.
My RGB led is also generic no-name, without a datasheet.

[lednique.com ldr details](http://lednique.com/opto-isolators-2/light-dependent-resistor-ldr/)

## Test methods

There are a few different methods, and variations of those used to measure total ammonia nitrogen, TAN, in aquaculture. The goal is to figure out if we have toxic levels of unionized ammonia NH3 in the water, but the test kits have a tendency to be ambigous regarding what they are actually indicating.

Two of the more common ones in the hobbyist aquarium world is:

The Salicylate method. In the salicylate method, monochloramine formed by the reaction of ammonia and hydrochlorine reacts with salicylate to form blue-green colored 5-aminosalicylate in proportion to the amount of ammoniacal nitrogen. Works well on lower concentrations of TAN, commonly 0–1.0 mg/L.

The Nessler method. A combination of mercury (II) iodide and potassium iodide in highly alkaline solution. Gives a yellow color. Contains mercury, and is thus not available in Norway. Also has a wider effective undiluted range of 0.02–5.0 TAN.

![Salicylate vs Nessler](img/notes_tan_methods.gif?raw=true "Salicylate vs Nessler")
Read more about these two [here](https://aquabaz.tripod.com/ammoniageneral.htm)

And a more detailed comparison of several methods [Comparison of Nessler, phenate, salicylate and ion selective electrode procedures for determination of total ammonia nitrogen in aquaculture](https://www.sciencedirect.com/science/article/abs/pii/S0044848615301058)

On the topic of units, Nofima has a nice writeup in Norwegian. [Here](https://www.nofima.no/filearchive/produksjon-og-giftighet-av-ammoniakk.pdf)

TAN = NH3-N + NH4+-N

Total Ammoniacal Nitrogen = Ammonia-Nitrogen + Ammonium-Nitrogen

This means we are looking at the ammount of nitrogen.

These two parts of TAN exists in a pH-related equilibrium.

![NH3 vs NH4](img/seneye_nh3_nh4.png?raw=true "NH3 vs NH4")

In RAS operating range, we may find pH from 7 to about 8.1, normal seawater.

Calculate Free Ammonia using [Hamza Reef Free Ammonia calculator](https://www.hamzasreef.com/Contents/Calculators/FreeAmmonia.php)

You can also see the [nitrogen-ion conversion chart](https://www.hamzasreef.com/Contents/Calculators/NitrogenIonConversion.php)

## JBL NH4 test kit
The JBL NH4 test kit is used for measuring ionized NH4+, or so they say. I think they actually indicate TAN. The values are indicated to be mg/l or ppm, ranging from below 0.05 to 5.

The chemistry used in this is the Salicylate method, which means the colors we will see range from a light green to dark blue, depending on the ammonia concentration.

![JBL TAN color sheet](img/jbl/jbl_tan.png?raw=true "JBL TAN color sheet")

Indicated colors are of the following "NH4", or I believe, TAN.
| Concentrations: 	| <0.05 	| 0.1 	| 0.2 	| 0.4 	| 0.6 	| 1 	| 1.5 	| 3 	| 5 	|
|-----------------	|-------	|-----	|-----	|-----	|-----	|---	|-----	|---	|---	|

The price is roughly 200 NOK, and you get 50 tests out of it if you follow the normal procedure.

The normal procedure is:
1. Add 5 ml water to be measured to a vial
2. Add 4x drops of Solution #1
3. Add 4x drops of Solution #2
4. Add 5x drops of Solution #3
5. Wait 15 minutes, for reaction to take place
6. Compare color of liquid to color indicated on test sheet

Remember that when we measure TAN, we have no idea how much is of the toxic unionized NH3 and how much is of the less toxic ionized NH4+.
To figure out this, we also need to look at the pH and possibly salinity and temperature as well, 

## Ammonia solutions

In order to test our colorimeter, with the JBL NH4 test kit, we need to make a few standard solutions.

We have 9% NH4Cl, Ammonium Chloride, unperfumed from the store.

For 100 liters of water, elevating it from 0 to 1 mg/L TAN, using 9% Ammonium Chloride, and a (calculator)[http://spec-tanks.com/ammonia-calculator-aquariums/].

We need to add 1.1 ml Ammonium Chloride solution.

This is for 1 liter of water, 0.011 ml Ammonium Chloride, too little for me to measure with my 1 ml syringe.

We can take a bucket of 20 liter, add 0.2 ml Ammonium Chloride and get a 1 mg/L solution.
We can take a bucket of 20 liter, add 1.1 ml  ml Ammonium Chloride and get a 5 mg/L solution.

We should also dilute us down to a few different ones.

I have 1 mg/L solution on hand, so I use this and make one more at 0.5 mg/L, by mixing 50/50 of water and solution.

To do later: Make a more complete table, so that we can make better tests.

## TAN kinetics

I put together autosampling, interval of 30 seconds, for 15 minutes. First tests with the real JBL TAN test kit.

Seawater of 1 mg/L TAN, at room temperature (ca 20 degree Celsius):
![TAN kinetics room temp](img/notes_tan_kinetics_roomtemp.png?raw=true "TAN kinetics room temp")

Seawater of 1 mg/L TAN, at fridge temperature (ca 4 degree Celsius):
![TAN kinetics fridge temp](img/notes_tan_kinetics_fridgetemp.png?raw=true "TAN kinetics fridge temp")

Seeing these side by side, we can clearly see that the cold one takes longer to react fully.

We also see that, after the procedure, waiting 15 minutes gives us end values that are not the same. This means, as far as I can tell, that the color is different.

First line of roomtemp:
t=41.7s: sampled ok, transmittance is: red 92.4%, green 91.6%, blue 80.1%, all 95.0%

Last line of roomtemp:
t=1062.0s: sampled ok, transmittance is: red 76%, green 80.6%, blue 65.3%, all 88.8%%

First line of chilled:
t=55.5s: sampled ok, transmittance is: red 97.4%, green 96.5%, blue 88.3%, all 97.5%

Last line of chilled:
t=1040.9s: sampled ok, transmittance is: red 79.7%, green 86.9%, blue 74.4%, all 92.3%