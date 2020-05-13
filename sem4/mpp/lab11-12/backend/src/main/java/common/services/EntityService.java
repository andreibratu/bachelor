package common.services;

import common.entities.BaseEntity;
import org.springframework.data.domain.PageRequest;
import common.services.behaviours.filter.FilterStrategy;

public interface EntityService<T extends BaseEntity<Long>>
{
    T addEntity(T entity);

    Iterable<T> getAllEntities(PageRequest request);

    T deleteEntity(Long id);

    T updateEntity(T updatedEntity);

    T getEntity(Long id);

    Iterable<T> filter(FilterStrategy strategy);
}
