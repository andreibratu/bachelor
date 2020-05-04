package server.services;

import common.services.behaviours.GenericBehaviour;
import common.services.behaviours.filter.FilterBehaviour;
import common.services.behaviours.filter.FilterStrategy;
import common.entities.GenreEnum;
import common.entities.Movie;
import org.junit.Before;
import org.junit.Test;

import java.util.List;
import java.util.Set;

import static org.junit.Assert.assertEquals;

public class FilterServicesTest
{
    private static FilterBehaviour filterBehaviour;
    private List<Movie> movies;

    @Before
    public void setUp()
    {
        filterBehaviour = new FilterBehaviour();
        movies = List.of(
            new Movie("Old Boy", GenreEnum.ACTION, 2003),
            new Movie("Gone with the wind", GenreEnum.ROMANTIC, 1939),
            new Movie("Shutter Island", GenreEnum.THRILLER, 2010),
            new Movie("Pulp Fiction", GenreEnum.ACTION, 1994)
        );
    }

    @Test
    public void testFilterByNumberAttribute()
    {
        List<Movie> result = (List<Movie>) filterBehaviour.filter(
                movies,
                new FilterStrategy("year", ">", 1999)
        );
        assertEquals(2, result.size());
    }

    @Test
    public void testFilterByStringAttribute()
    {
        List<Movie> result = (List<Movie>) filterBehaviour.filter(
                movies,
                new FilterStrategy("title", "CONTAINS", "With")
        );
        assertEquals("Gone with the wind", 1, result.size());
        result = (List<Movie>) filterBehaviour.filter(
                movies,
                new FilterStrategy("title", "CONTAINS", "WiTH"));
        assertEquals("GoNE wItH tHE WinD", 1, result.size());
    }

    @Test
    public void testFilterByEnumAttribute()
    {
        List<Movie> result = (List<Movie>) filterBehaviour.filter(
                movies,
                new FilterStrategy("genre", "NEQ", GenreEnum.ACTION)
        );
        assertEquals("Gone w/ Wind, Shutter Island", 2, result.size());
    }

    @Test
    public void testGetEntityAttributes()
    {
        assertEquals(
                Set.of("year", "title", "genre"),
                GenericBehaviour.getEntityAttributes(Movie.class).keySet());
    }
}
