package server.services.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;
import server.entities.Movie;
import server.repositories.MovieRepository;
import server.services.base.EntityService;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Optional;

@Component
@SuppressWarnings("unchecked")
public class MovieEntityServiceImplementation implements EntityService<Movie>
{
    private final MovieRepository movieRepository;

    @Value("${repository.movie.getAll}")
    private String getAllMethodName;

    @Value("${repository.movie.getAllSorted}")
    private String getAllSortedMethodName;

    @Autowired
    public MovieEntityServiceImplementation(MovieRepository movieRepository)
    {
        this.movieRepository = movieRepository;
    }

    @Override
    public Movie addEntity(Movie entity)
    {
        if (entity == null) throw new IllegalArgumentException();
        return this.movieRepository.save(entity);
    }

    @Override
    public Iterable<Movie> getAllEntities(int page)
    {
        try
        {
            Method getAllMethod = MovieRepository.class.getMethod(getAllMethodName);
            return (Iterable<Movie>) getAllMethod.invoke(this.movieRepository);
        }
        catch (NoSuchMethodException |
                IllegalAccessException |
                InvocationTargetException e)
        {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Iterable<Movie> getAllEntitiesSorted(int page)
    {
        try
        {
            Method getAllMethod = MovieRepository.class.getMethod(getAllSortedMethodName);
            return (Iterable<Movie>) getAllMethod.invoke(this.movieRepository);
        } catch (NoSuchMethodException |
                IllegalAccessException |
                InvocationTargetException e)
        {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Optional<Movie> deleteEntity(Long id)
    {
        Optional<Movie> found = movieRepository.findById(id);
        movieRepository.deleteById(id);
        return found;
    }

    @Override
    public Optional<Movie> updateEntity(Movie updatedEntity)
    {
        Optional<Movie> old = movieRepository.findById(updatedEntity.getId());
        movieRepository.deleteById(updatedEntity.getId());
        movieRepository.save(updatedEntity);
        return old;
    }

    @Override
    public Optional<Movie> getEntity(Long id)
    {
        return movieRepository.findById(id);
    }
}
