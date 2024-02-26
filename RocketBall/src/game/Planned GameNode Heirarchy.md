.
`-- GameNode (Base node, handles parents & children)
	|-- TransformNode (2D Transform)
	|	`-- CollisionBody
	|		|-- PhysicsBody (May contain collision shapes, moves according to forces unless kinematic)
	|		|
	|		`-- CollisionShape (Virtual base class for all colliders)
	|			|-- CollisionCircle (Circle primitive)
	|			|-- CollisionBox (Box primitive)
	|			|-- CollisionPlane (Plane primitive)
	|			`-- CollisionMesh (Contains a LineMesh, which defines its physical shape)
	|
	`-- SpriteMesh (Contains a LineMesh, which it draws to the screen)