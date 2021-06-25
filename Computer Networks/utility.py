import math


def vector_subract(a, b):
    return (a[0] - b[0], a[1] - b[1])

def vector_length(vec):
    return math.sqrt(vec[0] * vec[0] + vec[1] * vec[1])

def vector_normalize(vec, l = None):
    if l is None:
        l = vector_length(vec)
    if l > 0:
        return (vec[0] / l, vec[1] / l)
    else:
        return (0, 0)

def vector_multiply(vec, m: float):
    return (vec[0] * m, vec[1] * m)

def vector_round(vec):
    return (round(vec[0]), round(vec[1]))