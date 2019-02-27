from datetime import datetime
from typing import List, Callable
from bs4 import BeautifulSoup
from random import sample
from pony import orm
import json


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


def build_db():
    """Build the Pony databases object and used entities."""

    db = orm.Database()
    db.bind(provider='sqlite', filename='../storage/db.sqlite', create_db=True)

    class ClientEntity(db.Entity):
        id = orm.PrimaryKey(int)
        name = orm.Required(str)
        rentals = orm.Set("RentalEntity")

    class MovieEntity(db.Entity):
        id = orm.PrimaryKey(int)
        title = orm.Required(str)
        description = orm.Required(str)
        genre = orm.Required(str)
        rentals = orm.Set("RentalEntity")

    class RentalEntity(db.Entity):
        id = orm.PrimaryKey(int)
        movie = orm.Required("MovieEntity")
        client = orm.Required("ClientEntity")
        rented_date = orm.Required(datetime)
        due_date = orm.Required(datetime)
        returned_date = orm.Optional(datetime)

    db.generate_mapping(create_tables=True)

    return (db, ClientEntity, MovieEntity, RentalEntity)


def get_settings():
    """Read the configuration file from settings.json"""

    with open('settings.json', 'r') as f:
        return json.loads(f.read())


def my_filter(arr: List, f: Callable):
    return [x for x in arr if f(x)]


def shell_sort(arr: List, cmp: Callable):
    """Implementation of shell sort agorithm.

    # Kudos: Mohit Kumra from https://www.geeksforgeeks.org/shellsort/
    """

    # Start with a big gap, then reduce the gap
    n = len(arr)
    gap = n // 2

    # Do a gapped insertion sort for this gap size.
    # The first gap elements a[0..gap-1] are already in gapped
    # order keep adding one more element until the entire array
    # is gap sorted
    try:
        while gap > 0:

            for i in range(gap, n):

                # add a[i] to the elements that have been gap sorted
                # save a[i] in temp and make a hole at position i
                temp = arr[i]

                # shift earlier gap-sorted elements up until the correct
                # location for a[i] is found
                j = i
                while j >= gap and not cmp(arr[j - gap], temp):
                    arr[j] = arr[j - gap]
                    j -= gap

                # put temp (the original a[i]) in its correct location
                arr[j] = temp
            gap //= 2

    except TypeError:
        raise TypeError('Comparison callable should expect 2 args')
