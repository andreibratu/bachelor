package server.repositories;

import org.springframework.data.jpa.repository.EntityGraph;
import server.entities.Movie;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import server.entities.Rental;

import java.util.List;

@Repository("movieRepository")
public interface MovieRepository extends JpaRepository<Movie, Long>
{
    @EntityGraph("movie-full-details")
    List<Movie> findAll();

    @EntityGraph("rental-detailed-query")
    List<Rental> getRentals(Integer movieId);
}
