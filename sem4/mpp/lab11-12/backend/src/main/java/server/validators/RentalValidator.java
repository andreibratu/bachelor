package server.validators;

import common.entities.Rental;
import org.springframework.stereotype.Component;

import java.time.LocalDate;

/**
 * Validator for {code Rental} common.entities
 */
@Component("rental-validator")
public class RentalValidator implements Validator<Rental>
{
    /**
     * @param entity Movie entity that must be validated
     * @throws ValidatorException If {code clientId}, {code movieId} or {code startDate} or {code endDate} attribute is null,
     *                            startDate or endDate outside range of decency
     */
    @Override
    public void validate(Rental entity) throws ValidatorException
    {

        if (entity.getClientID() == null)
            throw new ValidatorException("Must have a Client Id!");
        if (entity.getMovieID() == null)
            throw new ValidatorException("Must have a Movie Id!");
        if (entity.getStartDate().isBefore(LocalDate.parse("2000-01-01")) || entity.getStartDate().isAfter(LocalDate.parse("2020-12-31")))
            throw new ValidatorException("Rental start date must be between 2000 and the current year!");
        try
        {
            if (entity.getEndDate().isBefore(LocalDate.parse("2000-01-01")) || entity.getEndDate().isAfter(LocalDate.parse("2020-12-31")))
                throw new ValidatorException("Rental start date must be between 2000 and the current year!");
        } catch (NullPointerException e)
        {
            /*
            NullPointer can be raised by not having a set End date
            */
        }
    }
}
