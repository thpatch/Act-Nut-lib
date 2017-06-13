Act/Nut lib
-----------

This project is a library to extract and edit act and nut files.
It was created for the files in the game Touhou 14.5 ~ Urban Legend in Limbo, and was only tested with files from this game.

Nut files are Squirrel 3.x closure files. It was created by reading the source code of [the Squirrel sq_readclosure function](https://github.com/albertodemichelis/squirrel/blob/8471ad1aeab4373d743f8139fc5baf63b429bb85/squirrel/sqapi.cpp#L1258), and by rewriting it in my own way. I tried to keep the same class names. My understanding of the format is [here](https://docs.google.com/document/d/1v53RGrYH7P8Fj4DqFyNW3fy_rbSwTWGwsitfO-7Mkws/edit?usp=sharing).

I don't know what Act files are, but they are everywhere in the game, and they contain nut files. All the knowledge from these files comes from reverse-engineering and guessing. There may be some places where I didn't understand correctly the format, and most class names are guessed.