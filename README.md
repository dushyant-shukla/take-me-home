# take-me-home
'Take Me Home' is a 2D platformer built on top of a custom game engine I developed as a requirement for class CS529 while studying at DigiPen Institute of Technology.

Exciting features of the game engine:
1. **Hardware accelerated graphics:** A 2D renderer written in OpenGL.
2. **Entity Component system:** Component based game-object composition.
3. **Serialization:** Json based data-externalization for game archetypes.
4. **Collision System:** AABB-AABB collision with impulse based collision resolution.

![](./Assets/play-test.gif)

It is a work in progress. Features on the way:
1. Health system: The only way for player to die currently is by falling in the water. With health-system in place, player's heath will get affected on every collision with enemy objects.
2. Level management.
