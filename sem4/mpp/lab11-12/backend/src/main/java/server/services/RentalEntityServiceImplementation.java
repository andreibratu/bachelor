package server.services;

import common.entities.Rental;
import org.springframework.stereotype.Component;
import server.services.base.EntityServiceImplementation;
import common.services.behaviours.filter.FilterBehaviour;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.beans.factory.annotation.Autowired;

@Component
public class RentalEntityServiceImplementation extends EntityServiceImplementation<Rental>
{
    @Autowired
    public RentalEntityServiceImplementation(
            FilterBehaviour filtering,
            JpaRepository<Rental, Long> repository
    ) {
        super(filtering, repository);
    }
}