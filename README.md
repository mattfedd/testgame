testgame - First pass at making a video game in C++
========

Goals and Progress
----
 
Overall I'm aiming to make a 2D platformer in C++ pretty much from scratch, not including the platform layer. The platform layer (Windows/Mac/Linux specific aspects) is handled with GLFW and OpenAL for window/input management and audio respectively. Random ideas on possible mechanics and features are here: https://docs.google.com/a/illinois.edu/document/d/1B46gzJL1oqGGw4U6O5DGu4mbCINVZZbUMn6RG-K7iq4/edit

The following are current features as of 2/22/15:
- Entity-Component-System
    - http://gameprogrammingpatterns.com/component.html
    - http://www.richardlord.net/blog/what-is-an-entity-framework
    - http://bp.io/post/1617
- Tile-based world
- Point-based collision for entity-tile interaction; no slopes or one-way platforms yet
    - http://games.greggman.com/game/programming_m_c__kids
- Background music and sound effects
    - http://distro.ibiblio.org/rootlinux/rootlinux-ports/more/freealut/freealut-1.1.0/doc/alut.html
- Text

Inspiration
----
- Iji (http://www.remar.se/daniel/iji.php)
- Moonman (http://forums.tigsource.com/index.php?topic=21997.0)
- An Untitled Story (http://www.mattmakesgames.com/)
- Shovel Knight (http://yachtclubgames.com/shovel-knight/)
- La Mulana (http://la-mulana.com/en/)
- Cave Story (http://en.wikipedia.org/wiki/Cave_Story)

Tools
-----

Name | Purpose
------|-------
Visual Studio 2012 | C++ IDE and debugger
Sublime Text 3 | General text editor
GLFW | OpenGL-based library for window and input management
ALUT | Convenient library on top of OpenAL for loading/playing audio
GIMP | Basic image editing
Tiled | Tilemap editing
LICEcap | GIF screencapture
Trello | Tasklist and progress tracking
Git Bash | Git CLI
Git Extensions | Git GUI
