package server.services.base;

import common.entities.BaseEntity;
import common.services.EntityService;
import common.services.behaviours.filter.FilterBehaviour;
import common.services.behaviours.filter.FilterStrategy;
import org.springframework.data.domain.PageRequest;
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
    public Optional<T> getEntity(Long id)
    {
        return this.repository.findById(id);
    }

    @Override
    public T addEntity(T entity)
    {
        if (entity == null) throw new IllegalArgumentException();
        return this.repository.save(entity);
    }

    @Override
    public Iterable<T> getAllEntities(PageRequest request)
    {
        return this.repository.findAll(request);
    }

    @Override
    public Optional<T> deleteEntity(Long id)
    {
        Optional<T> oldEntity = repository.findById(id);
        repository.deleteById(id);
        return oldEntity;
    }

    @Override
    public Optional<T> updateEntity(T updatedEntity)
    {
        Optional<T> oldEntityOptional = repository.findById(updatedEntity.getId());
        oldEntityOptional.ifPresent(oldEntity -> {
            repository.delete(oldEntity);
            repository.save(updatedEntity);
        });
        return oldEntityOptional;
    }

    @Override
    public Iterable<T> filter(FilterStrategy strategy)
    {
        return this.filtering.filter(this.repository.findAll(), strategy);
    }
}
