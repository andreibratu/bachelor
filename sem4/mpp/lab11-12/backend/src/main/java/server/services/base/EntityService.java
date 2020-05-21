package server.services.base;

import server.strategies.sort.SortStrategy;

import java.util.Optional;

public interface EntityService<T>
{
    T addEntity(T entity);

    Iterable<T> getAllEntities(Iterable<SortStrategy> sortStrategies, int page);

    Optional<T> deleteEntity(Long id);

    Optional<T> updateEntity(T updatedEntity);

    Optional<T> getEntity(Long id);
}
