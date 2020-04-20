package server.validators;

import common.entities.Rental;
import org.junit.Test;

import static org.junit.Assert.fail;

public class RentalValidatorTest
{
    private static final RentalValidator validator = new RentalValidator();

    @Test
    public void testOkEntity()
    {
        Rental rental= new Rental(1L, 1L);
        try
        {
            validator.validate(rental);
        } catch (ValidatorException e)
        {
            fail(e.getMessage());
        }
    }

    @Test(expected = ValidatorException.class)
    public void testNullClientID() throws ValidatorException
    {
        Rental rental = new Rental(null, 1L);
        validator.validate(rental);
    }

    @Test(expected = ValidatorException.class)
    public void testNullMovieID() throws ValidatorException
    {
        Rental rental = new Rental(1L, null);
        validator.validate(rental);
    }



}
