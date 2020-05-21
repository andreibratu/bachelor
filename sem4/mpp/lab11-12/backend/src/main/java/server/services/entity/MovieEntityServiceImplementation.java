package server.services.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Component;
import server.entities.Movie;
import server.services.base.EntityServiceImplementation;

@Component
public class MovieEntityServiceImplementation extends EntityServiceImplementation<Movie>
{
    @Autowired
    public MovieEntityServiceImplementation(JpaRepository<Movie, Long> repository)
    {
        super(repository);
    }
}
