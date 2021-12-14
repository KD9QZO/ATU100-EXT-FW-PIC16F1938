# TODO #

This file is intended to provide a _running_ **TODO** list for the project.


## High Priority ##

+ Get project to compile
+ Reformat code to a readable state


## Medium Priority ##

+ Refactor code to make variable and function names more readable
+ Figure out configuration bits setting for PIC16F1938 microcontroller


## Low Priority ##

+ Document code
+ Restructure source code into more files, with dedicated functions in each
+ Inline functions where appropriate


## Uncategorized ##

+ Use one of the two available ADC-enabled pins to allow reading the **BAND** analog voltage many transceivers output, allowing for quick recall of band-specific tuning parameters
+ Implement some form of **two-way** communication with a PC, where the PC can initiate a tuning request, as well as receive information about the state of the tuner
    + This could potentially be implemented using one of the **TxReq** lines to signal that the PC has data waiting to be read, then a separate microcontroller _(acting as an **I²C slave** and **USB device**)_ could have its memory read/written over the software I²C bus, on demand
