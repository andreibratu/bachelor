package server.controllers.base;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import server.dtos.Transferable;
import server.services.base.EntityService;
import server.validators.Validator;
import server.validators.ValidatorException;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@SuppressWarnings("unused")
public abstract class BaseEntityController<T extends Transferable<T>>
{
    protected final EntityService<T> service;
    private final Validator<T> validator;

    public BaseEntityController(EntityService<T> service, Validator<T> validator)
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
            return ResponseEntity.ok(entity.get().toDTO());
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
            return ResponseEntity.ok(savedEntity.toDTO());
        }
        catch (IllegalArgumentException | ValidatorException e)
        {
            return ResponseEntity.badRequest().body("Illegal request body");
        }
    }

    @GetMapping(produces = "application/json")
    public ResponseEntity<?> getAllEntities(
            @RequestParam(required = false) Integer offset,
            @RequestParam(required = false) List<String> attributes,
            @RequestParam(required = false) List<String> orders
    ) {
        offset = offset != null ? offset : 0;
        if (offset % 50 != 0)
        {
            return ResponseEntity.badRequest().body("Offset should be multiple of 50");
        }
        Iterable<T> response = this.service.getAllEntities(offset / 50);
        return ResponseEntity.ok(
                StreamSupport.stream(response.spliterator(), false)
                    .map(Transferable::toDTO)
                    .collect(Collectors.toList())
        );
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
            return ResponseEntity.ok(oldEntity.get().toDTO());
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
            return ResponseEntity.ok(oldEntity.get().toDTO());
        }
        catch (IllegalArgumentException | NullPointerException | ValidatorException e)
        {
            return ResponseEntity.badRequest().body("Bad request body");
        }
    }
}
