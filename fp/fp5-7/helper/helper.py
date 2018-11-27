from datetime import datetime
from typing import List
from bs4 import BeautifulSoup
from random import sample


def str_to_dt(date_str: str) -> datetime:
    """Utility that parses strings into Python datetime objects.

    The strings should respect the %d-%m-%Y format. See
    docs.python.org/3/library/datetime.html#strftime-and-strptime-behavior
    for further reference.

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
    """

    FORMAT = '%d %b %Y'
    return dt.strftime(FORMAT)


def abstract_search(l: List, query: str) -> List:
    """
    Return all objects in list that have a string attribute that partial
    matches the given query in lowercase.

    Args:
        l (List): A generic list of objects.
        query (str): The query term.
    Returns:
        A list that contains matching items.
    """

    # Search by id
    search_id = [
        o for o in l
        if hasattr(o, 'id') and str(getattr(o, 'id')) == query]

    if search_id != []:
        return search_id

    # Partial search
    return list(set([
        o for o in l for attr in dir(o)
        if type(getattr(o, attr))
        is str and query.lower() in getattr(o, attr).lower()
    ]))


def print_list(l: List):
    """Print a list of objects in a readable form."""

    print('----')
    print("\n".join([str(o) for o in l]))
    print('----')


def generate_movie_from_scraped_page():  # pragma: no cover
    """Generator function that scrapes movie information from local html file.

    Yields:
        A movie entity.
    """

    page = BeautifulSoup(open('helper/movies.html'), 'html.parser')

    for div in page.find_all('div', {'class': 'lister-item-content'}):
        title = div.find('h3').find('a').text
        genre = div.find('p', {'class': 'text-muted text-small'}) \
                   .find('span', {'class': 'genre'}).text.split(', ')[0]
        description = div.find_all('p')[1].text.strip()

        yield (title, genre, description)


def generate_name() -> str:  # pragma: no cover
    """Generator function that returns names."""

    names = open('helper/names.txt', 'r').read().splitlines()

    for name in sample(names, 100):
        yield name
