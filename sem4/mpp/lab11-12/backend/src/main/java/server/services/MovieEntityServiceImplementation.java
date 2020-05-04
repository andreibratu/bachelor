package server.services;

import common.entities.Movie;
import common.services.behaviours.filter.FilterBehaviour;
import common.services.behaviours.sort.SortBehaviour;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Component;
import server.services.base.EntityServiceImplementation;

@Component
public class MovieEntityServiceImplementation extends EntityServiceImplementation<Movie>
{
    @Autowired
    public MovieEntityServiceImplementation(
            FilterBehaviour filtering,
            SortBehaviour sorting,
            JpaRepository<Movie, Long> repository
    )
    {
        super(filtering, sorting, repository);
    }
}
