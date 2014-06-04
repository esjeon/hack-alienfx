
AlienFX device-specific protocol
================================

Device Configuration
--------------------

 - use configuration 1
 - occasionally, kernel drivers need to be disabled

URB Setup
---------

### Sending

 - bmRequestType = 0x21

        0... .... : Host to Device
        .01. .... : Request Type = Class
        ...0 0001 : Recipient = Interface

 - bRequest = 9 (Constant)
 - wValue = 0x0202 (Constant)
 - wIndex = 0 (Constant)
 - wLength = 9 (Constant. Smaller message must be padded with 0)


### Receiving

 - bmRequestType = 0xa1  

        1... .... : Device to Host
        .01. .... : Request Type = Class
        ...0 0001 : Recipient = Interface

 - bRequest = 9 (Constant)
 - wValue = 0x0202 (Constant)
 - wIndex = 0 (Constant)
 - wLength = 9 (Constant)


Areas
-----

 * Alienware 14
   - 00:01 : Keyboard - Left
   - 00:02 : Keyboard - Mid-Left
   - 00:04 : Keyboard - Mid-Right
   - 00:08 : Keyboard - Right
   - 00:60 : Bottom
   - 00:80 : Alien Logo
   - 01:00 : ALIENWARE Text
   - 02:00 : Touchpad
   - 48:00 : Status LED


Commands
--------

### 0x01: Morph ###


### 0x02: Pulse ###


### 0x03: Color ###

    02:03:uu:00:aa:aa:rg:b0:
    
    u : Unkown (sequence #?)
    a : Area
    r : Red
    g : Green
    b : Blue


### 0x04: Loop

    02:04:  :  :  :  :  :  :


### 0x05: Apply

    02:05:  :  :  :  :  :  :


### 0x06: Update Status code

    02:06:  :  :  :  :  :  :

 - The status code has to be retrieved manually.


### 0x07: Reset?

    02:07:tt:  :  :  :  :  :
    
    t : type

 - 00: reset keyboard
 - 01: reset keyboard
 - 02: ???
 - 03: reset all
 - 04: ???


### 0x08: Section?

    02:08:ss:  :  :  :  :  :
    
    s : section


### 0x09: Save

    02:09:  :  :  :  :  :  :

