package server.validators;

import server.entities.Client;
import org.springframework.stereotype.Component;

/**
 * Validator for {code Movie} common.entities
 */
@Component("client-validator")
public class ClientValidator implements Validator<Client>
{
    /**
     * @param entity Client entity that must be validated
     * @throws ValidatorException
     *      If {code name}, or {code address} attribute is null or
     *      the name or address has zero length.
     */
    @Override
    public void validate(Client entity) throws ValidatorException
    {
        try
        {
            if(entity.getName().length() == 0)
                throw new ValidatorException("Cannot have an empty name!");
            if(entity.getAddress() == null)
                throw new ValidatorException("Cannot have an empty address!");
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
