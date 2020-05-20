package server.services;

import common.entities.Client;
import org.springframework.stereotype.Component;
import server.services.base.EntityServiceImplementation;
import common.services.behaviours.filter.FilterBehaviour;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.beans.factory.annotation.Autowired;

@Component
public class ClientEntityServiceImplementation extends EntityServiceImplementation<Client>
{
    @Autowired
    public ClientEntityServiceImplementation(
            FilterBehaviour filtering,
            JpaRepository<Client, Long> repository
    ) {
        super(filtering, repository);
    }
}
