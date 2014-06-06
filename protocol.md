
AlienFX device-specific protocol
================================

Terminology
-----------

 - **Device**:
    An AlienFX USB device.

 - **Area**:
    A (or a set of) LED which share a sequence.

 - **Color**:

 - **Sequence**:
    An ordered list of colors, morphs, and pulses of an area.

 - **Theme**:
    A set of sequences and corresponding areas.


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


Commands
--------

### 0x01: Morph ###


### 0x02: Pulse ###


### 0x03: Color ###

    02:03:nn:00:aa:aa:rg:b0:
    
    n : Sequence ID
    a : Area
    r : Red
    g : Green
    b : Blue


### 0x04: Loop

    02:04:  :  :  :  :  :  :

 - Without this, the LED will go off after walking through the user-specified
   color sequence.


### 0x05: Execute

    02:05:  :  :  :  :  :  :

 - This must be called at the end.


### 0x06: Update Status code

    02:06:  :  :  :  :  :  :

 - The status code has to be retrieved manually.


### 0x07: Reset?

    02:07:tt:  :  :  :  :  :
    
    t : type

 - It takes some time to reset completely. Premature commands might fail.


### 0x08: Save-To

    02:08:ss:  :  :  :  :  :
    
    s : slot


### 0x09: Save Slot?

    02:09:  :  :  :  :  :  :


### 0x0E: Tempo

    02:0e:tt:tt:  :  :  :  :

    t: Tempo

 - AlienFX Minimum = 00:1e
 - AlienFX Maximum = 03:ae


Contants
--------

### Area

 - 00:01 : Keyboard - Left
 - 00:02 : Keyboard - Mid-Left
 - 00:04 : Keyboard - Mid-Right
 - 00:08 : Keyboard - Right
 - 00:20 : Bottom - Left
 - 00:40 : Bottom - Right
 - 00:80 : Alien Logo
 - 01:00 : ALIENWARE Text
 - 02:00 : Touchpad
 - 48:00 : Status LED (cannot be seprated)


### Reset

 - 00: reset keyboard
 - 01: reset keyboard
 - 02: ???
 - 03: reset all
       this also suspends the execution of sequences
 - 04: ???


### Save Slot

 - 01: Initial
 - 02: Stan-By
 - 05:
 - 06:
 - 07:
 - 08:
 - 09:


