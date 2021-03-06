package server.controllers;

import common.entities.Movie;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import server.controllers.base.EntityController;
import server.services.MovieEntityServiceImplementation;

@RestController
@RequestMapping("/movie")
public class MovieController extends EntityController<Movie>
{
    @Autowired
    public MovieController(MovieEntityServiceImplementation serviceImplementation)
    {
        super(serviceImplementation);
    }
}
