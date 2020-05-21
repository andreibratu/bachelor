package server.dtos;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Builder;
import lombok.Data;
import server.entities.GenreEnum;
import server.entities.Movie;

@Data
@Builder
public class MovieDTO implements DTO<Movie>
{
    @JsonProperty("id")
    private Long id;

    @JsonProperty("title")
    private String title;

    @JsonProperty("genre")
    private GenreEnum genreEnum;

    @JsonProperty
    private Integer year;
}
