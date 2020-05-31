package server.repositories.jpql;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import server.entities.Client;
import server.entities.Rental;

import java.util.List;

@Repository("jpqlClientRepository")
@SuppressWarnings("JpaQlInspection")
public interface JpqlClientRepository extends JpaRepository<Client, Long>
{
    @Query("SELECT * FROM rentals WHERE cliend_id = ?1")
    List<Rental> getRentals(Integer clientId);

    @Query("SELECT client_id, name, address, rental.id FROM client INNER JOIN rental ON client.client_id = rental.client_id")
    List<Client> findAll();
}
