import "libvideo";
import "mod_say";

Process main()
Begin
    say("Should display all 1's");
    say("======================");
    say(DOUBLE_BUFFER==1024);
    say(HW_SURFACE==2048);
    say(M1024X768==10240768);
    say(M1280X1024==12801024);
    say(M320X200==3200200);
    say(M320X240==3200240);
    say(M320X400==3200400);
    say(M360X240==3600240);
    say(M376X282==3760282);
    say(M400X300==4000300);
    say(M512X384==5120384);
    say(M640X400==6400400);
    say(M640X480==6400480);
    say(M800X600==8000600);
    say(MODE_16BITS==16);
    say(MODE_16BPP==16);
    say(MODE_2XSCALE==256);
    say(MODE_8BITS==8);
    say(MODE_8BPP==8);
    say(MODE_DOUBLEBUFFER==1024);
    say(MODE_FRAMELESS==8192);
    say(MODE_FULLSCREEN==512);
    say(MODE_HARDWARE==2048);
    say(MODE_MODAL==4096);
    say(MODE_WAITVSYNC==16384);
    say(MODE_WINDOW==0);
End;
