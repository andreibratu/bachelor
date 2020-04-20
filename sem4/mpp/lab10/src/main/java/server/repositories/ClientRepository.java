package server.repositories;

import common.entities.Client;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;


@Repository("clientRepository")
public interface ClientRepository extends JpaRepository<Client, Long> { }
