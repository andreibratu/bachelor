package server;

import common.services.EntityService;
import common.services.ReportingService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.context.annotation.Bean;
import org.springframework.remoting.httpinvoker.HttpInvokerServiceExporter;
import server.services.ClientEntityServiceImplementation;
import server.services.MovieEntityServiceImplementation;
import server.services.RentalEntityServiceImplementation;
import server.services.ReportingServiceImplementation;

@SpringBootApplication(scanBasePackages = {"common", "server"})
@EntityScan("common.entities")
public class Server
{
    private final MovieEntityServiceImplementation movieService;
    private final ClientEntityServiceImplementation clientService;
    private final RentalEntityServiceImplementation rentalService;
    private final ReportingServiceImplementation reportingService;

    @Autowired
    public Server(MovieEntityServiceImplementation movieService, ClientEntityServiceImplementation clientService,
                  RentalEntityServiceImplementation rentalService, ReportingServiceImplementation reportingService)
    {
        this.movieService = movieService;
        this.clientService = clientService;
        this.rentalService = rentalService;
        this.reportingService = reportingService;
    }

    @Bean(name = "/movie") HttpInvokerServiceExporter movieService()
    {
        HttpInvokerServiceExporter exporter = new HttpInvokerServiceExporter();
        exporter.setService(this.movieService);
        exporter.setServiceInterface(EntityService.class);
        return exporter;
    }

    @Bean(name = "/client") HttpInvokerServiceExporter clientService()
    {
        HttpInvokerServiceExporter exporter = new HttpInvokerServiceExporter();
        exporter.setService(clientService);
        exporter.setServiceInterface(EntityService.class);
        return exporter;
    }

    @Bean(name = "/rental") HttpInvokerServiceExporter rentalService()
    {
        HttpInvokerServiceExporter exporter = new HttpInvokerServiceExporter();
        exporter.setService(rentalService);
        exporter.setServiceInterface(EntityService.class);
        return exporter;
    }

    @Bean(name = "/reporting") HttpInvokerServiceExporter reportingService()
    {
        HttpInvokerServiceExporter exporter = new HttpInvokerServiceExporter();
        exporter.setService(reportingService);
        exporter.setServiceInterface(ReportingService.class);
        return exporter;
    }

    public static void main(String[] args)
    {
        SpringApplication.run(Server.class, args);
    }
}
