package server.entities;

import javax.persistence.Column;
import javax.persistence.Embeddable;
import java.io.Serializable;

@Embeddable
public class RentalKey implements Serializable
{
    @Column(name = "client_id")
    Long clientId;

    @Column(name = "movie_id")
    Long movieId;
}
