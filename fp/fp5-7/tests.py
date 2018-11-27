import unittest
import contextlib
import io

from abstract.observable import Observable
from abstract.observer import Observer

from entities.client_entity import Client
from entities.movie_entity import Movie

from repositories.client_repository import ClientRepository
from repositories.movie_repository import MovieRepository
from repositories.rental_repository import RentalRepository

from controllers.client_controller import ClientController
from controllers.movie_controller import MovieController
from controllers.rental_controller import RentalController
from controllers.history_controller import HistoryController

from exceptions.conflict_error import ConflictError
from helper.helper import str_to_dt


class EntitiesTest(unittest.TestCase):
    """Class that tests entities implementation."""

    def setUp(self):
        self.__test_client_entity = Client('Mary')
        self.__test_cowboys_movie_entity = Movie(
            title='Space Cowboys',
            description='Babe you have to see this one',
            genre='Space'
        )


    def test_update_entity(self):

        self.__test_client_entity.update('Jane')
        self.assertEqual(self.__test_client_entity.name, 'Jane')

        self.__test_cowboys_movie_entity.update(
            title='Space Cowboys',
            description='A more mature description',
            genre='Western'
        )
        self.assertEqual(self.__test_cowboys_movie_entity.genre, 'Western')


class RepositoriesTest(unittest.TestCase):
    """Class that tests the repositories objects."""

    def setUp(self):
        self.__client_repository = ClientRepository()
        self.__movie_repository = MovieRepository()
        self.__rental_repository = RentalRepository()
        self.__star_wars_movie = Movie(
            title='Stary Wars',
            description='Space soap opera',
            genre='action'
        )


    def test_repository_insert(self):

        client = Client('asdf')
        id = self.__client_repository.insert(client)
        self.assertTrue(hasattr(client, 'id'))

        client.update('dei')
        id = self.__client_repository.insert(client)
        self.assertEqual(client.id, id)


    def test_repository_delete(self):

        movie = Movie(
            title='star_wars',
            description='Space soap opera',
            genre='action'
        )

        id = self.__movie_repository.insert(movie)
        self.__movie_repository.delete(id)
        with self.assertRaises(KeyError):
            self.__movie_repository.delete(id + 1)


    def test_repository_get_all(self):
        self.assertIsInstance(self.__movie_repository.get_all(), list)


    def test_repository_get_one_movies(self):
        id = self.__movie_repository.insert(self.__star_wars_movie)
        self.assertIs(self.__movie_repository.get(id), self.__star_wars_movie)


class AbstractTests(unittest.TestCase):
    """Class that tests the Observable pattern implementation."""

    def setUp(self):
        self.__observer = Observer()
        self.__observable = Observable()
        self.__observable.subscribe(self.__observer)


    def test_observable_notimplemented(self):
        with self.assertRaises(NotImplementedError):
            self.__observable.notify('foo')


    def test_observable_unsubscribe(self):
        self.__observable.unsubscribe(self.__observer)


class ControllersTest(unittest.TestCase):
    """Class that holds the controller tests."""

    def setUp(self):
        self.__test_client_entity = Client('Mary')
        self.__test_cowboys_movie_entity = Movie(
            title='Space Cowboys',
            description='Babe you have to see this one',
            genre='Space'
        )
        self.__client_repository = ClientRepository()
        self.__movie_repository = MovieRepository()
        self.__rental_repository = RentalRepository()
        self.__star_wars_movie = Movie(
            title='Stary Wars',
            description='Space soap opera',
            genre='action'
        )
        self.__client_controller = ClientController(self.__client_repository)
        self.__movie_controller = MovieController(self.__movie_repository)
        self.__rental_controller = RentalController(
            movie_repository=self.__movie_repository,
            client_repository=self.__client_repository,
            rental_repository=self.__rental_repository
        )
        self.__history_controller = HistoryController()
        self.__client_controller.subscribe(self.__history_controller)
        self.__movie_controller.subscribe(self.__history_controller)
        self.__rental_controller.subscribe(self.__history_controller)

        self.__client_controller.create('Donald')
        self.__client_controller.create('Zhara')

        self.__movie_controller.create(
            title='Wonder Boy',
            description='Heartwarming super hero movie, cooler than testing',
            genre='Superhero'
        )

        self.__movie_controller.create(
            title='Starboy',
            description='Wait this is actually like a song or something',
            genre='Soul'
        )

        self.__output_str = io.StringIO()


    def test_client_controller_delete(self):
        self.__client_controller.delete(0)


    def test_client_controller_invalid_delete(self):
        with self.assertRaises(KeyError):
            self.__client_controller.delete(42)


    def test_client_controller_valid_update(self):
        self.__client_controller.update(0, 'Glover')
        with self.assertRaises(KeyError):
            self.__client_controller.update(42, 'Donald')


    def test_client_controller_print_clients(self):
        with contextlib.redirect_stdout(self.__output_str):
            self.__client_controller.display()
        self.assertIn('Donald', self.__output_str.getvalue())
        self.assertIn('Zhara', self.__output_str.getvalue())


    def test_client_controller_search(self):
        with contextlib.redirect_stdout(self.__output_str):
            self.__client_controller.search('don')
        self.assertIn('Donald', self.__output_str.getvalue())
        self.assertNotIn('zha', self.__output_str.getvalue())


    def test_movie_controller_valid_delete(self):
        self.__movie_controller.delete(0)


    def test_movie_controller_invalid_delete(self):
        with self.assertRaises(KeyError):
            self.__movie_controller.delete(42)


    def test_movie_controller_display_all(self):
        with contextlib.redirect_stdout(self.__output_str):
            self.__movie_controller.display()
        self.assertIn('Wonder Boy', self.__output_str.getvalue())


    def test_movie_controller_search(self):
        with contextlib.redirect_stdout(self.__output_str):
            self.__movie_controller.search('boy')
        self.assertIn('Wonder', self.__output_str.getvalue())


    def test_movie_controller_search_id(self):
        with contextlib.redirect_stdout(self.__output_str):
            self.__movie_controller.search('0')
        self.assertIn('Wonder', self.__output_str.getvalue())


    def test_movie_controller_update_valid(self):
        self.__movie_controller.update(
            id=0,
            title='Wonder Boy',
            description='The description is now shorter',
            genre='Superhero'
        )


    def test_movie_controller_invalid_update(self):
        with self.assertRaises(KeyError):
            self.__movie_controller.update(
                id=42,
                title='Wonder Boy',
                description='The description is now shorter',
                genre='Superhero'
            )


    def test_rental_controller_rent(self):
        self.__rental_controller.rent(
            movie_id=0,
            client_id=0,
            rented_date='19-11-2018',
            due_date='24-11-2018'
        )
        # Check no movie entity was left
        with contextlib.redirect_stdout(self.__output_str):
            self.__movie_controller.display()
        self.assertNotIn('Wonder Boy', self.__output_str.getvalue())


    def test_rental_controller_rent_invalid_client_id(self):
        with self.assertRaises(KeyError):
            self.__rental_controller.rent(
                movie_id=0,
                client_id=42,
                rented_date='19-11-2018',
                due_date='24-11-2018'
            )


    def test_rental_controller_rent_invalid_movie_id(self):
        with self.assertRaises(KeyError):
            self.__rental_controller.rent(
                movie_id=42,
                client_id=0,
                rented_date='19-11-2018',
                due_date='24-11-2018'
            )


    def test_rental_controller_resolve(self):
        self.__rental_controller.rent(
            movie_id=0,
            client_id=0,
            rented_date='19-11-2018',
            due_date='24-11-2018'
        )
        self.__rental_controller.resolve(0, '26-11-2018')

        with contextlib.redirect_stdout(self.__output_str):
            self.__movie_controller.display()
        self.assertIn('Wonder Boy', self.__output_str.getvalue())


    def test_rental_controller_rent_conflict(self):
        self.__rental_controller.rent(
            movie_id=0,
            client_id=0,
            rented_date='19-11-2018',
            due_date='24-11-2018'
        )

        with self.assertRaises(ConflictError):
            self.__rental_controller.rent(
                movie_id=1,
                client_id=0,
                rented_date='19-11-2018',
                due_date='24-11-2018'
            )


    def test_rental_controller_display(self):
        with contextlib.redirect_stdout(self.__output_str):
            self.__rental_controller.display()


    def test_rental_controller_stats(self):
        self.__rental_controller.rent(
            movie_id=0,
            client_id=0,
            rented_date='19-11-2018',
            due_date='24-11-2018'
        )

        self.__rental_controller.rent(
            movie_id=1,
            client_id=1,
            rented_date='21-11-2018',
            due_date='30-11-2018'
        )

        with contextlib.redirect_stdout(self.__output_str):
            self.__rental_controller.stats('days')
            self.__rental_controller.stats('current')
        with self.assertRaises(ValueError):
            self.__rental_controller.stats('foobar')


    def test_history_controller_undo_redo(self):
        self.__movie_controller.delete(0)
        with contextlib.redirect_stdout(self.__output_str):
            self.__movie_controller.display()
        self.assertNotIn('Wonder Boy', self.__output_str.getvalue())

        self.__history_controller.undo()
        with contextlib.redirect_stdout(self.__output_str):
            self.__movie_controller.display()
        self.assertIn('Wonder Boy', self.__output_str.getvalue())

        self.__history_controller.redo()
        with contextlib.redirect_stdout(self.__output_str):
            self.__movie_controller.display()
        self.assertIn('Wonder Boy', self.__output_str.getvalue())


class HelperTests(unittest.TestCase):
    """Class that tests helper functions."""

    def test_str_to_dt_invalid_format(self):
        with self.assertRaises(ValueError):
            str_to_dt('13_11-2019')
            str_to_dt('13-17-2019')


if __name__ == '__main__':
    unittest.main()
