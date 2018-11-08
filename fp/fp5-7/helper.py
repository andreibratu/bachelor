from datetime import datetime


def str_to_dt(date_str: str) -> datetime:
    """Utility that parses strings into Python datetime objects.

    The strings should respect the %d-%m-%Y format. See
    docs.python.org/3/library/datetime.html#strftime-and-strptime-behavior
    for further reference.

    Args:
        date_str (str): The string to be parsed.
    Returns:
        A datetime object.
    Raises:
        ValueError: String does not match the expected format.
    """

    FORMAT = '%d-%m-%Y'
    try:
        return datetime.strptime(date_str, FORMAT)
    except ValueError:
        raise ValueError('Invalid date string: {}'.format(date_str))


def pretty_date(dt: datetime) -> str:
    """Return a human readable representation of a datetime object.

    The string is displayed using the %d %b %Y format.

    Args:
        dt (datetime): The datetime object.
    Returns:
        The pretiffied string.
    """

    FORMAT = '%d %b %Y'
    return dt.strftime(FORMAT)
