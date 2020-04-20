package common.entities;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.*;

import javax.persistence.Entity;
import java.io.Serializable;

@Data
@Entity
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@EqualsAndHashCode(callSuper = true)
public class Movie extends BaseEntity<Long> implements Serializable
{
    @JsonProperty("title")
    private String title;

    @JsonProperty("genre")
    private GenreEnum genre;

    @JsonProperty("year")
    private Integer year;
}
