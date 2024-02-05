# Project File Structure

Visual Studio expects files to be laid out in the following way. Divert from this at your own inconvenience.

```
.
`-- RocketBall
    |-- lib
    |   |-- GLFW
 	|	|	`-- [Library files]
 	|	|
    |   |-- glm
 	|	|	`-- [Library files]
 	|	|
    |   |-- imgui
 	|	|	`-- [Library files]
 	|	|
    |   `-- [Additional libraries]
 	|
    |-- src
    |   |-- game
    |   |	`-- [Custom engine code files]
 	|	|
    |   `-- [LineRenderer codefiles]
	|
	|-- VSProject
	|	`-- [Visual Studio project files]
	|
	|-- Working
	|	`-- [Not sure what this is?]
	|
	`-- SimpleFramework.sln
```