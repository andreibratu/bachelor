package server.controllers.base;

import lombok.SneakyThrows;
import common.entities.GenreEnum;
import common.entities.BaseEntity;
import common.services.EntityService;
import org.springframework.data.domain.PageRequest;
import org.springframework.http.HttpStatus;
import org.springframework.data.domain.Sort;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import common.services.behaviours.filter.FilterStrategy;

import java.util.Map;
import java.util.Set;

@SuppressWarnings("unused")
public abstract class EntityController<T extends BaseEntity<Long>>
{
    final EntityService<T> service;

    public EntityController(EntityService<T> service)
    {
        this.service = service;
    }

    @GetMapping(value = "/{id}", produces = "application/json")
    public ResponseEntity<?> getEntity(@PathVariable long id)
    {
        return ResponseEntity.ok(this.service.getEntity(id));
    }

    @PostMapping(produces = "application/json")
    @ResponseStatus(HttpStatus.CREATED)
    public ResponseEntity<?> postEntity(@RequestBody T newEntity)
    {
        return ResponseEntity.ok(this.service.addEntity(newEntity));
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
        return ResponseEntity.ok(this.service.deleteEntity(id));
    }

    @PutMapping(value = "/{id}", produces = "application/json", consumes = "application/json")
    public ResponseEntity<?> updateEntity(@RequestBody T updatedEntity)
    {
        return ResponseEntity.ok(this.service.updateEntity(updatedEntity));
    }

    @SneakyThrows
    @GetMapping(value = "/filter")
    public ResponseEntity<?> filterEntities(@RequestParam Map<String, String> params)
    {
        FilterStrategy strategy;
        if (params.size() != 4 || !params.keySet().equals(Set.of("attribute", "operator", "compareValue", "attrClass")))
        {
            return ResponseEntity.badRequest().body("Invalid filter strategy!");
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
