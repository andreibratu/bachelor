package client.services;

import common.entities.Client;
import common.entities.GenreEnum;
import common.services.ReportingService;
import javafx.util.Pair;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.util.UriComponentsBuilder;

import java.util.List;

@Component("restReportingService")
public class RestReportingService implements ReportingService
{
    @Value("http://localhost:8080")
    private String SERVER_URL;

    private final RestTemplate restTemplate;

    @Autowired
    public RestReportingService(RestTemplate restTemplate)
    {
        this.restTemplate = restTemplate;
    }

    @Override
    @SuppressWarnings("unchecked")
    public List<Pair<Client, Integer>> getTopClients(int limit)
    {
        String url = SERVER_URL + "/top-clients/" + limit;
        UriComponentsBuilder builder = UriComponentsBuilder.fromHttpUrl(url)
                .queryParam("url", url);
        return restTemplate.getForObject(builder.toUriString(), List.class);
    }

    @Override
    @SuppressWarnings("unchecked")
    public List<Client> getBadRenters()
    {
        String url = SERVER_URL + "/bad-renters";
        return restTemplate.getForObject(url, List.class);
    }

    @Override
    @SuppressWarnings("unchecked")
    public List<Pair<GenreEnum, Integer>> getRentalsByGenre()
    {
        String url = SERVER_URL + "/rentals-genre";
        return restTemplate.getForObject(url, List.class);
    }
}
