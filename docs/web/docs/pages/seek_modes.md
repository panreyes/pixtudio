Definition
----------

Seek modes are used to specify the mode of seeking in a file, by passing
one of them to the [function](function "wikilink")
[fseek](fseek "wikilink")() as the [parameter](parameter "wikilink")
*relativeness*. The mode of seeking means to what position the seeking
will be related to.

List
----

  ------------ ----------- --------------------------------------------------------------------
  *Constant*   - *Value*   - *Relative to*
  SEEK\_SET    - 0         - The beginning of the file. This means just setting the position.
  SEEK\_CUR    - 1         - The current position.
  SEEK\_END    - 2         - The end of the file.
  ------------ ----------- --------------------------------------------------------------------

<Category:constantcategories>
