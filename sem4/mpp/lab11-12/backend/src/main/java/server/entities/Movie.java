package server.entities;

import lombok.*;
import server.dtos.DTO;
import server.dtos.MovieDTO;
import server.dtos.Transferable;

import javax.persistence.*;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

@Data
@Entity
@Builder
@NoArgsConstructor
@AllArgsConstructor
@EqualsAndHashCode(callSuper = true)
@NamedEntityGraphs({
        @NamedEntityGraph(name = "movieWithRentals",
                attributeNodes = @NamedAttributeNode(value = "rentals")),
        @NamedEntityGraph(name = "movieWithRentalsAndClient",
                attributeNodes = @NamedAttributeNode(value = "rentals", subgraph = "rentalWithClient"),
                subgraphs = @NamedSubgraph(name = "rentalWithClient",
                        attributeNodes = @NamedAttributeNode(value = "client")))
})
public class Movie extends BaseEntity<Long> implements Serializable, Transferable<Movie> {
    private String title;

    private GenreEnum genre;

    private Integer year;

    public Movie(String title, GenreEnum genre, Integer year)
    {
        this.title = title;
        this.genre = genre;
        this.year = year;
    }

    @OneToMany(mappedBy = "movie", cascade = CascadeType.ALL, fetch = FetchType.LAZY)
    @Builder.Default
    private Set<Rental> rentals = new HashSet<>();

    @Override
    public DTO<Movie> toDTO()
    {
        return MovieDTO.builder()
                .id(this.getId())
                .genreEnum(genre)
                .year(year)
                .title(title)
                .build();
    }
}
