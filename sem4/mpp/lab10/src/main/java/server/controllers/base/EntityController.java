package server.controllers.base;

import common.entities.BaseEntity;
import common.entities.GenreEnum;
import common.services.EntityService;
import common.services.behaviours.filter.FilterStrategy;
import common.services.behaviours.sort.SortStrategy;
import lombok.SneakyThrows;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

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
        SortStrategy strategy = null;
        if (params.size() != 0)
        {
            strategy = new SortStrategy();
            for(Map.Entry<String, String> entry : params.entrySet())
            {
                String k = entry.getKey();
                String v = entry.getValue();
                SortStrategy.Direction direction = (v.equals("ASC")) ?
                        SortStrategy.Direction.ASC :
                        SortStrategy.Direction.DESC;
                strategy.add(k, direction);
            }
        }
        Iterable<T> response = this.service.getAllEntities(strategy);
        System.out.println("SERVER " + response.toString());
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
