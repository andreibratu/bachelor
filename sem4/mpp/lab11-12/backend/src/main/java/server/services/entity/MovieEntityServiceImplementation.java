package server.services;

import common.entities.Movie;
import org.springframework.stereotype.Component;
import server.services.base.EntityServiceImplementation;
import common.services.behaviours.filter.FilterBehaviour;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.beans.factory.annotation.Autowired;

@Component
public class MovieEntityServiceImplementation extends EntityServiceImplementation<Movie>
{
    @Autowired
    public MovieEntityServiceImplementation(
            FilterBehaviour filtering,
            JpaRepository<Movie, Long> repository
    ) {
        super(filtering, repository);
    }
}
