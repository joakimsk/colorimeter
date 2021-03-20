# Colorimeter Notes


## PWM vs LDR resistance

Measurement of LDR resistance against PWM output value, Arduino ADC range is {0-255}. Shining through the colorimeter.
Colorimeter is kept in the dark (with a Norwegian lue), so light pollution should be minimal.

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

