package server.repositories;

import org.springframework.data.jpa.repository.EntityGraph;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import server.entities.Client;
import server.repositories.custom.ClientRepositoryCustom;

import javax.transaction.Transactional;
import java.util.List;

@Repository
@Transactional
public interface ClientRepository extends JpaRepository<Client, Long>, ClientRepositoryCustom
{

    @Query("select distinct c from Client c")
    @EntityGraph(
            value = "clientWithRentalsAndMovie",
            type = EntityGraph.EntityGraphType.LOAD)
    List<Client> findAllWithRentalsAndMovieGraph();

    @Query("select distinct c from Client c order by c.name")
    @EntityGraph(value = "clientWithRentalsAndMovie", type =
            EntityGraph.EntityGraphType.LOAD)
    List<Client> findAllWithRentalsAndMovieOrderByNameGraph();
}

