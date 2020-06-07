package common.entities;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import server.entities.GenreEnum;
import server.entities.Movie;

import static org.junit.Assert.assertEquals;


public class MovieTest {
    private static final Long ID = 1L;

    private static final String TITLE  = "MovieTitle";
    private static final String NEW_TITLE = "NEW_MovieTitle";
    private static final GenreEnum GENRE = GenreEnum.THRILLER;
    private static final GenreEnum NEW_GENRE = GenreEnum.HORROR;
    private static final Integer YEAR = 2019;
    private static final Integer NEW_YEAR = 2020;

    private Movie movie;

    @Before
    public  void setUp() {
        movie = Movie.builder().title(TITLE).genre(GENRE).year(YEAR).build();
        movie.setId(ID);
    }

    @After
    public void tearDown() {
        movie =null;
    }

    @Test
    public void testGetTitle() {
        assertEquals("Titles should be equal!", TITLE, movie.getTitle());
    }

    @Test
    public void testSetTitle() {
        movie.setTitle(NEW_TITLE);
        assertEquals("NEW Titles should be equal!", NEW_TITLE, movie.getTitle());
    }

    @Test
    public void testGetGenre() {
        assertEquals("Genres should be equal!", GENRE, movie.getGenre());
    }

    @Test
    public void getSetGenre() {
        movie.setGenre(NEW_GENRE);
        assertEquals("NEW Genres should be equal!", NEW_GENRE, movie.getGenre());
    }

    @Test
    public void testGetYEar() {
        assertEquals("Years should be equal!", YEAR, movie.getYear());
    }

    @Test
    public void getSetYear() {
        movie.setYear(NEW_YEAR);
        assertEquals("NEW Years should be equal!", NEW_YEAR, movie.getYear());
    }
}
