package client.services;

import client.services.base.RestEntityService;
import common.entities.Client;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

@Component("restClientService")
public class RestClientService extends RestEntityService<Client>
{
    public RestClientService(RestTemplate restTemplate)
    {
        super(restTemplate, Client.class, "client");
    }
}
