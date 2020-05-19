# Algorithm

* Algorithm takes as input the temperature and capacity, in integers

* Using the universes of discourse provided for temperature and capacity, we calculate\
  the probability of an input value to belong to the input's classes; this values\
  may not add up to 1.
 
* Using the given rules we decide, we apply AND between the probability of temperature class\
  and the probability of capacity class to obtain the probability for the output class.\
  If multiple rules concern the same output class the maximum probability found for an\
  output class will be considered.
  
* We divide the output graph for the power output in three triangles, determined by the points
    1. (0, 1),  (0, 0),  (10, 0)
    2. (10, 1), (5, 0),  (15, 0)
    3. (20, 1), (10, 0), (20, 0)

* Each triangle represents an output class. We apply a Mamdani approach: We intersect each triangle\
  with a parallel of line y={value_output_class}. If value of output class is zero, we do not take\
  it in consideration. The two points obtained from the intersection, together with the two points\
  of the base triangle are added to a set. The procedure is repeated for all triangles. These\
  points are the vertices of a polygon used to determine the value of the power output.
  
* The X coordinate of the polygon's centroid represents the power output.


# Calculations

CAPACITY: SMALL(0) MEDIUM(1) HIGH(2) <br>
TEMPERATURE: COLD(-2) COOL(-1) MODERATE(0) HOT(1) VERY HOT(2) <br>
POWER: SMALL(0) MEDIUM(1) HIGH(2) <br>

## Temperature 100, Capacity 5

* Temperature probabilities {-2: 0, -1: 0, 0: 0, 1: 0.5, 2: 0.5}

* Capacity probabilities    {0: 0, 1: 1, 2: 0}

* Power probabilities       {0: 0.5, 1: 0, 2: 0}

* The only power output class considered is 0; we register the following points by intersecting with y=0.5
    1. (0, 0)
    2. (10, 0)
    3. (0, 0.5)
    4. (5, 0.5)
    
* We obtain the centroid of value (3.8888, 0.2222). The power output is 3.8888.


## Temperature 30, Capacity 6

* Temperature probabilities {-2: 1, -1: 0, 0: 0, 1: 0, 2: 0}

* Capacity probabilities    {0: 0, 1: 0.5, 2: 0.2}

* Power probabilities       {0: 0, 1: 0.5, 2: 0.2}

* The register the power classes 1 and 2; we register the following points by intersecting with y=0.5 and y=0.2
    1. (5, 0)
    2. (15, 0)
    3. (7.5, 0.5)
    4. (12.5, 0.5)
    5. (10 0)
    6. (20 0)
    7. (12 0.2)
    8. (20 0.2)
    
* We obtain the centroid of value (12.2463, 0.2115). The power output is 12.2463.


# Conclusions

The power output is directly proportional with the capacity and inversely proportional with temperature.
