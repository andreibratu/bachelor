package client.services;

import client.services.base.RestEntityService;
import common.entities.Movie;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

@Component("restMovieService")
public class RestMovieService extends RestEntityService<Movie>
{
    public RestMovieService(RestTemplate restTemplate) {
        super(restTemplate, Movie.class, "movie");
    }
}
