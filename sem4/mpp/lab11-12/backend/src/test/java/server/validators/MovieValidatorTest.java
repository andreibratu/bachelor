package server.validators;

import server.entities.GenreEnum;
import server.entities.Movie;
import org.junit.Test;

import static org.junit.Assert.fail;

public class MovieValidatorTest
{
    private static final MovieValidator validator = new MovieValidator();

    @Test
    public void testOkEntity()
    {
        Movie movie = new Movie("Foo", GenreEnum.THRILLER, 1999);
        try
        {
            validator.validate(movie);
        } catch (ValidatorException e)
        {
            fail(e.getMessage());
        }
    }

    @Test(expected = ValidatorException.class)
    public void testEmptyTitle() throws ValidatorException
    {
        Movie movie = new Movie("", GenreEnum.COMEDY, 2018);
        validator.validate(movie);
    }

    @Test(expected = ValidatorException.class)
    public void testYearTooSmall() throws ValidatorException
    {
        Movie movie = new Movie("Train coming", GenreEnum.ACTION, 1895);
        validator.validate(movie);
    }

    @Test(expected = ValidatorException.class)
    public void testYearTooBig() throws ValidatorException
    {
        Movie movie = new Movie("Fast and Furious 50", GenreEnum.ACTION, 2050);
        validator.validate(movie);
    }

    @Test(expected = ValidatorException.class)
    public void testNullAttribute() throws ValidatorException
    {
        Movie movie = new Movie("title", GenreEnum.ACTION, null);
        validator.validate(movie);
    }
}
