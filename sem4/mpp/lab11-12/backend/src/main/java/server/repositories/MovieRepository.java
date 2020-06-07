package server.repositories;

import org.springframework.data.jpa.repository.EntityGraph;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import server.entities.Movie;
import server.repositories.custom.MovieRepositoryCustom;

import javax.transaction.Transactional;
import java.util.List;

@Repository
@Transactional
public interface MovieRepository extends JpaRepository<Movie, Long>, MovieRepositoryCustom
{
    @Query("select distinct m from Movie m")
    @EntityGraph(
            value = "movieWithRentalsAndClient",
            type = EntityGraph.EntityGraphType.LOAD
    )
    List<Movie> findAllMoviesWithRentalsAndClientGraph();

    @Query("select distinct m from Movie m order by m.title")
    @EntityGraph(
            value = "movieWithRentalsAndClient",
            type = EntityGraph.EntityGraphType.LOAD
    )
    List<Movie> findAllMoviesWithRentalsAndClientOrderByTitleGraph();
}
