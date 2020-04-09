package common.services;

import common.services.behaviours.filter.FilterStrategy;
import common.services.behaviours.sort.SortStrategy;
import common.entities.BaseEntity;

public interface EntityService<T extends BaseEntity<Long>>
{
    T addEntity(T entity);

    Iterable<T> getAllEntities(SortStrategy strategy);

    T deleteEntity(Long id);

    T updateEntity(T updatedEntity);

    T getEntity(Long id);

    Iterable<T> filter(FilterStrategy strategy);
}
