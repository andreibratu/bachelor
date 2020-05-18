from typing import Dict

from shapely.geometry import Point, MultiPoint

import input


def __point_on_segment_known_y(a: Point, b: Point, yC: float) -> Point:
    """
    Derived from the formula:
    y - y1 = m * (x - x1)
    """
    xA, yA = a.x, a.y
    xB, yB = b.x, b.y
    if xB == xA:
        # Segment parallel to Oy
        return Point(xA, yC)
    slope = (yB - yA) / (xB - xA)
    intercept = - slope * xA + yA
    xC = (yC - intercept) / slope
    return Point(xC, yC)


def get_probability(parameter: Dict[int, Dict], param_value: int) -> Dict[int, float]:
    """
    Calculate the probability for a given parameter value to belong in each of the parameter's classes.
    :param parameter: The universe of discourse for the parameter
    :param param_value: The value of the parameter
    :return:
        A dictionary mapping a class to its probability. Probabilities will
        not necessarily add up to one. TODO: Should they be scaled to 1?
    """
    ans = {}
    for cls, probabilities in parameter.items():
        if param_value not in probabilities:
            ans[cls] = 0
        else:
            ans[cls] = probabilities[param_value]
    return ans


def get_fuzzy_sets(
        temperature_probabilities: Dict[int, float],
        capacity_probabilities: Dict[int, float]
) -> Dict[int, float]:
    """
    Calculate the probability for each power class using the output rules and inputs' probabilities.
    If multiple probabilities are registered for the same class, the maximum will be considered.
    """
    power_classes = {k: None for k in input.power.keys()}
    for (rule_cap, rule_temp), power_cls in input.rules.items():
        temp_probability = temperature_probabilities[rule_temp]
        cap_probability = capacity_probabilities[rule_cap]
        # Apply AND
        power_probability = min(temp_probability, cap_probability)
        if power_classes[power_cls] is None:
            power_classes[power_cls] = power_probability
        else:
            power_classes[power_cls] = max(power_classes[power_cls], power_probability)
    return power_classes


def calculate_power_value(power_probabilities: Dict[int, float]) -> float:
    """
    Calculate the required power for the given inputs.
    The approach consists in intersecting every power class triangle with
    a y-constant line, with y equal to the probability of the respective
    class. The intersection will result in two points for the two sides
    of a triangle, which will be taken together with the points from
    the base of the triangle. A total of 4 * number_power_classes will be obtained,
    forming an irregular polygon. The necessary power will be the X coordinate of
    its centroid.
    :param power_probabilities: Probability of each power class
    :return: The power value
    """
    fuzzy_polygon_vertices = []
    power_points = {
        # Convention POINT_UP, POINT_LEFT, POINT_RIGHT, (x, y) pairs
        0: [Point(0.0, 1.0), Point(0.0, 0.0), Point(10, 0.0)],
        1: [Point(10.0, 1.0), Point(5.0, 0.0), Point(15.0, 0.0)],
        2: [Point(20.0, 1.0), Point(10.0, 0.0), Point(20.0, 0.0)]
    }
    for power_cls, prob in power_probabilities.items():
        if prob == 0:
            # Polygon for given class has an area of zero
            continue
        up, left, right = power_points[power_cls]
        intersection_left_line = __point_on_segment_known_y(up, left, prob)
        intersection_right_line = __point_on_segment_known_y(up, right, prob)
        # Add the four points of the class power polygon to the greater polygon
        fuzzy_polygon_vertices += [left, right, intersection_left_line, intersection_right_line]
    """
    Pro Gamer Move: Shapely expects points to be in order when constructing a Polygon object.
    Instead, we calculate the convex hull of the unordered set of points to get there.
    """
    fuzzy_polygon = MultiPoint(fuzzy_polygon_vertices).convex_hull
    centroid_fuzzy_polygon = fuzzy_polygon.centroid
    # Centroid's projection on the Ox axis is the answer
    return centroid_fuzzy_polygon.x


def control(input_temperature: int, input_capacity: int) -> float:
    temp_probabilities = get_probability(input.temperature, input_temperature)
    cap_probabilities = get_probability(input.capacity, input_capacity)
    power_probabilities = get_fuzzy_sets(temp_probabilities, cap_probabilities)
    return calculate_power_value(power_probabilities)
