import numpy as np

"""
CAPACITY: SMALL(0) MEDIUM(1) HIGH(2)
TEMPERATURE: COLD(-2) COOL(-1) MODERATE(0) HOT(1) VERY HOT(2)
POWER: SMALL(0) MEDIUM(1) HIGH(2)
"""

__cold_temperature = {k: v for k, v in zip(
    range(20, 51),
    [1 for _ in range(20, 30)] + [x for x in np.linspace(1, 0, num=21)]
)}

__cool_temperature = {k: v for k, v in zip(
    range(30, 71),
    [x for x in np.linspace(0, 1, num=21)[:20]] + [x for x in np.linspace(1, 0, num=21)]
)}

__moderate_temperature = {k: v for k, v in zip(
    range(60, 81),
    [x for x in np.linspace(0, 1, num=11)[:10]] + [x for x in np.linspace(1, 0, num=11)]
)}

__hot_temperature = {k: v for k, v in zip(
    range(70, 111),
    [x for x in np.linspace(0, 1, num=21)[:20]] + [x for x in np.linspace(1, 0, num=21)]
)}

__very_hot_temperature = {k: v for k, v in zip(
    range(90, 121),
    [x for x in np.linspace(0, 1, num=21)[:20]] + [1 for x in range(110, 121)]
)}

__small_capacity = {k: v for k, v in zip(
    range(0, 6),
    [x for x in np.linspace(1, 0, num=6)]
)}

__medium_capacity = {k: v for k, v in zip(
    range(3, 8),
    [x for x in np.linspace(0, 1, num=3)[:2]] + [x for x in np.linspace(1, 0, num=3)]
)}

__high_capacity = {k: v for k, v in zip(
    range(5, 11),
    [x for x in np.linspace(0, 1, num=6)]
)}

__small_power = {k: v for k, v in zip(
    range(0, 11),
    [x for x in np.linspace(1, 0, num=11)]
)}

__medium_power = {k: v for k, v in zip(
    range(5, 16),
    [x for x in np.linspace(0, 1, num=6)[:5]] + [x for x in np.linspace(1, 0, num=6)]
)}

__high_power = {k: v for k, v in zip(
    range(10, 21),
    [x for x in np.linspace(0, 1, num=11)]
)}

temperature = {
    -2 : __cold_temperature,
    -1 : __cool_temperature,
     0 : __moderate_temperature,
     1 : __hot_temperature,
     2 : __very_hot_temperature
}

capacity = {
    0: __small_capacity,
    1: __medium_capacity,
    2: __high_capacity
}

power = {
    0: __small_power,
    1: __medium_power,
    2: __high_power
}

rules = {
    # (Capacity, Temperature) -> Power
    (0, -2): 0, (1, -2): 1, (2, -2): 2,
    (0, -1): 0, (1, -1): 1, (2, -1): 2,
    (0, 0): 0, (1, 0): 0, (2, 0): 0,
    (0, 1): 0, (1, 1): 0, (2, 1): 0,
    (0, 2): 0, (1, 2): 0, (2, 2): 0
}
