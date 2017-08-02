=================
Tile Index Readme
=================

The Tile Index is a record of all tiles that will be shown in the world. It will contain information about each tile, like so:

[c] [name] [passable] [worldheight] [path] [type] [[misc...]]

============
Term Summary
============
[c]
	character key. Any ascii character between 32 and 127, exclusive (i.e. neither the SPACE char nor the DEL char),

[name]
	the name of the map (without spaces; use '_' instead),

[passable]
	binary truth indicating passability (i.e. a '1' will allow a character to pass through the tile, '0' will not),

[worldheight]
	binary truth indicating heigth of the tile in reference to the player (i.e. a '1' indicates the tile is "above" the player, causing the tile to be drawn over the player's image (e.g. a pillar or doorway arch that the player can go under); a '0' indicates the tile is "below" the player, performing the exact opposite effect (e.g. the floor or ground for the player to walk on)). Walls/doors are considered level 0.

[path]
	the path to the tile's image (i.e. for animatable objects like doors/water/lava/etc.) NOTE: the tile's image must be stored within pathToGame/maps/tiles

[type]
	the enumeration of the tile's type; (from Tiles.h) valid types include
		Floor,		// 0
		Door,		// 1
		Overhang,	// 2
		Wall		// 3

[misc...]
	TBD

### NOTES ### 
	The minimum required for a tile are "c", "name", "passable", "worldheight", "path", and "type".
	In a Tile Index file, character keys MUST be laid out in order, i.e. '!' (Ascii 32) must come before '"' (Ascii 33), and so on, since tile index searching is dependent on numeric indexing