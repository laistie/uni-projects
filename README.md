# University projects

In this repository are located some of the projects I developed for my university classes. Most of them (if not all) output reports in Portuguese, but are ~~almost~~ fully explained in English in this README; and I should warn you that I haven't gone through all of them before uploading them to my GitHub, although I can assure you they work :sweat_smile:


## Compilers

My first assignments from Compilers were actually developed using **only** C. After some time, I was introduced to Flex and Bison tools and began using them in my projects.

> 5th semester (2024)

### Portugol

### Lexical analyzer

In order to build a C compiler, the first step was making the lexical analyzer, which should use the Flex tool. In this assignment, each recognized token should have its classification printed. For example:

input:
```C
if(@)
{
    a
}
```

output:
```
IF
L_PAREN
error:lexical:1:4: @
R_PAREN
L_CURLY_BRACKET
IDENTIFIER(a)
R_CURLY_BRACKET
```

In the example above, there was also an error message indicating the line and column in which it occurred. Despite the error, the parsing process shall continue until it reaches the end of the input file.

This was the first assignment of Compilers I, but it was already full of details, such as warnings display and max size of identifiers or unterminated comments handling.

### Syntax analyzer

In the specification of this project, there were syntax diagrams that helped declaring the grammar, but it still took a while to define all rules correctly. This step of making a C compiler was marked by the usage of the Bison tool and needed the previous analyzer.

> 6th semester (2025)

### dcmat

### Register Allocation

### Linear Scan


## Computer Architecture :cd:

### MIPS assignments (Assembly)

> 3rd semester (2022)

Since this was my very first time dealing with Assembly (and earlier in this same semester, Machine Code), the folder won't contain all of my assignments, but the most interesting ones shall be included nonetheless.

> 4th semester (2023)

This folder includes some more difficult exercises, covering topics such as dynamic memory allocation and file handling.


## Data Structures :desktop_computer:

All assignments were developed using C language.
There was also an special rule for all assignments that structs shouldn't be declared in the .h file, making the usage of void* frequent.

> 2nd semester

### T1

In this assignment, since it was my very first data structures project, I mainly learned how to manipulate given paths in argv in order to work with files (reading and writing) and generate SVG files with them; also I had to use a doubly linked list for storing parameters from a .geo file:

| COMMAND |             PARAMETERS              | DESCRIPTION                                                  |
| :-----: | :---------------------------------: | :----------------------------------------------------------- |
|    c    |      i, x, y, r, border, fill       | Draws a circle centered at (_x_, _y_) with ray _r_, identifier _i_ and colored by _border_ and _fill_ colors |
|    r    |     i, x, y, w, h, border, fill     | Draws a rectangle with (_x_, _y_), (_x_ + _w_, _y_), (_x_, _y_ + _h_) and (_x_ + _w_, _y_ + _h_) vertexes, identifier _i_ and is colored by _border_ and _fill_ colors |
|    l    |      i, x1, y1, x2, y2, color       | Draws a line that links a point (_x1_, _y1_) to another point (_x2_, _y2_), has identifier _i_ and color specified by the parameters |
|    t    | i, x, y, border, fill, anchor, text | Draws a text at (_x_, _y_) that can have an anchor at the beginning, middle or end, has identifier _i_ and color specified by the parameters |

After reading the first query file and storing all parameters in the **doubly linked list**, a SVG file should be generated, containing all geometric shapes specified at .geo file. Following that, there could be a .qry file with some other functions:

| COMMAND |       PARAMETERS        | DESCRIPTION                                                  |
| :-----: | :---------------------: | ------------------------------------------------------------ |
|   inp   |            i            | Inserts the coordinates of the geometric shape identified by _i_ at a **static circular queue**; in case of lines, inserts the coordinate with lesser _x_, if they're equal, inserts the coordinate with lesser _y_ |
|   rmp   |                         | Removes from database the first coordinate inserted at the queue |
|   pol   |  i, d, e, border, fill  | Draws the polygon with vertexes at coordinates that are in the queue. The lines that compose the polygon have identifiers starting at _i_ and there's a distance _d_ between the fulfillment lines, which have a thickness _e_, of the geometric shape. The polygon's color is given by border and fill refers to the fulfillment lines' color |
|   clp   |                         | Removes from database all coordinates of the polygon         |
|   sel   |       x, y, w, h        | Selects all geometric shapes fully inside the area specified by the parameters; doesn't consider previous selections |
|  sel+   |       x, y, w, h        | Similar to sel, but it considers previous selections, adding new geometric shapes to the selected ones |
|  dels   |                         | Removes from database all geometric shapes that were selected |
|   dps   | i, dx, dy, border, fill | Generates new geometric shapes, similar to those that were selected, but located at (x', y'), x' = x + dx, y' = y + dy; the identifiers start at i and are incremented sequentially |
|   ups   | border, fill, dx, dy, n | Changes the colors and positions (transferring the coordinates like dps function does, but also considering y' = y + m * dy, m is the number of times that geometric shapes were changed) of n geometric shapes before (n < 0) or after (n > 0) the last that was selected by sel or sel+ |

So after reading and executing all functions at .qry file, there should be another SVG file and a report (.txt) of the processes executed.

### T2

This assignment took me way less time than the previous, since that were many functions I could use from the other project; still, they weren't the same and instead of working with a doubly linked list, I had to store all the following parameters inside a ternary search tree that should look like this:

![Ternary tree](./assets/ternarytree.png)

| COMMAND |             PARAMETERS              | DESCRIPTION                                                  |
| :-----: | :---------------------------------: | :----------------------------------------------------------- |
|    c    |      i, x, y, r, border, fill       | Draws a circle centered at (x, y) with ray r, identifier i and colored by border and fill colors |
|    r    |     i, x, y, w, h, border, fill     | Draws a rectangle with (x, y), (x + w, y), (x, y + h) and (x + w, y + h) vertexes, identifier i and is colored by border and fill colors |
|    l    |      i, x1, y1, x2, y2, color       | Draws a line that links a point (x1, y1) to another point (x2, y2), has identifier i and color specified by the parameters |
|    t    | i, x, y, border, fill, anchor, text | Draws a text at (x, y) that can have an anchor at the beginning, middle or end, has identifier i and color specified by the parameters |

Each geometric shape would represent a type of navy equipment and after generating the first SVG with .geo file, there could be a .qry file with some functions:

| COMMAND |    PARAMETERS    | DESCRIPTION                                                  |
| :-----: | :--------------: | ------------------------------------------------------------ |
|   na    |        v         | Assigns the level of aggressiveness v to attack areas        |
|   tr    |       x, y       | Torpedo that destroys all geometric shapes that has (x, y) as an internal point. There should be a red * if any shape was hit - in case of more than one, there should also be the number of shapes hit - or a gray * otherwise |
|   tp    | x, y, dx, dy, id | Torpedo that generates a clone of each geometric shape that has (x, y) as an internal point. There should be a red @ if any shape was hit or a gray @ otherwise; the clones have coordinates (x', y'), x' = x + dx, y' = y + dy, and their identifiers start at id and are incremented sequentially |
|   be    |    x, y, w, h    | Radiation bomb at area specified by parameters. Draws the area in red and any geometric shape fully inside that area should have a red . at its anchor and has its protection level decreased; if it reaches 0, then the shape should be removed from the SVG and set as inactive |

In order to make some calculations, it was given the following table:

| GEOMETRIC SHAPE | PROTECTION LEVEL | INACTIVATION POINTS | DESTRUCTION POINTS |
| :-------------: | :--------------: | :-----------------: | :----------------: |
|     circle      |        5         |         30          | 75 / (π * r² / 5)  |
|    rectangle    |        50        |         50          |  90 / (w * h / 5)  |
|      line       |        60        |         75          |        150         |
|      text       |        60        |         90          |        500         |

So after reading and executing all functions at .qry file, there should be another SVG file and a report (.txt) of the processes executed and the final score.

### Extra assignment

This one was a little bit more complicated, due to the number of data structures that were involved in the implementation: list, queue and a xyy ternary search tree variant, called yxx tree:

![Yxx Tree](./assets/yxxtree.png)

Basically, it was [T1](#T1) in terms of commands, but this time there was a mandatory .h file for yxx tree that should be followed and couldn't be modified. Also, the ternary search tree should contain the nodes from .geo file, working like a database for consulting.

> 3rd semester (2022)

### T3

This project was named "Pirate Fishing" and the basic components from .geo file - circles, rectangles, lines, texts - were the same as usual. Although each of them represented an element of the fishing:

| GEOMETRIC SHAPE |     ELEMENT    |
| :-------------: | :------------: |
|    rectangle    |      ship      |
|    text >--<    |     lobster    |
|     text $      |      coin      |
|  any other text | algae, rubbish | 
|      circle     |      fish      |
|       line      |     shrimp     |

Each of the ships can move, throw nets or even fire cannons; their actions cost a certain quantity of energy or can result in the gain of it:

| ACTION |      ENERGY      |
| :----: | :--------------: |
|  Move  |  E = distance/5  |
| Throw  | E = a/25 * d/5   |
|  Shot  |       E = d      |


## Discrete Mathematics :triangular_ruler:

### Linear congruence applications (Python)

> 2nd semester (2022)

This project embraces linear congruence applications, such as: ISBN-10, 10-digit barcode and Cadastro de Pessoas Físicas (CPF, commonly used in Brazil to register one's data).