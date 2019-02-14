**Considerations before start**

* Do you want to make a 48k game?
* Do you have read about IM2 interruptions?
* Do you know how ZX Spectrum paging works?

**Drawing on the screen with SP1**

Graphics are usually composed of pixel information (all pixels are stored as on or off) and color information that goes 
in 8x8 blocks. You'll see that Attribute clash is present everywhere everytime two sprites with different INK appear 
on the same 8x8 box, and that's why lot of games made heroes to be black and white with transparent background 
(aka mask).

There are two types of entities:
1. User-Defined Graphics (UDGs) (cheap on memory usage). Basically, kind of replacing an 8x8 ascii character by your own 'draw'.
2. Sprites (more memory usage). A computer graphic which may be moved on-screen and otherwise manipulated as a single entity.

Usually, UDGs are more intended for background items (even if they move, but SP1 won't help to move them), but it will help 
to repaint them if a sprite is on top of an UDG.

Sprites are more intended for moving items, like the game hero, enemies, ...
