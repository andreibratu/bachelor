package server.entities;

import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;
import server.dtos.ClientDTO;
import server.dtos.Transferable;

import javax.persistence.*;
import java.io.Serializable;
import java.time.LocalDate;
import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;

@Data
@Entity
@Builder
@NoArgsConstructor
@ToString(callSuper = true)
@SuppressWarnings("JpaDataSourceORMInspection")
@NamedEntityGraph(
        name = "client-full-details",
        attributeNodes = {
                @NamedAttributeNode("id"),
                @NamedAttributeNode("name"),
                @NamedAttributeNode("address"),
                @NamedAttributeNode(value = "rentals", subgraph = "rental-basic")
        },
        subgraphs = {
                @NamedSubgraph(
                        name = "rental-basic",
                        attributeNodes = {
                            @NamedAttributeNode("id"),
                        }
                )
        }
)
public class Client implements Serializable, Transferable<Client>
{
    @Id
    @GeneratedValue
    @Column(name = "client_id")
    private Long id;

    private String name;

    private String address;

    @OneToMany(mappedBy = "client", cascade = CascadeType.ALL, fetch = FetchType.LAZY)
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
        movie.getRentals().add(rental);
    }

    public void returnMovie(Movie movie, LocalDate endDate)
    {
        Rental rental = rentals.stream()
            .filter(r -> r.getMovie().getId().equals(movie.getId()))
            .findFirst().orElseThrow(RuntimeException::new);
        rental.setEndDate(endDate);
        movie.setRentals(movie.getRentals().stream()
                .filter(rental1 -> rental1.getId().equals(rental.getId()))
                .map(rental1 -> rental)
                .collect(Collectors.toSet())
        );
    }

    public ClientDTO toDTO()
    {
        return ClientDTO.builder()
                .address(address)
                .name(name)
                .id(id)
                .build();
    }
}
