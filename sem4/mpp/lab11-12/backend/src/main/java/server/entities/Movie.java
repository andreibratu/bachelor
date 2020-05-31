package server.entities;

import lombok.Data;
import lombok.NoArgsConstructor;
import server.dtos.DTO;
import server.dtos.MovieDTO;
import server.dtos.Transferable;

import javax.persistence.*;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

@Data
@Entity
@NoArgsConstructor
@SuppressWarnings("JpaDataSourceORMInspection")
@NamedEntityGraph(
        name = "movie-full-details",
        attributeNodes = {
                @NamedAttributeNode("id"),
                @NamedAttributeNode("title"),
                @NamedAttributeNode("genre"),
                @NamedAttributeNode("year"),
                @NamedAttributeNode(value = "rentals", subgraph = "rental-basic")
        },
        subgraphs = {
                @NamedSubgraph(
                        name = "rental-basic",
                        attributeNodes = {
                                @NamedAttributeNode("id")
                        }
                )
        }
)
public class Movie implements Serializable, Transferable<Movie>
{
    @Id
    @GeneratedValue
    @Column(name = "movie_id")
    private Long id;

    private String title;

    private GenreEnum genre;

    private Integer year;

    @OneToMany(mappedBy = "movie", cascade = CascadeType.ALL, fetch = FetchType.LAZY)
    private Set<Rental> rentals = new HashSet<>();

    @Override
    public DTO<Movie> toDTO()
    {
        return MovieDTO.builder()
                .id(id)
                .genreEnum(genre)
                .year(year)
                .title(title)
                .build();
    }
}
