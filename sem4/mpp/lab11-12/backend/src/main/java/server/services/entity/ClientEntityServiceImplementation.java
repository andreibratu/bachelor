package server.services.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Component;
import server.entities.Client;
import server.services.base.EntityServiceImplementation;

@Component
public class ClientEntityServiceImplementation extends EntityServiceImplementation<Client>
{
    @Autowired
    public ClientEntityServiceImplementation(JpaRepository<Client, Long> repository) {
        super(repository);
    }
}
