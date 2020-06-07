package server.entities;

import lombok.*;
import org.springframework.data.jpa.repository.Modifying;
import server.dtos.ClientDTO;
import server.dtos.Transferable;

import javax.persistence.*;
import javax.transaction.Transactional;
import java.time.LocalDate;
import java.util.HashSet;
import java.util.Set;
import java.util.function.Predicate;
import java.util.stream.Collectors;

@Data
@Entity
@Builder
@NoArgsConstructor
@AllArgsConstructor
@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
@SuppressWarnings("JpaDataSourceORMInspection")
@NamedEntityGraphs({
        @NamedEntityGraph(name = "clientWithRentals",
                attributeNodes = @NamedAttributeNode(value = "rentals")),
        @NamedEntityGraph(name = "clientWithRentalsAndMovie",
                attributeNodes = @NamedAttributeNode(value = "rentals", subgraph = "rentalWithMovie"),
                subgraphs = @NamedSubgraph(name = "rentalWithMovie",
                        attributeNodes = @NamedAttributeNode(value = "movie")))
})
public class Client extends BaseEntity<Long> implements Transferable<Client>
{
    @Column(name = "name", nullable = false)
    private String name;

    @Column(name = "address", nullable = false)
    private String address;

    @OneToMany(
            mappedBy = "client",
            cascade = CascadeType.ALL,
            fetch = FetchType.LAZY,
            orphanRemoval = true
    )
    private Set<Rental> rentals;

    public Set<Movie> getRentedMovies()
    {
        rentals = rentals == null ? new HashSet<>() : rentals;
        return rentals.stream()
                .map(Rental::getMovie)
                .collect(Collectors.toUnmodifiableSet());
    }

    public void rentMovie(Movie movie, LocalDate startDate)
    {
        Rental rental = new Rental();
        rental.setClient(this);
        rental.setMovie(movie);
        rental.setStartDate(startDate);
        rentals.add(rental);
    }

    @Modifying
    @Transactional
    public void returnMovie(Movie movie, LocalDate endDate)
    {
        Predicate<Rental> findRentalPredicate = r -> r.getMovie().getId().equals(movie.getId());
        Rental updatedRental = rentals.stream()
            .filter(findRentalPredicate)
            .findFirst().orElseThrow(RuntimeException::new);
        updatedRental.setEndDate(endDate);
        movie.setRentals(movie.getRentals().stream()
                .map(r -> r.getMovie().getId().equals(movie.getId()) ? updatedRental : r)
                .collect(Collectors.toSet())
        );
    }

    public ClientDTO toDTO()
    {
        return ClientDTO.builder()
                .address(address)
                .name(name)
                .id(this.getId())
                .build();
    }
}
