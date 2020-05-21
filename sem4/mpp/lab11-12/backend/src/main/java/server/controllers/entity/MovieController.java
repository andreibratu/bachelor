package server.controllers.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import server.controllers.base.BaseEntityController;
import server.entities.Movie;
import server.services.entity.MovieEntityServiceImplementation;
import server.validators.MovieValidator;

@RestController
@RequestMapping("/movies")
public class MovieController extends BaseEntityController<Movie>
{
    @Autowired
    public MovieController(
        MovieEntityServiceImplementation serviceImplementation,
        MovieValidator movieValidator
    ) {
        super(serviceImplementation, movieValidator);
    }
}
