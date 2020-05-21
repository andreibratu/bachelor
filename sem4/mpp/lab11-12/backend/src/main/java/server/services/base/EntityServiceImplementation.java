package server.services.base;

import lombok.SneakyThrows;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.repository.JpaRepository;
import server.strategies.sort.SortStrategy;

import java.util.Optional;
import java.util.concurrent.atomic.AtomicReference;

public abstract class EntityServiceImplementation<T> implements EntityService<T>
{
    private final JpaRepository<T, Long> repository;

    protected EntityServiceImplementation(JpaRepository<T, Long> repository)
    {
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
    public Iterable<T> getAllEntities(Iterable<SortStrategy> sortStrategies, int page)
    {
        AtomicReference<Sort> sortStrategy = new AtomicReference<>(Sort.unsorted());
        sortStrategies.forEach(strategy -> {
            String attribute = strategy.getAttribute();
            String order = strategy.getOrder();
            if (order.equals("ASC"))
            {
                sortStrategy.set(sortStrategy.get().and(Sort.by(attribute).ascending()));
            }
            else
            {
                sortStrategy.set(sortStrategy.get().and(Sort.by(attribute).descending()));
            }
        });
        PageRequest pageRequest = PageRequest.of(page, 50, sortStrategy.get());
        return this.repository.findAll(pageRequest);
    }

    @Override
    public Optional<T> deleteEntity(Long id)
    {
        Optional<T> oldEntity = repository.findById(id);
        repository.deleteById(id);
        return oldEntity;
    }

    @Override
    @SneakyThrows
    public Optional<T> updateEntity(T updatedEntity)
    {
        Long id = updatedEntity.getClass().getField("id").getLong(updatedEntity);
        Optional<T> oldEntityOptional = repository.findById(id);
        oldEntityOptional.ifPresent(oldEntity -> {
            repository.deleteById(id);
            repository.save(updatedEntity);
        });
        return oldEntityOptional;
    }
}
