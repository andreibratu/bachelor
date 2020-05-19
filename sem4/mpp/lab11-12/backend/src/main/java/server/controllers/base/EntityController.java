package server.controllers.base;

import lombok.SneakyThrows;
import common.entities.GenreEnum;
import common.entities.BaseEntity;
import common.services.EntityService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.http.HttpStatus;
import org.springframework.data.domain.Sort;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import common.services.behaviours.filter.FilterStrategy;
import server.validators.Validator;
import server.validators.ValidatorException;

import java.util.Map;
import java.util.Optional;
import java.util.Set;

@SuppressWarnings("unused")
public abstract class EntityController<T extends BaseEntity<Long>>
{
    private final EntityService<T> service;
    private final Validator<T> validator;

    @Autowired
    public EntityController(EntityService<T> service, Validator<T> validator)
    {
        this.service = service;
        this.validator = validator;
    }

    @GetMapping(value = "/{id}", produces = "application/json")
    public ResponseEntity<?> getEntity(@PathVariable long id)
    {
        try
        {
            Optional<T> entity = service.getEntity(id);
            if (entity.isEmpty())
            {
                return ResponseEntity.badRequest().body("Illegal id");
            }
            return ResponseEntity.ok(entity.get());
        }
        catch (IllegalArgumentException e)
        {
            return ResponseEntity.badRequest().body(e.getMessage());
        }
    }

    @PostMapping(produces = "application/json")
    @ResponseStatus(HttpStatus.CREATED)
    public ResponseEntity<?> createEntity(@RequestBody T newEntity)
    {
        try
        {
            validator.validate(newEntity);
            T savedEntity = service.addEntity(newEntity);
            return ResponseEntity.ok(savedEntity);
        }
        catch (IllegalArgumentException | ValidatorException e)
        {
            return ResponseEntity.badRequest().body("Illegal request body");
        }
    }

    @GetMapping(produces = "application/json")
    public ResponseEntity<?> getAllEntities(@RequestParam Map<String,String> params)
    {
        int offset = Integer.parseInt(params.getOrDefault("offset", "0"));
        if (offset % 50 != 0)
        {
            return ResponseEntity.badRequest().body("Offset should be multiple of 50");
        }
        params.remove("offset");
        Sort sortStrategy = Sort.unsorted();
        if (params.size() != 0)
        {
            for(Map.Entry<String, String> entry : params.entrySet())
            {
                String k = entry.getKey();
                String v = entry.getValue();
                if (v.equals("ASC"))
                {
                    sortStrategy.and(Sort.by(k).ascending());
                }
                else
                {
                    sortStrategy.and(Sort.by(k).descending());
                }
            }
        }
        Iterable<T> response = this.service.getAllEntities(PageRequest.of(offset / 50, 50, sortStrategy));
        return ResponseEntity.ok(response);
    }

    @DeleteMapping(value = "/{id}", produces = "application/json")
    public ResponseEntity<?> deleteEntity(@PathVariable long id)
    {
        try
        {
            Optional<T> oldEntity = this.service.deleteEntity(id);
            if (oldEntity.isEmpty())
            {
                return ResponseEntity.badRequest().body("Illegal id");
            }
            return ResponseEntity.ok(oldEntity.get());
        }
        catch (IllegalArgumentException e)
        {
            return ResponseEntity.badRequest().body("Null id");
        }
    }

    @PutMapping(value = "/{id}", produces = "application/json", consumes = "application/json")
    public ResponseEntity<?> updateEntity(@RequestBody T updatedEntity)
    {
        try
        {
            validator.validate(updatedEntity);
            Optional<T> oldEntity = service.updateEntity(updatedEntity);
            if (oldEntity.isEmpty())
            {
                return ResponseEntity.badRequest().body("Illegal request body");
            }
            return ResponseEntity.ok(oldEntity.get());
        }
        catch (IllegalArgumentException | NullPointerException | ValidatorException e)
        {
            return ResponseEntity.badRequest().body("Bad request body");
        }
    }

    @SneakyThrows
    @GetMapping(value = "/filter")
    public ResponseEntity<?> filterEntities(@RequestParam Map<String, String> params)
    {
        FilterStrategy strategy;
        if (params.size() != 4 || !params.keySet().equals(Set.of("attribute", "operator", "compareValue", "attrClass")))
        {
            return ResponseEntity.badRequest().body("Invalid filter object in request body");
        }
        else
        {
            Class<?> attrClass = Class.forName(params.get("attrClass"));
            Object compValue = null;
            if (attrClass == Integer.class)
            {
                compValue = Integer.parseInt(params.get("compareValue"));
            }
            if (attrClass == String.class)
            {
                compValue = params.get("attrClass");
            }
            if (attrClass == Float.class || attrClass == Double.class)
            {
                compValue = Double.parseDouble(params.get("compareValue"));
            }
            if (attrClass == GenreEnum.class)
            {
                compValue = GenreEnum.valueOf(params.get("compareValue"));
            }
            strategy = new FilterStrategy(
                params.get("attribute"),
                params.get("operator"),
                compValue
            );
        }
        return ResponseEntity.ok(this.service.filter(strategy));
    }
}
