package server.repositories;

import common.entities.Rental;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository("rentalRepository")
public interface RentalRepository extends JpaRepository<Rental, Long> { }
