from complex import Complex
import re


def parseNumber(s: str) -> Complex:
    """Parses given string into a Complex number.

    The method uses regex to extract the real and imaginary part.

    Args:
        s (str): The string to be parsed.
    Returns:
        The parsed Complex number.
    """

    full_match = re.compile(
        '^([-+]?[0-9]*\.?[0-9]+)(([-+]?[0-9]*\.?[0-9]+)[i])$'
    )
    real_number = re.compile('^[-+]?[0-9]*\.?[0-9]+$')
    imag_number = re.compile('^([-+]?[0-9]*\.?[0-9]+)[i]$')

    m = re.match(full_match, s)
    if m:
        return Complex(m.group(1), m.group(3))

    m = re.match(real_number, s)
    if m:
        return Complex(m.group(0), 0)

    m = re.match(imag_number, s)
    if m:
        return Complex(0, m.group(1))

    raise ValueError('Could not parse complex number')
