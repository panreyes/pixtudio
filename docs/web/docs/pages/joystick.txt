Description
-----------

A joystick is a general term for not just actual joysticks. Joysticks
can be, but are not limited to:

-   (actual) joysticks
-   steering wheels
-   gamepads
-   controllers on consols
-   GP2X main controls

A joystick provides different controls for different purposes.

Input
-----

### Axis

An axis is an analogue input, used for input that should be precise or
sensitive. Examples are the flight stick control of the joystick (an
actual joystick), the steer of a steering wheel and the analogue control
on a gamepad.

In Bennu, values of axes range between `-32768` and `32767`.

See [joy\_numaxes](joy_numaxes "wikilink")(),
[joy\_getaxis](joy_getaxis "wikilink")()

### Button

A button is a binary input, meaning it is either pressed or not.

In Bennu, pressed is `1` and not pressed is `0`.

See [joy\_numbuttons](joy_numbuttons "wikilink")(),
[joy\_getbutton](joy_getbutton "wikilink")()

### Hat

A hat is an 8-way digital pad. They are also called POV-hats because
they are mostly used to alter the Point Of View. Examples are POV-hats
on joysticks and steering wheels, but also D-pads on a gamepad can be a
hat.

In Bennu, [hat constants](hat_constants "wikilink") are used to describe
the position of a hat.

See [joy\_numhats](joy_numhats "wikilink")(),
[joy\_gethat](joy_gethat "wikilink")()

### Ball

A ball is like a mouse: only relative values are measured.

In Bennu, the relative values of balls range between `-32768` and
`32767`.

See [joy\_numballs](joy_numballs "wikilink")(),
[joy\_getball](joy_getball "wikilink")()

<Category:General> <Category:Joystick> <Category:mod_joy>
