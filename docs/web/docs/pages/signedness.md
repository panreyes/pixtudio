This applies to variables holding integer values ([int](int "wikilink"),
[word](word "wikilink"), [byte](byte "wikilink"), etc).

**Signedness** is a property of variables representing integer numbers.
A *signed* variable can represent both negative values and positive
values (and zero of course). An *unsigned* variable can only represent
zero and positive values.

While signed numbers can represent negative numbers, they lose a range
of larger numbers which can only be represented with unsigned numbers of
the same size (in bits). This is because in signed variables, roughly
half the possible values are negative values. Unsigned variables can
dedicate all the possible values to the positive number range.

E.g. the `[[int]]` in [Bennu](Bennu "wikilink") is a signed
[datatype](datatype "wikilink"), which can range from -2147483648 to
2147483647. Its unsigned counterpart is the unsigned datatype
`[[dword]]` (or `unsigned int`). This datatype ranges from 0 to
4294967295.
