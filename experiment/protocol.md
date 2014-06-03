AlienFX device-specific protocol
================================

AlienFX protocol is carried by URB.

Device Configuration
--------------------
 - use configuration 1
 - occasionally, kernel drivers need to be disabled

Sending
-------
 - bmRequestType = 0x21
      0... .... : Host to Device
      .01. .... : Request Type = Class
      ...0 0001 : Recipient = Interface
 - bRequest = 9 (Constant)
 - wValue = 0x0202 (Constant)
 - wIndex = 0 (Constant)
 - wLength = 9 (Constant. Smaller message must be padded with 0)

Receiving
---------
 - bmRequestType = 0xa1
      1... .... : Device to Host
      .01. .... : Request Type = Class
      ...0 0001 : Recipient = Interface
 - bRequest = 9 (Constant)
 - wValue = 0x0202 (Constant)
 - wIndex = 0 (Constant)
 - wLength = 9 (Constant)

Protocol
--------
 * Every message is prepended with 0x02
 * Known Commands:
    - 01: Morph
    - 02: Pulse
    - 03: Color
    - 04: Loop
    - 05: one of Apply/Commit/Execute
    - 06: Update Status
    - 07: Reset?
      + 00: reset keyboard
      + 01: reset keyboard
      + 02: ???
      + 03: reset all
      + 04: ???
    - 08: Section?
    - 09: Save
    
