Description
-----------

The system file is like a regular [file](file#Filetype "wikilink"), but
it contains on the fly created [graphics](graphic "wikilink"). These
graphics are for example created by [map\_new](map_new "wikilink")(),
[map\_clone](map_clone "wikilink")() or
[write\_in\_map](write_in_map "wikilink")().

The system file can be accessed using *0* as the
[fileID](fileID "wikilink"). While this file can also be a file loaded
from disc, the graphics in that file all have a
[graphID](graphID "wikilink") below *1000*. Graphics created on the fly
have graphID's *1000* or above.
