testgame - First pass at making a video game in C++
========

Tools
-----

Name | Purpose
------|-------
Visual Studio 2012 | C++ IDE and debugger
GLFW | OpenGL library for window and input management
GIMP | Basic image editing
Gyazo | GIF screencapture
Trello | Tasklist and progress tracking
Git Bash | Git CLI
Git Extensions | Git GUI

 
Goals and Progress
----
 
At the moment I'm aiming to make a 2D platformer in C++, using GLFW for window and input management. Info on game idea here: https://docs.google.com/a/illinois.edu/document/d/1B46gzJL1oqGGw4U6O5DGu4mbCINVZZbUMn6RG-K7iq4/edit

*The following are complete as of 1/1/15:*

-update/render loop

-graphics draw(textures, animations, masking) 

-Entity objects for all items placed onscreen

-input handling (move left, right)

-basic collision checks

-Sprite objects to handle all graphics for Entity objects

-animation, switching animation states, looping

-jumping

-crouching


Todo
----

-left/right animation swaps

-attack animation

-hitbox/hurtbox to replace current collision logic

-enemy AI

-health/HUD

-shield object

-level editor