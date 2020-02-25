# Door-Locker-System
* It's AVR project which consists of two parts:                                                                                           ## HMI_ECU

  - Its role is to let the user enter desired pass by __akeypad & LCD__ to send it throgh __UART Protocol__ to __Control_ECU__.
  - Let him decide to open the door which is connected with the __Control_ECU__ or reset the pass.

## Control_ECU

  - Its role is to save the received pass in an __external EEPROM__ by __I2C Protocol__ & gets the user decision of
    openning the door to start excute it.
