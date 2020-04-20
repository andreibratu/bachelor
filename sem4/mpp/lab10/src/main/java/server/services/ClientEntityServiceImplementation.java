package server.services;

import common.entities.Client;
import common.services.behaviours.filter.FilterBehaviour;
import common.services.behaviours.sort.SortBehaviour;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Component;
import server.services.base.EntityServiceImplementation;

@Component
public class ClientEntityServiceImplementation extends EntityServiceImplementation<Client>
{
    @Autowired
    public ClientEntityServiceImplementation(
            FilterBehaviour filtering,
            SortBehaviour sorting,
            JpaRepository<Client, Long> repository
    )
    {
        super(filtering, sorting, repository);
    }
}
