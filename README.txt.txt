Matric Number: A0102800A
Name: Suranjana Sengupta
Lab Group: 1

What am I drawing?
For Lab 5, I chose to draw The Burrow from Harry Potter. This house, as mentioned in the book and shown in the movies, has an extremely unsound structure, held up most definitely by 'magic'. In the story, The Burrow is said to look like it has 'grown' rooms from various angles to accommodate more family members/guests. :)

Primitives and Transformations Used:
1. There are SIX major types of shapes namely, plane, cuboid, cylinder, quad, circle and sphere. 
	a. The doors and windows of the house are created using polygon transformations.
	b. The roofs are created using quad transformations.
	c. The walls and gates are created using planes transformations.
	d. The chimney and stilts and tree trunks are created using cylinder transformations.
	e. The lake is created using circle transformations.
	f. The trees are created using sphere transformations.
2. Texturing is done for the following objects:
	a. Walls of the house: using wood5.bmp.
	b. Stilts, chimneys, window shades, gate/pen : using wood2.bmp
	c. Roof: using roog6.bmp
	d. Windows and doors using custom textures in customs folder.
	e. Lake and tree and tree bark also using custom textures.
	f. Plane: using grass1.bmp
Therefore, the types of geometric shapes textured are plane, sphere, cylinder and circle.
3. There are different variations of 'tophouse' and 'extendedwindow' which occur throughout the program to make up for various components of the house. 

Some functions used are:
1. glTranslatef(float tX, float tY, float tZ): to translate positions of features.
2. glScalef(float sX, float sY, float sZ): to scale up and down features. 
3. glRotatef(float degree, x,y,z) : rotation
4. glEnable(GL_BLEND)/glDisable(GL_BLEND) : enable/disale blending (for transperancy)
5. glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
6. glEnable(GL_TEXTURE_2D) : enable texture mapping
7. glBindTexture(GL_TEXTURE_2D, texSet): set the texture of the object

Methods Modified:
1. drawMyHouse(...): Changed the texture mapping of the floor plane to grass by enabling texture mapping.

Methods Created (only important ones stated here):
1. drawBurrow(): calls drawBaseHouse(), drawTopHouse(...), drawBackHouse(),drawExtendedHouse(...), drawExtendedWindow(), drawExtendedFloor(), drawPen() to draw the main features of the house. 
2. drawLake(): created a lake with surrounding greenery/bushes 
3. drawGrove(): created trees with textured trunk and leaves. 
4. drawSmoke(): created smoke using drawSphere(...) and set the transperancy level to 0.9.
5. drawAnimatedHouse(): will create the magic houses that pop out of The Burrow. 

Coolest thing(s) about my drawing:
1. I have made use of certain external textures to create the effects of the bushes, the bark of trees and the lake, doors and windows. This can be observed better by zooming into the house. 
2. The MAGIC feature, by pressing the 'M' key the MAGIC variable is toggled, and new rooms pop out of The Burrow to accommodate guests. 

