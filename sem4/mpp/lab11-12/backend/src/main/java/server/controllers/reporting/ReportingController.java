package server.controllers;

import common.entities.Client;
import common.entities.GenreEnum;
import common.services.ReportingService;
import javafx.util.Pair;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SuppressWarnings("unused")
@RestController("/reports")
public class ReportingController
{
    private final ReportingService reportingService;

    @Autowired
    public ReportingController(ReportingService reportingService)
    {
        this.reportingService = reportingService;
    }

    @GetMapping(value = "/top-clients", produces = "application/json")
    public Iterable<Pair<Client, Integer>> getTopClients(@RequestParam int limit)
    {
        return reportingService.getTopClients(limit);
    }

    @GetMapping(value = "/bad-renters", produces = "application/json")
    public Iterable<Client> getBadRenters()
    {
        return reportingService.getBadRenters();
    }

    @GetMapping(value = "/rentals-genre", produces = "application/json")
    public Iterable<Pair<GenreEnum, Integer>> getRentalsByGenre()
    {
        return reportingService.getRentalsByGenre();
    }
}
