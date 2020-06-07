package server.repositories.custom;

import server.entities.Client;

import java.util.List;

public interface ClientRepositoryCustom
{
    List<Client> findAllWithRentalsAndMovieJPQL();

    List<Client> findAllWithRentalsAndMovieCriteriaAPI();

    List<Client> findAllWithRentalsAndMovieSQL();

    List<Client> findAllWithRentalsSortedJPQL();

    List<Client> findAllWithRentalsSortedCriteriaAPI();

    List<Client> findAllWithRentalsSortedSQL();
}