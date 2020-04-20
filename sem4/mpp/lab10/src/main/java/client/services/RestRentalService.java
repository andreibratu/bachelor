package client.services;

import client.services.base.RestEntityService;
import common.entities.Rental;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

@Component("restRentalService")
public class RestRentalService extends RestEntityService<Rental>
{
    public RestRentalService(RestTemplate restTemplate)
    {
        super(restTemplate, Rental.class, "rental");
    }
}
