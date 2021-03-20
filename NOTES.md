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

Setting R1 = 258 kohm
We have R2 being the LDR, varying from 18 kohm to up to 2000 kohm (guestimates finger in the air values from the table).

This gives us two extremes, for high light and low light conditions, remembering that the LDR lowers resistance under higher light:
Vout = ( 18000 / (258000 + 18000)) * 5 = 0.32608695652 volts
Digital output = 0.32608695652 / 0.00488758553 = 66 (when Vin is 5v)

Vout = ( 2000000 / (258000 + 2000000)) * 5 = 4.4286979628 volts
Digital output = 4.4286979628 / 0.00488758553 = 906 (when Vin is 5v)

