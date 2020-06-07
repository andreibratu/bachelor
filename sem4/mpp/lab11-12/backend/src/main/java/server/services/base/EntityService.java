package server.services.base;

import java.util.Optional;

@SuppressWarnings("unused")
public interface EntityService<T>
{
    T addEntity(T entity);

    Iterable<T> getAllEntities(int page);

    Iterable<T> getAllEntitiesSorted(int page);

    Optional<T> deleteEntity(Long id);

    Optional<T> updateEntity(T updatedEntity);

    Optional<T> getEntity(Long id);
}
