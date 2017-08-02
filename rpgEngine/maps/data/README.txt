===============
Map Data Readme
===============

### Format Synopsis ###
	Data files will be formatted like so:
	name:[Name of Map]\n
	size:[Size of Map]\n
	spawn:[Spawn Point Data 0]\n
	spawn:[Spawn Point Data 1]....\n
	music:[Music Data]\n
	row:[Coord Data 0]\n
	row:[Coord Data 1]....\n
	[doorway:[Doorway Data]\n]
	end:end

### Header Index ###
	Name Data: the map's name
		<Format>
			name:[alphanumeric name with or without spaces]\n
		</Format>

	Size Data: the map's size in pixels
		<Format>
			size:[xPixels]x[yPixels]\n
		</Format>

	Spawn Point Data (each map has at least one spawn tile where the player spawns):
		<Format>
			spawn:[Alphanumeric Spawn Point Name with underscores as space chars] [xTileCoord] [yTileCoord]\n
		</Format>

	Music Data:	the map's background music, if any
		<Format>
			music:[music file name]\n
		</Format>
		<Note>
			music must be stored within path_to_game/audio as an .ogg file
		</Note>

	(OPTIONAL) Doorway Data: Information about a doorway
		<Format>
			doorway:[Door name] [Tile key] [Door x] [Door y] [Dest Map] [DestSpawn]
		</Format>
		<Note>
			"Door name" is the alphanumeric name of the door, where spaces are replaced by underscores (_) instead
			"Tile key" is the character key representing the door's tile (stored in TileIndex.txt)
			"Door x" is the x coordinate of the door (in tiles) within the map
			"Door y" is the y coordinate of the door (in tiles) within the map
			"Dest Map" is the name of the map file WITHOUT its extension (i.e. if the map's image name is "SomeMap.png", the Dest Map must be "SomeMap")
			"Dest Spawn" is the name of the desired spawn point
		</Note>

	(DEPRECATED) Coord Data:	data about each coordinate in the map
			<Format>
				coord:[xTileCoord] [yTileCoord] p[passability is 0 or 1]\n
			</Format>
			<Note>
				**DEPRECATED (support has been dropped; use Row Data instead)**
			</Note>

	Row Data: set groups of coordinates in the order they come
	row:[row number] [a string of character keys]\n, where the character key string is treated as an ascii char whose code corresponds to a blockId in the block database (an entity containing all the block's assigned properties). NOTE the space between the row number and character key string