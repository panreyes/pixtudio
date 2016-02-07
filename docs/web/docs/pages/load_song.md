Definition
----------

**INT** load\_song ( &lt;**STRING** filename&gt;, \[ &lt;**POINTER**
id&gt;\] )

Loads a song for later use with [play\_song](play_song "wikilink")().

There are multiple [filetypes](filetypes "wikilink") you can load using
this [function](function "wikilink"). Included are:

-   OGG Vorbis (.ogg). Good quality for [songs](song "wikilink") and
    doesn't take too much space (it's similar to \*.mp3).
-   MIDI (.mid). Takes very low space, but it's limited to samples of
    the soundcard.
-   Modules (.xm, .it, .s3m, .mod). Like MIDI, but Modules also contain
    the samples themselves.

Parameters
----------

  --------------------- -------------------------------------------------------------
  **STRING** filename   - The music file to be loaded, including a possible path.
  **POINTER** id        - Optional parameter, for loading a song in the background.
  --------------------- -------------------------------------------------------------

Returns
-------

**INT** : [SongID](SongID "wikilink")

  -------- -------------------------------------------------
  -2       - Waiting for the file to be loaded, see notes.
  -1       - There was an error loading the file.
  &gt;=0   - The songID of the newly created sound.
  -------- -------------------------------------------------

*the following applies for versions prior rc282:*

**INT** : [SongID](SongID "wikilink")

  -------- --------------------------------------------------------
  -1       - Could not load music file (errormessage in console).
  &gt;=0   - The SongID.
  -------- --------------------------------------------------------

Notes
-----

The optional parameter **id** was introduced in version rc282 and allows
you to load resources in the background. It used with the
[Offset](Offset "wikilink") operator. See example below:

          load_song("archivo_gordo.ogg", &idsong);
          while(idsong==-2)
                say("Big File Loading ....");
                frame;
          end
          if(idsong==-1)
              say("Something went wrong!!");
              exit(); // o return
          end

          say("Big file loaded ok!!");

Example
-------

    Program example;
    Private
        int song;
    Begin
        song = load_song("my_song.ogg");
        play_song(song,0);
        Repeat
            frame;
        Until(key(_ESC))
    OnExit
        unload_song(song);
    End

Used in example: [play\_song](play_song "wikilink")(),
[key](key "wikilink")(), [unload\_song](unload_song "wikilink")()

<Category:functions> <Category:sound> <Category:mod_sound>
