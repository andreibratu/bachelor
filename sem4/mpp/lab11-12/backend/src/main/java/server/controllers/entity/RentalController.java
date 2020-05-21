package server.controllers.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import server.dtos.RentalDTO;
import server.dtos.Transferable;
import server.entities.Client;
import server.entities.Movie;
import server.entities.Rental;
import server.repositories.ClientRepository;
import server.repositories.MovieRepository;

import java.util.Collection;
import java.util.List;
import java.util.Optional;
import java.util.function.Predicate;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/rentals")
@SuppressWarnings("unused")
public class RentalController
{
    private final ClientRepository clientRepository;
    private final MovieRepository movieRepository;

    @Autowired
    public RentalController(
        ClientRepository clientRepository,
        MovieRepository movieRepository
    ) {
        this.clientRepository = clientRepository;
        this.movieRepository = movieRepository;
    }

    @GetMapping(produces = "application/json")
    public ResponseEntity<?> getAllEntities()
    {
        List<Rental> rentals = this.clientRepository.findAll().stream()
                .map(Client::getRentals)
                .flatMap(Collection::stream)
                .collect(Collectors.toList());
        return ResponseEntity.ok(rentals.stream()
                .map(Transferable::toDTO)
                .collect(Collectors.toList())
        );
    }

    @PutMapping(value = "/{id}", produces = "application/json", consumes = "application/json")
    public ResponseEntity<?> updateEntity(@RequestBody RentalDTO updatedEntity)
    {
        Optional<Client> clientOptional = clientRepository.findById(updatedEntity.getClientId());
        Optional<Movie> movieOptional = movieRepository.findById(updatedEntity.getMovieId());
        if (clientOptional.isEmpty() || movieOptional.isEmpty())
        {
            return ResponseEntity.badRequest().body("Illegal request body");
        }
        Client client = clientOptional.get();
        client.returnMovie(movieOptional.get(), updatedEntity.getEndDate());
        clientRepository.save(client);
        return ResponseEntity.noContent().build();
    }

    @PostMapping(produces = "application/json")
    @ResponseStatus(HttpStatus.CREATED)
    public ResponseEntity<?> createEntity(@RequestBody RentalDTO dto)
    {
        Optional<Client> clientOptional = clientRepository.findById(dto.getClientId());
        Optional<Movie> movieOptional = movieRepository.findById(dto.getMovieId());
        if (clientOptional.isEmpty() || movieOptional.isEmpty())
        {
            return ResponseEntity.badRequest().body("Invalid body");
        }
        Client client = clientOptional.get();
        Movie movie = movieOptional.get();
        client.rentMovie(movie, dto.getStartDate());
        clientRepository.save(client);
        Predicate<Rental> filterPred = (Rental r) -> (
                r.getClient().getId().equals(client.getId()) &&
                r.getMovie().getId().equals(movie.getId())
        );
        Rental rental = client.getRentals().stream().filter(filterPred).findFirst().orElseThrow(RuntimeException::new);
        return ResponseEntity.ok(rental.toDTO());
    }
}
