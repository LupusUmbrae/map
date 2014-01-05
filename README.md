D&amp;D Map Editor
===

This is a somewhat ambitious project, the idea is to make not only a decent user friendly D&amp;D map editor it will also be able to display both a screen to the players and a DM only screen

It's also a good chance for me to learn SDL

Dependencies
* [SDL2](http://www.libsdl.org/)
* [SDL2 Image](http://www.libsdl.org/projects/SDL_image/)
* [SDL2 TTF](http://www.libsdl.org/projects/SDL_ttf/)
* [JsonCPP](http://jsoncpp.sourceforge.net/) 0.6.0.rc2
 
Developed on windows using MinGW, it should cross compile but i've not yet tried.

Also require a fix to minGw's io.h the references of "off64 _ t" to "_ off64_t" (without spaces, sorry formatting issues for _) see: http://sourceforge.net/p/mingw/bugs/2024/
