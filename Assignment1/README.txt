------------------------------------------------------------------
COMP 4300 - Assignment 1
------------------------------------------------------------------

In this assignment you will be writing a C++/SFML program which will read
descriptions of shapes from a configuration file, and then drawing those shapes
to the screen. Each shape will have a name, position, speed and color as well as
properties unique to each shape type. For example, a rectangle will have width
and height, and a circle will have a Radius. For this assignment, the position of
a shape refers to its SFML default of the upper-left corner of the shape.

You are also required to make these shapes "bounce" off the sides of the window
which contains them. That means if the shape's left side hits the left side
of the window, its X speed reverses. If the top of shape hits the top of the
window, its Y speed reverses. Similarly, if it hits the right side or bottom of the
window. You can assume that all shapes will always be configured to start 
entirely within the window, and you don't have to worry about to what happens if
they start outside the window. Each shape's name should be drawn on the exact
center of the shape in the given font size and color specified in the file.

A sample configuration file is given to you in config.txt, however marking will
be don with an unseen configuration file in order to test more completely. Be
sure to add and remove your own shapes to this file to test if they all work
correctly.

Each line of the configuration file specifies one of the config settings of the
assignment program, with the first string in each line being the type of setting
that the rest of the line specified. Lines in the config file can be one of the
following types, and lines can appearin any order in the file.

Window W H
- This line declares that the SFML Window must be constructed
with Width W and Height H, each of which will be integers.

Font F S R G B
- This line defines the font which is to be used to draw text
for this program. The format of the line is as follows:
Font File    F    std::string (it will have no spaces)
Font Size    S    int
RGB Color    (R, G, B) int, int, int

Rectangle N X Y SX SY R G B W H
- Defines a RectangleShape with:
Shape Name    Name    std::string
Initial Position    (X, Y)    float, float
Initial Speed       (SX, SY)  float, float
RGB Color           (R,G,B)   int, int, int
Size                (W, H)       float, float

Circle N X Y SX SY R G B R
- Defines a CircleShape with:
Shape Name    Name    std::string
Initial Position    (X,Y)    float, float
Initial Speed       (SX, SY) float, float
RGB Color           (R,G,B)  int, int, int
Radius              (R)      float

-----------------------------------------------------------------------------------
ASSIGNMENT HINTS
-----------------------------------------------------------------------------------
- In order to store an arbitrary number of shapes from the configuration file,
you must store them in a container - std::vector is recommended.

- A shape will 'touch' the side of the window if its bounding box makes
contact with it. Each shape's bounding rectangle can be obtained via:
shape.getLocalBounds(); // .top, .left, .width, .height
	- gives the LOCAL position of the (top, left) of the rectangle
	- LOCAL pos means it is relative to shape.getPosition(), not the window
	- as well as the (width, height) size of the rectangle
	
- Similarly, a sf::Text element's bounding rectangle can also be
retrieved via text.getLocalBounds(), which you will need to use to
center the text properly within a shape.

- Please use C++ file reading (std::ifstream makes this easy) rather
than C-style FILE reading.
