Definition
----------

**STRING** get_base_path (  )

Use this function to get the directory where the application was 
run from. This is where the application data directory is.

In macOS (and iOS), if the application is in a ".app" bundle, the
function will return the path to the app's resources directory
(Game.app/Contents/Resources/).

Returns
-------

**STRING** : The path to the directory where the application was run from. If the base path cannot be found, an empty string will be returned.

Example
-------

    IMPORT "mod_dir";
    IMPORT "mod_say";


    PROCESS main();
    BEGIN
        say("Base path: " + get_base_path());
    END
