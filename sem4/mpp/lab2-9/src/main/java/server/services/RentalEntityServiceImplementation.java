package server.services;

import common.entities.Rental;
import common.services.behaviours.filter.FilterBehaviour;
import common.services.behaviours.sort.SortBehaviour;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Component;
import server.services.base.EntityServiceImplementation;

@Component
public class RentalEntityServiceImplementation extends EntityServiceImplementation<Rental>
{
    @Autowired
    public RentalEntityServiceImplementation(
            FilterBehaviour filtering,
            SortBehaviour sorting,
            JpaRepository<Rental, Long> repository
    )
    {
        super(filtering, sorting, repository);
    }
}