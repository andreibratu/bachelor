package server.services.base;

import common.entities.BaseEntity;
import common.services.EntityService;
import common.services.behaviours.filter.FilterBehaviour;
import common.services.behaviours.filter.FilterStrategy;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public abstract class EntityServiceImplementation<T extends BaseEntity<Long>> implements EntityService<T>
{
    private final FilterBehaviour filtering;

    private final JpaRepository<T, Long> repository;

    public EntityServiceImplementation(
        FilterBehaviour filtering,
        JpaRepository<T, Long> repository
    ) {
        this.filtering = filtering;
        this.repository = repository;
    }

    @Override
    public T getEntity(Long id)
    {
        return this.repository.findById(id).orElseThrow(RuntimeException::new);
    }

    @Override
    public T addEntity(T entity)
    {
        T result = this.repository.save(entity);
        System.out.println(this.repository.count());
        return result;
    }

    @Override
    public Iterable<T> getAllEntities(PageRequest request)
    {
        return this.repository.findAll(request);
    }

    @Override
    public T deleteEntity(Long id)
    {
        Optional<T> oldEntity = repository.findById(id);
        repository.deleteById(id);
        return oldEntity.orElseThrow(RuntimeException::new);
    }

    @Override
    public T updateEntity(T updatedEntity)
    {
        T oldEntity = repository.findById(updatedEntity.getId()).orElseThrow(RuntimeException::new);
        repository.delete(oldEntity);
        repository.save(updatedEntity);
        return oldEntity;
    }

    @Override
    public Iterable<T> filter(FilterStrategy strategy)
    {
        return this.filtering.filter(this.repository.findAll(), strategy);
    }
}
