package server.controllers.reporting;

import javafx.util.Pair;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import server.dtos.Transferable;
import server.services.reporting.ReportingService;

import java.util.stream.Collectors;

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
    public ResponseEntity<?> getTopClients(@RequestParam int limit)
    {
        return ResponseEntity.ok(reportingService.getTopClients(limit).stream()
                .map(pair -> new Pair<>(pair.getKey().toDTO(), pair.getValue()))
                .collect(Collectors.toList()));
    }

    @GetMapping(value = "/bad-renters", produces = "application/json")
    public ResponseEntity<?> getBadRenters()
    {
        return ResponseEntity.ok(reportingService.getBadRenters().stream()
                .map(Transferable::toDTO)
                .collect(Collectors.toList())
        );
    }

    @GetMapping(value = "/rentals-genre", produces = "application/json")
    public ResponseEntity<?> getRentalsByGenre()
    {
        return ResponseEntity.ok(reportingService.getRentalsByGenre());
    }
}
