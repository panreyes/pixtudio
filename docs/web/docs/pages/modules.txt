Modules add extra functionality to [PixTudio](PixTudio "wikilink"), as PixTudio
on its own is just a language and a virtual machine. The default modules
contain the basics you need to make a game: video, audio, input, etc.
More advanced external libraries are available, like network and 3D
rendering.

Enabling a module is easy, using [import](import "wikilink"):

```
import "<modulename>"
```

Some external libraries use a header (.[INC](INC "wikilink")) instead,
so use [include](include "wikilink"):

```
include "<includename>"
```