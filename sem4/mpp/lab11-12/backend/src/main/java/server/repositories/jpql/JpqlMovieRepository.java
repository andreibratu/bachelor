package server.repositories.jpql;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import server.entities.Movie;

import java.util.List;

public interface JpqlMovieRepository extends JpaRepository<Movie, Long>
{
    @Query("SELECT movie_id, name, address, rental.id FROM movie INNER JOIN rental ON movie.movie_id = rental.movie_id")
    List<Movie> findAll();

    List<Movie> fin
}
