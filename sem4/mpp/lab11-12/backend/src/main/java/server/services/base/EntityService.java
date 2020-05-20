package common.services;

import common.entities.BaseEntity;
import common.strategies.sort.SortStrategy;
import org.springframework.data.domain.PageRequest;

import java.util.Optional;

public interface EntityService<T extends BaseEntity<Long>>
{
    T addEntity(T entity);

    Iterable<T> getAllEntities(Iterable<SortStrategy> sortStrategies, int page);

    Optional<T> deleteEntity(Long id);

    Optional<T> updateEntity(T updatedEntity);

    Optional<T> getEntity(Long id);
}
