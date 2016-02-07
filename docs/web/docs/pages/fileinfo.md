<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:mod_dir>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**Struct** Fileinfo

Fileinfo is a [global variable](global "wikilink")
[struct](struct "wikilink"), containing information about a
file/directory entry, lastly returned by [glob](glob "wikilink")().

Members
-------

  --------------------- -------------------------------------------------------------------------------------------------------
  *Member name*         - *Description*
  **STRING** path       - The path to the file/directory (without the name of the file/directory).
  **STRING** name       - The name of the file/directory.
  **INT** directory     - [true](true "wikilink")/[false](false "wikilink"): whether the file/directory is a directory or not
  **INT** hidden        - [true](true "wikilink")/[false](false "wikilink"): whether the file is hidden or not
  **INT** readonly      - [true](true "wikilink")/[false](false "wikilink"): whether the file is read only or not
  **INT** size          - The size in bytes of the file/directory.
  **STRING** created    - The date when the file/directory was created. \*. Not available in Unix/Linux\*\*
  **STRING** modified   - The date when the file/directory was last modified. \*
  **STRING** accessed   - The date when the file/directory was last accessed. \*
  **STRING** statechg   - The date when the file/directory's inode was last modified. \*. Only in Unix/Linux\*\*
  --------------------- -------------------------------------------------------------------------------------------------------

**\*** - The strings *created* and *modified* are in the format:
`DD/MM/YYYY hh:mm`.

**\*\*** - In Unix/Linux the creation time is not stored. Instead it has
a change time (ctime) that indicate when changes to the file or
directory's inode (owner, permissions, etc.) were made.
