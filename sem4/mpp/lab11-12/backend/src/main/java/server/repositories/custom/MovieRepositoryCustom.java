package server.repositories.custom;

import server.entities.Movie;

import java.util.List;

public interface MovieRepositoryCustom
{
    List<Movie> findAllWithRentalsAndClientJPQL();

    List<Movie> findAllWithRentalsAndClientCriteriaAPI();

    List<Movie> findAllWithRentalsAndClientSQL();

    List<Movie> findAllWithRentalsSortedJPQL();

    List<Movie> findAllWithRentalsSortedCriteriaAPI();

    List<Movie> findAllWithRentalsSortedSQL();
}
