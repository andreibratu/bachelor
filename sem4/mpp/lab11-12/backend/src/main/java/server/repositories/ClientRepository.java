package server.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import server.entities.Client;


@Repository("clientRepository")
public interface ClientRepository extends JpaRepository<Client, Long>
{
}
