# Break out game

## Overview:
 * This is a 2D ping pong classical-style game that i cloned from [learnopengl.com](https://learnopengl.com/)
 * This game was built in the progress of making my own game engine for the purpose of testing its functionalities. For now, i call it Waternion Game Engine.
 * Although this game is quite simple, but making a game from scratch like this you will gain a solid knowledge in Computer Graphics, Mathematics, Collision Dectection , Collision Resolution, also Game Engine Architecture and etc.
 
## Gameplay: 
   * Player will control the paddle to bounce the ball in order to clear all the bricks in a level.
   * Gray bricks are solid bricks and can't be destroyed by the ball.
   * Other bricks are non-solid bricks and can be destroyed by the ball.

## Basic Controls:
 * Press `A`, `D` to move the paddle horizontally.
 * Press `Space` to push the ball if the ball sticks with the paddle.
 
## Levels:
 * There are four levels in the game. Feel free to clone the repository and add more levels.
 * Press `1` or `2` key to select the level you want to play.
   * Level 1:

![image](https://user-images.githubusercontent.com/57148627/234757074-1958d7fe-26ff-4a35-a333-b405cc1d6326.png))

   * Level 2:

![image](https://user-images.githubusercontent.com/57148627/234757116-71f6c4e5-1ff4-44a0-851c-bda99a2629ac.png))
   
   * Level 3:

![image](https://user-images.githubusercontent.com/57148627/234757137-97e0b784-44c7-4d63-9539-cd2178ff89e1.png))
  
   * Level 4:
   
![image](https://user-images.githubusercontent.com/57148627/234757170-0db3fc5b-05de-4ab1-b5f8-9acb08976d39.png))


## Powerups:
 * There are six types of effects in the game. Four positive effects and two negative effections.
   * Positive effects include:
     * Size: increasing size for the paddle.
     * Speed: increasing speed for the ball.
     * Passthrough: allowing the ball to destroy and passthrough non-solid bricks.
     * Sticky: allowing the ball to stick with the user paddle in order for user to control the ball direction.
   * Negative effects include:
     * Chaos: the scene will be spinning around plus an post-processing effect.
     * Confuse: the scene will be flipped in both dimension X and Y plus an post-processing effect.
     
     
  * In game capture:
   
![image](https://user-images.githubusercontent.com/57148627/234757385-f42f414a-963d-46b6-a5ec-7f383fb001c7.png)

  * Chaos effect:

![image](https://user-images.githubusercontent.com/57148627/234757454-03f19e34-d9c7-49bb-b06f-4f0e2cc117a0.png)


  * Confuse effect:

![image](https://user-images.githubusercontent.com/57148627/234757624-d0355267-69de-411d-8890-1af4a6bba95c.png)

# Technical aspects:
 * Okay, that is enough for the demo. It's time to list some core features of the engine.

## Features:
 * Entity Component System
 * Collision Detection
 * Particle System
 * Post Processing
 * Native Scripting in C++
 * Audio System
 * Text Rendering
 
## Graphics API:
 * `OpenGL 3.3`
 
## Libraries:
 * `glfw` for creating the window context.
 * `glad` for loading OpenGL API.
 * `FreeType` for text rendering.
 * `irrklang` for audio (music and sounds).
