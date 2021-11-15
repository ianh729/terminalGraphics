# What is this project?

After a series of unsatisfactory tutorials and resources, I have decided to learn how 3D computer graphics work from the bottom up. To do this, I decided to use ASCII characters in the command terminal as my pixels, writing scripts in C. I intend to learn the fundamental algorithms, equations, and standards for 3D graphics, and implement them here, avoiding high-level libraries to truly learn.

Eventually, I intend to transfer this to OpenGL in C++.

### History

11/12/2021:

Today I started my project, focusing on basic perspective viewing. I learned how to project coordinates to a screen given a field of view (distance from screen, K1 in diagram below).  

(diagram goes here)  
I then implemented a screen, a z-buffer (which I have yet to use), and a function to draw a circle in the xy plane and render it.

11/15/2021:

Today I focused on fixing some boundary issues. First, I made the viewing area center on (0,0), instead of (0,0) being in the bottom left. I then set boundaries to make it so that vertices outside the viewing frustum would not be rendered, saving time. With this, I added a near and far z bound. I also added a sphere function. To begin making lighting/shading, I made a typedef for a Vector3 struct and made a dot product method. I then found the normal vector of each point of the sphere, and took the dot product of its normalized version and the light vector's normalization, and this was the luminance. The luminance is proportional to which character from the shading set is used. As of today, I have successfully rendered a sphere! A huge amount of optimization is required though, as I am still calculating the back vertices of the sphere, which cannot be seen.

### Resources:
https://www.a1k0n.net/2011/07/20/donut-math.html  
https://en.wikipedia.org/wiki/Z-buffering

### To Do:
* use matrices to change position of camera
* make simple multiplication a matrix
* make cube