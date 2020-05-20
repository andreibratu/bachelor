package server.services;

import common.entities.*;
import common.services.ReportingService;
import javafx.util.Pair;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Component;

import java.time.LocalDate;
import java.time.Period;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Component
public class ReportingServiceImplementation implements ReportingService
{
    private final JpaRepository<Rental, Long> rentalRepository;

    private final JpaRepository<Client, Long> clientRepository;

    private final JpaRepository<Movie, Long> movieRepository;

    private final static Logger logger = LoggerFactory.getLogger(ReportingServiceImplementation.class);

    @Autowired
    public ReportingServiceImplementation(
            JpaRepository<Client, Long> clientRepository,
            JpaRepository<Movie, Long> movieRepository,
            JpaRepository<Rental, Long> rentalRepository
    )
    {
        this.rentalRepository = rentalRepository;
        this.clientRepository = clientRepository;
        this.movieRepository = movieRepository;
    }

    public List<Pair<Client, Integer>> getTopClients(int limit)
    {
        Iterable<Rental> rentals = rentalRepository.findAll();
        Iterable<Long> clientIds = clientRepository.findAll().stream()
                .map(BaseEntity::getId).collect(Collectors.toList());

        // Count rentals
        Map<Long, Integer> countRentals = new HashMap<>();
        for(Long id: clientIds)
        {
            int clientCount = Math.toIntExact(StreamSupport.stream(rentals.spliterator(), false)
                    .filter(rental -> rental.getClientID().equals(id))
                    .count());
            countRentals.put(id, clientCount);
        }

        // Sort
        List<Map.Entry<Long, Integer>> entries = new ArrayList<>(countRentals.entrySet());
        entries.sort(Map.Entry.comparingByValue(Collections.reverseOrder()));

        // Return top `limit` pairs
        List<Pair<Client, Integer>> topClients = entries.stream().map(entry -> new Pair<>(
                clientRepository.findById(entry.getKey()).orElseThrow(RuntimeException::new),
                entry.getValue()))
                .limit(limit)
                .collect(Collectors.toList());
        logger.trace("Top clients: " + topClients.toString());
        return topClients;
    }

    public List<Client> getBadRenters()
    {
        Set<Long> badRenterIds = rentalRepository.findAll().stream()
                .filter(rental -> {
                    LocalDate startDate = rental.getStartDate();
                    LocalDate endDate = (rental.getEndDate() == null) ? LocalDate.now() : rental.getEndDate();

                    Period diff = Period.between(startDate, endDate);
                    return diff.getMonths() >= 1;
                })
                .map(Rental::getClientID)
                .collect(Collectors.toSet());
        return clientRepository.findAll().stream()
                .filter(client -> badRenterIds.contains(client.getId()))
                .collect(Collectors.toList());
    }

    public List<Pair<GenreEnum, Integer>> getRentalsByGenre()
    {
        Map<GenreEnum, Integer> countRentals = new HashMap<>();
        rentalRepository.findAll().forEach(rental -> {
            GenreEnum genre = movieRepository.findById(rental.getMovieID()).orElseThrow(RuntimeException::new).getGenre();
            countRentals.computeIfPresent(genre, (k, v) -> v+1);
            countRentals.putIfAbsent(genre, 1);
        });
        return countRentals.entrySet().stream()
                .map(entry -> new Pair<>(entry.getKey(), entry.getValue()))
                .collect(Collectors.toList());
    }
}
