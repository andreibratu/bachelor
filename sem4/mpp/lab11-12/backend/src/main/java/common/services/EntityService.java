package common.services;

import common.entities.BaseEntity;
import org.springframework.data.domain.PageRequest;
import common.services.behaviours.filter.FilterStrategy;

import java.util.Optional;

public interface EntityService<T extends BaseEntity<Long>>
{
    T addEntity(T entity);

    Iterable<T> getAllEntities(PageRequest request);

    Optional<T> deleteEntity(Long id);

    Optional<T> updateEntity(T updatedEntity);

    Optional<T> getEntity(Long id);

    Iterable<T> filter(FilterStrategy strategy);
}
