<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:mod_sound>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** sound\_freq = 22050

**Sound\_freq** is a [global variable](global_variable "wikilink"),
holding the set sound frequency, which is set when sound is used for the
first time, meaning altering the value of this variable will have no
effect after sound has been initialized. The higher the frequency, the
higher the quality is. Accepted frequencies are:

-   44100: high quality (recommended)
-   22050: medium quality (default)
-   11025: low quality (not recommended)

See also
--------

-   [sound\_mode](sound_mode "wikilink")
-   [sound\_channels](sound_channels "wikilink")

