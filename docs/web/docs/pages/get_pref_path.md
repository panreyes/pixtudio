Definition
----------

**STRING** get_pref_path ( &lt;**STRING** company&gt;, &lt;**STRING** appname&gt; )

Use this function to get the preferences dir for the described application.
This is where the game can store preferences and savegames.
If the folder does not exist, it will be created for you.

In android systems, your app must be assigned a single identifier in the form of
`org.pixtudio.sampleapp`. In this case, `org.pixtudio` should be the value for
`company` and `sampleapp` the value for `appname`.

Parameters
----------

| Parameter name     | Explanation                                    |
| ------------------ | ---------------------------------------------- |
| **STRING** company | The name of your company or development group. |
| **STRING** appname | The name of this app.                          |

Returns
-------

**STRING** : The path to the preferences directory. If the base path cannot be found, an empty string will be returned.

Example
-------

    IMPORT "mod_dir";
    IMPORT "mod_say";


    PROCESS main();
    BEGIN2
        say("Pref path: " + get_pref_path("org.pixtudio", "sampleapp"));
    END
