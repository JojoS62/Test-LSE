# Test-LSE

simple test program for LSE oscillator drive load setting.

How to use:
- connect a frequency meter to PA_8
- connect serial terminal to stdio

keys:  
 0: turn off LSE  
 9: turn on LSE  
 1: set drive load level low  
 2: set drive load level medium-low  
 3: set drive load level medium-high  
 4: set drive load level high  

This test was written for a STM32H743, but will work also with other MCU.
MCOx maybe changed and other STM32 series have only 2 different drive load levels.
