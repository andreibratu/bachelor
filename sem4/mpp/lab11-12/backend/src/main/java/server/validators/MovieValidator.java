package server.validators;

import common.entities.Movie;
import org.springframework.stereotype.Component;

import java.util.Calendar;

/**
 * Validator for {code Movie} common.entities
 */
@Component("movie-validator")
public class MovieValidator implements Validator<Movie>
{
    /**
     * @param entity Movie entity that must be validated
     * @throws ValidatorException
     *      If {code title}, {code genre} or {code year} attribute is null,
     *      the title has zero length, or the year is outside the
     *      range of decency.
     */
    @Override
    public void validate(Movie entity) throws ValidatorException
    {

        try
        {
            if(entity.getTitle().length() == 0)
                throw new ValidatorException("Cannot have an empty name!");
            if(entity.getGenre() == null)
                throw new ValidatorException("Must have a genre!");
            Integer movieYear = entity.getYear();
            Integer currentYear = Calendar.getInstance().get(Calendar.YEAR);
            if(movieYear < 1900 || movieYear > currentYear)
                throw new ValidatorException(currentYear + " " + movieYear + " year must be between 1900 and the current year!");
        }
        catch (NullPointerException e)
        {
            /*
            NullPointer can be raised by trying to access the length of
            a null title, or by arithmetic comparisons done with a null year
            */
            throw new ValidatorException("Null pointer exception!");
        }
    }
}
