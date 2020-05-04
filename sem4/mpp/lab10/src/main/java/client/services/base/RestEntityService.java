package client.services.base;

import common.entities.BaseEntity;
import common.services.EntityService;
import common.services.behaviours.filter.FilterStrategy;
import common.services.behaviours.sort.SortStrategy;
import javafx.util.Pair;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.util.UriComponentsBuilder;

public abstract class RestEntityService<T extends BaseEntity<Long>> implements EntityService<T>
{
    @Value("http://localhost:8080")
    private String SERVER_URL;

    private Class<T> type;

    private String branch;

    private final RestTemplate restTemplate;

    @Autowired
    public RestEntityService(RestTemplate restTemplate, Class<T> type, String branch)
    {
        this.branch = branch;
        this.type = type;
        this.restTemplate = restTemplate;
    }

    @Override
    public T addEntity(T entity)
    {
        System.out.println(entity.toString());
        System.out.println(type.toString());
        String url = SERVER_URL + "/" + branch;
        T result = null;
        try
        {
            result = this.restTemplate.postForObject(url, entity, type);
        }
        catch (Exception e)
        {
            System.out.println(e.toString());
        }
        return result;
    }

    @Override
    @SuppressWarnings("unchecked")
    public Iterable<T> getAllEntities(SortStrategy strategy)
    {
        UriComponentsBuilder builder = UriComponentsBuilder.fromHttpUrl(SERVER_URL + "/" + branch);
        if (strategy != null)
        {
            for(Pair<String, SortStrategy.Direction> pair : strategy.getFields())
            {
                builder.queryParam(pair.getKey(), pair.getValue().toString());
            }
        }
        Iterable<T> result = null;
        try
        {
            result = restTemplate.getForObject(builder.toUriString(), Iterable.class);
        }
        catch(Exception e)
        {
            System.out.println(e.toString());
        }
//        System.out.println(result);
        return result;
    }

    @Override
    public T deleteEntity(Long id)
    {
        String url = SERVER_URL + "/" + branch + "/" + id;
        T oldEntity = this.restTemplate.getForObject(url, type);
        this.restTemplate.delete(url);
        return oldEntity;
    }

    @Override
    public T updateEntity(T updatedEntity)
    {
        String url = SERVER_URL + "/" + branch + "/" + updatedEntity.getId();
        this.restTemplate.put(url, updatedEntity);
        return this.restTemplate.getForObject(url, type);
    }

    @Override
    public T getEntity(Long id)
    {
        String url = SERVER_URL + "/" + branch + "/" + id;
        return this.restTemplate.getForObject(url, type);
    }

    @Override
    @SuppressWarnings("unchecked")
    public Iterable<T> filter(FilterStrategy strategy)
    {
        UriComponentsBuilder builder = UriComponentsBuilder.fromHttpUrl(SERVER_URL + "/" + branch + "/filter");
        builder.queryParam("attribute", strategy.getAttribute());
        builder.queryParam("operator", strategy.getOperator());
        builder.queryParam("compareValue", strategy.getCompareValue());
        builder.queryParam("attrClass", strategy.getCompareValue().getClass());
        return this.restTemplate.getForObject(builder.toUriString(), Iterable.class);
    }
}
