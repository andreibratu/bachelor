package server.controllers;

import common.entities.Rental;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import server.controllers.base.EntityController;
import server.services.RentalEntityServiceImplementation;

@RestController
@RequestMapping("/rentals")
public class RentalController extends EntityController<Rental>
{
    public RentalController(RentalEntityServiceImplementation rentalEntityServiceImplementation)
    {
        super(rentalEntityServiceImplementation);
    }
}
