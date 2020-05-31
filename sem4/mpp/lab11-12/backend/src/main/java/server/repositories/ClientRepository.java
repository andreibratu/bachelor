package server.repositories;

import org.springframework.data.jpa.repository.EntityGraph;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import server.entities.Client;
import server.entities.Rental;

import java.util.List;


@Repository("clientRepository")
public interface ClientRepository extends JpaRepository<Client, Long>
{
    @EntityGraph("rental-detailed-query")
    List<Rental> getRentals(Integer clientId);

    @EntityGraph("client-full-details")
    List<Client> findAll();
}
