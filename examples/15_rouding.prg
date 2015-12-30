import "mod_math"
import "mod_say"

Process main()
Begin
    say("round(0.6): " + round(0.6));
    say("floor(0.6): " + floor(0.6));
    say("ceil(0.6): " + ceil(0.6));

    say("round(0.5): " + round(0.5));
    say("floor(0.5): " + floor(0.5));
    say("ceil(0.5): " + ceil(0.5));

    // Please note behaviour change with negative values
    say("round(-0.5): " + round(-0.5));
    say("floor(-0.5): " + floor(-0.5));
    say("ceil(-0.5): " + ceil(-0.5));
End
