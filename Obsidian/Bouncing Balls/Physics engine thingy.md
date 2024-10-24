Calculate the difference between the ball's position and the zone position
```cpp
dx = x - std::get<0>(zone);
dy = y - std::get<1>(zone);
```
Calculate the distance from the ball to the center of the zone
```cpp
float distance = std::sqrt(dx*dx+dy*dy);
```
Check if distance combined with radius is greater than its own boundary:
```cpp
if(distance + radius > zoneRadius) {
	float normal_x = dx/distance;
	float normal_y = dy/distance;

	float dot_product =  vx * normal_x + vy * normal_y;
	vx -= 2.f * dot_product * normal_x;
	vy -= 2.f * dot_product * normal_y;

	float overlap = distance + radius - zoneRadius;
	x -= overlap * normal_x;
	y -= overlap * normal_y;
}
```
Reflect the velocity based on the normal
```cpp
float dot_product = vx * normal_x + vy * normal_y;
vx -= 2.f * dot_product * normal_x;
vy -= 2.f * dot_product * normal_y;
```
Correct the position to avoid overlap
```cpp
float overlap = distance - (radius - zoneRadius);
x -= overlap * normal_x;
y -= overlap * normal_y;
```

# Physics for Balls colliding with each other

##### Distance Formula: For two balls with centers (x1, y1) and (x2,y2), the distance between them is: $$distance = \sqrt{(x2-x1)^2+(y2-y1)^2}$$
##### Collision Detection: Two balls are colliding if: $$distance \le radius1 + radius2$$
##### Check collision:
```cpp
bool checkCollision(const Ball& other) {
	// Calculate distance between the two balls
	float dx = other.x - x;
	float dy = other.y - y;
	float distance = std::sqrt(dx * dx + dy * dy);
	
	// Check if the distance is less than or equal to the sum of the radii
	return distance <= (radius + other.radius);
}
```
Calculate all other collisions:
```cpp
void resolveCollision(Ball& other) {
	// Vector from this ball to the other ball
	float dx = other.x - x;
	float dy = other.y - y;
	float distance = std::sqrt(dx * dx + dy * dy);

	if (distance==0) return; // Avoid division by zero

	// Normalize the vector
	float normal_x = dx/distance;
	float normal_y = dy/distance;

	// Calculate relative velocity
	float rel_vx = other.vx - vx;
	float rel_vy = other.vy - vy;

	// Calculate the relative velocity along the normal
	float dot_product = rel_vx * normal_x + rel_vy * normal_vy;

	// Only resolves if balls are moving towards each other
	if (dot_product > 0) return;

	// Calculate collision response (elastic collision)
	float impulse = 2 * dot_product / (radius + other.radius);

	vx += impulse * normal_x;
	vy += impulse * normal_y;
	other.vx += impulse * normal_x;
	other.vy += impulse * normal_y;

	// Avoid overlap by adjusting positions
	float overlap = radius + other.radius - distance;
	x -= overlap * normal_x / 2;
	y -= overlap * normal_y / 2;
	other.x -= overlap * normal_x / 2;
	other.y -= overlap * normal_y / 2;
}
```