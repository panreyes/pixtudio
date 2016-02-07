Description
-----------

Datatypes give meaning to data and dictate how a variable acts and
reacts. Examples of datatypes are `[[int]]`s, `[[float]]`s and
`[[string]]`s. Special cases are voids, arrays, varspaces and structs.
User made types can also be defined, by use of the operator
[Type](Type "wikilink").

List
----

<DPL> category = datatypes mode = userformat columns = 1 listseparators
= ,\\n\* [%TITLE%](%PAGE% "wikilink"),, redirects = include ordermethod
= titlewithoutnamespace resultsfooter = \\n%PAGES% datatypes </DPL>

Example
-------

    import "mod_draw"
    import "mod_wm"
    import "mod_key"
    import "mod_map"

    Type _point
        int x;
        int y;
    End

    Process Main()
    Private
        _point A,B;
    Begin

        // Init the points
        A.x = 100;
        A.y = 50;
        B.x = 250;
        B.y = 150;

        // Setup drawing
        drawing_map(0,0);
        drawing_color(rgb(0,255,255));

        // Draw a box
        drw_box(A,B);

        // Wait for key ESC or X button
        Repeat
            frame;
        Until(key(_ESC)||exit_status)

    End

    // Draw a box using two points
    Function int drw_box(_point A, _point B)
    Begin
        return draw_box(A.x,A.y,B.x,B.y);
    End

Used in example: [drawing\_map](drawing_map "wikilink")(),
[drawing\_color](drawing_color "wikilink")(), [rgb](rgb "wikilink")(),
[key](key "wikilink")(), [draw\_box](draw_box "wikilink")(),
[exit\_status](exit_status "wikilink")

<Category:general>
