# Test-LSE

simple test program for LSE oscillator drive load setting.

How to use:
- connect a frequency meter to PA_8 (MCO, master clock output)
- connect serial terminal to stdio

expected output:
 32.768 kHz signal at modal-content  

keys:  
 0: turn off LSE  
 9: turn on LSE  
 1: set drive load level low  
 2: set drive load level medium-low   / high on F4xx
 3: set drive load level medium-high  / n.a. on F4xx
 4: set drive load level high         / n.a. on F4xx
 l: toggle LED and call sleep_for(100ms)

This test was written for a STM32H743, but will work also with other MCU.
MCOx maybe changed and other STM32 series have only 2 different drive load levels.

toggle LED with sleep_for() can be used to test:
- LSE will be turned on on the first call when it was turn off
- when LSE is turned off afterwards, the 'l' command will crash Mbed because RTC has no clock
  (intended behaviour)