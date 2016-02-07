![[Trinit association
logo](http://trinit.es/)](Trinit_Logo.png "Trinit association logo")

This tutorial, originally made by Windgate for
[Trinit](http://trinit.es), tries to serve as a great starting point for
those new to [Bennu](Bennu "wikilink").

It's still a work in progress, but this article will be updated when new
lessons are translated.

\_\_TOC\_\_

Graphics I
==========

When creating a video game, the first thing you'll need is graphics.

You could start with simple graphics made with Paint or a similar simple
drawing program, but if you're going to take use several hours of work
for your video-game, it's better to start with some nice graphics as can
be your preferred game characters or the scenarios for that old game you
spent hundreds of hours playing long ago.

First of all, create a folder where you'll store your work.

Sprites
-------

A spriteset is a table of graphics with all the animations for a
particular character.

![1-1 Spriteset
Example](Windgate_tuto_image_1-1.png "1-1 Spriteset Example")

You'll have to choose several spritesets. You can find a great
collection of spritesets on the Internet, be it in sites as
<http://spritedatabase.net> or simply by searching in Google Images for
“sprite” and “ripped”.

When choosing your spritesets please take into account:

  ----------------- -----------------------------------------------------------------------------------------------------
  **Views**         Top, side or isometric. It's usually easier to start with side-view spritesets.
  **Animations**    Your character should NOT be able to perform more actions than those defined in its spriteset.
  **Resolutions**   The size in pixels of each animation (Sprite) is a good indication of the quality of the animation.
  ----------------- -----------------------------------------------------------------------------------------------------

Notice that Image I corresponds to an isometric-view spriteset, without
any jump animation and with a medium resolution: not as high as that
found in Street Fighter II nor as low as that found in the first Super
Mario Bros.

Backgrounds
-----------

Background images are the images where your game's action will take
place.

![1-2 Spriteset
Example](Windgate_tuto_image_1-2.png "1-2 Spriteset Example")

You should choose several background images. Again, have a look at
websites such as <http://vgmaps.com>, or look for them in Google Images
using “scroll”, “background” and “ripped” as keywords.

Just like sprites, background images can also use one of the views
listed above so be sure to choose one that uses the same view as your
sprites do. As stated above, it's better to start with a side-view game.

Regarding resolution, try to not use images with a very low resolution
(below 320x240 pixels) as they might not fill the screen completely but
also be sure not to use images that are too big (over 4096x4096 pixels)
as they use too many resources and they could decrease your game's
performance. We can always rescale the graphics, but that's something
we'll try to avoid as of now.

Please note that background imagess and sprites are completely different
things. In ripped background images you might sometimes find enemies or
items kept from the original games, those are useless to us and are
called “dirty”, as you'll probably have to clean them before using them
in your game.

Please note that in Image 2 can be a top-view background image, at a
somewhat low resolution and that can be considered dirty if your idea is
to make a game where the bushes can be cut down.

PUBLIC
======

We've already worked with most of Bennu's main utilities, but there's
still a very important aspect of Bennu we have not dealt with that will
certainly open you the doors to a very broad field of Bennu programming.

You can see that, by using PRIVATE variables, you cannot access data
belonging to a process even if you know its process ID. That limitation
makes it hard to guess things as simple as -for example- determining how
much damage a certain shot makes in a certain enemy.

You could implement such a feature by using LOCAL variables, but this is
discouraged as it modifies all the processes' varspace to hold that
variable, no matter what their type is, thus increasing the amount of
memory used.

To avoid that problem you can use variables with PUBLIC scope that only
modify the varspace of those processes that have that variable declared.
Its usage seems to be very simple and convenient but has a few rules
that must be followed, as shown below.

DECLARE sentence
----------------

Although you can declare the PUBLIC variables in the same way you do
with PRIVATE variables that won't generally allow us to access them, as
Bennu will give that process type a pre-defined varspace and only
contains some basic vars like graph, x, y, etc.

To overcome this limitation, Bennu implements the DECLARE sentence. You
must use it for all the processes that declare PUBLIC variables and
before the process declaration. In the example, we're going to declare
some PUBLIC data for our main character and thus, before declaring its
process we must add the following lines:

    DECLARE PROCESS main_character ( <Parameters for this process> )
        PUBLIC
            int health;
            int strength;
            int agility;
        END
    END

You can include that sentence right before declaring the main\_character
process. For that process, it'll be like if the variables had been
declared in their PRIVATE scope but, as you'll now see, the rest of the
game's processes can now access and modify them.

The data type associated to the process
---------------------------------------

The DECLARE sentence not only associates the new vars to the process but
it also changes the process identifier so we can have access to them.

Up until now, the process identifier was stored in a variable of type
integer (INT) and we could access its basic data (x, y, size, etc) as if
it was of a TYPE variable.

This continues to be like that and you'll be able to use the identifier
for the process like before but we'll now have another new data type
that allows us to access all the PUBLIC variables for that process in
the same way.

The new data type created by DECLARE is named after the process so in
our case main\_character will now also represent a valid data type. So
now any process can hold a PRIVATE var of type “main\_character” and
have access to its basic data and all its PUBLIC variables through it.

But beware: Variables of type “main\_character” and all the type vars
associated to a process with PUBLIC scope vars in them cannot be
modified before having a valid process identifier associated to them.

What does that mean?

That means that prior to PUBLIC variables usage, you must store a valid
process identifier. For example, any enemy that wants to get the
main\_processes “health” variable must first declare a PRIVATE variable
of type “main\_character”, as shown below:

    PRIVATE
        main_character objective;

And second, before accessing any of the fields in objective, it must
refer to the actual main\_character process, and check that the proess
still exists. You could do:

        IF ( objective = collision ( TYPE main_character ) )
            objective.health = objective.health - 1;
        END

Once more, please note that before being able to use objective.health
you must check there is a collision and therefore objective holds a
valid process identifier.

And, of course, apart from collision(), you can also use get\_id(),
father and -in general- any other method that returns a process ID for
main\_character to work with the new data TYPE returned by DECLARE.

<Category:general> <Category:tutorials>
